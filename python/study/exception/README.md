# traceback库
traceback是Python标准库中的一个模块，用于打印和处理异常信息。它提供了一些函数，可以方便地获取和处理异常信息，以便进行调试和错误处理。

以下是traceback库的一些常用函数：
- traceback.print_exc([limit[, file]])：打印当前异常的回溯信息到标准错误输出或指定文件中。
- traceback.format_exc([limit])：返回当前异常的回溯信息字符串。
- traceback.print_exception(etype, value, tb[, limit[, file]])：打印指定异常的回溯信息到标准错误输出或指定文件中。
- traceback.format_exception(etype, value, tb[, limit])：返回指定异常的回溯信息字符串。
- traceback.extract_tb(tb[, limit])：返回指定回溯信息中的栈帧列表。
- traceback.extract_stack([f[, limit]])：返回当前调用栈中的栈帧列表。

这些函数可以用于获取和处理异常信息，以便进行调试和错误处理。