#!/bin/bash
# ------------------------------------------
# Filename    : test.sh
# Version     : 1.0
# Date        : 2023-9-20 18:30:23
# Author      : 农民工老王@CSDN
# Email       : scwja@qq.com
# Website     : https://blog.csdn.net/monarch91
# Description : 国际化测试shell
# ------------------------------------------
export TEXTDOMAINDIR="./locale"
export TEXTDOMAIN="laowangtest"

getStr(){
  gettext -e -s "$1"
}

printf_loc(){
  local myStr=$(getStr "$1")
  shift
  printf "${myStr}\n" "$@"
}

printf_loc "WELCOME_WORDS"
printf_loc "INTRODUCE"  Laowang  32
