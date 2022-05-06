#!/bin/bash

# 日志打印
LOG()
{
    echo "${BASH_LINENO[0]}:${FUNCNAME[1]} $@" | logger -t "${MODULE_NAME}(${MODULE_PID})"
}

LOG 'xinput map-to-output device to hdmi'

export DISPLAY=":0"
output_name=`xrandr | grep "HDMI" | awk '{print $1}'`
id=`xinput | grep "ILITEK ILITEK-TP" | awk '{print $5}' | awk -F = '{print $2}'`
xinput map-to-output $id $output_name
