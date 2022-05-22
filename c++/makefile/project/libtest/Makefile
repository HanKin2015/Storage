.SUFFIXES:.c .o
CC=gcc
SRCS=test.c
OBJS=$(SRCS:.c=.o)
EXEC=libtest.so

all:$(OBJS)
	$(CC) -shared -o  $(EXEC) $(OBJS)

.c.o:
	$(CC) -Wall -g -fPIC -o $(@) -c $<

clean:
	rm -f $(OBJS)
	rm -f core*

