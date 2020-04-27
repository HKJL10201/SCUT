import numpy as np
import random

#数据集
dataset=[[[0, 0], [0]], 
         [[0, 1], [1]], 
         [[1, 0], [1]], 
         [[1, 1], [0]]] 

# 定义变量
#输入
X=[[0,0],[0,1],[1,0],[1,1]]
#真实值
y_=[0,1,1,0]
# 定义参数：随机生成w1~w12,b1,b2
w=np.random.rand(12)
b=np.random.rand(2)

# h1=x1*w1+x2*w2+x1*x2*w3+b1
def h1_net(x):
    return x[0]*w[0]+x[1]*w[1]+x[0]*x[1]*w[2]+b[0]

# h2=x1*w4+x2*w5+x1*x2*w6+b1
def h2_net(x):
    return x[0]*w[3]+x[1]*w[4]+x[0]*x[1]*w[5]+b[0]

# h3=x1*w7+x2*w8+x1*x2*w9+b1
def h3_net(x):
    return x[0]*w[6]+x[1]*w[7]+x[0]*x[1]*w[8]+b[0]

#sigmoid函数 
def G(net):
    return 1/(1+np.math.exp(-net))

def h1(x):
    return G(h1_net(x))

def h2(x):
    return G(h2_net(x))

def h3(x):
    return G(h3_net(x))

# out=h1*w10+h2*w11+h3*w12+b2
def out_net(x):
    return h1(x)*w[9]+h2(x)*w[10]+h3(x)*w[11]+b[1]

def out(x):
    return G(out_net(x))

def Er(i):
    x=X[i]
    y=out(x)
    return 0.5*(y_[i]-y)**2

def g(a):   #Sigmoid的导数
    return G(a)*(1-G(a))

def Optimizer(a,i):
    x=X[i]      #训练输入x为数据集X中某一组输入
    y=out(x)    #y即是out，算得的预测值
    d=y-y_[i]   #E对y的导数
    Ry=g(y)     #y对out_net的导数
    h1x=h1(x)
    h2x=h2(x)
    h3x=h3(x)
    #w12=w6-a*(y-y_)*R(out_net)*h3(x)
    w[11]-=a*d*Ry*h3x
    #w11=w6-a*(y-y_)*R(out_net)*h2(x)
    w[10]-=a*d*Ry*h2x
    #w10=w5-a*(y-y_)*R(out_net)*h1(x)
    w[9]-=a*d*Ry*h1x
    #w9=w4-a*(y-y_)*R(out_net)*w12*R(h3(x))*x2*x1
    w[8]-=a*d*Ry*w[11]*g(h3x)
    #w8=w4-a*(y-y_)*R(out_net)*w12*R(h3(x))*x2
    w[7]-=a*d*Ry*w[11]*g(h3x)
    #w7=w3-a*(y-y_)*R(out_net)*w12*R(h3(x))*x1
    w[6]-=a*d*Ry*w[11]*g(h3x)
    #w6=w4-a*(y-y_)*R(out_net)*w11*R(h2(x))*x2*x1
    w[5]-=a*d*Ry*w[10]*g(h2x)
    #w5=w4-a*(y-y_)*R(out_net)*w11*R(h2(x))*x2
    w[4]-=a*d*Ry*w[10]*g(h2x)
    #w4=w3-a*(y-y_)*R(out_net)*w11*R(h2(x))*x1
    w[3]-=a*d*Ry*w[10]*g(h2x)
    #w3=w2-a*(y-y_)*R(out_net)*w10*R(h1(x))*x2*x1
    w[2]-=a*d*Ry*w[9]*g(h1x)
    #w2=w2-a*(y-y_)*R(out_net)*w10*R(h1(x))*x2
    w[1]-=a*d*Ry*w[9]*g(h1x)
    #w1=w1-a*(y-y_)*R(out_net)*w10*R(h1(x))*x1
    w[0]-=a*d*Ry*w[9]*g(h1x)
    #b2=b2-a*(y-y_)*R(out_net)*1
    b[1]-=a*d*Ry
    #b1=b1-a*(y-y_)*R(out_net)*(w10*R(h1(x))*1+w11*R(h2(x))*1+w12*R(h3(x))*1)
    b[0]-=a*d*Ry*(w[9]*g(h1(x))+w[10]*g(h2(x))+w[11]*g(h3(x)))

#总损失
loss=0
for i in range(10000):
    j=random.randint(0,3)   #从样本中随机抽取一组x
    Optimizer(0.01,j)   #优化
    loss+=Er(j)         #记录损失
    if((i+1)%100==0):
        print(loss/(i+1))   #输出平均损失

print(w)
print(b)
#输出最终测试误差
final=0
for i in range(4):
    final+=Er(i)
print('最终误差：')
print(final/4)