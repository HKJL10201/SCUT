import input_data
import tensorflow as tf
import matplotlib.pyplot as plt

mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# 定义变量
x = tf.placeholder("float", [None, 784])
W = tf.Variable(tf.zeros([784,10]))
b = tf.Variable(tf.zeros([10]))
# 建立回归模型
y = tf.nn.softmax(tf.matmul(x,W) + b)
# 样本实际值
y_ = tf.placeholder("float", [None,10])
# 用交叉熵表示损失
cross_entropy = -tf.reduce_sum(y_*tf.log(y))
# 构建梯度下降优化器
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
# 初始化变量
init = tf.initialize_all_variables()

correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

xx=range(1000)
yy=[]
loss=[]

sess = tf.Session()
sess.run(init)
for i in range(1000):
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
    # 记录准确率
    yy.append(sess.run(accuracy, feed_dict={x: batch_xs, y_: batch_ys}))
    # 记录损失
    loss.append(sess.run(cross_entropy, feed_dict={x: batch_xs, y_: batch_ys}))

print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))
print(sess.run(cross_entropy, feed_dict={x: batch_xs, y_: batch_ys}))

sess.close()

plt.figure()
plt.plot(xx,yy,color="blue")
plt.figure()
plt.plot(xx,loss,color="red")
plt.legend()
plt.show()
