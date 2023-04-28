参考：https://blog.csdn.net/qq_33832591/article/details/52288255
详见：D:\Github\GitBook\gitbook\C++\makefile.md

发现编译出来的so文件没有SONAME，我在D:\Github\Storage\linux\神奇的软链接\README.md文件中提到使用ldconfig命令，需要使用到SONAME参数。

如果编译的共享库没有指定 SONAME，那么在使用 ldconfig 命令更新共享库缓存时，ldconfig 可能会将共享库的路径记录在缓存文件中，而不会记录共享库的 SONAME。这可能会导致程序在链接共享库时出现问题。

为了解决这个问题，您可以在编译共享库时指定 SONAME。在使用 gcc 编译共享库时，可以使用 -Wl,-soname,<SONAME> 选项来指定共享库的 SONAME。例如：
```
gcc -shared -Wl,-soname,libfoo.so.1 -o libfoo.so.1.0.0 foo.o bar.o
```

如果您已经编译了共享库，但是没有指定 SONAME，可以使用 objcopy 命令来添加 SONAME。例如：
```
objcopy --add-soname libfoo.so.1 libfoo.so.1.0.0
```
objcopy命令添加失败了，使用objcopy -soname libfoo.so.1 libfoo.so.1.0.0也失败了，可能是版本低的原因吧。
strip 命令是 GNU binutils 工具集中的一个工具，用于去除目标文件中的符号表、调试信息等，以减小文件大小。strip 命令不支持添加 SONAME，但是您可以使用 objcopy 命令来添加 SONAME，然后再使用 strip 命令去除符号表和调试信息。

```
.SUFFIXES:.c .o
CC=gcc
SRCS=libtest.c
OBJS=$(SRCS:.c=.o)
EXEC=libtest.so
all:$(OBJS)
		$(CC) -shared -Wl,-soname,libtest.so -o $(EXEC) $(OBJS)
.c.o:
		$(CC) -Wall -g -fPIC -o $(@) -c $<
clean:
		rm -f $(OBJS)
		rm -f core*
```

然后就可以了：
```
[root@ubuntu0006:~/hh] #readelf -a libtest.so | grep SONAME
 0x000000000000000e (SONAME)             Library soname: [libtest.so]
```