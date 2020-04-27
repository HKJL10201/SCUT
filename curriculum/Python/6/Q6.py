import numpy as np
import matplotlib.pyplot as plt

def plot_heart():
    t=np.linspace(-1,1,50000)       #参数t的范围在-1到1
    x=np.sin(t)*np.cos(t)*np.log(abs(t))    #x=sint·cost·ln|t|
    y=(abs(t)**0.5)*np.cos(t)               #y=√(|t|)·cost
    plt.figure(figsize=(5,5))           #画布大小
    plt.plot(x,y,color="red")           #绘制曲线
    plt.title("Cardioid")
    plt.legend()
    plt.show()

plot_heart()