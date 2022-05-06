#!/bin/sh
#
# 统计git仓库代码提交数量
#
# 用法: ./get_static_commit.sh 2021-3-3 2021-7-7 build
#
# author: hankin
# date  : 2021.07.06
#
# Copyright (c) 2021 hankin. All rights reserved.
#

# git目录
dir_list=$3

# 创建统计表
commit_file="commit.txt";
if [ -f $commit_file ]; then
        rm $commit_file
fi
touch $commit_file

# 循环目录
for dir in $dir_list
do
        echo "project:$dir"
        cd $dir
        if [ $? -eq 0 ]; then
                # 同步代码
                git pull >/dev/null

                # 统计代码信息
                git log --pretty=format:%H,%ai,%an,%s --no-merges --since=$1 --until=$2 --numstat |awk -F, 'BEGIN{hash="";author=""; date="";comment="";}{if (NF>=4) {gsub(/ /,"_",$0);hash=$1; date=substr($2,1,19); author=$3; comment=$4;} else if (NF>0) print hash"\t" date "\t" author"\t" comment "\t" $0;}' |awk '{hash[$1] = $1; author[$1] = $3; date[$1] = $2; comment[$1] = $4; file[$1] += 1; add[$1] += $5; del[$1] += $6; fileName[$1] = fileName[$1]","$7} END{for (i in hash) {printf "%s \t %s \t %s \t %s \t %d \t %d \t %d \n",hash[i],author[i],comment[i],date[i],add[i],del[i],file[i]}}' >> ../$commit_file;

                #返回上级目录
                cd ..
        fi
done

# 输出结果
echo "-----------------------------------"
awk 'BEGIN{printf "开发者\t\t提交次数\t新增代码行数\t删除代码行数\t改动文件数\n"}'
awk '{author[$2] = $2; commit[$2] += 1; add[$2] += $5; del[$2] += $6; file[$2] += $7;}END{for (i in author){ printf "%s\t%d\t\t%d\t\t%d\t\t%d\n",author[i],commit[i],add[i],del[i],file[i]}}' $commit_file | sort -k 2 -n -r ;
