.SUFFIXES:.cpp .o
CC=g++
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=main
start:$(OBJS)
		$(CC) -o $(EXEC) $(OBJS) -L../SO文件编译 -ltest
.cpp.o:
		$(CC) -Wall -g -o $(@) -c $<
clean:
		rm -f $(OBJS)
		rm -f core*
