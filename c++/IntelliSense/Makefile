CC 	= $(GCC_PREFIX)g++
TARGET 	= a.out
SRCS 	= $(shell find -name "*.cpp")
SRCS 	+= $(shell find -name "*.c")
OBJS 	= $(addsuffix .o,$(SRCS))
INCLUDE = -Iinclude/include
CFLAGS 	= -std=c++11 -fPIC $(INCLUDE) $(GLOBAL_CFLAGS)
LDFLAGS	= 

all:$(TARGET)	
	
$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<
		     
%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
	
clean:
	rm -rf $(TARGET) *.o