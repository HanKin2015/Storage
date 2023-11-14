#!/bin/bash
#
# 文 件 名: template.sh
# 文件描述: 模板
# 作    者: HanKin
# 创建日期: 2023.11.13
# 修改日期：2023.11.13
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# 脚本参数
set -euxo pipefail

# 全局变量

# 显示打包脚本的具体版本信息
show_version()
{
    echo "version: 1.0"
}

show_help()
{
    cat<<EOF
用法: ${0} [options]

选项：    
  -h,   显示帮助信息
  -V,   显示当前命令版本
  -d pack_dir     打包目录名（具体见特别说明）
  -v version      基础版本号
EOF
}

# 加写锁
write_lock()
{
    exec 200<>${g_lockfile}
    flock -n 200 || {
        echo "write flock fail, ${g_lockfile}, wating ..."
        flock 200
    }
}

# 加读锁
read_lock()
{
    exec 200<>${g_lockfile}
    flock -n -s 200 || {
        echo "read flock fail, ${g_lockfile}, wating ..."
        flock 200
    }
}

# 解锁, 如果不手动解锁，则进程结束后，自动解锁
unlock()
{
    exec 200<>${g_lockfile}
    flock -u 200
}

# 判断一个变量是否是数字
# 返回值: 0, 非数字; 1, 纯数字
is_number()
{
    if [ "$1x" = "0x" ]
    then
        return 1
    fi
    echo "$1" | grep -E "^[1-9][0-9]*$" > /dev/null
    if [ $? -eq 0 ]
    then
        return 1
    fi

    return 0
}

# Usage: get_value_from_conf conf_file key
# 忽略 # 开头的内容
get_value_from_conf()
{
    local conf="$1"
    local key="$2"

    if [ ! -f "${conf}" ]; then
        return 1
    fi

    cat "${conf}" | grep -v ^\# | grep "^${key}=" | awk 'BEGIN{FS="="} {print $2}'
    return 0
}

# Usage: convert_file_encoding conf_file
# 如果原先编码为ISO-8859，则转换文件编码为UTF-8，且为unix换行
convert_file_encoding()
{
    local tmpfile="$1"
    if [ ! -f "${tmpfile}" ];then
        echo "file not exist, ${tmpfile}"
        return 1
    fi

    file "${tmpfile}" | grep -q "ISO-8859"
    if [ $? -eq 0 ];then
        iconv -f gbk -t utf-8 "${tmpfile}" -o  "${tmpfile}"
        echo "convert to utf-8 ok, ${tmpfile}"
    fi

    file "${tmpfile}" | grep -q "CRLF line terminators"
    if [ $? -eq 0 ];then
        dos2unix "${tmpfile}"
        echo "dos2unix ok, ${tmpfile}"
    fi
    return 0
}

# 解析用户传递的参数
while getopts "hVd:s:N" arg
do
    case $arg in
        h)
            show_help
            exit 0
            ;;
        V)
            show_version
            exit 0
            ;;
        d)
            g_dirname="$OPTARG"
            ;;
        s)
            g_url="$OPTARG"
            ;;
        N)
            g_build=1
            ;;
        ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            show_help
            exit 1
            ;;
    esac
done

# 检查参数合法性
check_args
if [ $? -eq 1 ]
then
    echo "check argument fail"
    show_help
    exit 1
fi

show_args

# 修改配置文件的锁，避免异步修改配置文件
g_lockfile=/var/lock/metainfo.lock

exit 0
