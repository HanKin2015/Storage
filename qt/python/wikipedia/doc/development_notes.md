# 开发笔记

## 1、需求
- 将gitbook中baidubaike.md文件转换成sqlite3数据库
- 学习sqlite3

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
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/wikipedia.ico -w -F src/wikipedia.py`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/wikipedia.ico -w -F wikipedia.spec`

## 3、下一步改进点
- 增加状态栏

## 4、更新修改记录

### 20230418
- 基本功能完成，增查

## 5、问题记录

