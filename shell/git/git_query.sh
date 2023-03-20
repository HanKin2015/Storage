#!/bin/bash
#
# 文 件 名: git_query.sh
# 文件描述: 使用git命令查询某次提交简要详情：作者、文件、统计数量
# 用    法: ./git_query.sh commitd
#
# 使用stat参数就可以看见提交修改的数量
# git log --word-diff --author="zhangphil" --since="2018-04-16 00:00:01" --until="2018-04-16 12:00:00" -p --stat
#
# 注 意 点: subs这个变量不能修改成sub，修改后执行会变错
# 作    者: HanKin
# 创建日期: 2021.06.15
# 修改日期：2021.03.23

# Copyright (c) 2022 HanKin. All rights reserved.
#

# 1.入参(作者名)
commitd='HEAD~1..HEAD'              # commit
author=`git config --get user.name` # 作者
after='2018-04-16 00:00:01'         # 起始时间
before='2021-06-16 12:00:00'        # 结束时间

if [ $# -eq 1 ];then
    commitd=$1
fi
if [ $# -eq 2 ];then
    commitd=$1
    author=$2
fi

# 计算某次提交结果
function compute_one_commitd
{
    git show ${commitd} --author="${author}" --pretty=tformat: --numstat | awk '{ add += $1 ; subs += $2 ; sum += $1 + $2 } END { printf "[${commitd}]　新增行数: %s 删除行数 : %s 总行数: %s\n",add,subs,sum }'
}

# 计算从某次提交结果到仓库建立时(去掉commitd就是统计整个仓库某作者的上库统计)
function compute_from_commitd_to_init
{
    git log ${commitd} --author="${author}" --pretty=tformat: --numstat | awk '{ add += $1 ; subs += $2 ; sum += $1 + $2 } END { printf "[${commitd}]　新增行数: %s 删除行数 : %s 总行数: %s\n",add,subs,sum }'
}

# 计算某个时间段某作者的上库统计
function compute_time_period
{
    echo "统计结果" && git log --author=${author} --after=${after} --before=${before} --pretty=tformat: --numstat | gawk '{ add += $1 ; subs += $2 ; sum += $1 + $2 } END { printf "增加行数:%s 删除行数:%s 总行数:%s\n",add,subs,sum }'
}

# 输出某个时间段详情
function echo_time_period_detail
{
    git log --word-diff --author="何健xxxxx" --since="2018-04-16 00:00:01" --until="2021-06-16 12:00:00" -p --stat
}

# 版本转测统计模块代码量
compute_time_period

