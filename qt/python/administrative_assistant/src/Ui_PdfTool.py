# -*- coding: utf-8 -*-
"""
文 件 名: Ui_PictureTool.py
文件描述: 图片工具
作    者: HanKin
创建日期: 2023.05.15
修改日期：2023.05.15

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

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", 'PDF工具'))
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()
        
        # 创建按钮
        file_path_label = QLabel('文件路径:')
        self.file_path_edit = FileLineEdit()
        self.file_path_edit.setPlaceholderText("请输入发送文件完整路径(可鼠标双击选择文件)")
        
        save_path_label = QLabel('保存路径:')
        self.save_path_edit = FileLineEdit()
        self.save_path_edit.setPlaceholderText("请输入发送文件完整路径(可鼠标双击选择文件)")
        
        merged_path_label = QLabel('合并路径:')
        self.merged_path_edit = FileLineEdit()
        self.merged_path_edit.setPlaceholderText("请输入发送文件完整路径(可鼠标双击选择文件)")

        convert_button = QPushButton('转换')
        convert_button.clicked.connect(self.convert_button_slot)
        merged_button = QPushButton('合并')
        merged_button.clicked.connect(self.merged_button_slot)
        
        hbox = QHBoxLayout()
        hbox.addWidget(convert_button)
        hbox.addStretch(1)
        hbox.addWidget(merged_button)
        
        grid = QGridLayout()
        grid.addWidget(file_path_label, 0, 0)
        grid.addWidget(self.file_path_edit, 0, 1)
        grid.addWidget(save_path_label, 1, 0)
        grid.addWidget(self.save_path_edit, 1, 1)
        grid.addWidget(merged_path_label, 2, 0)
        grid.addWidget(self.merged_path_edit, 2, 1)
        grid.addLayout(hbox, 3, 0, 1, 3)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(grid)

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
    
    def convert_button_slot(self):
        """
        """
        
    def merged_button_slot(self):
        """
        """
    
    def pdf_convert_to_image(self, pdf_path, merged_image=False):
        """pdf转换成图像
        """

        # 设置PDF文件路径
        pdf_path = 'example.pdf'

        # 将PDF文件转换为图像
        images = convert_from_path(pdf_path)

        # 创建一个文件夹来保存图像
        if not os.path.exists('images'):
            os.makedirs('images')

        # 将图像保存到文件夹中
        for i, image in enumerate(images):
            image.save(f'images/page_{i+1}.png', 'PNG')

        # 将所有图像合成为一张长图
        image_files = os.listdir('images')
        image_files.sort()
        images = [Image.open(os.path.join('images', f)) for f in image_files]
        width, height = images[0].size
        total_height = height * len(images)
        new_image = Image.new('RGB', (width, total_height))
        y_offset = 0
        for image in images:
            new_image.paste(image, (0, y_offset))
            y_offset += height

        # 保存合成后的图像
        new_image.save('merged_image.jpg', 'JPEG')
        
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
