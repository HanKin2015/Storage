CC    = cc
LIBS  = -L./ -lz -lstdc++
CFLAGS= -O -I../..
WARN_CFLAGS= -Wall

TEST_ZLIB_OBJS = test_zlib.o zip.o unzip.o ioapi.o

.c.o:
	$(CC) -c $(CFLAGS) $(WARN_CFLAGS) $*.c $(LIBS)

.cpp.o:
	$(CC) -c $(CFLAGS) $(WARN_CFLAGS) $*.cpp $(LIBS) 

all: test_zlib

test_zlib:  $(TEST_ZLIB_OBJS)
	$(CC) $(CFLAGS) $(WARN_CFLAGS) -o $@ $(TEST_ZLIB_OBJS) $(LIBS)

test:   test_zlib
	./test_zlib test readme.txt
	./test_zlib -l test.zip
	mv readme.txt readme.old
	./test_zlib test.zip

clean:
	/bin/rm -f *.o *~ test_zlib
