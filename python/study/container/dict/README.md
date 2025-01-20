# 字典

## 1、dict和json的区别
json： (JavaScript Object Notation)的首字母缩写，字面的意思是(javascript对象表示法)，这里说的json指的是类似于javascript对象的一种数据格式对象，目前这种数据格式比较流行，逐渐替换掉了传统的xml数据格式， 前端使用ajax的时候后台返回该前端的数据格式就是json格式的。

字典：是一种数据结构，而json是一种数据格式, 格式就会有一些形式上的限制，比如json的格式要求必须且只能使用双引号作为key或者值的边界符号(值如果是数字可以不用加双引号)，不能使用单引号，用单引号或者不用引号会导致读取数据错误，而且“key”必须使用边界符（双引号），但字典就无所谓了,可以使用单引号，也可以使用双引号。

1、字典的类型是字典dict，是一种数据结构；json的类型是字符串str，json是一种格式； 接口测试是传参数payload时有时候是传的字符串，应该将payload的类型改为json
2、python dict 字符串用单引号，json强制规定双引
3、 json值可以是新的键值对（多层嵌套结构），字典的值一般只能是数值、文本
4、 json键名允许重复，字典不允许
5、结构相似，都是键值对

## 2、元组tuple
在 Python 中，字典的定义是用花括号 {} 包围的键值对，而元组是用圆括号 () 包围的。你在定义 class_code_functions 时，使用了一个逗号 , 结尾，这使得 Python 解释器将其视为一个元组。
```
class_code_functions = {
    "01": "audio",
    "02": "communication",
    "03": "hid",
    "07": "printer",
    "08": "storage",
    "09": "hub",
    "0B": "card",
    "0E": "video",
    "10": "video",
    "FF": "vendor_specific"
},  # 这里的逗号导致了元组的创建

for i in range(10):
    pass

print(type(class_code_functions))  # 输出: <class 'tuple'>
```