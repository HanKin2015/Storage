#!/bin/bash

arr1=`echo $(seq 3 9) | awk '{print $5,$6,$7}'`
echo ${arr1}
for elem in ${arr1}
do
	echo ${elem}
done


arr2=`ps aux | grep smbd | awk '{print $2}'`
echo ${arr2}
for elem in ${arr2}
do
	echo ${elem}
done


echo $(seq 1 9) | awk '{ print $5,$6,$7}' | while read a b c
do
	echo -n "Loop times: "
	echo $a $b $c
	rep=$(ls -l $0|column -t)
	echo "$rep" | sed -n 's/\([^ ]*\)  \([^ ]*\)  \([^ ]*\)  \(.*\)/\1'"[${a}]"'\2'"[${b}]"'\3'"[${c}]"'\4/p'
done
echo $a $b $c
