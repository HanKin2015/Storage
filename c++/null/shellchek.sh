#!/bin/bash

# 1、错误的示例
function wrong_usage()
{
	for dir in */ c/ a/
	do
		echo ${dir}
		cd ${dir}
		echo "do something in $PWD"
		cd ..
		#cd -
	done
	echo "now I am in $PWD"
}

# 2、正确的示例1
function right_usage1()
{
	for dir in */ c/ a/
	do
		echo ${dir}
		cd ${dir} || exit 
		echo "do something in $PWD"
		cd ..
		#cd -
	done
	echo "now I am in $PWD"
}

# 3、正确的示例2
function right_usage2()
{
	for dir in */ c/ a/
	do
		(
		echo ${dir}
		cd ${dir}
		echo "do something in $PWD"
		)
	done
	echo "now I am in $PWD"
}

function test1()
{
	cd a/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
	
	echo "HOME value is ${HOME}"
	# 对于全局变量值
	HOME="hankin"
	echo "HOME value is ${HOME}"
	
	cd c/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
	
	cd a/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
}

function test2()
{
	cd a/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
	
	echo "HOME value is ${HOME}"
	(
	# 对于全局变量值
	HOME="hankin"
	echo "HOME value is ${HOME}"

	cd c/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
	)
	echo "HOME value is ${HOME}"

	cd a/
	echo "do something in $PWD"
	cd ..
	echo "now I am in $PWD"
}

#wrong_usage
#right_usage1
#right_usage2
test1
#test2
echo "HOME value is ${HOME}"
