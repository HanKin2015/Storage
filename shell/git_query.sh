#!/bin/bash
#
# 使用git命令查询某次提交简要详情：作者、文件、统计数量
#
# 用法: ./git_query.sh commitd
# 
# 使用stat参数就可以看见提交修改的数量
# git log --word-diff --author="zhangphil" --since="2018-04-16 00:00:01" --until="2018-04-16 12:00:00" -p --stat
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



# 合并
echo "统计结果" && git log --author="何健29996" --after="2018-04-16 00:00:01" --before="2021-06-16 12:00:00" --pretty=tformat: --numstat | gawk '{ add += $1 ; subs += $2 ; loc += $1 - $2 } END { printf "增加行数:%s 删除行数:%s 变化总行数:%s\n",add,subs,loc }' && echo "详情如下:" && git log --word-diff --author="何健29996" --since="2018-04-16 00:00:01" --until="2021-06-16 12:00:00" -p --stat

# 计算统计结果
git log --author="何健29996" --after="2018-04-16 00:00:01" --before="2021-06-16 12:00:00" --pretty=tformat: --numstat | gawk '{ add += $1 ; subs += $2 ; loc += $1 - $2 } END { printf "增加行数:%s 删除行数:%s 变化总行数:%s\n",add,subs,loc }'

# 输出详情
git log --word-diff --author="何健29996" --since="2018-04-16 00:00:01" --until="2021-06-16 12:00:00" -p --stat





