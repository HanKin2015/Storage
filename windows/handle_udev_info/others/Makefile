CC      = g++
TARGET  = test
SRCS    = $(shell find -name "*.cpp")
SRCS    += $(shell find -name "*.c")
OBJS    = $(addsuffix .o,$(SRCS))
CFLAGS  = -g -Os
LDFLAGS = -lm

all: clean $(TARGET)
	./$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o