# 杀死该死的compton进程
# 真是蠢哭了，为啥不使用pidof

#!/bin/bash

function check(){
	local a="$1"
	printf "%d" "$a" &>/dev/null && echo "integer" && return
	printf "%d" "$(echo $a|sed 's/^[+-]\?0\+//')" &>/dev/null && echo "integer" && return
	printf "%f" "$a" &>/dev/null && echo "number" && return
	[ ${#a} -eq 1 ] && echo "char" && return
	echo "string"
}


ps aux | grep compton

ps aux | grep compton | awk '{print $2,$11,$12}'

#pids=`ps aux | grep compton | awk '{print $2}' | sed -n '1,$p'`
pids=`ps aux | grep compton | awk '{print $2}'`

echo ${pids}
echo 'pids type: ' $(check ${pids})

for pid in ${pids}
do
    echo ${pid}
	#kill -9 ${pid}
	#top -p ${pid}
	ps aux | grep ${pid}
done


# 首先其中一个是当前文件执行进程，另外一个是grep进程，还有一个也是当前文件执行进程
#hj=`ps aux | grep kill | awk '{print $2}'`
hj=`ps aux | grep kill`
echo 'lalalala:' ${hj}

