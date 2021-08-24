CC      = g++
TARGET  = test
SRCS    = $(shell find -name "*.cpp")
SRCS    += $(shell find -name "*.c")
OBJS    = $(addsuffix .o,$(SRCS))
CFLAGS  = -g -Os
LDFLAGS = -lm
LIBS    =  -std=c++11 -lgtest_main -lgtest -lpthread 

all: clean $(TARGET)
	./$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

test_log: test_log.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_log test_log.cpp

test_json_intf: test_json_intf.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_json_intf test_json_intf.cpp $(LIBS)

clean:
	rm -rf $(TARGET) *.o
	rm -rf test_log test.log
	rm -rf test_json_intf




