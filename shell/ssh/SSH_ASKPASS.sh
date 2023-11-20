#!/bin/bash
#
# 文 件 名: SSH_ASKPASS.sh
# 文件描述: ssh免密码输入，无需借助sshpass工具
# 备    注: https://qa.1r1g.com/sf/ask/854181121/
# 作    者: HanKin
# 创建日期: 2023.11.20
# 修改日期：2023.11.20
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# create a file that echo's out your password .. you may need to get crazy with escape chars or for extra credit put ASCII in your password...
echo "echo 1" > /tmp/1
chmod 777 /tmp/1

# sets some vars for ssh to play nice with something to do with GUI but here we are using it to pass creds.
export SSH_ASKPASS="/tmp/1"
export DISPLAY=YOURDOINGITWRONG # 这个后面的词语随便写，但是这一行必须要，真的神奇
setsid ssh root@172.22.16.1 -p 22