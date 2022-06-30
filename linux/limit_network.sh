#/bin/bash

rate=$1
delay=$2
loss=$3
jitter=$4

echo $IP

export LANG=zh_CN.UTF-8
#1. 开启IP转发
echo "1">/proc/sys/net/ipv4/ip_forward
#2. 开启IPTABLES
iptables -t nat -A POSTROUTING -j MASQUERADE

tcset --change --rate ${rate}kbps --loss ${loss} --delay ${delay} --delay-distro ${jitter} --direction outgoing enp0s18
tcset --change --rate ${rate}kbps --loss ${loss} --delay ${delay} --delay-distro ${jitter} --direction incoming enp0s19

echo "=========================================================="
echo | tc qdisc | grep "limit"
echo "=========================================================="
exit 0

