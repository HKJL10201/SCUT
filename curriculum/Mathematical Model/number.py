import numpy as np
dis=np.loadtxt('D:\\dis.txt')
while True:
    n=float(input())
    pos=np.where(dis==n)
    tar_row=pos[0]
    tar_col=pos[1]
    print('('+str(tar_row[0])+','+str(tar_col[0])+')')
    #print(pos)