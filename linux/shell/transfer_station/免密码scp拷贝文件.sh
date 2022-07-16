#!/bin/bash
#
# 文 件 名: 免输入密码scp拷贝文件.sh
# 文件描述: 免输入密码scp拷贝文件
# 注    意: 需要安装expect库
# 作    者: HanKin
# 创建日期: 2021.08.31
# 修改日期：2021.08.31
# 
# Copyright (c) 2021 HanKin. All rights reserved.
#

# 目标地址、用户、密码
IP=$1
USER='root'
PWD=$2

# 批量拷贝文件到同一个目录
LOCAL_FILES_PATH=(
	"/usr/bin/client/client"
	"/usr/bin/sever/server"
	"/usr/bin/study/study"
    )

for LOCAL_FILE_PATH in ${LOCAL_FILES_PATH[*]}
do
	expect -c "
	spawn scp  ${LOCAL_FILE_PATH} ${USER}@${IP}:/usr/local/bin
    expect \"password:\"
    send \"${PWD}\r\"
    expect eof
    "
done

# 单独拷贝文件到不同的目录
expect -c "
spawn scp /usr/bin/special ${USER}@${IP}:/usr/bin
expect \"password:\"
send \"${PWD}\r\"
expect eof
"

echo "all count equal 8"