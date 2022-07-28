#!/bin/bash

#将拷贝文件修改同名称，可以将所有需要拷贝的文件全部添加至document_name，
document_name="./1.txt ./2.txt ./3.txt"

for i in $document_name
do
#查看拷贝文件大小
memory=$(du -h $i | awk -F "M|K|G" '{print $1}') 
memory1=$(du -h $i| awk -F " " '{print $1}') 

echo "document memort :"$memory1

#拷贝开始时间
time1=$(date +%s)
echo "Start Time : "$time1

#输入拷贝路径
cp -r  $i  $1


#拷贝结束时间
time2=$(date +%s)
echo "End Time : "$time2

#输出时间差
time3=`expr $time2 - $time1`
echo "Interval Time : "$time3"s"

#输出拷贝文件速度
echo "copying speed :"`expr $memory / $time3`

echo "==========================="
sleep 3
done
rm -r ./*txt*
