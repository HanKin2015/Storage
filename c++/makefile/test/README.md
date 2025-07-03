# 1、ifeq 语句用于条件判断，不能直接执行命令
可以赋值使用，下列方式错误：
```
ifeq ($(ARCH), arm64)
    echo "arm64"
else
    echo "not arm64"
```
在 Makefile 中，echo 命令并不是直接在 ifeq 语句中执行的。

注意赋值语句不能写在像all、install这种section中：
```
ifeq ($(ARCH), arm64)
TARGET := arm64
else
TARGET := not arm64
endif

all:
	@echo $(TARGET)

ifeq ($(ARCH), arm64)
OUTPUT := $(shell echo "arm64")
else
OUTPUT := $(shell echo "not arm64")
endif

all:
	@echo $(OUTPUT)

错误演示
TARGET := hello

all:
	TARGET := world
	@echo $(TARGET)
# make
TARGET := hello
make: TARGET: No such file or directory
make: *** [Makefile:4: all] Error 127
```

# 2、:=和=
在 Makefile 中，变量赋值的方式有两种：:=（立即赋值）和 =（延迟赋值）。在你的例子中，使用 := 赋值会在解析时立即计算变量的值，而不是在执行时。

# 3、ifeq语句
demo见：Makefile.ifeq
```
make不指定则是从上到下执行
[root@ubuntu0006:~] #make
TARGET := not arm64
make: TARGET：命令未找到
Makefile:12: recipe for target 'wrong1' failed
make: *** [wrong1] Error 127
[root@ubuntu0006:~] #make wrong1
TARGET := not arm64
make: TARGET：命令未找到
Makefile:12: recipe for target 'wrong1' failed
make: *** [wrong1] Error 127

ifeq语句中不能有赋值语句，否则整体错误（从上面make: TARGET：命令未找到也能看出只能写命令）
[root@ubuntu0006:~] #make wrong2
make: Nothing to be done for 'wrong2'.
[root@ubuntu0006:~] #make wrong2
Makefile:21: *** missing separator。 停止。

ifeq语句前面不能存在空格或者tab键
[root@ubuntu0006:~] #make wrong3
ifeq (, arm64)
/bin/sh: 1: Syntax error: word unexpected (expecting ")")
Makefile:23: recipe for target 'wrong3' failed
make: *** [wrong3] Error 2
[root@ubuntu0006:~] #make wrong3 ARCH=1
ifeq (1, arm64)
/bin/sh: 1: Syntax error: word unexpected (expecting ")")
Makefile:23: recipe for target 'wrong3' failed
make: *** [wrong3] Error 2

正确演示
[root@ubuntu0006:~] #make right
touch b
[root@ubuntu0006:~] #make all
not arm64
```