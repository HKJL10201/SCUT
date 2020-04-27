for i in range(10):
    f=open('C:/data/data_'+str(i)+'.txt','rt',encoding='utf-8')
    w=open('C:/data/data_std/data_'+str(i)+'.txt','w+',encoding='utf-8')
    for line in f:
        line=line.replace('*','')
        w.write(line)
    f.close()
    w.close()
