# .cmake文件学习
在 CMake 中，.cmake 文件通常用于存放 CMake 脚本和模块，这些脚本和模块可以被其他 CMakeLists.txt 文件引用和使用。
.cmake 文件是 CMake 项目中的配置文件，通常用于定义变量、函数、选项或模块化配置，以复用代码或分离功能。

## 1、使用include
使用 include() 命令引入外部配置文件，路径可以是相对或绝对路径。
```
[root@ubuntu0006:~/cmake/include/build] #cmake ../
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
-- This is my_function from my_module.cmake
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /root/cmake/include/build
```

若需生成并包含动态文件（如基于某些参数生成的配置文件），可使用 configure_file()。
