# 开发笔记

## 1、需求
- 将之前开发的各种各样小工具集成

## 2、开发更新步骤
- 修改src中源码文件
- 修改doc中file_version_info.txt内容（一定要提前运行一下resource_convert_to_pyfile.py文件）
- pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F src/upan_auto_copy.py
- 取出exe文件，删除多余的文件夹
- 如果使用office_assistant.spec文件生成，可以省略文件信息和图标，以及可以修改生成exe文件的文件名
- 鱼和熊掌不可兼得，如果不使用spec文件可以使用-n或--name参数来指定PyInstaller生成的可执行文件的名称
- Lite版本需要更改office_assistant.spec文件和common.py文件

### 2-1、导出requirements.txt文件
pip freeze > requirements.txt

### 2-2、安装依赖
pip install pyusb
pip install pyzbar
pip install pyqtchart
pip install pyautogui

### 2-3、编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico -w -F src/office_assistant.py`
- 打包 `pyinstaller.exe office_assistant.spec`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/office_assistant.ico --add-binary "D:\\Github\\Storage\\qt\\python\\office_assistant\\src\\libzbar-64.dll;." --add-binary "D:\\Github\\Storage\\qt\\python\\office_assistant\\src\\libiconv.dll;." -F src/office_assistant.py`

## 3、下一步改进点
- 停止监控偶尔会停不下来，多次之后才会生效
- 明明托盘显示关闭屏幕监控（即开启屏幕监控），但是并没有开启屏幕监控
- 添加发送者信息
- 防止多个程序打开
- 在线更新功能参考：https://github.com/fandesfyf/JamTools/commit/27e6cf38187db474fcd8bd7e21ce2a740f1c3ebc#diff-84cfe7a66221384d5b6ddb703f513230afac2ebc351bc05666b6905e8c722fe6
- QMessageBox控件右键菜单不完美，无法捕获ContextMenu事件
- libzbar-64.dll文件为何不像libusb-1.0.dll打包进入exe文件（未解决前建议增加文件缺少提示）
- 复合设备，未能识别出正确的vpid
- 复合设备，如何来判断设备的连接数量（usbview也是这样判断数量，包含了hub，但是usbtree却去掉了hub）
- 页面错误增量时刻在增加，不清楚是不是这个导致了程序启动了一段时间后使用有些卡顿
- 清理工具改进，当前我的电脑遇到C盘满，需要清理磁盘，不清楚能删除哪些地方，目前有两个参考：C:\Windows\Temp和%temp%
- 工具开启检测设备长时间运行后会出现卡死问题
- 检测网站的版本信息（包含密码探索）

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

### 20230609
- 增加截图扫描二维码功能，但是需要引入numpy库，尝试改写实现，最终实现失败

### 20230612
- 扫描内容复制粘贴，并重写右键菜单
- 推出Lite版本，即简化版本，主要是为了去掉numpy带来的影响（去掉截图识别二维码功能）
- 增加NET FrameWork版本读取

### 20231220
- 解决dll文件未打包进入exe问题
- 解决监控屏幕程序异常问题

### 20230110
- 解决设备检测部分内存泄露问题
- 增加内存使用情况打印

### 20240227
- 优化部分不合理的设计和解决部分bug
- 创建sqlite3数据库操作界面

### 20240521
- 发现“是”生成的二维码解析出来是乱码，使用小爱视觉解析正常
- 确认识别二维码是不需要联网的，即可以离线
- 但是该二维码解析功能还是不能满足需要，识别的二维码是网址，一定需要联网，只能舍去

## 5、问题记录

### 5-1、pyinstaller打包后程序获取描述符崩溃
没有任何提示，日志无记录。
通过增加日志只能追踪到出事点，即行数，但是原因是未知的。
最好的办法是使用trycatch捕获异常，并打印机出错详细。

最终发现是udev = usb.core.find(idVendor=int(vid, 16), idProduct=int(pid, 16))这句执行失败，错误日志为No Backend。
因为之前遇到过很多次，已确认一定需要将libusb-1.0.dll文件放在src目录和C:\Windows\System32目录，二者缺一不可。

### 5-2、逃不过的numpy库
pyzbar.decode 函数需要读取图像数据才能进行二维码或条形码的解码。在大多数情况下，这意味着需要将图像文件加载到内存中，然后将其转换为 numpy 数组。例如，可以使用 OpenCV 库中的 cv2.imread 函数来加载图像文件，然后使用 numpy 库中的 numpy.array 函数将其转换为 numpy 数组。然后，可以将该数组传递给 pyzbar.decode 函数进行解码。
```
import cv2
import numpy as np
import pyzbar.pyzbar as pyzbar

