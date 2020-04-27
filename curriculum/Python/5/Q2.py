from PIL import Image
import numpy as np

def bond(n,bnd=0):      #用于限定像素不得超过图像边界
    if n<0:
        return 0
    elif n>bnd:
        return bnd
    else:
        return n

def gaussian_blur(pixels, radius):
    p=pixels
    r=radius
    tar=p.copy()       #图像矩阵的副本，用于接收转换后的矩阵
    row=len(p)        #矩阵（即图像像素）的行数
    col=len(p[0])     #矩阵（即图像像素）的列数
    for x in range(row):
        for y in range(col):
            #（x,y)像素的值=原图矩阵（a:b,c:d)的切片范围（非边缘情况a=x-r,b=x+r+1,c=y-r,d=y+r+1)内所有像素值的和（按列求和），减去像素（x,y）的值，再除以该范围的像素总数(b-a)*(d-c)-1
            tar[x,y]=(p[bond(x-r,row):bond(x+r+1,row),bond(y-r,col):bond(y+r+1,col)].sum(axis=0).sum(axis=0)-p[x,y])/((bond(x+r+1,row)-bond(x-r,row))*(bond(y+r+1,col)-bond(y-r,col))-1)
    return tar

def main():
    pxm=np.array(Image.open("./5\\Q1\\bird.jpg"))
    im=gaussian_blur(pxm,3)
    img=Image.fromarray(im)
    img.show()

main()
