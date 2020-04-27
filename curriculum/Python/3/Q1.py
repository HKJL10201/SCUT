def cycle(iterable):
    """
    实现一个循环迭代iterable的生成器
    :type iterable: 任何可迭代的对象，可能为字符串、list等
    """
    i=-1
    while True:
        i=(i+1)%len(iterable)
        a=iterable[i]
        yield a

it="abc"
g=cycle(it)
for i in range(10):
    print(next(g))