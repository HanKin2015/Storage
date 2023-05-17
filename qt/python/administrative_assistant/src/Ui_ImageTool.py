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

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        
        # 设置窗口
        _translate = QCoreApplication.translate
        self.setWindowTitle(_translate("MainWindow", '图片工具'))
        self.setGeometry(0, 0, 640, 480)
        self.setFont(QFont("Arial", 12))
        self.center()

        # 创建图片显示框
        self.image_label = QLabel('选择图片文件')
        self.image_label.setAlignment(Qt.AlignCenter)
        self.image_label.setFixedSize(500, 480)
        self.image_label.mousePressEvent = self.link_clicked
        self.image_label.setCursor(QCursor(Qt.PointingHandCursor))
        self.image_label.setStyleSheet("QLabel { color: blue; text-decoration: underline; }")

        # 创建按钮
        image_info_gb = QGroupBox('图片信息', self)
        image_info_label = QLabel('原字符串:', image_info_gb)
        imag_info_label = QLabel('原字符串:', image_info_gb)
        image_info_vbox = QVBoxLayout(image_info_gb)
        image_info_vbox.addWidget(image_info_label)
        image_info_vbox.addWidget(imag_info_label)
        
        modify_pixel_gb = QGroupBox('修改像素', self)
        self.modify_pixel_method_cb = QComboBox(modify_pixel_gb)
        self.modify_pixel_method_cb.addItem('按高度进行修改')
        self.modify_pixel_method_cb.addItem('按宽度进行修改')
        self.modify_pixel_method_cb.addItem('按高宽进行修改')
        self.modify_pixel_heigth_lineedit = QLineEdit(modify_pixel_gb)
        self.modify_pixel_heigth_lineedit.setPlaceholderText('高度')
        self.modify_pixel_width_lineedit = QLineEdit(modify_pixel_gb)
        self.modify_pixel_width_lineedit.setPlaceholderText('宽度')
        modify_button = QPushButton('修改', modify_pixel_gb)
        modify_pixel_vbox = QVBoxLayout(modify_pixel_gb)
        modify_pixel_vbox.addWidget(self.modify_pixel_method_cb)
        modify_pixel_vbox.addWidget(self.modify_pixel_heigth_lineedit)
        modify_pixel_vbox.addWidget(self.modify_pixel_width_lineedit)
        modify_pixel_vbox.addWidget(modify_button)
        
        image_crop_gb = QGroupBox('图片切割', self)
        self.crop_method_cb = QComboBox(image_crop_gb)
        self.crop_method_cb.addItem('按高度进行切分')
        self.crop_method_cb.addItem('按宽度进行切分')
        self.crop_count_lineedit = QLineEdit(image_crop_gb)
        self.crop_count_lineedit.setPlaceholderText('切割数量')
        crop_button = QPushButton('切割', image_crop_gb)
        image_crop_vbox = QVBoxLayout(image_crop_gb)
        image_crop_vbox.addWidget(self.crop_method_cb)
        image_crop_vbox.addWidget(self.crop_count_lineedit)
        image_crop_vbox.addWidget(crop_button)

        # 创建布局
        vbox = QVBoxLayout()
        vbox.addWidget(image_info_gb)
        vbox.addWidget(modify_pixel_gb)
        vbox.addWidget(image_crop_gb)
        
        hbox = QHBoxLayout()
        hbox.addWidget(self.image_label)
        hbox.addLayout(vbox)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(hbox)

    def link_clicked(self, event):
        """
        """
        
        file_path, _ = QFileDialog.getOpenFileName(self, "选择文件", ".", "All Files (*);;Text Files (*.txt)")
        if file_path:
            self.image_label.setPixmap(QPixmap(file_path))

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
    
    def crop_image(input_image_path, output_image_path_prefix):
        """按高度进行切分
        """
        
        with Image.open(input_image_path) as im:
            width, height = im.size
            third_height = height // 3
            top = 0
            bottom = third_height
            for i in range(3):
                box = (0, top, width, bottom)
                cropped_image = im.crop(box)
                cropped_image.save(f"{output_image_path_prefix}_{i}.jpg")
                top = bottom
                bottom += third_height
        
    def resize_image(input_image_path, output_image_path, size):
        """指定图片的像素
        """
        
        original_image = Image.open(input_image_path)
        width, height = original_image.size
        print('{} x {}'.format(width, height))
        if width < height:
            new_width = size
            new_height = int(size * height / width)
        else:
            new_height = size
            new_width = int(size * width / height)
        print('new {} x {}'.format(new_width, new_height))
        resized_image = original_image.resize((new_width, new_height))
        resized_image.save(output_image_path, format='JPEG')

    def compress_image(input_image_path, output_image_path, quality):
        """压缩图片文件大小
        """
        
        Image.MAX_IMAGE_PIXELS = 500000000
        with Image.open(input_image_path) as im:
            im.save(output_image_path, 'PNG', optimize=True, quality=quality)
    
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
