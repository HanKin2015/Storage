# 开发笔记

## 1、需求
- 获取系统当前USB设备及USB信息
- 检测当前所有USB设备驱动情况
- 显示USB设备加载sys驱动及inf文件

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i img/USBCheck.ico -F src/USBCheck.py
- 取出exe文件，删除多余的文件夹

### 编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/USBCheck.ico -w -F src/USBCheck.py`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/USBCheck.ico -w -F USBCheck.spec`

## 3、下一步改进点
- 

## 4、更新修改记录

### 20230320
- 基本布局完成

## 5、问题记录

### 5-1、截图区域实现
