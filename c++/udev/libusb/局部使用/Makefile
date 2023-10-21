CC            = aarch64-linux-gnu-g++
CPP           = aarch64-linux-gnu-g++ -E
TARGET        = device_helper_debian10
SRCS          = $(wildcard ./*c ./*.cpp)
OBJS          = $(addsuffix .o,$(SRCS))
CFLAGS        = -g -Wall -std=c++11
INC	          = -I ./include/
LIBUSB_CFLAGS = -I/home/ubuntu/src/out/arm64/root/usr/include/libusb-1.0
LIBUSB_LIBS   = -L/home/ubuntu/src/out/arm64/root/usr/lib -lusb-1.0

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBUSB_LIBS)

%.c.o:%.c
	$(CC) -c $(CFLAGS) $(INC) $(LIBUSB_CFLAGS) -o $@ $<

%.cpp.o:%.cpp
	$(CC) -c $(CFLAGS) $(INC) $(LIBUSB_CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o
