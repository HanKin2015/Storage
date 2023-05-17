# -*- coding: utf-8 -*-
"""
文 件 名: Ui_CopyTool.py
文件描述: 拷贝工具
作    者: HanKin
创建日期: 2023.04.26
修改日期：2023.04.26

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *
from hack_interface import *

class FileLineEdit(QLineEdit):
    def __init__(self, parent=None):
        super().__init__(parent)

    def mouseDoubleClickEvent(self, event):
        file_path, _ = QFileDialog.getOpenFileName(self, "选择文件", ".", "All Files (*);;Text Files (*.txt)")
        if file_path:
            self.setText(file_path)

    def contextMenuEvent(self, event):
        menu = QMenu(self)
        
        # 禁止右键菜单
        #event.accept()
        #menu.exec_(event.globalPos())

        # 重写右键菜单
        action1 = QAction("菜单项1", self)
        action2 = QAction("菜单项2", self)
        menu.addAction(action1)
        menu.addAction(action2)
        action = menu.exec_(event.globalPos())
        if action == action1:
            print("您选择了菜单项1")
        elif action == action2:
            print("您选择了菜单项2")

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # pyinstaller打包图片
        self.pyfile_convert_to_image(resource.msg_png, MSG_PNG)
        self.usb_check_icon = QIcon(MSG_PNG)
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", '拷贝工具'))
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()
        
        # 创建工具栏
        toolbar = QToolBar()
        self.addToolBar(toolbar)
        action1 = QAction(self.usb_check_icon, '设置服务器', self)
        action1.setToolTip('未来修改为图标')
        action2 = QAction(self.usb_check_icon, '显示行号', self)
        action3 = QAction(self.usb_check_icon, '高亮显示', self)
        toolbar.addAction(action1)
        toolbar.addAction(action2)
        toolbar.addAction(action3)

        # 创建按钮
        file_path_edit = FileLineEdit()
        file_path_edit.setPlaceholderText("请输入发送文件完整路径(可鼠标双击选择文件)")
        send_file_btn = QPushButton('发送文件')
        send_word_btn = QPushButton('发送文字')
        send_file_btn.clicked.connect(self.send_file_slot)
        send_file_btn.clicked.connect(self.send_word_slot)

        # 创建文本框
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(False)  # 设置为只读状态
        self.text_edit.setContextMenuPolicy(Qt.NoContextMenu)   # 禁止右键菜单
        
        # 创建文字拷贝按钮
        copy_word_btn = QPushButton('拷贝文字')
        copy_word_btn.clicked.connect(self.copy_word_slot)

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(file_path_edit)
        hbox.addWidget(send_file_btn)
        hbox.addWidget(send_word_btn)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.text_edit)
        vbox.addWidget(copy_word_btn)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)

    def center(self):
        """窗口居中显示
        """
        
        # 获取屏幕的大小和分辨率
        screen = QDesktopWidget().screenGeometry()
        # 获取主窗口的大小
        size = self.geometry()
        # 计算主窗口居中时左上角的坐标
        self.move(int((screen.width() - size.width()) / 2), int((screen.height() - size.height()) / 2))

    def pyfile_convert_to_image(self, image_data, image):
        """将py文件转换成图片
        """

        if not os.path.exists(image):
            tmp = open(image, 'wb+')
            tmp.write(base64.b64decode(image_data))
            tmp.close()
            
    def about(self):
        """关于
        """

        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(self, resource.FileDescription, aboutText)

    def closeEvent(self, event):
        """重写 closeEvent 方法来实现窗口关闭按钮的槽函数重写
        """

        # 自定义询问对话框
        reply = QMessageBox(self)
        reply.setWindowTitle('退出确认')
        reply.setText('是否确认退出?')
        reply.setIcon(QMessageBox.Question)
        yes_btn = reply.addButton('是', QMessageBox.YesRole)
        no_btn = reply.addButton('否', QMessageBox.NoRole)
        reply.exec_()
        if reply.clickedButton() == yes_btn:
            logger.info('******** stop ********\n')
            event.accept()
        else:
            event.ignore()
    
    def send_file_slot(self):
        """
        """
        
    def send_word_slot(self):
        """
        """
    
    def copy_word_slot(self):
        """拷贝文字槽函数
        """
        
        clipboard = QApplication.clipboard()
        clipboard.setText(self.text_edit.toPlainText())
    
def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    #app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = MainWindow()

    # 程序启动时打开主界面
    mainWindow.show()

    sys.exit(app.exec_())

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))
