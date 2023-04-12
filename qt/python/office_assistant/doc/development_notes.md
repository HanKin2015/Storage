# 开发笔记

## 1、需求
- 获取客户端

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/upan_auto_copy.py
- 取出exe文件，删除多余的文件夹

### 2-1、导出requirements.txt文件
pip freeze > requirements.txt

### 2-2、编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F src/office_assistant.py`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F office_assistant.spec`

## 3、下一步改进点
- 停止监控偶尔会停不下来，多次之后才会生效
- 明明托盘显示关闭屏幕监控（即开启屏幕监控），但是并没有开启屏幕监控
- 添加发送者信息
- 防止多个程序打开

## 4、更新修改记录

### 20230221


## 5、问题记录

