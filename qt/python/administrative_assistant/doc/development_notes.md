# 开发笔记

## 1、需求
- pdf转图片
- pdf转word
- ocr提取文字
- 图片高宽等分切割
- 无损修改图片像素
- 压缩图片文件大小

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/administrative_assitant.py
- 取出exe文件，删除多余的文件夹
- 如果使用office_assistant.spec文件生成，可以省略文件信息和图标，以及可以修改生成exe文件的文件名
- 鱼和熊掌不可兼得，如果不使用spec文件可以使用-n或--name参数来指定PyInstaller生成的可执行文件的名称

### 2-1、导出requirements.txt文件
pip freeze > requirements.txt

### 2-2、编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/logo.ico -w -F src/administrative_assistant.py`
- 打包 `pyinstaller.exe -w -F administrative_assistant.spec`

## 3、下一步改进点
- 

## 4、更新修改记录

### 20230515
- 创建此项目

## 5、问题记录

### 5-1、File "pdf2image.py", line 595, in pdfinfo_from_path "Unable to get page count. Is poppler installed and in PATH?"
使用了pdf2image库来将PDF文件转换为图像：pip install pdf2image
但是这个库需要依赖Poppler工具，下载并安装Poppler工具。您可以从以下网址下载适用于Windows的Poppler工具：https://blog.alivate.com.au/poppler-windows/. 下载后，将其解压缩到一个文件夹中，例如“C:\Program Files\poppler-xx.xx.xx\”。

将Poppler工具的路径添加到系统的环境变量中。打开“控制面板” -> “系统和安全” -> “系统” -> “高级系统设置” -> “环境变量”，在“系统变量”中找到“Path”变量，点击“编辑”，在变量值的末尾添加Poppler工具的路径，例如“C:\Program Files\poppler-xx.xx.xx\bin\”。

一定要重新启动Python解释器，不然读取不到最新环境变量，然后再次运行您的代码。




