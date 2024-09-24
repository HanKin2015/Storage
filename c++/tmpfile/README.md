在C语言中，tmpnam、mkstemp 和 tmpfile 是用于创建临时文件的函数。它们各自有不同的用途和特点。

## 1、tmpnam
tmpnam 函数用于生成一个唯一的临时文件名。
注意：tmpnam 生成的文件名并不会自动创建文件，因此在多线程或多进程环境中可能会有竞争条件，导致文件名冲突。

已淘汰：Note: Avoid use of tmpnam(); use mkstemp(3) or tmpfile(3) instead.
警告： the use of `tmpnam' is dangerous, better use `mkstemp'

## 2、mkstemp
mkstemp 函数用于创建一个唯一的临时文件，并返回一个文件描述符。
```
#include <stdlib.h>

int mkstemp(char *template);
```
参数：template 是一个字符数组，包含一个唯一的文件名模板。模板必须以六个连续的 'X' 结尾，这些 'X' 会被替换为一个唯一的字符串以生成文件名。

注意：mkstemp 会创建并打开文件，因此避免了 tmpnam 的竞争条件问题。

## 3、tmpfile
tmpfile 函数用于创建一个临时文件，并返回一个指向该文件的 FILE 指针。
注意：tmpfile 创建的临时文件在关闭时会自动删除。

