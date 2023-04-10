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
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F src/office_assistant.py`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F office_assistant.spec`

## 3、下一步改进点
- 停止监控偶尔会停不下来，多次之后才会生效
- 明明托盘显示关闭屏幕监控（即开启屏幕监控），但是并没有开启屏幕监控
- 添加发送者信息
- 防止多个程序打开

## 4、参考资料

### 4-1、PROCESS EXPLORER 
由Sysinternals开发的Windows系统和应用程序监视工具，已并入微软旗下。不仅结合了Filemon（文件监视器）和Regmon（注册表监视器）两个工具的功能，还增加了多项重要的增强功能。包括稳定性和性能改进、强大的过滤选项、修正的进程树对话框（增加了进程存活时间图表）、可根据点击位置变换的右击菜单过滤条目、集成带源代码存储的堆栈跟踪对话框、更快的堆栈跟踪、可在 64位 Windows 上加载 32位 日志文件的能力、监视映像（DLL和内核模式驱动程序）加载、系统引导时记录所有操作等。

## 4、更新修改记录

### 20230221
- 项目创建（参考D:\Github\Storage\python\udev\upan_auto_copy项目创建）

### 20230307
- 打包有326MB，经过from xxx import xxx修改后打包为323MB，优化不明显。使用PIL代替cv2库后打包72.4MB
- 截图区域实现
- 第一次打开退出框不居中，第二次打开居中显示

### 20230308
- 优化各种BUG

### 20230312
- 完成托盘悬浮消息的实现

### 20230313
- 整理代码结构，统一使用resource.py文件存储资源文件

### 20230314
- 解决消息过长问题
- 解决出现异常时还在不停发送消息问题

## 5、问题记录

### 5-1、截图区域实现
win32ui和pyqt5结合会在退出时崩溃。
尝试使用pyqt5替代。
```
self.setWindowFlags(Qt.FramelessWindowHint)
self.setWindowFlags(Qt.WindowStaysOnTopHint)
置顶生效，无边框不生效

self.setWindowFlags(Qt.WindowStaysOnTopHint)
self.setWindowFlags(Qt.FramelessWindowHint)
置顶不生效，无边框生效

self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint)
置顶生效，无边框生效
```

### 5-2、QMessageBox第一次打开不居中
会闪一次，体验也不好。后面挺过增加窗口属性隐藏主窗口解决。
```
mainWindow.show()
mainWindow.hide()
```

### 5-3、file_version_info.txt文件书写规范
需要在一个文件夹内多创建一个文件才能触发鼠标悬停显示文件信息，即两个文件以上。
filevers变量不能存在前导零，否则打包的时候报错：
```
  File "<string>", line 9
    filevers=(2023, 03, 08, 1),
                     ^
```

### 5-4、usb_camera_monitor_tool.spec文件备份
由于在.gitignore文件中过滤了spec文件，因此备份一份：
```
.vs
x64
<<<<<<< HEAD
=======
*.exe
build
.pyc
dist
*.spec
__pycache__
>>>>>>> 1d36228e2a4f62604d4c94b336da5b53ed28546e
```

### 5-5、注意截图区域建议不要开启
很奇怪，在win7系统上面执行显示截图区域的方块并不能截取到，即可以一直开着。但是在win10系统则不能，会截取到红色方块，即需要关闭。

### 5-6、