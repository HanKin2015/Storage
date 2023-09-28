https://blog.csdn.net/Gefangenes/article/details/131715167

## 1、websocket简介
websocket 说白一点就是，建立客户端和服务端双向通讯通道， 服务器可以主动向客户端发消息。

## 2、官方教程
[2023-09-22 10:49:40,142] WARNING in __init__: WebSocket transport not available. Install gevent-websocket for improved performance.

## 3、一个很奇怪的bug
应该可能是环境问题，一旦把debug模式开启后就打不开网页。
另外使用socketio执行的时候不会提示填写什么网址，一开始害我一直在直接打开html文件。
另外html文件一定需要放在templates文件夹里面，可能是程序中使用render_template函数进行调用html文件。
