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