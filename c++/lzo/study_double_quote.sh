#
# $*以一个单字符串显示所有向脚本传递的参数
# 如果"$*"用双引号括起来则以"$1 $2 ... $n"的形式输出所有参数
#

#!/bin/bash

function problematic_code()
{
	echo $1

	echo '------------------------'

	for i in $*; do
		echo $i
	done

	echo '------------------------'

	for i in $@; do
		echo $i
	done
}


function correct_code()
{
	echo "$1"
	
	echo '------------------------'

	for i in "$*"; do
		echo "$i"
	done

	echo '------------------------'

	for i in "$@"; do
		echo "$i"
	done
}

problematic_code 1 2 3 4

echo '############################'

correct_code 1 2 3 4 5 6

