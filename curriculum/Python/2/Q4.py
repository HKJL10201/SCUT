# 统计text中26个英文字母(不区分大小写)出现的次数，并输出。
def count_letter():
    
    with open("./2\\Q4.txt", "r") as f:
        text = f.read()

    alph={}
    for le in range(65,91):
        alph[chr(le)]=0

    for ch in text:
        if(ord(ch)>96):
            ch=chr(ord(ch)-32)
        if(alph.get(ch)!=None):
            alph[ch]=(int)(alph[ch])+1

    return alph

dic=count_letter()
print(dic)