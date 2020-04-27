from PIL import Image
import numpy as np
import time

def bond(n,bnd=0):      #用于限定像素不得超过图像边界
    if n<0:
        return 0
    elif n>bnd:
        return bnd
    else:
        return n

pxm=np.array(Image.open("./5\\Q1\\bird.jpg"))

def gaussian_blur(pixels, radius):
    t1=time.time()
    tar=pixels.copy()       #图像矩阵的副本，用于接收转换后的矩阵
    for x in range(len(pixels)):        #矩阵（即图像像素）的行数
        for y in range(len(pixels[0])):     #矩阵（即图像像素）的列数
            tar[x,y]=(pixels[bond(x-radius,len(pixels)):bond(x+radius+1,len(pixels)),bond(y-radius,len(pixels[0])):bond(y+radius+1,len(pixels[0]))].sum(axis=0).sum(axis=0)-pixels[x,y])/((bond(x+radius+1,len(pixels))-bond(x-radius,len(pixels)))*(bond(y+radius+1,len(pixels[0]))-bond(y-radius,len(pixels[0])))-1)
    t2=time.time()    
    print("函数执行时间："+str(t2-t1)+"秒")
    return tar

im=gaussian_blur(pxm,10)
img=Image.fromarray(im)
img.show()
