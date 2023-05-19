# -*- coding: utf-8 -*-
"""
文 件 名: Ui_MathTool.py
文件描述: 数学工具
作    者: HanKin
创建日期: 2023.05.19
修改日期：2023.05.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", '数学工具'))
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()

        # 进制转换
        decimal_conversion_gb = QGroupBox('进制转换', self)
        dec_rb = QRadioButton('十进制')
        dec_rb.setChecked(True) # 设置单选按钮为选中状态
        dec_rb.toggled.connect(self.radio_button_slot)
        self.dec_label = QLabel('0', decimal_conversion_gb)
        
        hex_rb = QRadioButton('十六进制')
        hex_rb.toggled.connect(self.radio_button_slot)
        self.hex_label = QLabel('0', decimal_conversion_gb)
        
        oct_rb = QRadioButton('八进制')
        oct_rb.toggled.connect(self.radio_button_slot)
        self.oct_label = QLabel('0', decimal_conversion_gb)
        
        bin_rb = QRadioButton('二进制')
        bin_rb.toggled.connect(self.radio_button_slot)
        self.bin_label = QLabel('0', decimal_conversion_gb)
        
        self.number_lineedit = QLineEdit(decimal_conversion_gb)
        
        decimal_conversion_grid = QGridLayout(decimal_conversion_gb)
        decimal_conversion_grid.addWidget(dec_rb, 0, 0)
        decimal_conversion_grid.addWidget(self.dec_label, 0, 1)
        decimal_conversion_grid.addWidget(hex_rb, 1, 0)
        decimal_conversion_grid.addWidget(self.hex_label, 1, 1)
        decimal_conversion_grid.addWidget(oct_rb, 2, 0)
        decimal_conversion_grid.addWidget(self.oct_label, 2, 1)
        decimal_conversion_grid.addWidget(bin_rb, 3, 0)
        decimal_conversion_grid.addWidget(self.bin_label, 3, 1)
        decimal_conversion_grid.addWidget(self.number_lineedit, 4, 0)

        # 最大公约数和最小公倍数
        gcd_lcm_gb = QGroupBox('公约倍数', self)
        self.gcd_label = QLabel('最大公约数: 0', gcd_lcm_gb)
        self.lcm_label = QLabel('最小公倍数: 0', gcd_lcm_gb)
        self.cd_label = QLabel('公约数: 0', gcd_lcm_gb)
        self.x_lineedit = QLineEdit(gcd_lcm_gb)
        self.y_lineedit = QLineEdit(gcd_lcm_gb)
        gcd_lcm_btn = QPushButton('求值', gcd_lcm_gb)
        gcd_lcm_btn.clicked.connect(self.gcd_lcm_btn_slot)
       
        gcd_lcm_grid = QGridLayout(gcd_lcm_gb)
        gcd_lcm_grid.addWidget(self.gcd_label, 0, 0)
        gcd_lcm_grid.addWidget(self.lcm_label, 1, 0)
        gcd_lcm_grid.addWidget(self.cd_label, 2, 0)
        gcd_lcm_grid.addWidget(self.x_lineedit, 3, 0)
        gcd_lcm_grid.addWidget(self.y_lineedit, 3, 1)
        gcd_lcm_grid.addWidget(gcd_lcm_btn, 3, 2)

        # 创建布局
        vbox = QVBoxLayout()
        vbox.addWidget(decimal_conversion_gb)
        vbox.addWidget(gcd_lcm_gb)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)

    def radio_button_slot(self):
        """
        """
        
        rb = self.sender()
        if rb.isChecked() == True: # 判断单选按钮是否被选中
            print('<' + rb.text() + '> 被选中')
        else:
            print('<' + rb.text() + '> 被取消选中状态')

    def gcd_lcm_btn_slot(self):
        """
        """
        
        pass

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
