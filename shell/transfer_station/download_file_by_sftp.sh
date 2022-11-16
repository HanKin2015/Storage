#!/bin/bash
#
# 文 件 名: download_file_by_sftp.sh
# 文件描述: 通过sftp命令上传文件到服务器
# 作    者: HanKin
# 创建日期: 2022.10.12
# 修改日期：2022.10.12
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

#sftp服务器地址
host="10.70.22.178"
#端口
port=2210
sftp_user="test"
#密码
password="123456"

#下载到本地的目录
localDir="/sf/mx/small"
[ ! -d $localDir ] && mkdir -p $localDir
#sftp中待下载文件目录
remoteDir="C:\User\Administrator\Desktop\test"

#要下载的文件为
fileName="freeSSHd.exe"

lftp -u ${sftp_user},${password} sftp://${host}:${port}<<EOF
cd ${remoteDir}
lcd ${localDir} 
get $fileName
by
EOF

