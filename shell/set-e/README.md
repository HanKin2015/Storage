# 1、set -e
set -x用来在运行结果之前，先输出执行的那一行命令。
set -e从根本上解决了这个问题，它使得脚本只要发生错误，就终止执行。（有一个例外情况，就是不适用于管道命令）

set -e在添加的地方后才能执行遇到错误后就会退出。因此应该在文件开头加上set -e,这句语句告诉bash如果任何语句的执行结果不是true则应该退出。
```
[root@ubuntu0006:~/myservice-1.0] #./test.sh
+ grep -q hj /home/hello
+ [ 1 -eq 0 ]
+ echo file /home/hello has no 'hj' string
file /home/hello has no 'hj' string
+ set -e
+ grep -q hj /var/log/update_install.log
[root@ubuntu0006:~/myservice-1.0] #echo $?
1
[root@ubuntu0006:~/myservice-1.0] #bash test.sh
+ grep -q hj /home/hello
+ '[' 1 -eq 0 ']'
+ echo 'file /home/hello has no '\''hj'\'' string'
file /home/hello has no 'hj' string
+ set -e
+ grep -q hj /var/log/update_install.log
[root@ubuntu0006:~/myservice-1.0] #echo $?
1
```
