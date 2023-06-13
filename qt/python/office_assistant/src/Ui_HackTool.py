# -*- coding: utf-8 -*-
"""
文 件 名: Ui_HackTool.py
文件描述: 黑客工具界面
作    者: HanKin
创建日期: 2023.04.25
修改日期：2023.04.25

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *
from hack_interface import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # pyinstaller打包图片
        self.pyfile_convert_to_image(resource.usb_check_ico, USB_CHECK_ICO)
        self.usb_check_icon = QIcon(USB_CHECK_ICO)
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", '黑客工具'))
        self.setWindowIcon(self.usb_check_icon)
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()

        # 创建按钮
        scan_btn = QPushButton('显示系统信息')
        copy_btn = QPushButton('一键复制描述符')
        save_btn = QPushButton('一键保存USB设备信息')
        scan_btn.clicked.connect(self.show_os_info)

        # 创建文本框
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)  # 设置为只读状态

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(scan_btn)
        hbox.addWidget(copy_btn)
        hbox.addWidget(save_btn)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.text_edit)

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
    
    def show_os_info(self):
        """显示系统信息
        """
        
        os_info  = '客户端版本 : {}\n'.format(get_client_version())
        os_info += 'vdc版本 : {}\n'.format(get_vdc_version())
        os_info += 'agent版本 : {}\n'.format(get_agent_version())
        os_info += 'usb设备加载的驱动 : {}\n'.format(get_usb_lower_filters())
        os_info += 'image设备加载的驱动 : {}\n'.format(get_image_lower_filters())
        os_info += 'camera设备加载的驱动 : {}\n'.format(get_camera_lower_filters())
        os_info += '登录的用户名 : {}\n'.format(get_login_user_name())
        os_info += '硬件SN码 : {}\n'.format(get_hardware_sn())
        os_info += '.NET Framwork版本 : {}\n'.format(get_dotnet_versions())
        IP, MAC = get_ip_mac_address()
        os_info += 'IP地址 : {}\n'.format(IP)
        os_info += 'MAC地址 : {}\n'.format(MAC)
        system_info = get_computer_system_info()
        os_info += '电脑名称 : {}\n'.format(system_info['CSCaption'])
        os_info += '使 用 者 : {}\n'.format(system_info['UserName'])
        os_info += '操作系统 : {}\n'.format(system_info['OSCaption'])
        os_info += '系统位数 : {}\n'.format(system_info['OSArchitecture'])
        os_info += '系统版本 : {}\n'.format(system_info['Version'])
        os_info += '开机时间 : {}'.format(system_info['LastBootUpTime'])
        self.text_edit.setPlainText(os_info)
    
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
