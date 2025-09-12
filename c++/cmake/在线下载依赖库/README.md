# FetchContent运行结果
```
root@hankin:~/opencv# mkdir build
root@hankin:~/opencv# cd build/
root@hankin:~/opencv/build# cmake ..
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done

-- {fmt} version: 11.2.0
-- Build type: 
-- Configuring done (10.8s)
-- Generating done (0.0s)
-- Build files have been written to: /root/opencv/build
root@hankin:~/opencv/build# 
root@hankin:~/opencv/build# ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  _deps  Makefile
root@hankin:~/opencv/build# make
[ 20%] Building CXX object _deps/fmt-build/CMakeFiles/fmt.dir/src/format.cc.o
[ 40%] Building CXX object _deps/fmt-build/CMakeFiles/fmt.dir/src/os.cc.o
[ 60%] Linking CXX static library libfmt.a
[ 60%] Built target fmt
[ 80%] Building CXX object CMakeFiles/myapp.dir/main.cpp.o
[100%] Linking CXX executable myapp
[100%] Built target myapp
root@hankin:~/opencv/build# ./myapp 
Hello, world!
The answer is 42.
I'd rather be happy than right.
Date and time: 2025-09-12 04:14:58.740003174
Time: 04:14
[1, 2, 3]
```