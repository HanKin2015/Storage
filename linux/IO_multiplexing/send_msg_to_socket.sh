#!/bin/bash

# socat，是linux下的一个工具，其功能与有“瑞士军刀”之称的netcat类似，不过据说可以看做netcat的加强版。
# 的确如此，它有一些netcat所不具备却又很有需求的功能，例如ssl连接这种。nc可能是因为比较久没有维护，
# 确实显得有些陈旧了。

# apt install socat

# 这种方法可能只适用于本地通信
while true
do
    echo {\"method\":\"windows_maximsize\"} | socat - unix-connect:/proc/20702/fd/3
    sleep  5
done

# 可行的通信
socat - TCP:localhost:9999

# 发现有多个socket连接时，服务端只响应最开始连接的socket，当前一个socket连接断开时再接收后面的socket连接，消息不丢失
