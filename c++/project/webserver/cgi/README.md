# cgi脚本

参考：https://zhuanlan.zhihu.com/p/25013398
https://blog.csdn.net/weixin_39609623/article/details/86312439

## 1、简介
通用网关接口（Common Gateway Interface）是一个Web服务器主机提供信息服务的标准接口。通过CGI接口，Web服务器就能够获取客户端提交的信息，转交给服务器端的CGI程序进行处理，最后返回结果给客户端。

组成CGI通信系统的是两部分：一部分是html页面，就是在用户端浏览器上显示的页面。另一部分则是运行在服务器上的Cgi程序。

## 2、基本原理
服务器和CGI程序之间的通讯才是我们关注的。一般情况下，服务器和CGI程序之间是通过标准输入输出来进行数据传递的，而这个过程需要环境变量的协作方可实现。

对于CGI程序来说，它继承了系统的环境变量。CGI环境变量在CGI程序启动时初始化，在结束时销毁。

当一个CGI程序不是被HTTP服务器调用时，它的环境变量几乎是系统环境变量的复制。当这个CGI程序被HTTP服务器调用时，它的环境变量就会多了以下关于HTTP服务器、客户端、CGI传输过程等项目。

环境变量是一个保存用户信息的内存区。当客户端的用户通过浏览器发出CGI请求时，服务器就寻找本地的相应CGI程序并执行它。在执行CGI程序的同时，服务器把该用户的信息保存到环境变量里。接下来，CGI程序的执行流程是这样的：查询与该CGI程序进程相应的环境变量：第一步是request_method，如果是POST，就从环境变量的len，然后到该进程相应的标准输入取出len长的数据。如果是GET，则用户数据就在环境变量的QUERY_STRING里。

## 3、CGI 的局限性与替代技术
尽管 CGI 简单直观，但存在明显缺点：

性能低下：每个请求创建新进程，频繁请求会导致服务器资源消耗大（CPU、内存占用高）。
开发效率低：需手动处理环境变量、输入解析等底层细节，缺乏现代框架的便捷功能（如路由、模板引擎）。

因此，CGI 逐渐被更高效的技术替代：

FastCGI：进程复用（一个进程处理多个请求），减少进程创建开销（如 PHP-FPM、Python 的 Flup）。
嵌入式脚本：如 PHP、JSP，脚本代码嵌入 HTML，由服务器模块直接解析，无需创建外部进程。
Web 框架：如 Python 的 Django/Flask、Node.js 的 Express，通过内置服务器或 WSGI/ASGI 协议与 Web 服务器通信，性能和开发效率更优。

总结
CGI 是 Web 发展早期实现动态内容的关键技术，定义了服务器与外部程序的通信标准，具有语言无关、跨平台的特点。但由于性能限制，现在已很少直接使用，更多作为基础概念存在。理解 CGI 的工作原理，有助于掌握后续更复杂的 Web 服务器与应用程序交互机制（如 FastCGI、WSGI 等）。

## 4、运行cgi脚本
使用python语言，但是导入cgi库失败，新版Ubuntu默认支持python3运行，但不存在pip3安装命令，如果通过apt安装pip3命令后再安装cgi库的话就会报错：
```
This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
```
这个错误是由于现代 Debian/Ubuntu 系统（以及其他基于 Debian 的发行版）采用了 PEP 668 规范，限制了直接在系统全局 Python 环境中安装包，以避免系统包管理和 pip 安装的包发生冲突。

对于 cgi 模块，它其实是 Python 标准库的一部分，通常不需要单独安装。如果你的系统中确实缺失，可以尝试安装完整的 Python 环境：
```
sudo apt update
sudo apt install python3-full
```
最终通过此方法解决。但是还存在警告，经查询得知：
你看到的 DeprecationWarning: 'cgi' is deprecated 警告是因为 Python 3.13 及以后版本将移除 cgi 标准库模块，目前只是提醒你这个模块未来会被淘汰。

虽然有警告，但当前版本（Python 3.13 之前）仍然可以正常使用。如果想消除警告并为未来兼容做准备，可以用以下两种方法：
方法 1：忽略警告（简单快速）
在 post.cgi 脚本开头添加忽略警告的代码：
```
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning, module="cgi")

# 然后再导入cgi模块
import cgi
```

方法 2：替换为 cgi 的替代方案（推荐长期解决方案）
cgi 模块的核心功能（解析表单数据）可以用 Python 标准库的 urllib.parse 替代，示例如下：

修改 post.cgi 中解析表单的部分：
```
# 替换原来的 import cgi
from urllib.parse import parse_qs
import sys

# 读取请求体并解析表单数据
content_length = int(os.environ.get('CONTENT_LENGTH', 0))
post_data = sys.stdin.read(content_length)
form_data = parse_qs(post_data)  # 解析表单数据，返回字典

# 获取表单字段的值（示例）
# 假设表单有个名为"username"的字段
username = form_data.get('username', [''])[0]  # 取第一个值
```
这种方式完全避免使用 cgi 模块，没有 deprecation 警告，且兼容未来的 Python 版本。

## 5、实战

### 5-1、注意事项
html文件必需要是600权限，否则打开不显示内容，如错误添加了执行x权限。
cgi脚本需要添加执行x权限，否则无法正常被调用执行。

### 5-2、http服务器
cgi脚本直接通过本地的html调用是无法正常运行的，只能显示出源代码。
因此必须要有http服务器才能正常运行cgi脚本。

首先是借助已有项目运行http服务器：
https://github.com/EZLippi/Tinyhttpd/tree/master
https://github.com/forthespada/MyPoorWebServer/tree/master

注意运行http服务器程序后浏览器打开http://127.0.0.1:6379后出现：
The server could not fulfill your request because the resource specified is unavailable or nonexistent. 
问题原因是已有项目中已经写明了首页html的名字以及访问的路径，需要按照项目中规定的来，否则就会报这个错误，这个错误也是http服务器程序中输出的。

走过很多弯路，曾经一度以为是root权限导致浏览器无法访问其html文件，然后各种修改后仍然无效，最终发现与文件权限无关。

### 5-3、c语言版本
demo见：D:\interview\Storage\c++\project\web_server\cgi\简单入门示例-c语言版本

编译 C 程序为 CGI 可执行文件
编译时需要确保生成的是可执行文件，并且具有执行权限：
```
gcc hello.c -o hello.cgi
chmod +x hello.cgi
```

### 5-4、python版本
demo见：D:\interview\Storage\c++\project\web_server\cgi\简单入门示例-python语言版本

不需要编译，只要本地能正常运行python脚本即可。


