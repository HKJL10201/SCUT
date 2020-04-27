import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

##构建标准循环神经网络进行预测任务 
#数据生成：使用函数𝑦 = 𝑠𝑖𝑛(0.06𝑥) + 𝑈(−0.1,0.1),𝑥 = 1,2,⋯,600
num=600                     #600个样本点
X=np.linspace(1,num,num)    #𝑥 = 1,2,⋯,600
Y=np.sin(0.06*X)+np.random.uniform(-0.1,0.1)
#训练集＆测试集样本
divide=0.7      #分界点
y_train=Y[0:int(num*divide)]    #训练集样本点：前面600 × 0.7 = 420个样本点 
y_test=Y[int(num*divide):]      #测试集样本点：后面600 × 0.3 = 180个样本点 

#----------------------------------------------------------------------
batch_size = 1    #批处理大小
time_step = 7   #输入维度大小
hidden_dim = 32 #隐藏神经元数量
output_dim = 1  #输出维度

# 获取数据，每次获取7个样本
inputs = tf.placeholder(tf.float32,shape=[time_step])
#将输入数据转换成RNN输入格式[1,7,1]
x = tf.reshape(inputs,shape=[batch_size,time_step,output_dim])
#正确标签的占位符
labels = tf.placeholder(tf.float32,shape=[batch_size])
#定义RNN细胞
cell = tf.nn.rnn_cell.BasicLSTMCell(num_units=hidden_dim)
#构建 LSTM 循环神经网络
output1, state1 = tf.nn.dynamic_rnn(cell, x, dtype=tf.float32)
output2, state2 = tf.nn.dynamic_rnn(cell, x, dtype=tf.float32)
output3, state3 = tf.nn.dynamic_rnn(cell, x, dtype=tf.float32)

# 构建输出层
#dropout层
dropout1 = tf.layers.dropout(inputs=state1[1],rate=0.4)
dropout2 = tf.layers.dropout(inputs=state2[1],rate=0.4)
dropout3 = tf.layers.dropout(inputs=state3[1],rate=0.4)
#全连接层
full_connected1 = tf.layers.dense(dropout1, 1)
full_connected2 = tf.layers.dense(dropout2, 1)
full_connected3 = tf.layers.dense(dropout3, 1)

#定义损失
MSE1 = tf.reduce_sum(tf.square(full_connected1-labels))
MSE2 = tf.reduce_sum(tf.square(full_connected2-labels))
MSE3 = tf.reduce_sum(tf.square(full_connected3-labels))
#随机梯度下降算法
train_step1 = tf.train.GradientDescentOptimizer(0.01).minimize(MSE1)
#动量梯度下降算法
train_step2 = tf.train.MomentumOptimizer(0.01,0.1).minimize(MSE2)
# Adam 优化算法
train_step3 = tf.train.AdamOptimizer().minimize(MSE3)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    loss = [[],[],[]]
    predict = [[],[],[]]
    for i in range(int(num*divide) - time_step):    #在训练集上进行训练
        _,sat = sess.run([train_step1, MSE1], feed_dict={inputs: y_train[i:i+time_step], labels: [y_train[i+time_step]]})
        loss[0].append(sat)
        _,sat = sess.run([train_step2, MSE2], feed_dict={inputs: y_train[i:i+time_step], labels: [y_train[i+time_step]]})
        loss[1].append(sat)
        _,sat = sess.run([train_step3, MSE3], feed_dict={inputs: y_train[i:i+time_step], labels: [y_train[i+time_step]]})
        loss[2].append(sat)
    for i in range(int(num*(1-divide)) - time_step):    #在测试集上进行测试
        _, sat = sess.run([train_step1, full_connected1], feed_dict={inputs: y_test[i:i+time_step], labels: [y_test[i + time_step]]})
        predict[0].append(sat[0][0])
        _, sat = sess.run([train_step2, full_connected2], feed_dict={inputs: y_test[i:i+time_step], labels: [y_test[i + time_step]]})
        predict[1].append(sat[0][0])
        _, sat = sess.run([train_step3, full_connected3], feed_dict={inputs: y_test[i:i+time_step], labels: [y_test[i + time_step]]})
        predict[2].append(sat[0][0])

#训练误差随迭代次数的变化图
plt.subplot(321)
plt.plot(X[0:413],loss[0])
#及测试集的预测值和真实值的对比图
plt.subplot(322)
plt.plot(X[427:],y_test[time_step:],'.')
plt.plot(X[427:],predict[0])
#训练误差随迭代次数的变化图
plt.subplot(323)
plt.plot(X[0:413],loss[1])
#及测试集的预测值和真实值的对比图
plt.subplot(324)
plt.plot(X[427:],y_test[time_step:],'.')
plt.plot(X[427:],predict[1])
#训练误差随迭代次数的变化图
plt.subplot(325)
plt.plot(X[0:413],loss[2])
#及测试集的预测值和真实值的对比图
plt.subplot(326)
plt.plot(X[427:],y_test[time_step:],'.')
plt.plot(X[427:],predict[2])
plt.show()