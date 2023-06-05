# 开发笔记

## 1、需求
- 将之前开发的各种各样小工具集成

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/upan_auto_copy.py
- 取出exe文件，删除多余的文件夹
- 如果使用office_assistant.spec文件生成，可以省略文件信息和图标，以及可以修改生成exe文件的文件名
- 鱼和熊掌不可兼得，如果不使用spec文件可以使用-n或--name参数来指定PyInstaller生成的可执行文件的名称

### 2-1、导出requirements.txt文件
pip freeze > requirements.txt

### 2-2、编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F src/office_assistant.py`
- 打包 `pyinstaller.exe -w -F office_assistant.spec`

## 3、下一步改进点
- 停止监控偶尔会停不下来，多次之后才会生效
- 明明托盘显示关闭屏幕监控（即开启屏幕监控），但是并没有开启屏幕监控
- 添加发送者信息
- 防止多个程序打开
- 在线更新功能参考：https://github.com/fandesfyf/JamTools/commit/27e6cf38187db474fcd8bd7e21ce2a740f1c3ebc#diff-84cfe7a66221384d5b6ddb703f513230afac2ebc351bc05666b6905e8c722fe6

## 4、更新修改记录

### 20230412
- 创建此项目

### 20230424
- 修复usb检测中设备传输类型bug

### 20230425
- base64解码实现
- 黑客工具实现

### 20230426
- 拷贝工具界面实现

### 20230524
- 完成数学工具（质因数的快速方法研究、单元测试）

### 20230525
- 重构部分代码
- 消除No Icon set错误
- 完成USB设备拔插检测
- 完成托盘更多功能迁移

### 20230526
- 完成屏幕监控
- 其他小问题，第一个beta版本发布
- 修复USB设备检测状态栏问题

### 20230529
- 修复pyinstaller打包后程序无法获取描述符问题
- 拔插设备显示vid和pid

## 5、问题记录

### 5-1、pyinstaller打包后程序获取描述符崩溃
没有任何提示，日志无记录。
通过增加日志只能追踪到出事点，即行数，但是原因是未知的。
最好的办法是使用trycatch捕获异常，并打印机出错详细。

最终发现是udev = usb.core.find(idVendor=int(vid, 16), idProduct=int(pid, 16))这句执行失败，错误日志为No Backend。
因为之前遇到过很多次，已确认一定需要将libusb-1.0.dll文件放在src目录和C:\Windows\System32目录，二者缺一不可。


