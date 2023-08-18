#!/bin/bash
#
# 使用git命令查询某次提交简要详情：作者、文件、统计数量
#
# 用法: ./git_query.sh commitd
#
# Author: hejian
# Date  : 2021.06.15
#
# Copyright (c) 2021 HanKin. All rights reserved.
#

# 1.入参
commitd="HEAD~1..HEAD"
author=`git config --get user.name`
if [ $# -eq 1 ];then
    commitd=$1
fi
if [ $# -eq 2 ];then
    commitd=$1
    author=$2
fi

git log ${commitd} --author="${author}" --pretty=tformat: --numstat | awk '{ add += $1 ; subs += $2 ; loc += $1 + $2 } END { printf "[${commitd}]　新增行数: %s 删除行数 : %s 总行数: %s\n",add,subs,loc }'













