# 日志解析自动化工具

## 1、参数解析
使用文件拖曳的方式执行参数解析出来的是文件绝对路径。
```
['D:\\Github\\Storage\\python\\project\\日志文件解析工具\\dist\\log_file_parse_t
ool.exe', 'D:\\Github\\Storage\\c++\\standard_library\\struct\\copy_struct2.cpp'
]
******** starting ********
process spend 0.0 s.

请按任意键继续. . .
```

## 2、usb设备vpid获取
通过New USB device found关键字获取。

## 3、emi日志解析
可能有误判，需要加强条件判断，如大写字母。测试发现不会误判，if "EMI" in line这语句已经是进行大小写判断了，小写emi不会匹配上。

## 4、历史文件处理



## 5、终端类型判断
已做，暂时不需要，直接找相应的文件名即可。

## 6、error日志解析
- EMI电磁干扰
- 枚举失败

## 7、打包命令
pyinstaller -F log_file_parse_tool.py -n log_file_parse_tool20241104


