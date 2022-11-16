#!/usr/bin/python
# -*- coding: UTF-8 -*-

"""
zip() 函数用于将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的列表。
如果各个迭代器的元素个数不一致，则返回列表长度与最短的对象相同，利用 * 号操作符，可以将元组解压为列表。
zip 方法在 Python 2 和 Python 3 中的不同：在 Python 3.x 中为了减少内存，zip() 返回的是一个对象。如需展示列表，需手动 list() 转换。
"""

list1 = [3, 2, 4, 1, 0, 5]
list2 = ['three', 'two', 'four', 'one', 'zero']
print(list1)
print(list2)
print(zip(list1, list2))    # 无法输出
print(*(zip(list1, list2))) # 正常输出
print(list(zip(list1, list2)))
print(list(sorted(zip(list1, list2))))
print(*sorted(zip(list1, list2)))
print(zip(*sorted(zip(list1, list2))))

list1, list2 = zip(*sorted(zip(list1, list2)))
print(list1)
print(list2)
