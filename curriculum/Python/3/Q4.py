import time

def timeit(func):
    """
    :type func: 一个函数
    """
    def wrapper(num):
        t1=time.time()
        func(num)
        t2=time.time()
        print("函数执行时间："+str(t2-t1)+"秒")
    return wrapper

@timeit
def func(num):
    return sum(range(num))

func(1000000)