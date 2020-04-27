import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

num_observations=100
x=np.linspace(-3,3,num_observations)
Y=np.sin(x)+np.random.uniform(-0.5,0.5,num_observations)

# 初始化参数b,w
b = tf.Variable(0.)
w = tf.Variable(0.)
# 构造一个线性模型
y = w*x+b

# 定义损失函数
MSE = tf.reduce_mean(tf.square(Y-y))
# 定义一个梯度下降法来进行训练的优化器
optimizer = tf.train.GradientDescentOptimizer(0.001)
# 定义一个最小化代价函数
train = optimizer.minimize(MSE)

# 初始化变量
init = tf.global_variables_initializer()

w2=1.
b2=1.

with tf.Session() as sess:
    sess.run(init)      # 运行初始化变量
    for step in range(3000):    #训练3000次
        sess.run(train)
    #print(sess.run([w, b]),sess.run(MSE))
    w2=sess.run(w)
    b2=sess.run(b)
    print('w:'+str(w2)+' b:'+str(b2)+' 损失：'+str(sess.run(MSE)))

plt.figure(figsize=(5,5))           #画布大小
plt.plot(x,Y,'ro',color="blue")           #绘制散点图
plt.plot(x,w2*x+b2,color="red")           #绘制曲线
plt.legend()
plt.show()