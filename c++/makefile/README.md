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
```