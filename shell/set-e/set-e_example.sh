#!/bin/bash
#
# 文 件 名: set-e_example.sh
# 文件描述: 学习set -e参数
# 作    者: HanKin
# 创建日期: 2023.11.13
# 修改日期：2023.11.13
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# shell脚本报错即刻退出
# 开启: set -o errexit  (set -e)
# 关闭: set +o errexit  (set +e)

set -e

rm x

echo "hello world"

<<EOF
[root@ubuntu0006:~/cmake] #bash s.sh（默认情况下是关闭）
rm: 无法删除'x': 没有那个文件或目录
hello world
[root@ubuntu0006:~/cmake] #vi s.sh
[root@ubuntu0006:~/cmake] #bash s.sh（开启后即set -e）
rm: 无法删除'x': 没有那个文件或目录
[root@ubuntu0006:~/cmake] #
EOF