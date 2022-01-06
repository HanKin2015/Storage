# 目录结构
- 日志：log
- 数据：data

# 文件简介
- configure_data_share_storage_service.py：后台服务程序，负责收发客户端的消息，进行操作数据库，通知修改机制
- sqlite3_operation_library.py：数据库操作文件，包含增删改查
- server.py：打包成exe文件，按道理来说应该写成线程，客户端接收消息模块
- client.py:客户端程序，可以进行增删改查
- encryption_algorithm_library.py：加密算法库文件

# 运行
- 首先启动configure_data_share_storage_service.py程序，监听127.0.0.1:8384端口
- 然后启动client.py即可操作

# 环境
语言：python
编译器：python3.7.4
python库：anadonda3(version 1.7.3)
需要安装：pycrypto、ConcurrentLogHandler、rsa


# API设计
- 函数参数不能超过5个
- 




# 判断一个字符串是否在数组中
使用in语句
```
valid_data = ['a', 'b']
if data in valid_data:
    return True
return False
```

# 常犯的错
布尔值：True和False
if语句可以不用加括号


# 线程

# 进程间通信之socket

# 进程间通信之udp

# 调用另外一个py文件的全局变量结果会怎样
```a.py
x = 10

def fun():
    print(x)

x += 100
```
---
```b.py
import a

a.fun()
```
输出结果为：110

稍微改了一下
```a.py
x = 10

def fun():
    print(x)

def t():
    x += 1000

x += 100

if __name__ == '__main__':
    t()
```
结果不变：110

# os.mkdir和makedirs区别
尽量使用makedirs，因为可以同时建立子文件夹


# 全局变量
如果全局变量不初始化值的话，必须添加global关键字     
函数里可以定义局部变量，并初始化初始值
但是不能在函数里之间操作全局变量，会出错未定义，需要global关键字
```
x = 10
global y

def fun():
    x += 100 # wrong
    x = 100  # right
    global x
    x += 100 # right
``` 








































# cmd的python运行环境
使用了anaconda搭建的环境后，不需要费时在cmd上面搭建环境，直接使用anaconda的cmd窗口即可。

在cmd中运行：C:\Users\hj159\Anaconda3\Scripts\activate.bat


# ImportError: cannot import name 'winrandom'
- 删除库文件夹
- pip install pycrypto还是有版本存在
- conda install pycrypto安装后解决



# 项目

实现一个配置数据共享存储模块

要求：
1.对外支持多线程/多进程的数据安全读写访问；
2.对外提供数据更改通知机制，能及时让外部获取数据的变化。
3.数据存储要求支持加密安全，加密算法要求可扩展；

说明：
1.配置数据存储在SQLite里，模块读取出来后转换为JSON格式给业务模块使用，比如员工配置信息：
{
"employees": [
{ "jobNumber":"100000" , "firstName":"Bill" , "salary":"20000" },
{ "jobNumber":"100001" , "firstName":"George" , "salary":"25000" },
{ "jobNumber":"100002" , "firstName":"Thomas" , "salary":"30000" }
]
}

员工SVN账号配置信息：
{
"svnAccounts": [
{ "jobNumber":"100000" , "user":"bill123" , "pwd":"123456" },
{ "jobNumber":"100001" , "user":"george123" , "pwd":"123456" },
{ "jobNumber":"100002" , "user":"thomas123" , "pwd":"123456" }
]
}

假设配置数据存储共享模块为G，另外有两个业务模块A和B，那么：
1，题目要求中的第1点就是期望G能提供让业务模块A和B安全读写操作配置的接口。
比如：新增一名员工，删除一名员工，调整员工薪水（两个业务模块A和B可能同时调整某一个员工的薪水，因此需要考虑安全读写访问）。

2，题目要求中的第2点就是如果业务模块A修改了员工配置信息，需要能及时通知业务模块B，让业务模块B及时更新自己的业务逻辑。

3，题目要求中的第2点是需要通过加密来确保数据的安全存储，并且加密算法是可扩展的，比如更改加密算法。

提示：
1，以上配置信息字段是最基本的，可以根据实现需要，增加其他字段。
2，本题中的数据都是配置信息，不会特别多，暂时不用考虑性能问题。



## 数据库操作：增删改查

## 的




