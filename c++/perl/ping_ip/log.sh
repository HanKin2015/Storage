#!/bin/bash

# 日志打印
LOG()
{
    echo "`date` ${BASH_LINENO[0]}:${FUNCNAME[1]} $@"
}

LOG "hello world!"
