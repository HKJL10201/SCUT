import os
import string

def counter(file):  #计算单个文件代码行数
    lines=0     #代码行数
    code=open(file,'r',encoding='utf-8')    #考虑到中文注释，用utf-8读取
    flag=0      #多行注释的标志
    for line in code.readlines():   #遍历每一行代码
        if not line.split():
            continue        #忽略空行
        line=line.strip()       #消除前后空白符
        if line.startswith('#'):
            continue        #忽略单行注释
        line=line.split()
        if line[0]=="'''" or line[0]=='"""':    #遇到多行注释的情况
            if flag==0:
                flag=1      #多行注释的开始
            elif flag==1:
                flag=0      #多行注释的结束
            continue
        if flag==1:
            continue        #多行注释内的行数全部忽略
        lines+=1
    return lines

def code_counter(dir):
    """
    :type dir: string, 一个目录路径
    :rtype: int, 代码行数
    """
    total=0     #全部文件代码总行数
    for maindir, subdir, file_name_list in os.walk(dir):    #遍历目录及子目录
        for filename in file_name_list: 
            if filename.split('.')[-1]=='py':   #检测文件是否为py文件
                apath = os.path.join(maindir, filename)
                total+=counter(apath)       #统计该文件的代码行数
    return total

print(code_counter(os.getcwd()))