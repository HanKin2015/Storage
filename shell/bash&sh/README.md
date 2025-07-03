# bash和sh的区别

## 1、比较符号=和==
```
[root@ubuntu0006:~/myservice-1.0] #./test.sh
./test.sh: 5: [: hello: unexpected operator
not equal
not equal
./test.sh: 17: ./test.sh: [[: not found
not equal
[root@ubuntu0006:~/myservice-1.0] #bash test.sh
not equal
not equal
not equal
```