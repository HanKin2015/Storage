#!/bin/bash
#
# 文 件 名: log.sh
# 文件描述: 安装包中执行文件
# 作    者: HanKin
# 创建日期: 2024.01.15
# 修改日期：2024.01.15
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

LOG_FILE="/tmp/make_package.log"
log()
{
    echo "$(date '+%Y-%m-%d %H:%M:%S.%3N') ${BASH_SOURCE[0]}($$):"\
      "${FUNCNAME[1]}:${BASH_LINENO[0]} $@" >> ${LOG_FILE}
}

# 模块名称
MODULE_NAME=`basename $0`
# 模块进程 ID
MODULE_PID=$$
# 日志打印
LOG()
{
    echo "`date "+%Y-%m-%d %H:%M:%S.%3N"` ${MODULE_NAME}(${MODULE_PID}): $@"
}

#检查是否日志过大
function loglimit()
{
	#6M 需要能保存最大文件，一天的量，限制为了防止异常过大
	MAXKSIZE=6000
	let MINKSIZE=${MAXKSIZE}/2
	if [ ${#} -ne 1 ]; then
		return 2;
	fi
	if ! test -e ${1} ; then
		return 1;
	fi
	CURKSIZE=`ls -l ${1} | awk '{print $5}'`
	let CURKSIZE/=1024
	#echo "loglimit $CURKSIZE"
	if [ ${CURKSIZE} -gt ${MAXKSIZE} ]; then
		let SKIPKSIZE=${CURKSIZE}-${MINKSIZE}
		#文件大小注意 和 上面的 MAXKSIZE 对应 6M，bs 大小影响速度 但是 bs大小要注意，不然出问题
		dd if=${1} of=/tmp/loglimit bs=1024 count=6000 skip=${SKIPKSIZE}
		echo ">>>>trunc<<<<"`date` >${1}
		cat /tmp/loglimit >>${1}
		LOG "rm SKIPKSIZE: ${SKIPKSIZE} ${1}"
		rm -f /tmp/loglimit
	fi
}

loglimit ${LOG_FILE}

LOG "begin" >> ${LOG_FILE} 2>&1
log "this is hahaha"