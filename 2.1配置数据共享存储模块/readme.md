# 目录结构
- 日志：log
- 数据：data


# 环境
语言：python
编译器：python3.7.4
python库：anadonda3(version 1.7.3)
需要安装：pycrypto、ConcurrentLogHandler


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




