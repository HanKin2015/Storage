# C++ 标准库 <exception>
std::exception: 所有标准异常类的基类，定义了异常的基本接口。它有一个虚函数 what()，用于返回异常信息的 C 风格字符串。

std::runtime_error: 表示运行时错误，通常是由于程序逻辑问题导致的异常，例如无效的参数、无法打开文件等。
```
throw std::runtime_error("Runtime error occurred");
```

std::logic_error: 表示逻辑错误，通常是由于程序逻辑错误导致的异常，例如逻辑断言失败、索引越界等。
```
throw std::logic_error("Logic error occurred");
```

std::invalid_argument: 表示传递给函数的参数无效。
```
throw std::invalid_argument("Invalid argument");
```

std::out_of_range: 表示访问超出有效范围的对象，如数组、容器等。
```
throw std::out_of_range("Out of range");
```

std::overflow_error 和 std::underflow_error: 表示数值计算时出现溢出或下溢。
```
throw std::overflow_error("Overflow occurred");
throw std::underflow_error("Underflow occurred");
```