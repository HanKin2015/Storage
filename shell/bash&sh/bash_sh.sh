#!/bin/sh
#
# 文 件 名: bash_sh.sh
# 文件描述: bash和sh之间的巨大区别
# 作    者: HanKin
# 创建日期: 2025.06.30
# 修改日期：2025.06.30
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

NAME="hello"

if [ "${NAME}" == "world" ]; then
    echo "equal"
else
    echo "not equal"
fi

if [ "${NAME}" = "world" ]; then
    echo "equal"
else
    echo "not equal"
fi

if [[ "${NAME}" == "world" ]]; then
    echo "equal"
else
    echo "not equal"
fi