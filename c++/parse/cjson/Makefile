CC 	= g++
TARGET 	= main.so
SRCS 	= $(shell find -name "*.cpp")
SRCS 	+= $(shell find -name "*.c")
OBJS 	= $(addsuffix .o,$(SRCS))
CFLAGS 	= -std=c++11 -fPIC -I.
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
