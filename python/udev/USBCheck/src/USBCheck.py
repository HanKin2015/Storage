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
import USBInterface

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
        self.setGeometry(0, 0, 700, 500)
        self.center()
        
        # 创建菜单栏
        menu_bar = QMenuBar()
        self.setMenuBar(menu_bar)

        # 添加菜单项
        file_memu = QMenu('文件', self)
        menu_bar.addMenu(file_memu)
        exit_action = QAction('退出', self)
        exit_action.triggered.connect(self.close)
        file_memu.addAction(exit_action)
        
        help_menu = QMenu('帮助', self)
        menu_bar.addMenu(help_menu)
        about_action = QAction('关于', self)
        about_action.triggered.connect(self.about)
        help_menu.addAction(about_action)


        # 创建按钮
        scan_btn = QPushButton('扫描检测硬件改动')
        copy_btn = QPushButton('一键复制描述符')
        save_btn = QPushButton('一键保存USB设备信息')
        scan_btn.clicked.connect(self.scan_check_hardware_change)

        # 创建一个 QStandardItemModel 对象
        model = QStandardItemModel()
        
        # 设置表头
        model.setHorizontalHeaderLabels(['主机控制器'])
        self.root_item = model.invisibleRootItem()

        # 创建一个 QTreeView 对象
        tree_view = QTreeView()
        
        # 设置模型
        tree_view.setModel(model)
        tree_view.setSelectionMode(QAbstractItemView.SingleSelection)
        tree_view.clicked.connect(self.on_tree_view_clicked)

        # 创建文本框
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)  # 设置为只读状态
        self.text_edit2 = QTextEdit()
        self.text_edit2.setReadOnly(True)  # 设置为只读状态

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(scan_btn)
        hbox.addWidget(copy_btn)
        hbox.addWidget(save_btn)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)

        vbox2 = QVBoxLayout()
        vbox2.addWidget(tree_view)
        vbox2.addWidget(self.text_edit2)

        hbox2 = QHBoxLayout()
        hbox2.addLayout(vbox2)
        hbox2.addWidget(self.text_edit)

        vbox.addLayout(hbox2)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)
        
        # 创建状态栏
        status_bar = QStatusBar(self)
        self.setStatusBar(status_bar)

        self.status_label = QLabel('当前共有0个USB设备连接')
        status_bar.addWidget(self.status_label)

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

    def scan_check_hardware_change(self):
        """
        """
        
        udev_info_list = USBInterface.get_udev_info_list()
        if not udev_info_list:
            QMessageBox.warning(self, '警告', '没有USB设备连接')
            #return
        
        # 清除所有内容
        self.root_item.removeRows(0, self.root_item.rowCount())
        
        for udev_info in udev_info_list:
            if udev_info['deviceID'].count('&') == 1:
                logger.debug(udev_info['deviceID'])
                item = QStandardItem(udev_info['Name'])
                vid, pid = USBInterface.get_vid_pid(udev_info['deviceID'])
                
                for udev_info_child in udev_info_list:
                    vid_child, pid_child = USBInterface.get_vid_pid(udev_info_child['deviceID'])
                    if udev_info_child['deviceID'].count('&') > 1 and vid == vid_child and pid == pid_child:
                        child = QStandardItem(udev_info_child['Name'])
                        item.appendRow(child)
                
                self.root_item.appendRow(item)

    def on_tree_view_clicked(self, index: QModelIndex):
        model = index.model()
        item = model.itemFromIndex(index)
        content = item.text()
        self.text_edit.setPlainText(content)
    
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
