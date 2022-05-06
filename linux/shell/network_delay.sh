#!/bin/bash
#
# 文 件 名: network_delay.sh
# 文件描述: 设置网络延迟
# 用    法: ./network_delay.sh delay 1.2.3.4 100ms 10ms
# 作    者: HanKin
# 创建日期: 2021.08.09
# 修改日期：2021.08.09
# 
# Copyright (c) 2021 HanKin. All rights reserved.
#

:<<BLOCK
流量控制 （tc）

1.查看网卡 eth0 的流控的配置 (qdisc 表示排队规则 queueing discipline)
tc qdisc show dev eth0

2.将网卡 eth0 的传输设置为延迟 100 毫秒发送
tc qdisc add dev eth0 root netem delay 100ms
注：将上述规则的 add 修改为 del 即删除指定规则

3.将网卡 eth0 的传输设置为延迟 100ms ± 10ms (90 ~ 110 ms 之间的任意值)发送。
tc qdisc add dev eth0 root netem delay 100ms 10ms

4.将网卡 eth0 的传输设置为随机丢掉 1% 的数据包
tc qdisc add dev eth0 root netem loss 1%

5.限制带宽, 延迟, 丢包
tc qdisc add dev eth4 root handle 1: htb r2q 1
tc filter add dev eth4 parent 1: protocol ip prio 16 u32 match ip dst 177.1.80.159 flowid 1:1
tc class add dev eth4 parent 1: classid 1:1 htb rate 50kbit ceil 50kbit
tc qdisc add dev eth4 parent 1:1 handle 2: netem delay 50ms loss 30%
修改规则：
tc class change dev eth4 parent 1: classid 1:1 htb rate 1mbit ceil 1mbit

6.设置指定IP的延迟和丢包
tc qdisc add dev eth0 root handle 1: prio
tc filter add dev eth0 parent 1: protocol ip prio 16 u32 match ip dst 177.1.80.159 flowid 1:1
tc qdisc add dev eth0 parent 1:1 handle 10: netem delay 50ms loss 1%

7.删除所有规则
tc qdisc del dev eth4 root
BLOCK

# 1.获取本机网卡端口名,如ens18/eth0
INTF=`ip addr | grep -B2 10.70 | awk '{print $2}' | head -n 1 | sed s/://g`
echo "net interface $INTF"

# 2.设置本机到指定IP地址延迟
IP=$2

# 3.延迟数值
DELAY=$3

# 4.抖动数值
JITTER=$4

# 设置延迟函数
function delay() {
    tc qdisc add dev ${INTF} root handle 1: htb default 30
    tc class add dev ${INTF} parent 1: classid 1:1 htb rate 100000kbit
    tc class add dev ${INTF} parent 1: classid 1:2 htb rate 100000kbit
    tc filter add dev ${INTF} protocol ip parent 1:0 prio 1 u32  match ip dst ${IP} flowid 1:1
    tc filter add dev ${INTF} protocol ip parent 1:0 prio 1 u32  match ip src ${IP} flowid 1:2
    tc qdisc add dev ${INTF} parent 1:1 handle 10: netem delay ${DELAY} ${JITTER} loss 0%
}

# 取消延迟函数
function stopDelay() {
    tc qdisc del dev ${INTF} root
}

# 判断是设置延迟还是取消延迟
case "$1" in
    delay)
        echo "start ${INTF} to ${IP} delay ${DELAY}, ${JITTER}"
        delay
        echo "done"
        ;;

    stopDelay)
        echo "stop delay"
        stopDelay
        echo "done"
        ;;

    *)
        echo "usage: delay stopDelay"
        ;;
esac
