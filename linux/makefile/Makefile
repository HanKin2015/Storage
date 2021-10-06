ifeq (Linux,$(shell uname -s))
UT_EXE=oj_unittest
else
UT_EXE=oj_unittest.exe
endif

ifeq ($(DEBUG),1)
DBGFLAGS=-D_DEBUG
else
DBGFLAGS=
endif


all: test main

test:
	cat header_c.h header_c_plus_plus.h sum.h sum.c main.c > main.cpp; \

main: main.cpp
	g++ main.cpp -o main

clean:
	rm main.cpp main

help:
	@echo help informations.
	@echo $(UT_EXE)

.PHONY: test all main clean
