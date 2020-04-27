import numpy as np

'''data=np.loadtxt('D:/Math/data_matrix.txt')
f=open('D:/Math/data_mean_locs.txt','w+')
mean=np.mean(data,axis=1)
for i in range(len(mean)):
    f.write(str(mean[i])+'\n')
f.close()'''

'''f=open('D:/Math/pos.txt','rt',encoding='utf-8')
fm=open('D:/Math/data_mean_locs.txt','rt')
w=open('D:/Math/pos_matrix.txt','w+')
for line in f:
    words=line.split()
    mean=fm.readline()
    w.write(words[1]+'\t'+words[2]+'\t'+mean)
f.close()
fm.close()
w.close()'''
