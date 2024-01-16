#!/bin/bash
#
# 文 件 名: install.sh
# 文件描述: 安装脚本
# 作    者: HanKin
# 创建日期: 2024.01.15
# 修改日期：2024.01.15
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#
function install()
{
    dos2unix ./bin/log.sh
    chmod a+x ./bin/log.sh
    ./bin/log.sh
}

function uninstall()
{
    if [ -d ./bin/ ];then
        rm -rf ./bin/
    fi
}

case $1 in
install)
    install
;;
uninstall)
    uninstall
;;
*)
    echo "param is invalid"
;;
esac
