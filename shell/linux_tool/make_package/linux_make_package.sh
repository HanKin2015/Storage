#!/bin/bash
#
# 文 件 名: linux_make_package.sh
# 文件描述: 制作简易安装包
# 作    者: HanKin
# 创建日期: 2024.01.15
# 修改日期：2024.01.15
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#
function lock_dir()
{
    exec 300<>"${g_workdir}/working.lock"
    flock -n 300 || {
        echo "write flock fail"
        echo "xxx"
        exit 1
    }
}

function unlock_dir()
{
    exec 300<>"${g_workdir}/working.lock"
    flock -u 300
    echo "unlock file ok, ${g_lockfile}"
}

install_file="xxxx.bin"
if [ -f ${install_file} ]; then
    rm -rf "${install_file}"
fi

dos2unix install.sh
zip -r xxxx.zip bin/ install.sh

dos2unix preinst.sh
cat preinst.sh xxxx.zip >> ${install_file}
if [ $? -ne 0 ]; then
    echo "failed"
    unlock_dir
    exit 1
fi
chmod a+x ${install_file}