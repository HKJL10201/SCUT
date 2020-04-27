def special_sum(a, amount):
    """
    :type a: int
    :type amount: int
    :rtype: int
    """
    n=0     #第i个加数的值
    sum=0   #相加的结果
    for i in range(amount):
        n+=a*(10**i)    #第i个加数的值
        sum+=n
        print(n)
    return sum

print(special_sum(-2,5))