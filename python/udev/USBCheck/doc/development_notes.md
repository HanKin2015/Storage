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
- 设备驱动被替换后获取描述符失败，但是usbview能成功获取，还需要先前的vpid进行获取
- 看是否可以直接通过py文件打包，而不是通过spec文件

## 4、更新修改记录

### 20230320
- 基本布局完成

### 20230321
- 扫描检测硬件改动功能完成
- 获取描述符信息
- 获取系统信息
- 获取额外的信息

### 20230322
- hid设备获取成功，即键盘

### 20230425
- 解决耳机设备崩溃问题，即传输类型修正

## 5、问题记录

### 5-1、有报错警告
```
QBasicTimer::start: QBasicTimer can only be used with threads started with QThread
QBasicTimer::start: QBasicTimer can only be used with threads started with QThread
```
不清楚为啥之前的没有，大体原因是由于main函数导致，将main函数中的内容移动到第一列对齐即可消除。

仔细研究发现：
```
from PyQt5.QtWidgets import QApplication, QTableView, QHeaderView, QWidget, QVBoxLayout
from PyQt5.QtGui import QStandardItemModel, QStandardItem, QIcon

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        # 创建一个 QStandardItemModel 对象
        self.model = QStandardItemModel(self)

        # 创建一个 QTableView 对象
        self.table_view = QTableView()

        # 设置模型
        self.table_view.setModel(self.model)

        # 设置布局
        layout = QVBoxLayout()
        layout.addWidget(self.table_view)
        self.setLayout(layout)

def main():
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()

main()
```
上述该代码就会存在该警告，通过给QStandardItemModel添加父级即可消除该警告。
修改参考：https://www.pythonheidong.com/blog/article/292905/8bbfe4bd89a96c1a1c9e/
该程序不是“崩溃”的：它只是在正常关闭过程中打印一条错误消息。
显示消息的原因是垃圾收集的副作用。当python关闭时，删除对象的顺序可能无法预测。这可能导致C ++端的对象按“错误”顺序删除，因此Qt有时会在这种情况下抱怨。
一种“修复”示例代码的方法是简单地重命名一些PyQt对象。如果我改名字combobox来combo，例如，该错误信息消失。对此没有什么神秘的-只是改变了删除对象的顺序。
但是，解决该问题的另一种更健壮的方法是确保QStringListModel拥有父级，因为Qt传递给组合框时很可能没有所有权。当子对象以这种方式链接在一起时，Qt应该始终正确处理子对象的删除。

还得是百度，chagpt果然不是万能的，搜索了一半天就没有给我正确答案。

### 5-2、无法获取设备驱动被替换的情景
已经无法从PnP中获取设备真实的vpid了。
```
import time
import win32com.client
from log import logger
import sys

def main():
    """主函数
    """

    wmi = win32com.client.GetObject("winmgmts:")
    logger.info(wmi)  # <COMObject winmgmts:>

    # 系统的所有PnP设备
    logger.info("===================Win32_PnPEntity=================")   
    count = 0
    for pnp in wmi.InstancesOf('Win32_PnPEntity'):
        for prop in pnp.Properties_:
            if prop.Value != None and '090C' in str(prop.Value):
                print('{} : {}'.format(prop.Name, prop.Value))
            count += 1
    logger.info('there are {} PnP devices'.format(count))

    sys.exit()
```