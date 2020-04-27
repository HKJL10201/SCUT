from __future__ import division, print_function, absolute_import

import matplotlib.pyplot as plt
import numpy as np
import input_data
import tensorflow as tf

# 导入MNIST数据集
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# A custom initialization (see Xavier Glorot init)
def glorot_init(shape):
    return tf.random_normal(shape=shape, stddev=1. / tf.sqrt(shape[0] / 2.))

# 训练参数
num_steps = 20000
batch_size = 128
learning_rate = 0.0002

# 结构参数
In_img = 784  # 输入图片维度：784（28 × 28）
In_nois = 100 # 输入噪声维度：100 
G_hidden = 256  #生成器隐藏层维度： 256 

# 模型参数
G_weight1 = tf.Variable(glorot_init([In_nois, G_hidden]))
G_weight2 = tf.Variable(glorot_init([G_hidden, In_img]))
G_bias1 = tf.Variable(tf.zeros([G_hidden]))
G_bias2 = tf.Variable(tf.zeros([In_img]))

# 生成器
def Generator(x):
    hidden = tf.add(tf.matmul(x, G_weight1), G_bias1)
    hidden = tf.nn.relu(hidden)     #使用ReLU激活函数
    out = tf.add(tf.matmul(hidden, G_weight2), G_bias2)
    out = tf.nn.sigmoid(out)        #使用Sigmoid激活函数
    return out

# 结构参数
In_img = 784  # 输入图片维度：784（28 × 28）
D_hidden = 256  #判别器隐藏层维度： 256 
D_out = 1   #判别器输出层维度： 1

# 模型参数
D_weight1 = tf.Variable(glorot_init([In_img, D_hidden]))
D_weight2 = tf.Variable(glorot_init([D_hidden, D_out]))
D_bias1 = tf.Variable(tf.zeros([D_hidden]))
D_bias2 = tf.Variable(tf.zeros([D_out]))

# 判别网络
def Discriminator(x):
    hidden = tf.add(tf.matmul(x, D_weight1), D_bias1)
    hidden = tf.nn.relu(hidden)     #使用ReLU激活函数
    out = tf.add(tf.matmul(hidden, D_weight2), D_bias2)
    out = tf.nn.sigmoid(out)        #使用Sigmoid激活函数
    return out

##############创建网络
# 网络输入
G_input = tf.placeholder(tf.float32, shape=[None, In_nois])
D_input = tf.placeholder(tf.float32, shape=[None, In_img])

# 创建生成网络
G_sample = Generator(G_input)

# 创建两个判别网络 (一个来自噪声输入, 一个来自生成的样本)
D_real = Discriminator(D_input)
D_fake = Discriminator(G_sample)

# 定义损失
G_loss = -tf.reduce_mean(tf.log(D_fake))
D_loss = -tf.reduce_mean(tf.log(D_real) + tf.log(1. - D_fake))

# 定义优化器
optimizer_G = tf.train.AdamOptimizer(learning_rate)
optimizer_D = tf.train.AdamOptimizer(learning_rate)

# 训练每个优化器的变量
# 生成网络变量
G_vars = [G_weight1, G_weight2, G_bias1, G_bias2]
# 判别网络变量
D_vars = [D_weight1, D_weight2, D_bias1, D_bias2]

# 最小化损失函数
train_G = optimizer_G.minimize(G_loss, var_list=G_vars)
train_D = optimizer_D.minimize(D_loss, var_list=D_vars)

# 初始化变量
init = tf.global_variables_initializer()

# 开始训练
with tf.Session() as sess:
    sess.run(init)

    for i in range(1, num_steps+1):
        # 准备数据
        batch_x, _ = mnist.train.next_batch(batch_size)
        # 产生噪声给生成网络
        z = np.random.uniform(-1., 1., size=[batch_size, In_nois])

        # 训练
        feed_dict = {D_input: batch_x, G_input: z}
        _, _, gl, dl = sess.run([train_G, train_D, G_loss, D_loss],
                                feed_dict=feed_dict)
        if i % 1000 == 0 or i == 1:
            print('Step %i: Generator Loss: %f, Discriminator Loss: %f' % (i, gl, dl))
            if i==num_steps:
                print('最终损失: 生成器损失: %f, 判别器损失: %f' % (gl, dl))


    # 使用生成器网络从噪声生成图像
    f, a = plt.subplots(2, 5, figsize=(5, 2))
    for i in range(5):
        # 噪声输入.
        z = np.random.uniform(-1., 1., size=[4, In_nois])
        g = sess.run([G_sample], feed_dict={G_input: z})
        g = np.reshape(g, newshape=(4, 28, 28, 1))
        # 将原来黑底白字转换成白底黑字，更好的显示
        #g = -1 * (g - 1)
        for j in range(2):
            # 从噪音中生成图像。 扩展到3个通道，用于matplotlib
            img = np.reshape(np.repeat(g[j][:, :, np.newaxis], 3, axis=2),newshape=(28, 28, 3))
            a[j][i].axis('off')
            a[j][i].imshow(img)

    plt.show()