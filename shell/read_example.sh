#!/bin/bash

echo -n "请输入姓名："
read test
echo $test

read test?"请输入姓名："
echo $test

echo -n "请输入密码："
read -s pwd
echo "" # 输入完自动换行
echo "密码已接收"

echo -n "3秒内输入内容："
read -t 3 msg

echo -n "请选择y/n："
read -n 1 opt
echo ""
echo 你选择了：$opt

echo -n "输入姓名 年龄："
read name age
echo 姓名：$name，年龄：$age

console:/data/hj # echo -n "请输入姓名："
请输入姓名：hejian
console:/data/hj # echo $test
hejian
