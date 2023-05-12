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

## 5、问题记录

