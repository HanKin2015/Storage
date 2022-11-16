#!/bin/bash
#
# 文 件 名: upload_file_by_sftp.sh
# 文件描述: 通过sftp命令上传文件到服务器
# 作    者: HanKin
# 创建日期: 2022.10.12
# 修改日期：2022.10.12
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

#sftp服务器地址
host="10.70.202.241"
#端口
port=22
sftp_user="root"
#密码
password="123456"

#下载到本地的目录
localDir="D:/Tools/upan_auto_copy"
[ ! -d $localDir ] && mkdir -p $localDir
#sftp中待下载文件目录
remoteDir="/sf/log"

#要下载的文件为
fileName="upan_auto_copy.exe"

sftp ${sftp_user}@${host}<<EOF
cd ${remoteDir}
lcd ${localDir} 
put $fileName
EOF

