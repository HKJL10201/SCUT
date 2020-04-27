def selection_sort(iterable, *, comparator):
    """
    :type iterable: 可迭代对象
    :type comparator: 接受两个参数的函数对象
    :rtype: list
    """
    a=[]
    for x in iterable:      #将可迭代对象转换为列表
        a.append(x)
    for i in range(len(a)): #对列表进行选择排序
        min=i           #最小值下标
        j=len(a)-1      #从最后一个元素向前遍历
        while(j>i):
            if comparator(a[j],a[min])<0:
                min=j           #当遍历的元素比最小值更小，记录当前遍历的下标
            j-=1
        a[i],a[min]=a[min],a[i]     #将第i个元素换为最小值
    return a

#测试样例如下：
a=selection_sort(["ab", "abc", "a"], comparator=lambda x,y: len(x)-len(y))
print(a)

def gen10():
    for i in range(10):
        yield 10-i

b=selection_sort(gen10(), comparator=lambda x,y: x-y)
print(b)