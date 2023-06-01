# 学习打印公共变量

## 执行结果
```
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
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE
-- [variable]
-- CMAKE_BUILD_TYPE=
-- PROJECT_SOURCE_DIR=/root/cmake
-- PROJECT_NAME=CMakeStudy
-- PROCESSOR_COUNT=
-- CMAKE_CURRENT_SOURCE_DIR=/root/cmake
-- CMAKE_BINARY_DIR=/root/cmake/build
-- PROJECT_BINARY_DIR=/root/cmake/build
-- CMAKE_INSTALL_PREFIX=/usr/local
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/build

[root@ubuntu0006:~/cmake/build] #pwd
/root/cmake/build
```