# 读取图像文件
img = cv2.imread('barcode.png')

# 将图像转换为 numpy 数组
img_array = np.array(img)

# 解码二维码或条形码
decoded = pyzbar.decode(img_array)

# 打印解码结果
for obj in decoded:
    print(obj.data)
```
使用numpy库可以更方便地进行数值计算和数组操作。如果您不想使用numpy库，可以使用Python内置的列表和基本数学运算符来进行数值计算和数组操作。但是需要注意的是，使用Python内置的列表进行数值计算和数组操作可能会比使用numpy库更慢，因为numpy库是专门为数值计算和数组操作而设计的，具有更高的效率和性能。

### 5-3、Failed to execute script 
其实是确认库文件，你会发现很难排查，可以通过去掉w参数，然后在dos窗口执行exe文件即可。

程序中使用了pyzbar库，这个库需要依赖libzbar-64.dll和libiconv.dll文件。因此需要将这个文件C:\Users\Administrator\Anaconda3\Lib\site-packages\pyzbar放在C:\Windows\System32目录下，以及src目录下。

### 5-4、QMessageBox弹框能够复制粘贴
box.setTextInteractionFlags(Qt.TextSelectableByMouse)

### 5-5、QMessageBox弹框右键菜单重写
事件捕获不到，使用everything搜索源文件QEvent，发现C:\Users\Administrator\Anaconda3\Library\include\qt\QtCore\qcoreevent.h文件，就是需要的。

### 5-6、发现不管怎么限制import都会打进exe文件中
如在common.py中通过if语句限制了numpy库的导入，但是使用pyinstaller打包还是会导入，只有注释掉了才正常。

### 5-7、Failed to start embedded python interpreter
可能是打包过程中出现异常，导致打出来的包不完整，重新打包即可。

### 5-8、长时间USB设备检测会导致软件卡死
任务管理器看页面错误增量大约在21左右，导致页面错误不断地在增加，很大概率跟这个有关。

测试demo见：D:\Github\Storage\python\bug\page_error_increment.py

现在的方案还是不行，还得使用 subprocess 模块来调用命令行工具 wmic 来获取。目前方案开启监控后WMI Provider Host占用CPU还是排行第一，只不过从之前的非常高降到了低或者中。
不过测试发现使用wmic工具命令也会有这个问题，这个应该已经是最优方案了，除非不调用wmi接口，而是其他接口。

### 5-9、解决sqlite数据库输入带有单引号和双引号数据问题
尝试通过将字符串进行加解密，结果发现加密后的字符串也失败了。
```
key, iv, encrypted_descriptor = encrypt_data(descriptor.encode('utf-8'))
descriptor = "{}{}{}".format(key, iv, encrypted_descriptor)

SQL_INSERT_ONE_DATA = 'INSERT INTO {} VALUES(NULL, "{}", "{}", "{}");'.format(table_name,
                      device_type, descriptor, remark)
print(SQL_INSERT_ONE_DATA)
cursor.execute(SQL_INSERT_ONE_DATA)
```

最终问AI得到解决方法：
```
import sqlite3

# 连接到数据库（如果不存在则会创建）
conn = sqlite3.connect('my_database.db')

# 创建一个游标对象
cursor = conn.cursor()

# 创建一个表
cursor.execute('''CREATE TABLE IF NOT EXISTS my_table (my_column TEXT)''')

# 要插入的包含双引号和单引号的字符串
my_string = '包含双引号"和单引号\'的字符串'

# 使用参数化查询和绑定变量来插入数据
cursor.execute("INSERT INTO my_table (my_column) VALUES (?)", (my_string,))

# 提交更改
conn.commit()

# 关闭连接
conn.close()
```

