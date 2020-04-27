import numpy as np
dis=np.loadtxt('D:\\dis_ori.txt')
f=open('D:\\merge.txt','w+')
for z in range(31):
    num=len(dis)
    dis_min=np.min(dis)
    f.write(str(z+1))
    f.write('\t')
    f.write(str(dis_min))
    f.write('\t')
    pos=np.where(dis==dis_min)
    tar_row=pos[0]
    tar_row=tar_row[0]
    tar_col=pos[1]
    tar_col=tar_col[0]
    f.write(str(tar_row))
    f.write(',')
    f.write(str(tar_col))
    f.write('\n')
    new_row=[]
    tar=[tar_row,tar_col]
    for i in range(num):
        if i in tar:
            continue
        new_row.append(min([dis[max([i,tar_row]),min([i,tar_row])],dis[max([i,tar_col]),min([i,tar_col])]]))
    dis=np.delete(dis,max([tar_row,tar_col]),axis=0)
    dis=np.delete(dis,max([tar_row,tar_col]),axis=1)
    dis=np.delete(dis,min([tar_row,tar_col]),axis=0)
    dis=np.delete(dis,min([tar_row,tar_col]),axis=1)
    dis=np.row_stack((dis,new_row))
    num=len(dis)
    new_col=[]
    for n in range(num):
        new_col.append(9)
    dis=np.column_stack((dis,new_col))
    np.savetxt('D:\\dis\\dis_'+str(z+1)+'.txt',dis,fmt='%.2f')