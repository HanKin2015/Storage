# configure_file()学习
configure_file() 是 CMake 中一个非常有用的命令，用于生成配置文件。它可以根据给定的模板文件和变量生成新的文件，通常用于生成动态的配置文件，比如头文件、CMake 配置文件等。

## 1、使用configure_file()
configure_file() 的基本语法如下：
```
configure_file(<input> <output> [COPYONLY] [ESCAPE_QUOTES] [@ONLY])
```
- <input>: 输入文件的路径，通常是一个模板文件。
- <output>: 输出文件的路径，生成的文件将被写入此路径。
- COPYONLY: 如果指定，CMake 将仅复制输入文件到输出文件，而不进行变量替换。
- ESCAPE_QUOTES: 如果指定，CMake 将转义输出文件中的引号。
- @ONLY: 仅替换以 @VAR@ 形式定义的变量，而不替换 ${VAR} 形式的变量。

configure_file(config.h.in config.h @ONLY)
在 CMakeLists.txt 中使用 configure_file() 将config.h.in文件生成一个实际的 config.h 文件

## 2、运行结果
```
[root@ubuntu0006:~/cmake/debug/include/build] #cmake ../
-- The C compiler identification is GNU 8.1.0
-- The CXX compiler identification is GNU 8.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/local/gcc-8.1.0/bin/gcc-8.1.0 - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/local/gcc-8.1.0/bin/g++-8.1.0 - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: /root/cmake/debug/include/build
[root@ubuntu0006:~/cmake/debug/include/build] #ll
总用量 32
-rw-r--r-- 1 root root 14039 6月  11 13:28 CMakeCache.txt
drwxr-xr-x 5 root root  4096 6月  11 13:28 CMakeFiles/
-rw-r--r-- 1 root root  1626 6月  11 13:28 cmake_install.cmake
-rw-r--r-- 1 root root    63 6月  11 13:28 config.h
-rw-r--r-- 1 root root  4057 6月  11 13:28 Makefile
[root@ubuntu0006:~/cmake/debug/include/build] #cat config.h
#pragma once

#define VERSION_MAJOR 1
#define VERSION_MINOR 0

```

## 3、《实战》文件夹运行结果
```
[root@ubuntu0006:~/cmake/debug/include/build] #cmake ../ -DCLIENT_TYPE=macd
-- Detect Client Type <Linux>
CMake Error at CMakeLists.txt:27 (message):
  unknown client type macd !!!


-- Configuring incomplete, errors occurred!
[root@ubuntu0006:~/cmake/debug/include/build] #cmake ../ -DCLIENT_TYPE=mac
-- Detect Client Type <Linux>
-- Client Type <Mac>
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /root/cmake/debug/include/build
[root@ubuntu0006:~/cmake/debug/include/build] #cat config.h
/*******************************************************************************
* 文 件 名: config.h
* 文件描述: 全局配置头文件(由cmake生成)
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.11
* 修改日期：2025.06.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/* 客户端类型 */
#define CLIENT_TYPE_LINUX
/* #undef CLIENT_TYPE_WIN */
#define CLIENT_TYPE_MAC

/* The following is used to silence warnings for unused variables */
#if defined(UNREFERENCED_PARAMETER)
#define UNUSED(var) UNREFERENCED_PARAMETER(var)
#else
#define UNUSED(var) do { (void)(var); } while(0)
#endif

#endif /* __CONFIG_H__ */
```

