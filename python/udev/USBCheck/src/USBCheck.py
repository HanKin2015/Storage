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
        self.udev_info_list = None
        
        # pyinstaller打包图片
        self.pyfile_convert_to_image(resource.USBCheck_ico, USB_CHECK_ICO)
        self.usb_check_icon = QIcon(USB_CHECK_ICO)
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", APP_NAME))
        self.setWindowIcon(self.usb_check_icon)
        self.setGeometry(0, 0, 900, 560)
        self.center()
        
        # 创建菜单栏
        menu_bar = QMenuBar()
        self.setMenuBar(menu_bar)

        # 添加菜单项
        file_memu = QMenu('文件(&F)', self)
        menu_bar.addMenu(file_memu)
        exit_action = QAction('退出(&E)', self)
        exit_action.triggered.connect(self.close)
        file_memu.addAction(exit_action)
        
        help_menu = QMenu('帮助(&H)', self)
        menu_bar.addMenu(help_menu)
        about_action = QAction('关于(&N)', self)
        about_action.triggered.connect(self.about)
        #about_action.setIcon(self.usb_check_icon)
        #about_action.setShortcut(Qt.CTRL + Qt.Key_N)
        
        help_menu.addAction(about_action)

        # 创建按钮
        scan_btn = QPushButton('扫描检测硬件改动')
        copy_btn = QPushButton('一键复制描述符')
        save_btn = QPushButton('一键保存USB设备信息')
        scan_btn.clicked.connect(self.scan_check_hardware_change)

        # 创建一个 QStandardItemModel 对象
        model = QStandardItemModel(self)
        
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

        self.status_label = QLabel('当前共有 0 个USB设备连接')
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

    def closeEvent(self, event):
        """重写 closeEvent 方法来实现窗口关闭按钮的槽函数重写
        """
        
        """
        reply = QMessageBox.question(self, '退出确认', '是否确认退出?', QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            logger.info('******** stop ********\n')
            os.remove(USB_CHECK_ICO)
            event.accept()
        else:
            event.ignore()
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
        
    def scan_check_hardware_change(self):
        """
        """
        
        self.udev_info_list = USBInterface.get_udev_info_list()
        if not self.udev_info_list:
            QMessageBox.warning(self, '警告', '没有USB设备连接')
            return
        
        # 清除所有内容
        self.root_item.removeRows(0, self.root_item.rowCount())
        
        udev_count = 0
        for udev_info in self.udev_info_list:
            if udev_info['deviceID'].count('&') <= 4:
                logger.debug(udev_info['deviceID'])
                item = QStandardItem(udev_info['Name'])
                vid, pid = USBInterface.get_vid_pid(udev_info['deviceID'])
                
                for udev_info_child in self.udev_info_list:
                    vid_child, pid_child = USBInterface.get_vid_pid(udev_info_child['deviceID'])
                    if udev_info_child['deviceID'].count('&') > 4 and vid == vid_child and pid == pid_child:
                        child = QStandardItem(udev_info_child['Name'])
                        item.appendRow(child)
                
                self.root_item.appendRow(item)
                udev_count += 1
        
        # 修改状态栏
        self.status_label.setText('当前共有 {} 个USB设备连接'.format(udev_count))

    def on_tree_view_clicked(self, index: QModelIndex):
        """树型视图点击槽函数
        """
        
        model = index.model()
        item = model.itemFromIndex(index)
        content = item.text()
        for udev_info in self.udev_info_list:
            if udev_info['Name'] == content:
                vid, pid = USBInterface.get_vid_pid(udev_info['deviceID'])
                
                # 显示描述符信息
                device_desc, cfg_desc = USBInterface.get_udev_descriptor(vid, pid)
                if device_desc == None or cfg_desc == None:
                    self.text_edit.clear()
                    self.text_edit2.clear()
                    QMessageBox.warning(self, '警告', '该USB设备描述符信息获取失败')
                    return
                desc = '{}\n\n{}'.format(device_desc, cfg_desc)
                self.text_edit.setPlainText(desc)
    
                # 显示额外信息
                sys_path, inf_names = USBInterface.get_sys_inf_path_name(udev_info['Service'])
                system_info = USBInterface.get_system_info()
                bcdUSB = USBInterface.get_bcdUSB(device_desc)
                transfer_types = USBInterface.get_endpoint_attributes(cfg_desc)
                udev_extra_info  = '设备名称 : {}\n'.format(udev_info['Name'])
                udev_extra_info += 'vid  pid : {}:{}\n'.format(vid, pid)
                udev_extra_info += 'inf 文件 : {}\n'.format(inf_names)
                udev_extra_info += 'sys 路径 : {}\n'.format(sys_path)
                udev_extra_info += '驱动状态 : {}\n'.format(udev_info['Status'])
                udev_extra_info += '传输类型 : {}\n'.format(transfer_types)
                udev_extra_info += '设备类型 : {}\n'.format(udev_info['PNPClass'])
                udev_extra_info += 'USB 协议 : {}\n\n'.format(bcdUSB)
                udev_extra_info += '电脑名称 : {}\n'.format(system_info['CSCaption'])
                udev_extra_info += '使 用 者 : {}\n'.format(system_info['UserName'])
                udev_extra_info += '操作系统 : {}\n'.format(system_info['OSCaption'])
                udev_extra_info += '系统位数 : {}\n'.format(system_info['OSArchitecture'])
                udev_extra_info += '系统版本 : {}\n'.format(system_info['Version'])
                udev_extra_info += '开机时间 : {}'.format(system_info['LastBootUpTime'])
                self.text_edit2.setPlainText(udev_extra_info)
    
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
