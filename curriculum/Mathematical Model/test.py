import numpy as np
data=np.loadtxt('D:\\data.txt')
std_data=data.copy()
row=len(data)
col=len(data[0])
for i in range(row):
    for j in range(col):
        std_data[i,j]=(data[i,j]-min(data[:,j]))/(max(data[:,j]-min(data[:,j])))
dis=np.ones((row,row))*9
dis_out=np.zeros((row,row))
for i in range(row):
    for j in range(i):
        dis[i,j]=sum(list(map(abs,std_data[i]-std_data[j])))
        dis_out[i,j]=dis[i,j]
pos=np.where(dis==np.min(dis))
tar_row,tar_col=pos[0],pos[1]
#print(data)
#print(std_data)
#print(dis)
print('('+str(tar_row[0])+','+str(tar_col[0])+')')
#print(tar_col[0])
#np.savetxt('D:\\std_data.txt',std_datax)
#np.savetxt('D:\\dis.txt',dis_out,fmt='%.3f')
#np.savetxt('D:\\dis_ori.txt',dis,fmt='%.3f')
'''f=open('D:\\dis_out.txt','w+')
for i in range(row):
    for j in range(row):
        f.write(str(round(dis_out[i,j],2)))
        f.write('\t')
    f.write('\n')'''