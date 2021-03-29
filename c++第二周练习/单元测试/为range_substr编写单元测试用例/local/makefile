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

test:
	cat prepend.c template.c append.c > oj_unittest.c;	\
	gcc $(DBGFLAGS) -g -fprofile-arcs -ftest-coverage -std=c99 -Wall -o $(UT_EXE) oj_unittest.c;	\
	./$(UT_EXE) > oj_unittest.out;								\
	gcov -o oj_unittest.exe oj_unittest.c;						\
	diff -w test1.out oj_unittest.out > /dev/null;				\
	if [ $$? -ne 0 ]; then										\
		echo "REJECTED";										\
		exit 1;													\
	else														\
		echo "PASSED";											\
		exit 0;													\
	fi															\

clean: 
	rm -f oj_unittest oj_unittest.out oj_unittest.c oj_unittest.exe
	rm -f *.gcov *.gcda *.gcno

.PHONY: test clean

