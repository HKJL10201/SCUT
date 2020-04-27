import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

##构建标准循环神经网络进行预测任务 
#数据生成：使用函数𝑦 = 𝑠𝑖𝑛(0.06𝑥) + 𝑈(−0.1,0.1),𝑥 = 1,2,⋯,600
num=600                     #600个样本点
X=np.linspace(1,num,num)    #𝑥 = 1,2,⋯,600
Y=np.sin(0.06*X)+np.random.uniform(-0.1,0.1)
#训练集&测试集样本
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
cell = tf.nn.rnn_cell.BasicRNNCell(num_units=hidden_dim)
#构建标准循环神经网络
output, state = tf.nn.dynamic_rnn(cell, x, dtype=tf.float32)

# 构建输出层
#全连接层
full_connected = tf.layers.dense(state, 1)
#定义损失
MSE = tf.reduce_sum(tf.square(full_connected-labels))
#梯度下降优化
optimizer = tf.train.GradientDescentOptimizer(0.01)
train_step = optimizer.minimize(MSE)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    loss = []       #用于储存训练集上的训练损失
    predict = []    #用于储存测试集上的预测数据
    for i in range(int(num*divide) - time_step):    #在训练集上进行训练
        _,sat = sess.run([train_step, MSE], feed_dict={inputs: y_train[i:i+time_step], labels: [y_train[i+time_step]]})
        loss.append(sat)
    for i in range(int(num*(1-divide)) - time_step):    #在测试集上进行测试
        _, sat = sess.run([train_step, full_connected], feed_dict={inputs: y_test[i:i+time_step], labels: [y_test[i + time_step]]})
        predict.append(sat[0][0])

#可视化样本：
plt.subplot(311)
plt.plot(X,Y,'.',color='blue')
#训练误差随迭代次数的变化图
plt.subplot(312)
plt.plot(X[0:413],loss)
#及测试集的预测值和真实值的对比图
plt.subplot(313)
plt.plot(X[427:],y_test[time_step:],'.')
plt.plot(X[427:],predict)
plt.show()