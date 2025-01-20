# Flask-SocketIO

## 1、websocket简介
Python WebSocket 是一种用于在客户端和服务器之间进行双向通信的协议。WebSocket 允许在单个 TCP 连接上进行全双工通信，这意味着客户端和服务器可以同时发送和接收消息，而不需要每次都建立新的连接。Python 提供了多种库来实现 WebSocket 功能，最常用的包括 websocket-client 和 websockets。

Flask-SocketIO 是一个用于在 Flask 应用中实现 WebSocket 功能的扩展。它结合了 Flask 的简洁性和 Socket.IO 的强大功能，允许开发者轻松地在 Flask 应用中实现实时双向通信。

## 2、example示例
使用方式：首先运行python example/socketio_example.py，然后在浏览器上面输入http://127.0.0.1:8029/即可
使用F12按键查看Console信息，会出现“发送成功”消息。

### 问题2-1、WARNING in __init__: WebSocket transport not available. Install gevent-websocket for improved performance.
```
pip install gevent-websocket
```

### 问题2-2、AttributeError: type object 'Server' has no attribute 'reason'
```
(base) D:\Users\User\Desktop>python socketio_example.py
Traceback (most recent call last):
  File "socketio_example.py", line 2, in <module>
    from flask_socketio import SocketIO, emit
  File "C:\Users\User\anaconda3\lib\site-packages\flask_socketio\__init__.py", line 52, in <module>
    class SocketIO:
  File "C:\Users\User\anaconda3\lib\site-packages\flask_socketio\__init__.py", line 168, in SocketIO
    reason = socketio.Server.reason
AttributeError: type object 'Server' has no attribute 'reason'

(base) D:\Users\User\Desktop>pip show flask-socketio python-socketio
Name: Flask-SocketIO
Version: 5.5.0
Summary: Socket.IO integration for Flask applications
Home-page:
Author:
Author-email: Miguel Grinberg <miguel.grinberg@gmail.com>
License:
Location: c:\users\user\anaconda3\lib\site-packages
Requires: Flask, python-socketio
Required-by:
---
Name: python-socketio
Version: 5.11.0
Summary: Socket.IO server and client for Python
Home-page:
Author:
Author-email: Miguel Grinberg <miguel.grinberg@gmail.com>
License:
Location: c:\users\user\anaconda3\lib\site-packages
Requires: bidict, python-engineio
Required-by: Flask-SocketIO

更新库文件，但是已是最新版本
(base) D:\Users\User\Desktop>pip install --upgrade flask-socketio python-socketio
```

发现另外一个环境测试正常，原因是python-socketio-5.12.1，通过查看C:\ProgramData\anaconda3\Lib\site-packages\socketio\server.py文件发现高版本确实存在reason字段，但是低版本不存在，然后从pypi网站下载了python_socketio-5.12.1-py3-none-any.whl进行安装（https://pypi.org/project/python-socketio/#history），然而安装失败：
```
(base) D:\Users\User\Desktop\socketio>pip3 install python_socketio-5.12.1-py3-none-any.whl
Looking in indexes: http://mirrors.sangfor.org/pypi/simple, http://mirrors.sangfor.org/sfpypi/simple
Processing d:\users\user\desktop\socketio\python_socketio-5.12.1-py3-none-any.whl
Requirement already satisfied: bidict>=0.21.0 in c:\users\user\anaconda3\lib\site-packages (from python-socketio==5.12.1) (0.22.1)
Requirement already satisfied: python-engineio>=4.11.0 in c:\users\user\anaconda3\lib\site-packages (from python-socketio==5.12.1) (4.11.2)
INFO: pip is looking at multiple versions of python-socketio to determine which version is compatible with other requirements. This could take a while.
ERROR: Package 'python-socketio' requires a different Python: 3.7.6 not in '>=3.8'
问题电脑python版本为3.7.6，正常电脑python版本为3.8.8

最终妥协(base) D:\Users\User\Desktop\socketio>pip install flask-socketio==5.3.2
```

### 问题2-3、python程序运行后无反应
`http://127.0.0.1:8029/`输入完成后也没有反应，然后通过F12按键发现打开socket.io.js失败了，原因是内网，无法访问互联网，从外网将socket.io.js文件下载到本地，修改html文件为<script src="/static/js/socket.io.js"></script>
注意：js文件一定要放在static目录下面，测试过放在根目录和sta目录都不行。
目录结构：
```
your_project/
│
├── app.py  # 你的 Flask 应用
├── static/
│   └── js/
│       └── socket.io.js  # 下载的 socket.io.js 文件
└── templates/
    └── index.html  # 你的 HTML 文件
```

## 3、一个很奇怪的bug
应该可能是环境问题，一旦把debug模式开启后就打不开网页。
报错如下：
```
ImportError: cannot import name 'EVENT_TYPE_OPENED' from 'watchdog.events' (C:\ProgramData\Anaconda3\lib\site-packages\watchdog\events.py)
```

另外使用socketio执行的时候不会提示填写什么网址，一开始害我一直在直接打开html文件。
另外html文件一定需要放在templates文件夹里面，可能是程序中使用render_template函数进行调用html文件。

```
python脚本不添加index.html问题：
Not Found
The requested URL was not found on the server. If you entered the URL manually please check your spelling and try again.

不添加到templates文件夹问题：
jinja2.exceptions.TemplateNotFound: index.html

Internal Server Error
The server encountered an internal error and was unable to complete your request. Either the server is overloaded or there is an error in the application.
```

## 4、记住一点
使用flask_socketio长连接一定需要一个html网页

## 5、解决socketio库中的线程问题
project：D:\Github\Storage\python\web\socketio\socketio_thread

问题现象：想在项目中弹出一个messagebox弹框，不想阻碍主程序的程序，因此考虑使用线程调用函数弹出messagebox弹框，结果怎么调试都阻碍了主程序的执行，但是测试demo却是正常的。

尝试过多个失败的方式：
- 使用socketio.start_background_task函数反而demo程序也会阻碍
- 使用thread = threading.Thread(target=cls.show_error, args=(invalid_list,))函数demo程序正常，但是项目阻碍
- 主攻threading函数，怀疑可能是类调用引起、文件调用引起，测试后发现demo程序使用threading就是正常的
- SocketIO异步方式有eventlet和threading，但是gevent需要高版本，因此不测试，更改async_mode参数并没有用
- 最终解决方案还是靠google，确实对于疑难问题还是好用一点

解决方案：
参考https://segmentfault.com/q/1010000043310040
https://github.com/miguelgrinberg/Flask-SocketIO/blob/e024b7ec9db4837196d8a46ad1cb82bc1e15f1f3/example/app.py#L30-L31
发现程序中存在一个叫做eventlet.monkey_patch()的函数，发现项目中也存在这个东西

使用 eventlet.monkey_patch() 可能会导致阻塞的原因主要与 eventlet 的工作方式有关。eventlet 是一个用于并发网络应用的库，它通过协作式多任务处理来实现并发，这意味着它会在 I/O 操作时切换上下文，而不是使用线程或进程。
eventlet 通过猴子补丁（monkey patching）来替换标准库中的某些模块（如 socket、threading、time 等），使其支持协作式多任务处理。如果你的代码中有阻塞调用（例如，Tkinter 的 messagebox.showerror），这会导致整个事件循环被阻塞，因为 eventlet 期望所有 I/O 操作都是非阻塞的。

使用 eventlet.spawn 启动 Tkinter 线程: 使用 eventlet.spawn 来启动一个新的协作任务，这样可以在 eventlet 的上下文中运行 Tkinter 的代码。