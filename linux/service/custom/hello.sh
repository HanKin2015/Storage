#!/bin/bash
#
# 文 件 名: hello.sh
# 文件描述: 将文件放置到/etc/init.d/目录下
# 参    考: https://blog.csdn.net/qq_28657577/article/details/80738161
# 作    者: HanKin
# 创建日期: 2022.07.06
# 修改日期：2022.07.06
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#
 
SERVICE_NAME="hello"
 
function start()
{
    echo "start $SERVICE_NAME"
    /home/$SERVICE_NAME
    echo "start $SERVICE_NAME ok!"
    exit 0;
}
 
function stop()
{
    echo "stop $SERVICE_NAME"
    killall $SERVICE_NAME
    echo "stop $SERVICE_NAME ok!"
}
 
case "$1" in
start)
    start
    ;;
stop)
    stop
    ;;
restart)
    stop
    start
    ;;
*)
    echo "usage: $0 start|stop|restart"
    exit 0;
esac
exit