import os
from PIL import Image

def batch_resize(dir, size):
    """
    :type dir: string, 目录路径
    :type size: tuple
    """
    #几乎所有图片格式：
    pics=["bmp","BMP","jpg","JPG","jpeg","JPEG","png","PNG","tif","TIF","gif","GIF","pcx","tga","exif","fpx","svg","psd","cdr","pcd","dxf","ufo","eps","ai","raw","WMF","webp"]
    files=os.listdir(dir)   #提取目录下的文件列表
    for fle in files:       #遍历文件
        if fle.split('.')[-1] in pics:      #检测文件是否为图片
            pic=os.path.join(dir,fle)       #创建访问图片的路径
            img=Image.open(pic)         #打开图片
            img=img.resize(size)        #缩放图片
            rst=os.path.join(dir,"result")      #子目录result
            if not os.path.exists(rst):
                os.makedirs(rst)                #若不存在该目录则创建新目录
            pic=os.path.join(rst,fle)       #图片的保存路径
            img.save(pic)           #保存图片

#测试样例：
#batch_resize("D:/Temp",(16,16))
