CC      = gcc
CPP     = g++
TARGET  = handle_udev_info
SRCS    = $(shell find . -maxdepth 1 -name "*.cpp")
SRCS    += $(shell find . -maxdepth 1 -name "*.c")
SRCS    += $(shell find ./third_library/cjson -maxdepth 1 -name "*.c")
SRCS    += $(shell find ./third_library/zlib -maxdepth 1 -name "*.c")
OBJS    = $(addsuffix .o,$(SRCS))
CFLAGS  = -g -Os
CPPFLAGS= -g -Os -std=c++11
LDFLAGS = -lm
INCLUDE = -I./third_library/cjson -I./third_library/zlib -I./third_library/cmdline
LIBS	= -L./third_library/zlib -lz -lpthread

all: clean $(TARGET)
	./$(TARGET)

$(TARGET):$(OBJS)
	$(CPP) $(LDFLAGS) -o $@ $^ $(INCLUDE) $(LIBS) 

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDE) $(LIBS) 

%.cpp.o:%.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $< $(INCLUDE) $(LIBS) 

clean:
	rm -rf $(TARGET) *.o
