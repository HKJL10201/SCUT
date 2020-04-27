from PIL import Image

def get_gray(r,b,g,alpha=256):          #获取并返回像素点的灰度值
    gray=int(0.2126*r+0.7152*g+0.0722*b)
    return gray

path="./4\\Q3\\"        #图像文件路径
im=Image.open(path+"bird.jpg")
a=Image.open(path+"1.jpg")
b=Image.open(path+"2.jpg")
c=Image.open(path+"3.jpg")
d=Image.open(path+"4.jpg")
e=Image.open(path+"5.jpg")
f=Image.open(path+"6.jpg")

tar=[0,a,b,c,d,e,f]     #图像1~6列表

size=552    #原图像尺寸
pix=16      #图像1~6的尺寸（简称小图）

for y in range(int(size/pix)+1):
    for x in range(int(size/pix)+1):
        pic=im.crop([x*pix,y*pix,x*pix+pix,y*pix+pix])        #以小图尺寸为单位对原图进行遍历
        gray=0
        for i in range(pix):           #遍历原图在当前单位面积的每个像素点
            for j in range(pix):
                gray+=get_gray(*pic.getpixel((j,i)))        #统计每个单位面积的灰度值
        gray/=pix*pix           #计算每个单位面积的平均灰度
        num=6-int(gray/(255/6))         #按灰度大小分为等级1~6
        im.paste(tar[num],(x*pix,y*pix))        #将当前单位面积的原图替换为相应灰度等级的小图
        #print(num,end=" ")         #以矩阵形式输出每个单位面积的灰度等级
    #print()
#im.save(path+"converted_bird.jpg","jpeg")       #保存转换后的图像
im.show()
