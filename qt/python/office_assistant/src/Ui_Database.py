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
from AES_encrypt_decrypt import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.udev_info_list = None
        self.db_path = r'D:/Github/Storage/python/study/sqlite3/udev_info.db'
        self.connection = None
        
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
        create_db_action = QAction(self.usb_check_icon, '新建数据库', self)
        open_db_action = QAction(self.usb_check_icon, '打开数据库', self)
        create_table_action = QAction(self.usb_check_icon, '新建数据表', self)
        toolbar.addAction(create_db_action)
        toolbar.addAction(open_db_action)
        toolbar.addAction(create_table_action)
        create_db_action.triggered.connect(self.create_db_slot)
        open_db_action.triggered.connect(self.open_db_slot)
        create_table_action.triggered.connect(self.create_table_slot)

        # 创建按钮
        self.db_name_btn = QPushButton('db_name')
        self.db_name_btn.setEnabled(False)
        self.table_list_cb = QComboBox(self)
        show_table_btn = QPushButton('显示数据表')
        update_table_btn = QPushButton('更新数据表')
        drop_table_btn = QPushButton('删除数据表')
        show_table_btn.clicked.connect(self.show_table_slot)
        update_table_btn.clicked.connect(self.update_table_slot)
        drop_table_btn.clicked.connect(self.drop_table_slot)

        # 创建文本框
        self.device_type_lineedit = QLineEdit()
        self.device_type_lineedit.setPlaceholderText("设备类型")
        self.text_edit = QTextEdit()
        self.text_edit.setPlaceholderText("设备描述符信息")
        self.text_edit.setReadOnly(False)  # 设置为只读状态
        self.text_edit.setContextMenuPolicy(Qt.NoContextMenu)   # 禁止右键菜单
        self.remark_lineedit = QLineEdit()
        self.remark_lineedit.setPlaceholderText("备注")
        
        # 创建文字拷贝按钮
        copy_word_btn = QPushButton('写入数据表中')
        copy_word_btn.clicked.connect(self.insert_data_slot)

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(self.db_name_btn)
        hbox.addWidget(self.table_list_cb)
        hbox.addWidget(show_table_btn)
        hbox.addWidget(update_table_btn)
        hbox.addWidget(drop_table_btn)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.device_type_lineedit)
        vbox.addWidget(self.text_edit)
        vbox.addWidget(self.remark_lineedit)
        vbox.addWidget(copy_word_btn)

        # 创建一个中心窗口，并将布局设置为中心窗口的布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        central_widget.setLayout(vbox)
        
        # 设置默认打开的数据库
        self.update_table_list()

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
            close_sqlite3(self.connection)
            event.accept()
        else:
            event.ignore()
    
    def update_table_list(self):
        """更新数据表列表下拉框内容
        """
        self.db_name_btn.setText(os.path.basename(self.db_path))
        connection = open_sqlite3(self.db_path)
        self.connection = connection
        table_list = get_table_list(connection)
        print(table_list)
        self.table_list_cb.clear()
        for table in table_list:
            self.table_list_cb.addItem(table)
    
    def create_db_slot(self):
        """新建数据库槽函数
        """
        db_path, db_type = QFileDialog.getSaveFileName(self, "选择保存路径", ".", "database (*.db);;All Files (*);;sqlite3 (*.sqlite3)")
        if db_path:
            print(db_path, db_type)
            self.db_path = db_path
            self.update_table_list()
    
    def open_db_slot(self):
        """打开数据库槽函数
        """
        db_path, _ = QFileDialog.getOpenFileName(self, "选择文件", ".", "All Files(*);;Text Files(*.txt)")
        if db_path:
            print(db_path)
            self.db_path = db_path
            self.update_table_list()
    
    def drop_table_slot(self):
        """删除数据表槽函数
        """
        table_name = self.table_list_cb.currentText()
        if table_name:
            reply = QMessageBox(self)
            reply.setWindowTitle('确认')
            reply.setText('确定删除{}数据表?'.format(table_name))
            reply.setIcon(QMessageBox.Question)
            yes_btn = reply.addButton('是', QMessageBox.YesRole)
            no_btn = reply.addButton('否', QMessageBox.NoRole)
            reply.exec_()
            if reply.clickedButton() == yes_btn:
                sql = "DROP TABLE {};".format(table_name)
                cursor = self.connection.cursor()
                cursor.execute(sql)
                self.update_table_list()
    
    def show_table_slot(self):
        """
        """
        table_name = self.table_list_cb.currentText()
        if table_name:
            sql = "SELECT * from {};".format(table_name)
            cursor = self.connection.cursor()
            cursor.execute(sql)
            data = cursor.fetchall()
            
            std = ShowTableDialog(data)
            std.exec_()
    
    def update_table(self, sql):
        """
        """
        cursor = self.connection.cursor()
        cursor.execute(sql)
    
    def update_table_slot(self):
        """更新数据表槽函数
        """
        table_name = self.table_list_cb.currentText()
        if table_name:
            sql = "PRAGMA table_info({});".format(table_name)
            cursor = self.connection.cursor()
            cursor.execute(sql)
            table_info = cursor.fetchall()
            # 打印表结构信息
            for column in table_info:
                print(column)
            ctd = TableOperationDialog("update", table_name, table_info)
            ctd.table_operation_signal.connect(self.update_table)
            ctd.exec_()
        
    def create_table(self, sql):
        """很奇怪，改成普通函数后无法识别
        在 Python 中，如果你想要连接一个类的方法作为信号的槽，你需要使用 self 来指明这个方法属于哪个对象
        """
        cursor = self.connection.cursor()
        cursor.execute(sql)
        self.update_table_list()
        
    def create_table_slot(self):
        ctd = TableOperationDialog("create")
        ctd.table_operation_signal.connect(self.create_table)
        ctd.exec_()

    def insert_data_slot(self):
        """
        """
        device_type = self.device_type_lineedit.text()
        descriptor = self.text_edit.toPlainText()
        remark = self.remark_lineedit.text()
        if not all([device_type, descriptor, remark]):
            QMessageBox.warning(self, '检查空值', '请填写所有内容')
            return
        
        #sql = "PRAGMA table_info({});".format(table_name)
        cursor = self.connection.cursor()
        
        #table_info = cursor.fetchall()
        table_name = self.table_list_cb.currentText()
        if table_name:
            #key, iv, encrypted_descriptor = encrypt_data(descriptor.encode('utf-8'))
            #descriptor = "{}{}{}".format(key, iv, encrypted_descriptor)
        
            #SQL_INSERT_ONE_DATA = 'INSERT INTO {} VALUES(NULL, "{}", "{}", "{}");'.format(table_name,
            #                      device_type, descriptor, remark)
            #print(SQL_INSERT_ONE_DATA)
            try:
            #    cursor.execute(SQL_INSERT_ONE_DATA)
                # 使用参数化查询和绑定变量来插入数据
                cursor.execute("INSERT INTO {} (device_type, descriptor, remark) VALUES (?, ?, ?)".format(table_name),
                                (device_type, descriptor, remark,))
                self.connection.commit()    # 这一行很重要，否则无法添加进去
                if cursor.rowcount > 0:
                    QMessageBox.information(self, '结果', '添加数据成功')
                    print("SQL执行成功")
                else:
                    QMessageBox.critical(self, '结果', '添加数据失败')
                    print("SQL执行未修改任何行")
            except sqlite3.Error as e:
                QMessageBox.critical(self, '结果', 'SQL执行失败')
                print("SQL执行失败:", e)

