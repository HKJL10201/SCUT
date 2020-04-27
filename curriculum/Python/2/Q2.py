def strip(string):
    words=string.split()
    s=""
    for a in words:
        s+=a
    return s

st=strip("abc defg  hijk    lmn")
print(st)