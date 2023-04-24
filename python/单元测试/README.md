# unittest --- 单元测试框架

参考：https://docs.python.org/zh-cn/3/library/unittest.html

## 1、简介
unittest 单元测试框架是受到 JUnit 的启发，与其他语言中的主流单元测试框架有着相似的风格。其支持测试自动化，配置共享和关机代码测试。支持将测试样例聚合到测试集中，并将测试与报告框架独立。

为了实现这些，unittest 通过面向对象的方式支持了一些重要的概念。

### 1-1、测试脚手架
test fixture 表示为了开展一项或多项测试所需要进行的准备工作，以及所有相关的清理操作。举个例子，这可能包含创建临时或代理的数据库、目录，再或者启动一个服务器进程。

### 1-2、测试用例
一个测试用例是一个独立的测试单元。它检查输入特定的数据时的响应。 unittest 提供一个基类： TestCase ，用于新建测试用例。

### 1-3、测试套件
test suite 是一系列的测试用例，或测试套件，或两者皆有。它用于归档需要一起执行的测试。

### 1-4、测试运行器（test runner）
test runner 是一个用于执行和输出测试结果的组件。这个运行器可能使用图形接口、文本接口，或返回一个特定的值表示运行测试的结果。

## 2、基本示例
代码见：D:\Github\Storage\python\单元测试\example_unittest_string.py

继承 unittest.TestCase 就创建了一个测试样例。上述三个独立的测试是三个类的方法，这些方法的命名都以 test 开头。 这个命名约定告诉测试运行者类的哪些方法表示测试。

每个测试的关键是：调用 assertEqual() 来检查预期的输出； 调用 assertTrue() 或 assertFalse() 来验证一个条件；调用 assertRaises() 来验证抛出了一个特定的异常。使用这些方法而不是 assert 语句是为了让测试运行者能聚合所有的测试结果并产生结果报告。

通过 setUp() 和 tearDown() 方法，可以设置测试开始前与完成后需要执行的指令。

最后的代码块中，演示了运行测试的一个简单的方法。 unittest.main() 提供了一个测试脚本的命令行接口。
在调用测试脚本时添加 -v 参数使 unittest.main() 显示更为详细的信息，生成如以下形式的输出:
```
(base) D:\Github\Storage\python\单元测试>python example_unittest_string.py
...
----------------------------------------------------------------------
Ran 3 tests in 0.001s

OK

(base) D:\Github\Storage\python\单元测试>python example_unittest_string.py -v
test_isupper (__main__.TestStringMethods)
测试系统是否为大写字符串函数isupper() ... ok
test_split (__main__.TestStringMethods)
测试系统切割函数split() ... ok
test_upper (__main__.TestStringMethods)
测试系统转换大写函数upper() ... ok

----------------------------------------------------------------------
Ran 3 tests in 0.012s

OK
```
以上例子演示了 unittest 中最常用的、足够满足许多日常测试需求的特性。文档的剩余部分详述该框架的完整特性。

## 3、命令行接口
后面的可以省略，都是一些高级的单元测试，一般使用不到。

unittest 模块可以通过命令行运行模块、类和独立测试方法的测试:
```
python -m unittest test_module1 test_module2
python -m unittest test_module.TestClass
python -m unittest test_module.TestClass.test_method
```



