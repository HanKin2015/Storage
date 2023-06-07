## 1、直接编译
```
[root@ubuntu0006:~/cmake] #g++ main.cpp mymath.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
ret = 11
3
```

## 2、修改成CMake编译
add_subdirectory(tests)需要增加tests文件夹，并且需要文件夹里面含有CMakeLists.txt文件。
```
CMake Error at CMakeLists.txt:48 (add_subdirectory):
  add_subdirectory given source "tests" which is not an existing directory.

CMake Error at CMakeLists.txt:48 (add_subdirectory):
  The source directory

    /root/cmake/tests

  does not contain a CMakeLists.txt file.
```

并且会在add_subdirectory执行后执行当前文件夹下的CMakeLists.txt文件。
```
[root@ubuntu0006:~/cmake/build] #cmake ..
-- [tests variable]
-- CMAKE_BUILD_TYPE=
-- PROJECT_SOURCE_DIR=/root/cmake
-- PROJECT_NAME=CMakeStudy
-- PROCESSOR_COUNT=
-- CMAKE_CURRENT_SOURCE_DIR=/root/cmake/tests
-- CMAKE_BINARY_DIR=/root/cmake/build
-- PROJECT_BINARY_DIR=/root/cmake/build
-- CMAKE_INSTALL_PREFIX=/usr/local
-- [main options]
-- ENABLE_LIBUVC_BACKEND=ON
-- BUILD_TESTING=ON
-- BUILD_COVERAGE_REPORT=OFF
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/build
```

## 3、执行结果
```
[root@ubuntu0006:~/cmake/build] #./main
ret = 11
3
```



