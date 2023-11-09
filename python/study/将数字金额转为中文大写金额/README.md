# 将数字金额转为中文大写金额

来源：https://mp.weixin.qq.com/s/roeEZ5eIclz8tRpu34ARIg

## 1、num2chinese库
首先关于num2chinese库，根本无法使用。
当前环境是3.7.6，安装完成后num2chinese库根本没有任何函数，__init__.py是一个空文件。
```
(base) D:\Users\User\Desktop>python
Python 3.7.6 (default, Jan  8 2020, 20:23:39) [MSC v.1916 64 bit (AMD64)] :: Anaconda, Inc. on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import num2chinese
>>> dir(num2chinese)
['__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__path__', '__spec__']
>>> help(num2chinese)
Help on package num2chinese:

NAME
    num2chinese

PACKAGE CONTENTS
    normalizer

FILE
    c:\users\user\anaconda3\lib\site-packages\num2chinese\__init__.py


>>> import math
>>> dir(math)
['__doc__', '__loader__', '__name__', '__package__', '__spec__', 'acos', 'acosh', 'asin', 'asinh', 'atan', 'atan2', 'atanh', 'ceil', 'copysign', 'cos', 'cosh', 'degrees', 'e', 'erf', 'erfc', 'exp', 'expm1', 'fabs', 'factorial', 'floor', 'fmod', 'frexp', 'fsum', 'gamma', 'gcd', 'hypot', 'inf', 'isclose', 'isfinite', 'isinf', 'isnan', 'ldexp', 'lgamma', 'log', 'log10', 'log1p', 'log2', 'modf', 'nan', 'pi', 'pow', 'radians', 'remainder', 'sin', 'sinh', 'sqrt', 'tan', 'tanh', 'tau', 'trunc']
>>> dir(num2chinese.normalizer)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: module 'num2chinese' has no attribute 'normalizer'
>>> import normalizer
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ModuleNotFoundError: No module named 'normalizer'
>>>
```

## 2、关于文中提到的函数
只能满足部分要求，需要待完善。
