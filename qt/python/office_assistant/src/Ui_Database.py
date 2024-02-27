# -*- coding: utf-8 -*-
"""
文 件 名: Ui_Database.py
文件描述: 数据库界面
作    者: HanKin
创建日期: 2024.02.27
修改日期：2024.02.27

Copyright (c) 2024 HanKin. All rights reserved.
"""

from common import *
from sqlite3_interface import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # pyinstaller打包图片
        self.pyfile_convert_to_image(resource.usb_check_ico, USB_CHECK_ICO)
        self.usb_check_icon = QIcon(USB_CHECK_ICO)
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", '数据库工具'))
        self.setWindowIcon(self.usb_check_icon)
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()
        
        # 创建工具栏
        toolbar = QToolBar()
        self.addToolBar(toolbar)
        create_db = QAction(self.usb_check_icon, '新建数据库', self)
        open_db = QAction(self.usb_check_icon, '打开数据库', self)
        create_table = QAction(self.usb_check_icon, '新建数据表', self)
        toolbar.addAction(create_db)
        toolbar.addAction(open_db)
        toolbar.addAction(create_table)
        create_db.triggered.connect(self.create_db_slot)

        # 创建按钮
        delete_files_path_cb = QComboBox(self)
        delete_files_path_cb.addItem(r'D:\Users\Administrator\My Document\WeChat Files\wxid_2gh9d5knc6th21\FileStorage\MsgAttach')
        delete_files_path_cb.addItem(r'D:\Github\Storage\python\project\files_classify_delete-duplication\a')
        delete_files_path_cb.addItem(r'C:\Users\Administrator\AppData\Local\口袋助理\files')
        send_file_btn = QPushButton('更新数据表')
        send_word_btn = QPushButton('删除数据表')
        send_file_btn.clicked.connect(self.send_file_slot)
        send_file_btn.clicked.connect(self.send_word_slot)

        # 创建文本框
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(False)  # 设置为只读状态
        self.text_edit.setContextMenuPolicy(Qt.NoContextMenu)   # 禁止右键菜单
        
        # 创建文字拷贝按钮
        copy_word_btn = QPushButton('写入数据表中')
        copy_word_btn.clicked.connect(self.copy_word_slot)

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(delete_files_path_cb)
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
            os.remove(USB_CHECK_ICO)
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
    
    def create_db_slot(self):
        file_path, _ = QFileDialog.getSaveFileName(self, "选择保存路径", ".", "All Files (*);;Text Files (*.txt)")
        if file_path:
            print(file_path)
    
    def open_db_slot(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "选择文件", ".", "All Files (*);;Text Files (*.txt)")
        if file_path:
            print(file_path)

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
