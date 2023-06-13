## 1、直接编译
```
mkdir build && cd build
cmake -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=/usr/lib/ .. && make -j8

[root@ubuntu0006:~/cmake/build] #make install
make: *** No rule to make target 'install'。 停止。
并没有拷贝过去

[root@ubuntu0006:~/cmake] #ldd a.out
        linux-vdso.so.1 =>  (0x00007fff8a3dc000)
        libmymath.so => not found
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fa5ec2f5000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fa5ec0df000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fa5ebd15000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fa5eba0c000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fa5ec677000)
[root@ubuntu0006:~/cmake] #cp build/libmymath.so /usr/lib/
[root@ubuntu0006:~/cmake] #ldd a.out
        linux-vdso.so.1 =>  (0x00007ffd0b2c1000)
        libmymath.so => /usr/lib/libmymath.so (0x00007f405148d000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f405110b000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f4050ef5000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4050b2b000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f4050822000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f405168f000)
[root@ubuntu0006:~/cmake] #./a.out
ret = 11
3
```

## 2、单元测试
```
cmake -DBUILD_TESTING=ON .. && make -j8 && ctest -V

[root@ubuntu0006:~/cmake/build] #ctest -V
UpdateCTestConfiguration  from :/root/cmake/build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/root/cmake/build/DartConfiguration.tcl
Test project /root/cmake/build
Constructing a list of tests
Done constructing a list of tests
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: reserved_test

1: Test command: /root/cmake/build/tests/reserved/reserved_test
1: Test timeout computed to be: 9.99988e+06
1: Running main() from /media/sangfor/vdb/unittest/googletest-release-1.11.0/googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from ReservedTest
1: [ RUN      ] ReservedTest.foo
1: [       OK ] ReservedTest.foo (0 ms)
1: [----------] 1 test from ReservedTest (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/2 Test #1: reserved_test ....................   Passed    0.00 sec
test 2
    Start 2: unit_test

2: Test command: /root/cmake/build/tests/unit_test/unit_test
2: Test timeout computed to be: 9.99988e+06
2: Running main() from /media/sangfor/vdb/unittest/googletest-release-1.11.0/googletest/src/gtest_main.cc
2: [==========] Running 2 tests from 1 test suite.
2: [----------] Global test environment set-up.
2: [----------] 2 tests from TestSum
2: [ RUN      ] TestSum.PositiveNumbers
2: [       OK ] TestSum.PositiveNumbers (0 ms)
2: [ RUN      ] TestSum.NegativeNumbers
2: [       OK ] TestSum.NegativeNumbers (0 ms)
2: [----------] 2 tests from TestSum (0 ms total)
2:
2: [----------] Global test environment tear-down
2: [==========] 2 tests from 1 test suite ran. (0 ms total)
2: [  PASSED  ] 2 tests.
2/2 Test #2: unit_test ........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

## 3、覆盖率
安装gcovr命令
```
apt install gcovr
```

### 3-1、
可见：D:\Github\Storage\c++\覆盖率
```
cmake -DBUILD_TESTING=ON -DBUILD_COVERAGE_REPORT=ON -DCMAKE_BUILD_TYPE=Debug .. && make -j8 && make gcovr_html
```

如果要生成xml执行make gcovr_xml
生成html执行make gcovr_html

直接使用gcovr命令是正常的，但是使用make gcovr_html有问题。
```
[root@ubuntu0006:~/cmake/build] #g++ -fprofile-arcs -ftest-coverage -fPIC -O0 ../mymath.cpp ../main.cpp -std=c++11 -o program
[root@ubuntu0006:~/cmake/build] #./program
ret = 11
3
[root@ubuntu0006:~/cmake/build] #gcovr -r ..
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
main.cpp                                       7       7   100%
mymath.cpp                                     2       2   100%
tests/reserved/test.cpp                        2       2   100%
tests/unit_test/unit_test.cpp                  6       6   100%
------------------------------------------------------------------------------
TOTAL                                         17      17   100%
------------------------------------------------------------------------------
[root@ubuntu0006:~/cmake/build] #gcovr -r .. --html --html-details -o example-html-details.html
[root@ubuntu0006:~/cmake/build] #ll
总用量 204
drwxr-xr-x 6 root root  4096 6月  13 11:29 ./
drwxr-xr-x 5 root root  4096 6月  13 10:45 ../
-rw-r--r-- 1 root root 13776 6月  13 10:57 CMakeCache.txt
drwxr-xr-x 8 root root  4096 6月  13 10:59 CMakeFiles/
-rw-r--r-- 1 root root  1498 6月  13 10:45 cmake_install.cmake
-rw-r--r-- 1 root root   256 6月  13 10:41 CTestTestfile.cmake
-rw-r--r-- 1 root root 10123 6月  13 11:29 example-html-details.html
-rw-r--r-- 1 root root  9522 6月  13 11:29 example-html-details.main.cpp.html
-rw-r--r-- 1 root root  7470 6月  13 11:29 example-html-details.mymath.cpp.html
-rw-r--r-- 1 root root  9060 6月  13 11:29 example-html-details.tests_reserved_test.cpp.html
-rw-r--r-- 1 root root 12219 6月  13 11:29 example-html-details.tests_unit_test_unit_test.cpp.html
drwxr-xr-x 2 root root  4096 6月  13 10:57 gcovr_html/
-rwxr-xr-x 1 root root 24360 6月  13 10:57 libmymath.so*
-rw-r--r-- 1 root root  1780 6月  13 11:28 main.gcda
-rw-r--r-- 1 root root 11460 6月  13 10:59 main.gcno
-rw-r--r-- 1 root root  7363 6月  13 10:57 Makefile
-rw-r--r-- 1 root root   228 6月  13 11:28 mymath.gcda
-rw-r--r-- 1 root root   200 6月  13 10:59 mymath.gcno
-rwxr-xr-x 1 root root 41624 6月  13 10:59 program*
drwxr-xr-x 3 root root  4096 6月  13 10:45 Testing/
drwxr-xr-x 6 root root  4096 6月  13 10:57 tests/
```

## 4、初识CTest
CTest是CMake集成的一个测试工具，在使用CMakeLists.txt文件编译工程的时候，CTest会自动configure、build、test和展现测试结果

CTest有两个模式：
模式一： 使用CMake configure 和 build工程，在CMakeLists.txt文件中，使用特殊的命令取创建tests。CTest用来执行那些测试
模式二： 使用CTest来执行一个script(这个script的语法必须和CMakeLists.txt相同)，去控制整个程序的输出结果