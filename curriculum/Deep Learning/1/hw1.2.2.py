import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

num_observations=100
x=np.linspace(-3,3,num_observations)
Y=np.sin(x)+np.random.uniform(-0.5,0.5,num_observations)

# 初始化参数
w1 = tf.Variable(0.)
w2 = tf.Variable(0.)
w3 = tf.Variable(0.)
b = tf.Variable(0.)
# 构造回归模型
y = w1*x + w2*x**2 + w3*x**3 + b

# 定义损失函数
MSE = tf.reduce_mean(tf.square(Y-y))
# 定义一个梯度下降法来进行训练的优化器
optimizer = tf.train.GradientDescentOptimizer(0.001)
# 定义一个最小化代价函数
train = optimizer.minimize(MSE)

# 初始化变量
init = tf.global_variables_initializer()

ww1=1.
ww2=1.
ww3=1.
bb=1.

with tf.Session() as sess:
    sess.run(init)
    for step in range(3000):
        sess.run(train)
    print(sess.run([w1, w2, w3, b]),sess.run(MSE))
    ww1=sess.run(w1)
    ww2=sess.run(w2)
    ww3=sess.run(w3)
    bb=sess.run(b)

plt.figure(figsize=(5,5))           #画布大小
plt.plot(x,Y,'ro',color="blue")           #绘制散点图
plt.plot(x,ww1*x+ww2*x**2+ww3*x**3+bb,color="red")           #绘制曲线
plt.legend()
plt.show()