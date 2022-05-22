CC      = gcc
CPP     = g++
TARGET  = test
SRCS    = $(shell find -name "*.cpp")
SRCS    += $(shell find -name "*.c")
OBJS    = $(addsuffix .o,$(SRCS))
CFLAGS  = -g -Os -Wold-style-declaration
CPPFLAGS= -g -Os -std=c++11
LDFLAGS = -lm
LIBS    = -pthread

all: clean $(TARGET)
	./$(TARGET)

$(TARGET):$(OBJS)
	$(CPP) $(LDFLAGS) -o $@ $^ $(LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $< $(LIBS)

%.cpp.o:%.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $< $(LIBS)

clean:
	rm -rf $(TARGET) *.o