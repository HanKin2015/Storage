#!/bin/bash

function install_lzo()
{
    echo "=================install lzo=======================\n"
    #安装lzo
    local zipFile="./lzo-2.09.tar.gz"
    local zipExt=".tar.gz"
    tar -zxvpf ${zipFile} -C .
    cd `dirname ${zipFile}`/`basename ${zipFile} ${zipExt}` &&
    local CRGS="'-Wno-error -fsigned-char' --enable-shared"
    ./configure CPPFLAGS=${CRGS} &&
    make install
    cd -
}

#install_lzo

function study_double_quote1()
{
	local x='12345'
	local y=213

	echo "x=${x} y=${y}"

	if [ ${x} -lt ${y} ]; then
		echo "x less than y"
	else
		echo "x greater than or equal y"
	fi

	if [ ${x} \< ${y} ]; then
		echo "x < y"
	else 
		echo "x >= y"
	fi
}

function study_double_quote2()
{
	local x='12345'
	local y=213

	echo "x=${x} y=${y}"

	if [ "${x}" -lt "${y}" ]; then
		echo "x less than y"
	else
		echo "x greater than or equal y"
	fi

	if [[ "${x}" < "${y}" ]]; then
		echo "x < y"
	else 
		echo "x >= y"
	fi
}

study_double_quote1
study_double_quote2




