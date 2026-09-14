[root@HANKIN ~]$ sh hj.sh
hj.sh: 第 10 行:local: a: 只读变量
hj.sh: 第 11 行:local: b: 只读变量
321
1
1
declare -- c="123"
[root@HANKIN ~]$ cat hj.sh
#!/bin/bash
readonly a=1
declare -r b=11
function test ()
{
    # 这一步创建局部变量失败，但是不阻止后面执行，所以输出 1
    local -r a=2
    local b=33

    # 这一步会终止脚本的后面执行
    #a=3
    #b=22
    echo $a
}

test
echo $a


# 只读变量
declare -r x=10
x=20   # 报错，只读不能改

# 整数变量
declare -i num=5
num="abc" # 报错，只能数字

# 数组
declare -a arr=(1 2 3)

# 关联数组（key-value）
declare -A dict
dict["name"]="hankin"
