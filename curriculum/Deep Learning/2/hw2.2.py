import warnings
warnings.filterwarnings('ignore')
import input_data
import tensorflow as tf
import matplotlib.pyplot as plt

mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# 定义变量
x = tf.placeholder(tf.float32)
y_ = tf.placeholder(tf.float32)

x_images = tf.reshape(x, [-1, 28, 28, 1])

# 卷积层1
#5*5的卷积核，1个平面->32个平面（每个平面抽取32个特征） 
conv1_Kernel = tf.Variable(tf.truncated_normal([5, 5, 1, 32], stddev=0.1))
conv1_biases = tf.Variable(tf.constant(0.1, shape=[32]))
#第一次卷积之后变为 28*28*32
conv1 = tf.nn.relu(tf.nn.conv2d(x_images, conv1_Kernel, strides=[1, 1, 1, 1], padding='SAME') + conv1_biases)
# 池化层1
#第一次池化之后变为 14*14*32
conv1_pooling = tf.nn.max_pool(conv1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

# 卷积层2
#5*5的卷积核，32个平面->64个平面（每个平面抽取2个特征）
conv2_Kernel = tf.Variable(tf.truncated_normal([5, 5, 32, 64], stddev=0.1))
conv2_biases = tf.Variable(tf.constant(0.1, shape=[64]))
#第二次卷积之后变为 14*14*64
conv2 = tf.nn.relu(tf.nn.conv2d(conv1_pooling, conv2_Kernel, strides=[1, 1, 1, 1], padding='SAME') + conv2_biases)
# 池化层2
#第二次池化之后变为 7*7*64
conv2_pooling = tf.nn.max_pool(conv2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

#全连接层
#7*7*64的图像展平为3136维输入
cnet1_input = tf.reshape(conv2_pooling, [-1, 3136])
#参数w和b，隐含单元数为 1024 
cnet1_Weight = tf.Variable(tf.truncated_normal([3136, 1024], stddev=0.1))
cnet1_biases = tf.Variable(tf.constant(0.1, shape=[1024]))
#全连接层输出
cnet1 = tf.nn.relu(tf.add(tf.matmul(cnet1_input, cnet1_Weight), cnet1_biases))

#dropout层
dropout=tf.layers.dropout(inputs=cnet1,rate=0.25)

#输出层
#参数w和b
cnet2_Weight = tf.Variable(tf.truncated_normal([1024, 10], stddev=0.1))
cnet2_biases = tf.Variable(tf.constant(0.1, shape=[10]))
#输出
y = tf.nn.softmax(tf.add(tf.matmul(dropout, cnet2_Weight), cnet2_biases))

#loss and train
loss = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), 1))
train_step = tf.train.AdamOptimizer(0.0001).minimize(loss)

# 定义精确度
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

init = tf.global_variables_initializer()

xx=range(501)


sess = tf.Session()
sess.run(init)
acc=[]
ls=[]
for i in range(501):
    train_images, train_labels = mnist.train.next_batch(200)
    sess.run(train_step, feed_dict={x:train_images, y_:train_labels})
    # 记录准确率
    acc.append(sess.run(accuracy, feed_dict={x:train_images, y_:train_labels}))
    # 记录损失
    ls.append(sess.run(loss, feed_dict={x:train_images, y_:train_labels}))
    if i % 100 == 0:
        test_images, test_labels = mnist.test.next_batch(2000)
        train_accuracy = sess.run(accuracy, feed_dict={x:train_images, y_:train_labels})
        test_accuracy = sess.run(accuracy, feed_dict={x:test_images, y_:test_labels})
        print('step:%d train accuracy:%.4f test accuracy:%.4f' %(i, train_accuracy, test_accuracy))
test_images, test_labels = mnist.test.next_batch(2000)
test_accuracy = sess.run(accuracy, feed_dict={x:test_images, y_:test_labels})
test_loss = sess.run(loss, feed_dict={x:test_images, y_:test_labels})
print('最终分类精度：%.4f 最终分类损失：%.4f' %(test_accuracy,test_loss))

sess.close()

plt.figure()
plt.plot(xx,acc,color="blue")
plt.figure()
plt.plot(xx,ls,color="red")
plt.legend()
plt.show()
