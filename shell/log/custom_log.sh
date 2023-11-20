#!/bin/bash
#
# 文 件 名: custom_log.sh
# 文件描述: 日志打印
# 作    者: HanKin
# 创建日期: 2023.11.20
# 修改日期：2023.11.20
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# 日志打印
LOG()
{
    # 这就是教训，单引号无法进行解析变量值，需要双引号
    echo 'BASH_LINENO: ${BASH_LINENO}'
    echo '${BASH_LINENO}'
    echo ${BASH_LINENO}

    echo '~~~~~~~~~~~~~~~~~~~~~~~~~~'

    echo "BASH_LINENO: ${BASH_LINENO}"
    echo "FUNCNAME   : ${FUNCNAME}"
    echo "MODULE_PID : ${MODULE_PID}"
    echo "MODULE_NAME: ${MODULE_NAME}"
    echo "@          : $@"

    echo '--------------------------'

    echo "${BASH_LINENO[0]}:${FUNCNAME[1]} $@" | logger -t "${MODULE_NAME}(${MODULE_PID})"

    echo '##########################'
}

LOG 'xinput map-to-output device to hdmi'

echo "BASH_LINENO: ${BASH_LINENO[0]}"
echo "FUNCNAME   : ${FUNCNAME[0]}"
echo "MODULE_PID : ${MODULE_PID}"
echo "MODULE_NAME: ${MODULE_NAME}"
echo "@          : $@"

test_log()
{
    echo "BASH_LINENO: ${BASH_LINENO}"
    echo "FUNCNAME   : ${FUNCNAME}"
    echo "MODULE_PID : ${MODULE_PID}"
    echo "MODULE_NAME: ${MODULE_NAME}"
    echo "@          : $@"

    echo "总共有 ${#FUNCNAME[@]} 个函数调用."
    echo "总共有 ${#BASH_LINENO[@]} 个不同的行数."

    func_cnt=${#FUNCNAME[@]}
    for((i=0; i<func_cnt; i++)); do
        echo ${FUNCNAME[$i]} ${BASH_LINENO[$i]}
    done
}

func1()
{
    echo "I am func1"
    test_log
}

func2()
{
    echo "I am func2"
    func1
    test_log
}

func2 "arg1" "arg2"

:<<EOF
输出结果：
BASH_LINENO: ${BASH_LINENO}
${BASH_LINENO}
26
~~~~~~~~~~~~~~~~~~~~~~~~~~
BASH_LINENO: 26
FUNCNAME   : LOG
MODULE_PID :
MODULE_NAME:
@          : xinput map-to-output device to hdmi
--------------------------
##########################
BASH_LINENO: 0
FUNCNAME   : main
MODULE_PID :
MODULE_NAME:
@          :
I am func2
I am func1
BASH_LINENO: 56
FUNCNAME   : test_log
MODULE_PID :
MODULE_NAME:
@          :
总共有 4 个函数调用.
总共有 4 个不同的行数.
test_log 56
func1 62
func2 66
main 0
BASH_LINENO: 63
FUNCNAME   : test_log
MODULE_PID :
MODULE_NAME:
@          :
总共有 3 个函数调用.
总共有 3 个不同的行数.
test_log 63
func2 66
main 0
EOF