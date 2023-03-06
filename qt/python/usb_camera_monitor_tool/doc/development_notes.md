# 开发笔记

## 1、需求
- 获取客户端

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/upan_auto_copy.py
- 取出exe文件，删除多余的文件夹

### 编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/usb_camera_monitor_tool.ico -w -F src/usb_camera_monitor_tool.py`

## 3、下一步改进点
- 打包有326MB，经过from xxx import xxx修改后打包为323MB，优化不明显

## 4、参考资料

### 4-1、PROCESS EXPLORER 
由Sysinternals开发的Windows系统和应用程序监视工具，已并入微软旗下。不仅结合了Filemon（文件监视器）和Regmon（注册表监视器）两个工具的功能，还增加了多项重要的增强功能。包括稳定性和性能改进、强大的过滤选项、修正的进程树对话框（增加了进程存活时间图表）、可根据点击位置变换的右击菜单过滤条目、集成带源代码存储的堆栈跟踪对话框、更快的堆栈跟踪、可在 64位 Windows 上加载 32位 日志文件的能力、监视映像（DLL和内核模式驱动程序）加载、系统引导时记录所有操作等。

## 4、更新修改记录

### 20230221
- 项目创建（参考D:\Github\Storage\python\udev\upan_auto_copy项目创建）