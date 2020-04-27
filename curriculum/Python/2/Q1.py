def valid_number():
    x=[]
    for d in range(125,625):
        n=0
        for i in range(0,4):
            n+=((int)(d/(5**i))%5)*(10**i)
        x.append(n)
    return x
num=valid_number()
print(num)