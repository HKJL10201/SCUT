#1
import numpy as np
#2
a=[4,5,6]
print('a的类型：'+str(type(a)))
print('a的各维度大小：'+str(np.shape(a)))
print('a的第一个元素：'+str(a[0]))
#3
b=[[4,5,6], [1,2,3]]
print('b的各维度大小：'+str(np.shape(b)))
print('b[0,0]: '+str(b[0][0])+'\tb[0,1]: '+str(b[0][1])+'\tb[1,1]: '+str(b[1][1]))
#4
c=np.zeros((3,3))
d=np.ones((4,5))
e=np.eye(4)
#5
f=np.arange(12)
print(f)
print('f的各维度大小：'+str(np.shape(f)))
f=np.reshape(f,(3,4))
print(f)
print('f的各维度大小：'+str(np.shape(f)))
print('f第二行：'+str(f[1,:]))
print('f最后两列：\n'+str(f[:,2:4]))
print('f第三行最后一个元素：'+str(f[2][-1]))

