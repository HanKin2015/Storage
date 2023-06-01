## 1、学习
- CMake中的option用于控制编译流程，相当于C语言中的宏条件编译
- message语法
- 在执行cmake时，可以使用-D+选项名称，修改选项的值（必须要有这个前缀）
- add_definitions语法
- test是关键词不能使用这个作为生成文件名
- 项目名和生成文件名可以不一样

可以看到，虽然子项中TEST_OPTION选项定义为了OFF，但是，由于主项目中TEST_OPTION选项的值是ON，导致子项目的选项值变为了ON，可以看出，对于同一选项，子项目值遵循主项目的定义。

注意：对于这种，主、次架构的项目来说，整个工程只有一个CMakeCache.txt，其位于主项目的编译目录下，子项目会根据此CMakeCache.txt中选项的定义，进行子项目本身的编译。

## 2、更多详情
D:\Github\GitBook\gitbook\C++\cmake.md

## 3、运行结果
mkdir build
cmake ..
make

```
# 使用test关键字报错
CMakeExpSub.
-- TEST_OPTION defined: OFF
-- TEST_OPTION OFF.
CMake Error at CMakeLists.txt:32 (add_executable):
  The target name "test" is reserved or not valid for certain CMake features,
  such as generator expressions, and may result in undefined behavior.


-- Configuring incomplete, errors occurred!
See also "/root/cmake/build/CMakeFiles/CMakeOutput.log".

# cmake执行完成之后，选项的值会保存到 CMakeCache.txt 中
[root@ubuntu0006:~/cmake/build] #cat CMakeCache.txt | grep OPTION
TEST_OPTION:BOOL=OFF

[root@ubuntu0006:~/cmake/build] #cmake ..
-- CMakeExpMaster.
-- TEST_OPTION defined: OFF
-- TEST_OPTION OFF.
-- NOT-TEST_OPTION ON.
--

CMakeExpSub.
-- TEST_OPTION defined: OFF
-- TEST_OPTION OFF.
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/build

# 在执行cmake时，可以使用-D+选项名称，修改选项的值
[root@ubuntu0006:~/cmake/build] #cmake .. -DTEST_OPTION=ON
-- CMakeExpMaster.
-- TEST_OPTION defined: ON
-- TEST_OPTION ON.
-- NOT-TEST_OPTION OFF.
--

CMakeExpSub.
-- TEST_OPTION defined: ON
-- TEST_OPTION ON.
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/build
[root@ubuntu0006:~/cmake/build] #make
Scanning dependencies of target test2
[ 50%] Building C object CMakeFiles/test2.dir/test.c.o
[100%] Linking C executable test2
[100%] Built target test2
[root@ubuntu0006:~/cmake/build] #./test2
Hello, CMake.
HJ = 345
JH = 1
```