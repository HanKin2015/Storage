#!/bin/bash
echo "=== Step 1: Compile shared library (libtest_shared.so) ==="
gcc -fPIC -shared -Wl,-Bsymbolic test.c -o libtest_shared.so
echo "=== Step 2: Compile static library (libtest.a) ==="
gcc -c test.c -o test.o
ar rcs libtest.a test.o
echo "=== Step 3: Compile main program (mixing static and dynamic) ==="

# 注意链接顺序：先动态 (-ltest_shared)，再强制静态 (-Wl,-Bstatic -ltest)，再切回动态

gcc main.c -L. -Wl,-Bstatic -ltest -Wl,-Bdynamic -ltest_shared -ldl -o main -Wl,-rpath,'\(ORIGIN'
echo "=== Build complete! Running... ==="
./main