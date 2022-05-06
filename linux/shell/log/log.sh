#!/bin/bash
#
# 文 件 名: log.sh
# 文件描述: this is function script for shell log
# 作    者: HanKin
# 创建日期: 2021.08.27
# 修改日期：2021.08.27
# 
# Copyright (c) 2021 HanKin. All rights reserved.
#

CNONE='\033[00m' #\033[01;00m
CRED='\033[01;31m'
CGREEN='\033[01;32m'
CYELLOW='\033[01;33m'
CBLUE='\033[01;34m'
CPURPLE='\033[01;35m'
CCYAN='\033[01;36m'
CWHITE='\033[01;37m'

CBOLD='\033[1m'
CUNDERLINE='\033[4m'
CBLINK='\033[5m'

CWARN=$CPURPLE
CNOTICE=$CYELLOW
CNOTICE2=$CRED
CERROR=$CRED
CENTER=$CCYAN
CDFT=$CPURPLE
CFATAL=${CERROR}${CBLINK}
COK=$CGREEN
C0=$CNONE

# -e使转义字符生效(默认无)
# readlink读软链接下一层,readlink -f相当于realpath读取最终指向的文件
# 从Ubuntu 6.10开始,默认使用dash(theDebian Almquist Shell)而不是bash(the GNUBourne-Again Shell)
if [ -z "$CE" ] ; then
	if readlink /bin/sh | grep "bash\|dash" ; then
		CE="-e"
	else
		CE=""
	fi
fi

#wapper for CLOG_PRE
if [ -n "$CLOG_PRE" ] ; then
	CLOG_PRE_WAPPER=${C0}${CBOLD}${CLOG_PRE}
else
	CLOG_PRE_WAPPER=
fi

if [ ! -n "$CLOG_SWITCH" ]; then
	CLOG_SWITCH=1
fi

ltext()
{
	[ 1 -eq "$CLOG_SWITCH" ] && echo ${CE} "$*";
	[ -n "$CLOG_PATH" ] && [ x"$LOGFILE_SWITCH" != x"0" ] && echo ${CE} $* >> "$CLOG_PATH";
}

dots()
{
	seconds=${1:-3} # sleep 3 second by default

	for i in $(seq 0 1 $seconds) ; do 
		sleep 1;
		ltext -n '.';
	done
}

ltrace()
{
	ltext "${CBOLD}[T]${CLOG_PRE_WAPPER}${C0}$*";
}

lwarn()
{
	ltext "${CWARN}[W]${CLOG_PRE_WAPPER}${C0}$*";
}

lenter()
{
	ltext "${CENTER}[${CBLINK}_${C0}${CENTER}]${CLOG_PRE_WAPPER}${C0}$*";
}

lok()
{
	ltext "${COK}[O]${CLOG_PRE_WAPPER}${C0}$*";
}

lnotice()
{
	ltext "${CNOTICE}[N]${CLOG_PRE_WAPPER}${C0}$*";
}

lnotice2()
{
	ltext "${CNOTICE2}[N]${CLOG_PRE_WAPPER}${C0}$*";
}

lerror()
{
	ltext "${CERROR}[E]${CLOG_PRE_WAPPER}${C0}$*";
}

lfatal()
{
	exit_code=$1;
	shift;

	type cb_lexit > /dev/null 2>&1 && cb_lexit;

	ltext "${CFATAL}[F]${CLOG_PRE_WAPPER}${C0}$* exit${CERROR}($exit_code)${C0}!";

	if [ -f "${CLOG_DIE_PATH}" ];then
		local ret=""
		ret=$(cat ${CLOG_DIE_PATH})
		if [ x"$ret" != x"" ];then
			exit $exit_code;
		fi
	fi

	echo "$*">"${CLOG_DIE_PATH}"
	exit $exit_code;
}

lfataltimeout()
{
	time_out_seconds=$1;
	shift;
	exit_code=$1;
	shift;

	ltext "${CFATAL}[F]${CLOG_PRE_WAPPER}${C0}$*";
	ltext -n "\t$0 will exit${CERROR}($exit_code)${C0} in ${CNOTICE}${time_out_seconds}${C0} seconds ";
	dots $time_out_seconds;
	ltext "";

	exit $exit_code;
}

update_version_file()
{
	UPDATE_VERSION_FILE=/sf/cfg/update.version
	if [ -f $UPDATE_VERSION_FILE ]; then
		echo "update failed">$UPDATE_VERSION_FILE
	fi
}
die()
{
	lang=$(cat /etc/system.conf | grep 'lang=' | awk -F'=' '{print $2}')
	if [ x"en" = x"${lang}" ]; then
		return;
	fi
	update_result "$1" "fail" "$2"
	lfatal $*;
}
die_en()
{
	lang=$(cat /etc/system.conf | grep 'lang=' | awk -F'=' '{print $2}')
	if [ x"en" != x"${lang}" ]; then
		return;
	fi
	update_result "$1" "fail" "$2"
	lfatal $*;
}

# 导出函数
export -f ltext
export -f dots
export -f ltrace
export -f lwarn
export -f lenter
export -f lok
export -f lnotice
export -f lnotice2
export -f lerror
export -f lfatal
export -f die
export -f die_en