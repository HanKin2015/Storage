#!/bin/bash

if grep -q hello data.txt ; then 
	echo "data.txt has word 'hello'"
else 
	echo "data.txt has not word 'hello'"
fi 


if grep -q world data.txt; then
	echo "data.txt has word 'world'"
else 
	echo "data.txt has not word 'world'"
fi

success=0
if echo ${success} ; then
	echo yes
else
	echo no
fi
