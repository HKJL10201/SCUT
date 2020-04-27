from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

def image_hist(img):
    ar=img[:,:,0].flatten()         #red数组
    ag=img[:,:,1].flatten()         #green数组
    ab=img[:,:,2].flatten()         #blue数组
    agry=0.2126*ar+0.7152*ag+0.0722*ab      #灰度数组
    
    plt.subplot(221)
    plt.xticks([0,50,100,150,200,250])
    plt.hist(agry, bins=256, normed=1,facecolor='black',edgecolor='black')
    plt.subplot(222)
    plt.xticks([0,50,100,150,200,250])
    plt.hist(ar, bins=256, normed=1,facecolor='r',edgecolor='r')
    plt.subplot(223)
    plt.xticks([0,50,100,150,200,250])
    plt.hist(ag, bins=256, normed=1, facecolor='g',edgecolor='g')
    plt.subplot(224)
    plt.xticks([0,50,100,150,200,250])
    plt.hist(ab, bins=256, normed=1, facecolor='b',edgecolor='b')
    
    plt.show()

img=np.array(Image.open("./5\\Q3\\scut.jpg"))
image_hist(img)