## 1、windows编译方式
使用 cmake 命令生成 Makefile：
```
cmake -S . -B build
```
linux下没有这两个选项，这是windows系统下面的参数。


使用 make 命令编译项目：
```
make -C build
```

运行测试：
```
make -C build test
```

生成代码覆盖率报告：
```
make -C build coverage
```

这将在 build 目录下生成一个名为 coverage.html 的 HTML 报告文件，其中包含有关代码覆盖率的详细信息。

## 2、Linux编译方式
```
[root@ubuntu0006:~/cmake/hj] #tree .
.
├── CMakeLists.txt
└── test
    └── test.cpp

1 directory, 2 files
[root@ubuntu0006:~/cmake/hj] #mkdir build
[root@ubuntu0006:~/cmake/hj] #cd build
[root@ubuntu0006:~/cmake/hj/build] #cmake ..
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
-- Build files have been written to: /root/cmake/hj/build
[root@ubuntu0006:~/cmake/hj/build] #make
Scanning dependencies of target mytest
[ 50%] Building CXX object CMakeFiles/mytest.dir/test/test.cpp.o
[100%] Linking CXX executable mytest
[100%] Built target mytest
[root@ubuntu0006:~/cmake/hj/build] #./mytest
hello coverage
```

## 3、覆盖率
```
[root@ubuntu0006:~/cmake/hj/build] #make coverage
Scanning dependencies of target coverage
[100%] Generating code coverage report
[100%] Built target coverage
[root@ubuntu0006:~/cmake/hj/build] #ll
总用量 124
drwxr-xr-x  4 root root  4096 6月  15 09:50 ./
drwxr-xr-x  4 root root  4096 6月  15 09:50 ../
-rw-r--r--  1 root root 14907 6月  15 09:50 CMakeCache.txt
drwxr-xr-x 34 root root  4096 6月  15 09:50 CMakeFiles/
-rw-r--r--  1 root root  1345 6月  15 09:50 cmake_install.cmake
-rw-r--r--  1 root root  7597 6月  15 09:50 coverage.html
-rw-r--r--  1 root root 10820 6月  15 09:50 coverage.test_test.cpp.html
-rw-r--r--  1 root root   294 6月  15 09:50 CTestTestfile.cmake
-rw-r--r--  1 root root  2590 6月  15 09:50 DartConfiguration.tcl
-rw-r--r--  1 root root 18856 6月  15 09:50 Makefile
-rwxr-xr-x  1 root root 38256 6月  15 09:50 mytest*
drwxr-xr-x  3 root root  4096 6月  15 09:50 Testing/
```
生成coverage.html和coverage.test_test.cpp.html文件。

## 4、append_coverage_compiler_flags函数
append_coverage_compiler_flags() 函数是 CMake 的 CodeCoverage 模块中的一个函数，用于向编译器添加代码覆盖率相关的编译选项。该函数的语法如下：
```
append_coverage_compiler_flags()
```
该函数会向 CMAKE_CXX_FLAGS 和 CMAKE_C_FLAGS 变量中添加以下编译选项：
```
-g：生成调试信息。
-O0：禁用优化。
--coverage：启用代码覆盖率。
```

## 5、setup_target_for_coverage_gcovr_html函数
setup_target_for_coverage_gcovr_html() 函数是 CMake 的 CodeCoverage 模块中的一个函数，用于生成代码覆盖率报告。该函数的语法如下：
```
setup_target_for_coverage_gcovr_html(
    NAME target
    [DEPENDENCIES deps...]
    [EXCLUDE exclude...]
    [BASE_DIRECTORY dir]
    [FILTER filter...]
    [HTML_DIRECTORY dir]
    [HTML_TITLE title]
    [LCOV_ARGS args...]
    [GENHTML_ARGS args...]
)

该函数会创建一个自定义的 make 目标，用于生成代码覆盖率报告。参数说明如下：

NAME：要生成代码覆盖率报告的目标名称。
DEPENDENCIES：生成代码覆盖率报告所依赖的目标。
EXCLUDE：要排除的文件或目录。
BASE_DIRECTORY：代码覆盖率报告的基本目录。
FILTER：要包含或排除的文件或目录。
HTML_DIRECTORY：HTML 报告文件的输出目录。
HTML_TITLE：HTML 报告文件的标题。
LCOV_ARGS：传递给 lcov 命令的额外参数。
GENHTML_ARGS：传递给 genhtml 命令的额外参数。
```

## 6、结合4和5的函数编写CMakeLists文件
代码见：D:\Github\Storage\c++\cmake\practice6\CMakeLists.txt.2

```
[root@ubuntu0006:~/cmake/hj/build] #cmake ..
CMake Warning at cmake/CodeCoverage.cmake:208 (message):
  Code coverage results with an optimised (non-Debug) build may be misleading
Call Stack (most recent call first):
  CMakeLists.txt:3 (include)


-- Appending code coverage compiler flags: -g --coverage -O0
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/hj/build
```