class ShowTableDialog(QDialog):
    def __init__(self, table_data):
        super().__init__()
        self.resize(365, 240)
        self.setWindowTitle("数据表内容")

         # 创建数据模型
        model = QStandardItemModel(4, 3)
        for row, data in enumerate(table_data):
            for column in range(3):
                item = QStandardItem(data[column+1])
                model.setItem(row, column, item)

        # 设置列名
        model.setHorizontalHeaderLabels(['device_type', 'descriptor', 'remark'])

        # 创建表格视图
        table_view = QTableView()
        table_view.setModel(model)

        # 设置表格视图为主窗口的中心部件
        #self.setCentralWidget(table_view)
        
        # 创建垂直布局
        layout = QVBoxLayout()
        layout.addWidget(table_view)

        # 将布局设置为对话框的布局
        self.setLayout(layout)

class TableOperationDialog(QDialog):
    table_operation_signal = pyqtSignal(str)
    def __init__(self, opt_type, table_name=None, table_info=None):
        super().__init__()
        self.resize(360, 240)
        self.setWindowTitle("数据表操作")

        table_name_label = QLabel("表名")
        data_type_cb = QComboBox(self)
        data_type_cb.addItem("TEXT")
        data_type_cb.addItem("INT")
        self.table_name_lineedit = QLineEdit()
        column1_label = QLabel("列名1")
        data_type_cb1 = QComboBox(self)
        data_type_cb1.addItem("TEXT")
        data_type_cb1.addItem("INT")
        self.column1_lineedit = QLineEdit()
        column2_label = QLabel("列名2")
        data_type_cb2 = QComboBox(self)
        data_type_cb2.addItem("TEXT")
        data_type_cb2.addItem("INT")
        self.column2_lineedit = QLineEdit()
        column3_label = QLabel("列名3")
        data_type_cb3 = QComboBox(self)
        data_type_cb3.addItem("TEXT")
        data_type_cb3.addItem("INT")
        self.column3_lineedit = QLineEdit()
        ok_btn = QPushButton("确定")
        if opt_type == "create":
            ok_btn.clicked.connect(self.create_table_slot)
        elif opt_type == "update":
            if len(table_info) < 4:
                print("table info size ({}) less than 4".format(len(table_info)))
                return
            self.table_name_lineedit.setText(table_name)
            self.column1_lineedit.setText(table_info[1][1])
            self.column2_lineedit.setText(table_info[2][1])
            self.column3_lineedit.setText(table_info[3][1])
            ok_btn.clicked.connect(self.update_table_slot)
        elif opt_type == "query":
            ok_btn.clicked.connect(self.create_table_slot)

        grid = QGridLayout(self)
        grid.addWidget(table_name_label, 0, 0)
        grid.addWidget(data_type_cb, 0, 1)
        grid.addWidget(self.table_name_lineedit, 0, 2)
        grid.addWidget(column1_label, 1, 0)
        grid.addWidget(data_type_cb1, 1, 1)
        grid.addWidget(self.column1_lineedit, 1, 2)
        grid.addWidget(column2_label, 2, 0)
        grid.addWidget(data_type_cb2, 2, 1)
        grid.addWidget(self.column2_lineedit, 2, 2)
        grid.addWidget(column3_label, 3, 0)
        grid.addWidget(data_type_cb3, 3, 1)
        grid.addWidget(self.column3_lineedit, 3, 2)
        grid.addWidget(ok_btn, 4, 2)

        self.setLayout(grid)
        #self.center()

    def create_table_slot(self):
        """sqlite3.OperationalError: AUTOINCREMENT is only allowed on an INTEGER PRIMARY KEY
        """
        SQL_CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS {}
          (ID   INTEGER      PRIMARY KEY AUTOINCREMENT,
           {}   TEXT                NOT NULL,
           {}   TEXT                NOT NULL,
           {}   TEXT                NOT NULL);'''.format(self.table_name_lineedit.text(), self.column1_lineedit.text(),
                                                         self.column2_lineedit.text(), self.column3_lineedit.text())
        print(SQL_CREATE_TABLE)
        self.table_operation_signal.emit(SQL_CREATE_TABLE)
        self.close()

    def update_table_slot(self):
        """
        ALTER TABLE table_name ADD COLUMN column_name data_type;
        ALTER TABLE table_name DROP COLUMN column_name;
        ALTER TABLE table_name RENAME COLUMN old_column_name TO new_column_name;
        
        修改列属性的示例步骤：
        -- 添加新列
        ALTER TABLE table_name ADD COLUMN new_column_name new_data_type;

        -- 将旧列的数据迁移到新列
        UPDATE table_name SET new_column_name = old_column_name;

        -- 删除旧列
        ALTER TABLE table_name DROP COLUMN old_column_name;

        -- 如果需要，重命名新列以匹配旧列的名称
        ALTER TABLE table_name RENAME COLUMN new_column_name TO old_column_name;
        """
        SQL_CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS {}
          (ID   INT     PRIMARY KEY NOT NULL,
           {}   TEXT                NOT NULL,
           {}   TEXT                NOT NULL,
           {}   TEXT                NOT NULL);'''.format(self.table_name_lineedit.text(), self.column1_lineedit.text(),
                                                         self.column2_lineedit.text(), self.column3_lineedit.text())
        print(SQL_CREATE_TABLE)
        self.table_operation_signal.emit(SQL_CREATE_TABLE)
        self.close()

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
