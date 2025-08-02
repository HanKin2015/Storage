# 单元测试gtest
参考：https://zhuanlan.zhihu.com/p/15533978517
C++代码具有多样性，包括函数、类、模板等。针对不同类型的代码，测试方法也有所不同。理解这些差异，有助于编写更有效的测试用例。

## 1、针对不同类型C++代码的测试方法

### 1-1、测试独立函数
独立函数通常是最直接的测试目标。通过验证函数输入输出的关系，可以确保其按预期工作。

### 1-2、测试类方法
对于类中的成员函数，通常需要测试其状态变化和行为。使用测试夹具（Test Fixtures）可以有效管理测试对象的生命周期和共享资源。

### 1-3、测试模板类和函数
模板类和函数由于其泛型特性，需要在不同类型下进行测试，以确保其通用性和正确性。

## 2、通用的测试处理方式

### 2-1、使用测试夹具（Test Fixtures）
测试夹具允许在多个测试用例中共享初始化和清理代码，减少重复代码，提高测试的可维护性。

### 2-2、参数化测试
参数化测试允许在不同参数组合下运行同一测试用例，显著提升测试覆盖率，发现更多潜在问题。

### 2-3、Mock 对象
在复杂系统中，部分组件可能依赖外部资源或具有复杂的内部逻辑。使用Mock对象可以模拟这些依赖，隔离被测试单元，确保测试的独立性和可靠性。

由于确实代码，因此未跑起来！

## 3、基本测试准则
编写高质量的单元测试不仅依赖于正确使用测试框架，还需要遵循一些基本的测试准则。这些准则有助于确保测试的有效性、可维护性和可读性。

### 3-1、独立性
每个测试用例应独立于其他测试，无需依赖特定的执行顺序或共享状态。独立性确保测试结果的可靠性，避免因某个测试的失败影响其他测试。

### 3-2、清晰明了
测试用例应具有清晰的命名和结构，便于理解其目的和行为。命名应描述被测试的功能和预期的结果。

### 3-3、高覆盖率
确保测试覆盖了代码的各种路径，包括正常情况、边界条件和异常情况。高覆盖率有助于发现隐藏的缺陷，提升代码质量。

### 3-4、快速反馈
测试应尽可能快速执行，以便开发者能够频繁运行测试，及时发现和修复问题。长时间运行的测试可能导致测试频率降低，影响开发效率。

### 3-5、可维护性
测试代码应与生产代码一样注重可维护性。清晰的结构、良好的命名和适当的注释有助于长期维护和扩展测试。

## 4、使用 CTest 运行测试
CMake提供了CTest工具，可以更方便地管理和运行测试。使用CTest可以集成到更大的自动化测试流程中。
CTest是CMake自带的测试驱动程序，能够与Google Test无缝集成，提供更强大的测试管理功能。通过CTest，可以轻松地运行所有测试、生成测试报告，并与持续集成系统集成。
```
root@hankin:~/gtest/参数化测试/buil# ctest --verbose
Test project /root/gtest/参数化测试/buil
    Start 1: CompareTests/StringTest.CompareStrings/("hello", "hello", true)
1/4 Test #1: CompareTests/StringTest.CompareStrings/("hello", "hello", true) ....   Passed    0.01 sec
    Start 2: CompareTests/StringTest.CompareStrings/("hello", "world", false)
2/4 Test #2: CompareTests/StringTest.CompareStrings/("hello", "world", false) ...   Passed    0.00 sec
    Start 3: CompareTests/StringTest.CompareStrings/("", "", true)
3/4 Test #3: CompareTests/StringTest.CompareStrings/("", "", true) ..............   Passed    0.01 sec
    Start 4: CompareTests/StringTest.CompareStrings/("abc", "abcd", false)
4/4 Test #4: CompareTests/StringTest.CompareStrings/("abc", "abcd", false) ......   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.03 sec
```

## 5、覆盖率
cmake -DCMAKE_BUILD_TYPE=Coverage ..

折腾了一下，需要忽略行号不匹配错误。
```
lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
lcov --remove coverage.info '/usr/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_report
```

打开 coverage_report/index.html 查看覆盖率详情。

## 6、使用持续集成（CI）工具
将测试流程集成到持续集成系统中，实现每次代码提交后自动运行测试。常用的CI工具包括GitHub Actions、Jenkins、Travis CI等。