差参数：-DCMAKE_BUILD_TYPE=Debug
```
[root@ubuntu0006:~/cmake/hj/build] #cmake -DCMAKE_BUILD_TYPE=Debug ..
-- Appending code coverage compiler flags: -g --coverage -O0
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/hj/build
[root@ubuntu0006:~/cmake/hj/build] #make
[ 50%] Building CXX object CMakeFiles/mytest.dir/test/test.cpp.o
[100%] Linking CXX executable mytest
[100%] Built target mytest
[root@ubuntu0006:~/cmake/hj/build] #./mytest
hello coverage
[root@ubuntu0006:~/cmake/hj/build] #make coverage
[ 66%] Built target mytest
[100%] Running gcovr to produce HTML code coverage report.
Traceback (most recent call last):
  File "/usr/bin/gcovr", line 1952, in <module>
    datafiles = get_datafiles(args[1:], options)
  File "/usr/bin/gcovr", line 389, in get_datafiles
    files = search_file(".*\.gc(da|no)$", dir_)
  File "/usr/bin/gcovr", line 356, in search_file
    raise IOError("Unknown directory '"+path+"'")
OSError: Unknown directory 'coverage/index.html'
CMakeFiles/coverage.dir/build.make:57: recipe for target 'CMakeFiles/coverage' failed
make[3]: *** [CMakeFiles/coverage] Error 1
CMakeFiles/Makefile2:67: recipe for target 'CMakeFiles/coverage.dir/all' failed
make[2]: *** [CMakeFiles/coverage.dir/all] Error 2
CMakeFiles/Makefile2:74: recipe for target 'CMakeFiles/coverage.dir/rule' failed
make[1]: *** [CMakeFiles/coverage.dir/rule] Error 2
Makefile:118: recipe for target 'coverage' failed
make: *** [coverage] Error 2
```
跟之前一样的错误，说明是这两个函数存在问题。但是可以看出append_coverage_compiler_flags函数没有问题，参数是加进去了。问题出现在setup_target_for_coverage_gcovr_html函数，由于网上下载了CodeCoverage.cmake文件，不清楚是不是这个文件的问题。

## 7、使用百度答案未解决
代码见：D:\Github\Storage\c++\cmake\practice6\CMakeLists.txt.3

```
[root@ubuntu0006:~/cmake/hj/build] #cmake -DCMAKE_BUILD_TYPE=Debug ..
-- CMAKE_COMPILER_IS_GNUCXX=1
-- Appending code coverage compiler flags: -g --coverage -O0
CMake Warning at CMakeLists.txt:24 (message):
  PROJECT_NAME=Project


-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/hj/build
[100%] Built target mytest
[root@ubuntu0006:~/cmake/hj/build] #./mytest
hello coverage
[root@ubuntu0006:~/cmake/hj/build] #make Project_coverage
Scanning dependencies of target Project_coverage
make[3]: *** No rule to make target '../Project', needed by 'CMakeFiles/Project_coverage'。 停止。
CMakeFiles/Makefile2:104: recipe for target 'CMakeFiles/Project_coverage.dir/all' failed
make[2]: *** [CMakeFiles/Project_coverage.dir/all] Error 2
CMakeFiles/Makefile2:111: recipe for target 'CMakeFiles/Project_coverage.dir/rule' failed
make[1]: *** [CMakeFiles/Project_coverage.dir/rule] Error 2
Makefile:131: recipe for target 'Project_coverage' failed
make: *** [Project_coverage] Error 2
```

## 8、查了许久终解决
百度了很久，相关问题情况很少，几乎没有，因此找不到答案，怀疑可能是gcovr版本低问题，但是想不通为何直接使用gcovr命令能正常生成html文件。现在想通了，可能是后面进行了大改呢，改变了一些参数以及依赖文件库。

最终使用chatGPT寻求答案，其实也可以使用高版本的ubuntu安装高版本的gcovr，直接一测试就出结果了，但是没有这个环境。因此一个高版本ubuntu是多么的迫切需求。

问：使用CodeCoverage.cmake库，对gcovr有版本要求，我的版本是3.2
答：根据CodeCoverage.cmake的官方文档，gcovr的最低版本要求是3.3。因此，如果您的gcovr版本是3.2，建议升级到3.3或更高版本以确保与CodeCoverage.cmake库的兼容性。

CodeCoverage.cmake是CMake官方提供的一个模块，用于生成代码覆盖率报告。它的官方文档可以在CMake官方文档网站上找到，链接为：https://cmake.org/cmake/help/latest/module/CodeCoverage.html。
在CMake官方没有找到答案。

至于gcovr的最低版本要求是3.3，这个信息可以在gcovr的官方文档中找到。gcovr的官方文档可以在其官方网站上找到，链接为：https://gcovr.com/en/stable/installation.html。在该页面中，有一段关于版本要求的说明，其中提到了gcovr的最低版本要求是3.3。

但是这里发现：
```
Python	gcovr
2.6	    3.4
2.7	    4.2
3.4	    4.1
3.5	    4.2
3.6	    5.0
```
我的python3是3.5.9，因此需要对应的4.2版本，先是安装了3.3版本，行不通，最后安装了4.2版本，以及
```
配置镜像源
mkdir .pip
vi .pip/pip.conf

安装依赖包
pip install jinja2
pip install lxml

安装4.2版本gcovr：https://github.com/gcovr/gcovr/releases
python3 setup.py install

原版本卸载不掉，直接覆盖whereis
mv /usr/local/bin/gcovr /usr/bin/gcovr

[root@ubuntu0006:~/cmake/hj/build] #make coverage
-- Appending code coverage compiler flags: -g --coverage -O0
-- CMAKE_SOURCE_DIR=/root/cmake/hj
-- CMAKE_BINARY_DIR=/root/cmake/hj/build
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/hj/build
[ 66%] Built target mytest
[100%] Running gcovr to produce HTML code coverage report.
lines: 100.0% (4 out of 4)
branches: 50.0% (2 out of 4)
Open ./coverage/index.html in your browser to view the coverage report.
[100%] Built target coverage
[root@ubuntu0006:~/cmake/hj/build] #gcovr --version
gcovr 4.2

Copyright 2013-2018 the gcovr authors
Copyright 2013 Sandia Corporation
Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
the U.S. Government retains certain rights in this software.
```

