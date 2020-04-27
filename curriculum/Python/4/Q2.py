from collections import Counter
# 使用Collections.Counter统计text中26个英文字母(不区分大小写)出现的次数，并输出。
def count_letter():
    """
    :rtype: 返回一个dict，其中key为英文字母，value为字母出现的次数
    """
    with open("./2\\Q4.txt", "r") as f:
        text = f.read()

    c=Counter()
    for ch in text:
        n=ord(ch)
        if n<65 or n>122 or (n>90 and n<97):    #过滤非字母字符
            continue
        if n>96:        #统一大小写
            ch=chr(n-32)
        c[ch]=c[ch]+1
        
    return c

dic=count_letter()
print(dic)