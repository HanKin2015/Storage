# -*- coding: utf-8 -*-
"""
文 件 名: wikipedia.py
文件描述: 存储一些日常查询百度百科的一些词条
作    者: HanKin
创建日期: 2023.04.17
修改日期：2023.04.18

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *
import wikipedia_interface

class ListDelegate(QStyledItemDelegate):
    def paint(self, painter, option, index):
        super().paint(painter, option, index)
        if index.row() < index.model().rowCount() - 1:
            pen = QPen(Qt.gray, 1, Qt.SolidLine)
            painter.setPen(pen)
            painter.drawLine(option.rect.bottomLeft(), option.rect.bottomRight())

class Ui_MainWindow(object):
    def __init__(self):
        super().__init__()
        self.image_prepare()
    
    def setupUi(self, MainWindow):
        """
        """
    
        # 主窗口ID
        self.ui = MainWindow
        self.window_setting()
        QMetaObject.connectSlotsByName(self.ui)
        self.ui.destroyed.connect(self.close)
        
        # 初始化菜单栏
        self.init_menu()
        
        # 初始化状态栏
        self.init_status_bar()

        # 构建内容组件
        self.init_body()

        # 去掉边框和置顶显示以及任务栏显示
        #self.ui.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        
        # 去掉背景框
        #self.ui.setAttribute(Qt.WA_TranslucentBackground)

        # 配置托盘
        #self.init_tray_icon()
        
        # 百科词条目录加载显示
        self.load_wikipedia_catalog()

    def init_status_bar(self):
        """初始化状态栏
        """
        
        # 创建状态栏
        status_bar = QStatusBar(self.ui)
        self.ui.setStatusBar(status_bar)

        self.status_label = QLabel('当前共有 0 个百科词条')
        status_bar.addWidget(self.status_label)

    def init_body(self):
        """初始化主体界面
        """

        hbox_top = QHBoxLayout()

        # 创建编辑器
        self.edit = QLineEdit(self.ui)
        hbox_top.addWidget(self.edit)

        # 创建按钮
        query_btn = QPushButton('查询', self.ui)
        query_btn.clicked.connect(self.query_btn_slot)
        hbox_top.addWidget(query_btn)
        
        # 创建编辑框小部件
        self.display_text_edit = QTextEdit()
        self.display_text_edit.setReadOnly(True)  # 设置为只读状态
        self.display_text_edit.setFontPointSize(16)

        # 创建列表小部件
        self.listwidget = QListWidget(self.ui)
        self.listwidget.itemClicked.connect(self.item_clicked_slot)
        self.listwidget.setItemDelegate(ListDelegate())
        
        hbox_bottom = QHBoxLayout()
        hbox_bottom.addWidget(self.display_text_edit, 3)
        hbox_bottom.addWidget(self.listwidget, 1)

        # 将编辑器和列表小部件添加到垂直布局中
        vbox = QVBoxLayout()
        vbox.addLayout(hbox_top)
        vbox.addLayout(hbox_bottom)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.ui.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)

    def init_menu(self):
        """初始化菜单栏
        """
        
        # 创建菜单栏
        menu_bar = QMenuBar()
        self.ui.setMenuBar(menu_bar)

        # 添加菜单项
        file_memu = QMenu('文件(&F)', self.ui)
        menu_bar.addMenu(file_memu)
        exit_action = QAction(QIcon(EXIT_PNG), '退出(&Q)', self.ui)
        exit_action.triggered.connect(self.ui.close)
        exit_action.setShortcut(Qt.CTRL + Qt.Key_Q)
        file_memu.addAction(exit_action)
        
        language_memu = QMenu('语言(&L)', self.ui)
        menu_bar.addMenu(language_memu)
        
        run_memu = QMenu('运行(&R)', self.ui)
        menu_bar.addMenu(run_memu)
        remove_dimension_action = QAction(QIcon(ABOUT_PNG), '移除引用标注(&E)', self.ui)
        remove_dimension_action.triggered.connect(self.remove_dimension_slot)
        remove_dimension_action.setShortcut(Qt.CTRL + Qt.Key_E)
        run_memu.addAction(remove_dimension_action)
        import_database_action = QAction(QIcon(ABOUT_PNG), '导入数据库(&I)', self.ui)
        import_database_action.triggered.connect(self.import_database_slot)
        import_database_action.setShortcut(Qt.CTRL + Qt.Key_I)
        run_memu.addAction(import_database_action)
        
        help_menu = QMenu('帮助(&H)', self.ui)
        menu_bar.addMenu(help_menu)
        
        about_action = QAction(QIcon(ABOUT_PNG), '关于(&A)', self.ui)
        about_action.triggered.connect(self.about)
        about_action.setShortcut(Qt.CTRL + Qt.Key_A)
        help_menu.addAction(about_action)

    def query_btn_slot(self):
        """
        """

        key = self.edit.text().strip()
        if key == '':
            logger.warning('input query content please')
            return
        logger.info('query {}...'.format(key))
        
        value = wikipedia_interface.db_query(key)
        self.display_text_edit.setText(value)
        
    def image_prepare(self):
        """图片预处理
        pyinstaller打包图片
        """
        
        self.pyfile_convert_to_image(resource.wikipedia_ico, WIKIPEDIA_ICO)
        self.pyfile_convert_to_image(resource.about_png, ABOUT_PNG)
        self.pyfile_convert_to_image(resource.exit_png, EXIT_PNG)
        self.pyfile_convert_to_image(resource.help_png, HELP_PNG)
    
    def window_setting(self):
        """窗口设置
        """
        
        self.ui.setObjectName('MainWindow')
        _translate = QCoreApplication.translate
        self.ui.setWindowTitle(_translate('MainWindow', APP_NAME))
        self.ui.setWindowIcon(QIcon(WIKIPEDIA_ICO))
        self.ui.setGeometry(0, 0, 900, 560)
        self.center()

    def center(self):
        """窗口居中显示
        """
        
        # 获取屏幕的大小和分辨率
        screen = QDesktopWidget().screenGeometry()
        # 获取主窗口的大小
        size = self.ui.geometry()
        # 计算主窗口居中时左上角的坐标
        self.ui.move(int((screen.width() - size.width()) / 2), int((screen.height() - size.height()) / 2))

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
        QMessageBox.about(self.ui, resource.FileDescription, aboutText)

    def close(self):
        """关闭
        参考微信qq，现在都是没有二次确认退出，这个函数主要是为了情况新生成的文件
        """
        
        logger.info('******** stop ********\n')
        os.remove(WIKIPEDIA_ICO)
        os.remove(HELP_PNG     )
        os.remove(ABOUT_PNG    )
        os.remove(EXIT_PNG     )

    def remove_dimension_slot(self):
        """
        """

        result = wikipedia_interface.remove_eference_dimension(NEW_ENTRY_PATH)
        if result == -1:
            QMessageBox.about(self.ui, '警告', '{} 文件不存在'.format(NEW_ENTRY_PATH))
            return
        
    def import_database_slot(self):
        """
        """

        entry_list = wikipedia_interface.parse_content(NEW_ENTRY_PATH)
        if entry_list == None:
            QMessageBox.about(self.ui, '警告', '{} 文件不存在'.format(NEW_ENTRY_PATH))
            return
        wikipedia_interface.db_import(entry_list)
        self.load_wikipedia_catalog()
        
    def load_wikipedia_catalog(self):
        """加载维基百科目录
        """
        
        key_list = wikipedia_interface.get_wikipedia_entries()
        
        self.listwidget.clear()
        for key in key_list:
            self.listwidget.addItem(str(key))
        self.status_label.setText('当前共有 {} 个百科词条'.format(len(key_list)))
    
    def item_clicked_slot(self, item):
        """百科目录列表点击槽函数
        """
        
        if item == None:
            logger.error('no item')
            return
        
        key = item.text()
        logger.info(key)
        value = wikipedia_interface.db_query(key)
        self.display_text_edit.setText(value)

def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    #app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = QMainWindow()

    # 构建程序界面
    ui = Ui_MainWindow()
    ui.setupUi(mainWindow)

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