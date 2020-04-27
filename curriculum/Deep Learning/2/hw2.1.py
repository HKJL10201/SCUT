import input_data
import tensorflow as tf
import matplotlib.pyplot as plt

mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# 定义变量
x = tf.placeholder("float", [None, 784])
# 样本实际值
y_ = tf.placeholder("float", [None, 10])
# 各层的weight
w1=tf.Variable(tf.random_normal([784, 256]))
w2=tf.Variable(tf.random_normal([256, 256]))
w=tf.Variable(tf.random_normal([256, 10]))
# 各层的bias
b1=tf.Variable(tf.random_normal([256]))
b2=tf.Variable(tf.random_normal([256]))
b=tf.Variable(tf.random_normal([10]))
# 定义各层神经网络
layer1 = tf.matmul(x, w1) + b1
layer2 = tf.matmul(layer1, w2) + b2
layer3 = tf.matmul(layer2, w) + b
# 输出层
y = tf.nn.softmax(layer3)
# 交叉熵损失
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=layer3, labels=y_))
# 构建Adam优化算法优化器
train_step = tf.train.AdamOptimizer(0.01).minimize(cross_entropy)
# 定义精确度
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
# 初始化变量
init = tf.initialize_all_variables()

xx=range(500)
acc=[]
ls=[]

with tf.Session() as sess:
    # 运行初始化程序
    sess.run(init)
    for step in range(1, 501):
        # 获取样本
        batch_xs, batch_ys = mnist.train.next_batch(128)
        # 运行训练
        sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
        # 记录准确率
        acc.append(sess.run(accuracy, feed_dict={x: batch_xs, y_: batch_ys}))
        # 记录损失
        ls.append(sess.run(cross_entropy, feed_dict={x: batch_xs, y_: batch_ys}))
    print('最终精度&损失：')
    print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))
    print(sess.run(cross_entropy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))

plt.figure()
plt.plot(xx,acc,color="blue")
plt.figure()
plt.plot(xx,ls,color="red")
plt.legend()
plt.show()
