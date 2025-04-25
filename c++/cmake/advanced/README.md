# 学习cmake

## 1、学习
- 不区分大小写

## 2、更多详情
D:\Github\GitBook\gitbook\C++\cmake.md

## 3、运行结果
mkdir build
cmake ..
make

版本要求过高：
```
[root@ubuntu0006:~/cmake] #ll
总用量 16
drwxr-xr-x  2 root root 4096 5月  22 10:42 ./
drwx------ 37 root root 4096 5月  22 10:41 ../
-rw-r--r--  1 root root  434 5月  22 10:40 cmake_example.cpp
-rw-r--r--  1 root root  103 5月  22 10:41 CMakeLists.txt
[root@ubuntu0006:~/cmake] #mkdir build
[root@ubuntu0006:~/cmake] #cd build/
[root@ubuntu0006:~/cmake/build] #cmake ..
CMake Error at CMakeLists.txt:1 (cmake_minimum_required):
  CMake 3.10 or higher is required.  You are running version 3.5.1


-- Configuring incomplete, errors occurred!
```

修改版本要求：
```
[root@ubuntu0006:~/cmake/build] #vi ../CMakeLists.txt
[root@ubuntu0006:~/cmake/build] #cmake ..
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/build
[root@ubuntu0006:~/cmake/build] #ll
总用量 36
drwxr-xr-x 3 root root  4096 5月  22 10:43 ./
drwxr-xr-x 3 root root  4096 5月  22 10:43 ../
-rw-r--r-- 1 root root 11465 5月  22 10:43 CMakeCache.txt
drwxr-xr-x 5 root root  4096 5月  22 10:43 CMakeFiles/
-rw-r--r-- 1 root root  1339 5月  22 10:43 cmake_install.cmake
-rw-r--r-- 1 root root  4900 5月  22 10:43 Makefile
[root@ubuntu0006:~/cmake/build] #make
Scanning dependencies of target MyProject
[ 50%] Building CXX object CMakeFiles/MyProject.dir/cmake_example.cpp.o
[100%] Linking CXX executable MyProject
[100%] Built target MyProject
[root@ubuntu0006:~/cmake/build] #ll
总用量 48
drwxr-xr-x 3 root root  4096 5月  22 10:43 ./
drwxr-xr-x 3 root root  4096 5月  22 10:43 ../
-rw-r--r-- 1 root root 11465 5月  22 10:43 CMakeCache.txt
drwxr-xr-x 5 root root  4096 5月  22 10:43 CMakeFiles/
-rw-r--r-- 1 root root  1339 5月  22 10:43 cmake_install.cmake
-rw-r--r-- 1 root root  4900 5月  22 10:43 Makefile
-rwxr-xr-x 1 root root  9008 5月  22 10:43 MyProject*
[root@ubuntu0006:~/cmake/build] #./MyProject
********* main[20] *********
```



