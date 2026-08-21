#!/bin/sh

A="10"
B="2"

echo "字符串比较运算符： = 或 == 和 != 和 < 和 >"
echo "数值比较运算符（用于整数）：-eq 和 -ne 和 -gt 和 -lt 和 -ge 和 -le"

# 转义字符的重要性或者[[]]和[]区别
echo "============字符串比较(>)============"
echo "错误的方式"
if [ "$A" > "$B" ]; then
        echo "$A greater than $B"
else
        echo "$A less than $B"
fi
if [ "$B" > "$A" ]; then
        echo "$B greater than $A"
else
        echo "$B less than $A"
fi

echo "正确的方式1(\)"
if [ "$A" \> "$B" ]; then
        echo "$A greater than $B"
else
        echo "$A less than $B"
fi
if [ "$B" \> "$A" ]; then
        echo "$B greater than $A"
else
        echo "$B less than $A"
fi

echo "正确的方式2([[]])"
if [[ "$A" > "$B" ]]; then
        echo "$A greater than $B"
else
        echo "$A less than $B"
fi
if [[ "$B" > "$A" ]]; then
        echo "$B greater than $A"
else
        echo "$B less than $A"
fi

echo "============数值比较(-gt)============"
if [ "$A" -gt "$B" ]; then
        echo "$A greater than $B"
else
        echo "$A less than $B"
fi
if [[ "$B" -gt "$A" ]]; then
        echo "$B greater than $A"
else
        echo "$B less than $A"
fi

echo "============写错了变量引用============"
echo "在 [ 命令中，> 符号通常会被 Shell 先解释为重定向操作符（把输出写入文件）[ 非空字符串 ] 永远返回 真 (True)"
if [ "A" > "B" ]; then
        echo "A greater than B"
else
        echo "A less than B"
fi

echo "-gt 强制要求两边必须是整数"
if [ "A" -gt "B" ]; then
        echo "A greater than B"
else
        echo "A less than B"
fi