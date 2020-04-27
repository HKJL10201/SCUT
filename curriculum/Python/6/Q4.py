import random

def get_pi():
    """
    :rtype: float
    """
    n=1000000       #随机撒点的个数
    rn=0        #圆内点计数
    sm=0        #总点数计数
    while sm<n:
        x=random.random()       #随机取x、y坐标（范围为0到1）
        y=random.random()
        sm+=1
        if x**2+y**2<=1:        #第一象限内半径为1的1/4圆及其外切正方形
            rn+=1           #点落在圆内则+1
    return 4*rn/sm      #返回值为1/4圆的面积×4

print(get_pi())
