#!/system/bin/sh

succ_sum=0
succ_sum=$((succ_sum + 1))
succ_sum=$((succ_sum + 1))

if [ $succ_sum = 2 ] ;then
    echo "passed!"
else
    echo "failed!"
fi
echo $succ_sum

# 这种写法在这个特定场景下结果是对的，但严格来说是错的，属于"碰巧能跑"。
# [ 是 test 命令的别名，= 在里面做的是字符串比较，不是数值比较。
# [ $succ_sum = 2 ]   # 比较 "2" 和 "2"，字符串相等，返回 true
# 这只是因为两边恰好都是纯数字字符串，结果碰巧对了。

# 空值/空格风险需要添加双引号
# 如果变量有前导零，字符串比较会翻车
# 读你代码的人看到 = 会以为你在比较字符串，但你实际想比较的是数字，造成误解

# 用 -eq（POSIX 标准，兼容 sh）