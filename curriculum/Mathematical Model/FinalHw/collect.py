'''f=open('D:/Math/data_0.txt','rt',encoding='utf-8')
locs_dict={}
for line in f:
    words=line.split()
    locs_dict[words[1]]=[]
    locs_dict[words[1]].append(words[2])
f.close()
for i in range(1,10):
    f=open('D:/Math/data_'+str(i)+'.txt','rt',encoding='utf-8')
    for line in f:
        words=line.split()
        locs_dict[words[1]].append(words[2])
    f.close()'''
#print(locs_dict)
'''f=open('D:/Math/data_sum.txt','w+',encoding='utf-8')
for k in locs_dict.keys():
    f.write(k)
    for i in range(len(locs_dict[k])):
        f.write('\t'+locs_dict[k][i])
    f.write('\n')
f.close()
'''