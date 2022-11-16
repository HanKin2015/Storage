#! /bin/bash

file_path="/var/log/hj.json"
dir_path="/var/log"

if [ -f $file_path ]
then
	echo "-f $file_path exist!"
else
	echo "-f $file_path not exist!"
fi

if [ -f $dir_path ]
then
	echo "-f $dir_path exist!"
else
	echo "-f $dir_path not exist!"
fi

if [ -d $file_path ]
then
	echo "-d $file_path exist!"
else
	echo "-d $file_path not exist!"
fi

if [ -d $dir_path ]
then
	echo "-d $dir_path exist!"
else
	echo "-d $dir_path not exist!"
fi

if [ -e $file_path ]
then
	echo "-e $file_path exist!"
else
	echo "-e $file_path not exist!"
fi

if [ -e $dir_path ]
then
	echo "-e $dir_path exist!"
else
	echo "-e $dir_path not exist!"
fi

echo -e "\n-e filename 如果 filename存在，则为真
-d filename 如果 filename为目录，则为真
-f filename 如果 filename为常规文件，则为真
-L filename 如果 filename为符号链接，则为真
-r filename 如果 filename可读，则为真
-w filename 如果 filename可写，则为真
-x filename 如果 filename可执行，则为真
-s filename 如果文件长度不为0，则为真
-h filename 如果文件是软链接，则为真"
