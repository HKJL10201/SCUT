import numpy as np

'''data=np.loadtxt('D:/Math/data_matrix.txt')
std_data=data.copy()
row=len(data)
col=len(data[0])
for i in range(row):
    for j in range(col):
        std_data[i,j]=(data[i,j]-min(data[i]))/(max(data[i]-min(data[i])))
np.savetxt('D:/Math/data_std.txt',std_data,fmt='%.3f')'''

'''f=open('D:/Math/data_std.txt','rt')
w=open('D:/Math/data_font.txt','w+')
for line in f:
    line=line.replace(' ','\n')
    w.write(line)
f.close()
w.close()'''

'''f=open('D:/Math/data_font.txt','rt')
w=open('D:/Math/data_plot.txt','w+')
index=[8,9,10,11,12,1,2,3,4,5]
i=0
for line in f:
    line=line.replace('\n','\t'+str(index[i])+'\n')
    w.write(line)
    i=(i+1)%len(index)
f.close()
w.close()'''

'''data=np.loadtxt('D:/Math/data_std.txt')
f=open('D:/Math/data_mean.txt','w+')
index=[8,9,10,11,12,1,2,3,4,5]
mean=np.mean(data,axis=0)
for i in range(len(mean)):
    f.write(str(mean[i])+'\t'+str(index[i])+'\n')
f.close()'''

'''data=np.loadtxt('D:/Math/data_std.txt')
f=open('D:/Math/data_stdmean.txt','w+')
index=[8,9,10,11,12,1,2,3,4,5]
mean=np.mean(data,axis=0)
mean_std=list(mean)
for i in range(len(mean_std)):
    mean_std[i]=(mean[i]-min(mean))/(max(mean)-min(mean))
    f.write(str(mean_std[i])+'\t'+str(index[i])+'\n')
f.close()'''

'''f=open('D:/Math/data_std.txt','rt')
w=open('D:/Math/data_stdtab.txt','w+')
for line in f:
    line=line.replace(' ','\t')
    w.write(line)
f.close()
w.close()'''