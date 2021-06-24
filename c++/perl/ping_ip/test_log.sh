#!/bin/bash

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
    echo "${BASH_LINENO[0]}:${FUNCNAME[1]} $@" | logger -t "hankin" 

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






