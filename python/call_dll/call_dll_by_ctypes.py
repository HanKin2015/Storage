# -*- coding: utf-8 -*-
"""
文 件 名: call_dll_by_ctypes.py
文件描述: 使用ctypes库调用c++语言编写的dll文件
作    者: HanKin
创建日期: 2023.12.27
修改日期：2023.12.27

Copyright (c) 2023 HanKin. All rights reserved.
"""
import struct
import ctypes

def get_python_bit():
    """获取python环境位数
    """
    print(struct.calcsize('P') * 8)

def call_dll_base():
    """简单调用dll文件函数
    """
    # 加载 DLL 文件
    example_dll = ctypes.WinDLL(r'D:\Users\User\Desktop\卡慢检测工具\卡慢检测工具\mathematics.dll')

    # 列出所有属性和方法（无法直接列出DLL文件中的所有函数和方法）
    print(dir(example_dll))
    #print(help(example_dll))
    print(example_dll.__dict__.keys())

    # 调用 DLL 中的函数
    #result = example_dll.arithmetic_operation.Add(4, 5)    # 类函数调用比较复杂
    result = example_dll.export333()

    # 如果函数有参数，可以像下面这样传递参数
    # result = example_dll.some_function(arg1, arg2, ...)

    # 打印结果
    print(result)

    function_name = 'export333'
    func = getattr(example_dll, function_name)
    func.restype = ctypes.c_int # 返回值类型
    func.argtypes = []          # 入参类型
    result = func()
    print(result)
   
def call_dll_senior():
    """进阶版调用类函数
    """
    # 加载DLL
    my_dll = ctypes.CDLL(r'D:\Users\User\Desktop\卡慢检测工具\卡慢检测工具\mathematics.dll')

    # 定义类的结构体
    # 定义类
    class ArithmeticOperation(ctypes.Structure):
        _fields_ = []

    # 设置函数参数和返回类型
    my_dll.Add.argtypes = [ctypes.POINTER(ArithmeticOperation), ctypes.c_double, ctypes.c_double]
    my_dll.Add.restype = ctypes.c_double

    my_dll.Sub.argtypes = [ctypes.POINTER(ArithmeticOperation), ctypes.c_double, ctypes.c_double]
    my_dll.Sub.restype = ctypes.c_double

    my_dll.Multi.argtypes = [ctypes.POINTER(ArithmeticOperation), ctypes.c_double, ctypes.c_double]
    my_dll.Multi.restype = ctypes.c_double

    my_dll.Div.argtypes = [ctypes.POINTER(ArithmeticOperation), ctypes.c_double, ctypes.c_double]
    my_dll.Div.restype = ctypes.c_double

    # 创建类实例
    arithmetic_instance = ArithmeticOperation()

    # 调用类函数
    result_add = my_dll.Add(ctypes.byref(arithmetic_instance), 2.0, 3.0)
    result_sub = my_dll.Sub(ctypes.byref(arithmetic_instance), 5.0, 2.0)
    result_multi = my_dll.Multi(ctypes.byref(arithmetic_instance), 4.0, 2.0)
    result_div = my_dll.Div(ctypes.byref(arithmetic_instance), 10.0, 2.0)
    print(result_add, result_sub, result_multi, result_div)

def test1():
    """使用dll中的实例调用函数失败
    """
    my_dll = ctypes.CDLL(r'D:\Users\User\Desktop\卡慢检测工具\卡慢检测工具\ArithmeticsDll.dll')
    print(my_dll.Export333())
    print(my_dll.ExportN(12345))
    arithmetics_instance = my_dll.ArithmeticsInstance1()
    arithmetics_instance = my_dll.ArithmeticsInstance2()
    print(arithmetics_instance)
    print(arithmetics_instance.Add(3, 5))

def test2():
    """使用dll中封装的c语言接口调用，但是结果存在异常
    """
    my_dll = ctypes.CDLL(r'D:\Users\User\Desktop\卡慢检测工具\卡慢检测工具\ArithmeticsDll.dll')
    print(my_dll.Export333())
    print(my_dll.ExportN(12345))
    print(my_dll.Add(3, 5))
    print(my_dll.Sub(3, 5))
    print(my_dll.Multi(3, 5))
    print(my_dll.Div(3, 5))

def test3():
    """使用dll中封装的c语言接口调用
    """
    my_dll = ctypes.CDLL(r'D:\Users\User\Desktop\卡慢检测工具\卡慢检测工具\ArithmeticsDll.dll')
    print(my_dll.Export333())
    print(my_dll.ExportN(12345))
    
    # 设置函数参数和返回类型（这步很重要）
    my_dll.Add.argtypes = [ctypes.c_double, ctypes.c_double]
    my_dll.Add.restype = ctypes.c_double
    my_dll.Sub.argtypes = [ctypes.c_double, ctypes.c_double]
    my_dll.Sub.restype = ctypes.c_double
    my_dll.Multi.argtypes = [ctypes.c_double, ctypes.c_double]
    my_dll.Multi.restype = ctypes.c_double
    my_dll.Div.argtypes = [ctypes.c_double, ctypes.c_double]
    my_dll.Div.restype = ctypes.c_double
    print(my_dll.Add(3, 5))
    print(my_dll.Sub(3, 5))
    print(my_dll.Multi(3, 5))
    print(my_dll.Div(3, 5))

if __name__ == '__main__':
    test3()