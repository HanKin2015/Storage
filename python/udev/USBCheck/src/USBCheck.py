# -*- coding: utf-8 -*-
"""
文 件 名: USBCheck.py
文件描述: USB设备检查
作    者: HanKin
创建日期: 2023.03.20
修改日期：2023.03.20

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # pyinstaller打包图片
        self.pyfile_convert_to_image(resource.USBCheck_ico, USB_CHECK_ICO)
        self.usb_check_icon = QIcon(USB_CHECK_ICO)
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", APP_NAME))
        self.setWindowIcon(self.usb_check_icon)
        self.setGeometry(0, 0, 600, 400)
        
        # 创建菜单栏
        menu_bar = QMenuBar(self)
        self.setMenuBar(menu_bar)

        # 添加菜单项
        help_menu = QMenu('帮助', self)
        menu_bar.addMenu(help_menu)

        about_action = QAction('关于', self)
        about_action.triggered.connect(self.about)
        help_menu.addAction(about_action)

        exit_action = QAction('退出', self)
        exit_action.triggered.connect(self.close)
        help_menu.addAction(exit_action)

        # 创建按钮
        button1 = QPushButton('扫描检测硬件改动')
        
        button2 = QPushButton('Button 2')
        button3 = QPushButton('Button 3')

        # 创建树型结构
        model = QStandardItemModel()
        root_item = model.invisibleRootItem()

        item1 = QStandardItem('Item 1')
        item2 = QStandardItem('Item 2')
        item3 = QStandardItem('Item 3')

        child1 = QStandardItem('Child 1')
        child2 = QStandardItem('Child 2')
        child3 = QStandardItem('Child 3')

        root_item.appendRow(item1)
        root_item.appendRow(item2)
        root_item.appendRow(item3)

        item1.appendRow(child1)
        item1.appendRow(child2)
        item2.appendRow(child3)

        # 设置标题行
        model.setHeaderData(0, Qt.Horizontal, '主机控制器')
        tree_view = QTreeView()
        tree_view.setModel(model)
        tree_view.setSelectionMode(QAbstractItemView.SingleSelection)
        tree_view.clicked.connect(self.on_tree_view_clicked)

        # 创建文本框
        text_edit = QTextEdit()
        text_edit.setReadOnly(True)  # 设置为只读状态

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(button1)
        hbox.addWidget(button2)
        hbox.addWidget(button3)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)

        hbox2 = QHBoxLayout()
        hbox2.addWidget(tree_view)
        hbox2.addWidget(text_edit)

        vbox.addLayout(hbox2)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)
        
        # 创建状态栏
        status_bar = QStatusBar(self)
        self.setStatusBar(status_bar)

        status_label = QLabel("Ready")
        status_bar.addWidget(status_label)

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

    def on_tree_view_clicked(self, index: QModelIndex):
        model = index.model()
        item = model.itemFromIndex(index)
        content = item.text()
        self.findChild(QTextEdit).setPlainText(content)
    
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
