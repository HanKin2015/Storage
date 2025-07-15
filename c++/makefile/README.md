系统学习见study文件夹

万能模板，几乎复制粘贴即可使用。
```
CC 	= $(GCC_PREFIX)g++
TARGET 	= libExUtils.so
SRCS 	= $(shell find -name "*.cpp")
SRCS 	+= $(shell find -name "*.c")
OBJS 	= $(addsuffix .o,$(SRCS))
CFLAGS 	= -std=c++11 -fPIC -I. $(GLOBAL_CFLAGS)
LDFLAGS	= -shared

all:$(TARGET)	
	
$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<
		     
%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
	
clean:
	rm -rf $(TARGET) *.o
```

## 新弄了一个arm架构上使用libusb库的Makefile
```
CC            = aarch64-linux-gnu-g++
CPP           = aarch64-linux-gnu-g++ -E
TARGET        = device_helper_debian10
SRCS          = $(wildcard ./*c ./*.cpp)
OBJS          = $(addsuffix .o,$(SRCS))
CFLAGS        = -g -Wall -std=c++11
INC	          = -I ./include/
LIBUSB_CFLAGS = -I/home/ubuntu/src/out/debian10/arm64/root/usr/include/libusb-1.0
LIBUSB_LIBS   = -L/home/ubuntu/src/out/debian10/arm64/root/usr/lib -lusb-1.0

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBUSB_LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) $(INC) $(LIBUSB_CFLAGS) -o $@ $<

%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) $(INC) $(LIBUSB_CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o
```

## .PHONY
在 Makefile 中，.PHONY 是一个特殊的目标（target），用于声明伪目标（phony target）。其核心作用是避免目标名称与文件冲突，并优化执行逻辑。

特性			普通目标						.PHONY 声明的目标
依赖检查		检查依赖文件是否更新			不检查依赖，总是执行命令
同名文件冲突	若存在同名文件，可能不执行		强制执行，不受同名文件影响
时间戳比较	比较目标与依赖的时间戳		跳过时间戳比较
典型用途		生成文件（如编译目标）		执行命令（如清理、测试）

.PHONY 是 Makefile 中用于声明伪目标的特殊标记，其核心作用是：
- 避免与同名文件冲突，确保目标命令总是执行。
- 优化性能，跳过不必要的时间戳检查。
- 提高可读性，明确标识 “非文件生成” 类目标。