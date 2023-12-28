# -*- coding: utf-8 -*-
"""
文 件 名: pybind11_example.py
文件描述: 使用pybind11库调用c++代码
作    者: HanKin
创建日期: 2023.12.28
修改日期：2023.12.28

Copyright (c) 2023 HanKin. All rights reserved.
"""
import Pybind11Example

if __name__ == '__main__':
    print(Pybind11Example.age(1234))
    print(Pybind11Example.Name('zhangsan'))
    
    hello_class = Pybind11Example.Hello()
    hello_class.say('hello')
    
    world_class = Pybind11Example.World()
    world_class.say('world')
    
    test_class = Pybind11Example.Test(1, 2, 'lisi', 23)
    test_class.print()
    print(test_class.name)
    print(test_class.GetName())
    print(test_class.age)
    test_class.age = 123456
    print(test_class.age)
    print(test_class.SetHeight(172))
    print(test_class.GetHeight())
    
    st_struct = Pybind11Example.ST("wangmazi")
    st_struct.str = "hello pybind11"
    st_struct.i   = 987654
    print(st_struct.str, st_struct.i)
    print(st_struct.name)
    #st_struct.name = "hj"   # AttributeError: can't set attribute
    st_struct.SetName("jack")
    print(st_struct.name)

r"""
(base) D:\Users\User\Desktop>python k.py
age = 1234
None
Name: zhangsan
zhangsan
hello
world
i= 1 j= 2
lisi
lisi
23
123456
None
172
hello pybind11 987654
wangmazi
jack
"""