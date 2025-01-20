# 类的学习

## 1、魔法方法
https://blog.csdn.net/m0_66881249/article/details/128878537
https://baijiahao.baidu.com/s?id=1762485769871728635&wfr=spider&for=pc

魔法方法的官方名称为special method，指的是Python自带的，具有强大功能的，在一些特定情况下会被自动调用的方法，方法名一般以两个下划线开始，并且以两个下划线结束，Python中大致有100多个魔法方法。

- __init__方法相当于是构造函数
- __del__方法相当于是析构函数
- __str__()方法：定义对象的字符串表示，可以通过print(obj)打印该对象，也可以通过str(obj)方法得到该字符串表示
- __add__()方法：定义对象间的加法操作，可以使用+运算符进行操作，相当于是operator运算符重载
- __call__()方法：定义一个可调用的对象，使实例对象可以像函数一样被调用

demo见：D:\Github\Storage\python\study\class\magic_method.py

## 2、__dict__方法
https://blog.csdn.net/m0_57133702/article/details/120564391

a、类的静态函数、类函数、普通函数、全局变量以及一些内置的属性都是放在类__dict__里的
b、对象的__dict__中存储了一些self.xxx的一些东西
c、一些内置的数据类型是没有__dict__属性的，如：int, list, dict等这些常用的数据类型是没有__dict__属性的

demo见：D:\Github\Storage\python\study\class\magic_method.py
那是不是之前想知道调用的dll文件有哪些方法就使用这个呢？答案是不行。
```
print(my_dll.__dict__) ==>> {'_name': 'D:\\Users\\User\\Desktop\\ArithmeticsDll.dll', '_FuncPtr': <class 'ctypes.CDLL.__init__.<locals>._FuncPtr'>, '_handle': 1942880256}

print(dir(my_dll)) ==>> ['_FuncPtr', '__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattr__', '__getattribute__', '__getitem__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_func_flags_', '_func_restype_', '_handle', '_name']
```

## 3、两种初始化方式
demo见：class_inherit.py
静态配置：如果配置文件是静态的且不需要频繁更改，使用类属性的方式是合适的。
动态配置：如果配置文件可能会在运行时更改，或者你需要处理加载过程中的错误，使用实例属性的方式更为合适。

## 4、类的定义顺序
```
class Son3:
    father = Father3()
    def __init__(self):
        pass
class Father3:
    def __init__(self):
        pass
```
报错：NameError: name 'Father3' is not defined
demo见：order_of_class_definition1.py和order_of_class_definition2.py

## 5、类的装饰器
1. @classmethod
功能：将一个方法定义为类方法。类方法的第一个参数是类本身（通常命名为 cls），而不是实例。
用法：可以通过类本身或类的实例调用。

2. @staticmethod
功能：将一个方法定义为静态方法。静态方法不需要访问类或实例的属性和方法。
用法：可以通过类本身或类的实例调用。

3. @property
功能：将一个方法定义为属性。可以通过属性访问而不是方法调用来获取值。
用法：通常用于实现 getter 方法。

4. @<property_name>.setter
功能：为 @property 定义一个 setter 方法，以便可以通过属性设置值。
用法：通常与 @property 一起使用。

5. @<property_name>.deleter
功能：为 @property 定义一个 deleter 方法，以便可以通过属性删除值。
用法：通常与 @property 一起使用。

6. @dataclass（Python 3.7+）
功能：用于简化类的定义，自动生成 __init__、__repr__、__eq__ 等方法。
用法：通过装饰器将类标记为数据类。

7. @abstractmethod（与 ABC 一起使用）
功能：用于定义抽象方法，强制子类实现这些方法。
用法：通常与 ABC（抽象基类）一起使用。

demo见：

## 6、抽象类
from abc import ABC, abstractmethod 是 Python 中用于定义抽象基类（Abstract Base Class, ABC）的一个模块。这个模块提供了一种机制，可以定义接口和强制子类实现特定的方法。

1. ABC 类
ABC 是一个基类，用于定义抽象基类。抽象基类不能被实例化，目的是为了提供一个接口，强制子类实现特定的方法。

2. abstractmethod 装饰器
abstractmethod 是一个装饰器，用于标记一个方法为抽象方法。抽象方法在抽象基类中定义，但不提供具体实现。任何继承该抽象基类的子类都必须实现这些抽象方法，否则将无法实例化子类。

demo见：D:\Github\Storage\python\study\class\abstractmethod_example.py

## 7、枚举变量
在 Python 中，枚举（Enum）是一种用于定义一组命名常量的类。使用枚举可以使代码更加清晰和可读，特别是在需要使用一组固定值的情况下。Python 的 enum 模块提供了 Enum 类来创建枚举。
demo见：D:\Github\Storage\python\study\class\enum_example.py
