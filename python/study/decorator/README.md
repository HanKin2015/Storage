# 装饰器

## 1、staticmethod
@staticmethod是Python中的一个装饰器，用于将一个类方法转换为静态方法。静态方法是不需要访问类或实例属性的方法，它们可以直接通过类名调用，而不需要创建类的实例。

代码见：D:\Github\Storage\python\study\decorator\staticmethod_example.py
在这段代码中，@staticmethod装饰器用于将hello()方法转换为静态方法。这意味着可以直接通过类名调用hello()方法，而不需要创建类的实例。例如，如果类名为MyClass，可以使用MyClass.hello()来调用hello()方法。

需要注意的是，静态方法不能访问类或实例属性，因为它们没有类或实例的上下文。在这段代码中，hello()方法只使用了局部变量，因此可以安全地转换为静态方法。

## 2、retry
retrying是一个Python库，用于在函数执行失败时自动重试。它提供了一些装饰器和函数，可以方便地实现函数重试的逻辑。

retrying库的主要特点包括：
- 灵活的重试策略：可以通过设置stop_max_attempt_number、wait_fixed、wait_random_min等参数来控制重试的次数、间隔和随机性。
- 支持异常过滤：可以通过设置retry_on_exception参数来指定需要重试的异常类型，或者通过自定义函数来判断是否需要重试。
- 支持返回值过滤：可以通过设置retry_on_result参数来指定需要重试的返回值，或者通过自定义函数来判断是否需要重试。
- 支持日志输出：可以通过设置log_level和log_formatter参数来控制日志输出的级别和格式。

使用retrying库非常简单，只需要在需要重试的函数上添加@retry装饰器即可。

代码见：