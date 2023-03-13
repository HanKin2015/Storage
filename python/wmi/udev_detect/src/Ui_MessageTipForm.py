# -*- coding: utf-8 -*-
"""
文 件 名: Ui_MessageTipForm.py
文件描述: 消息提示窗口类
作    者: HanKin
创建日期: 2023.03.10
修改日期：2023.03.10
Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class Ui_MessageTipForm(QWidget):
    """消息提示窗口类
    """
    
    startFlashingTrayIconSignal = pyqtSignal(str)
    stopFlashingTrayIconSignal  = pyqtSignal()
    
    def __init__(self):
        super().__init__()
    
        self.orignalHeight = None
        self.orignalPoint  = None
        self.messageCountRole = Qt.UserRole + 0x01
        self.messageTextRole  = Qt.UserRole + 0x02
        
        self.initUI()

    def initUI(self):
        """初始化界面
        """
        
        # 窗口属性
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowMaximizeButtonHint)

        # 设置QWidget的背景色和边框
        #self.setStyleSheet('''
        #    QWidget {
        #        background-color: #f0f0f0;
        #        border: 1px solid #ccc;
        #    }
        #''')

        # 创建 QLabel
        self.label = QLabel('新消息(0)', self)
        #self.label.setMaximumHeight(18)
        self.label.setContentsMargins(0, 0, 0, 0)
        # 设置样式表
        self.label.setStyleSheet('''
            QLabel {
                margin-top: 0px;
                margin-bottom: 0px;
                padding: 0px;
            }
        ''')

        # 创建 QListWidget
        self.listWidget = QListWidget(self)
        self.listWidget.itemClicked.connect(self.itemClickedSlot)
        
        # 设置样式表
        self.listWidget.setStyleSheet('''
            QListWidget {
                border: none;
            }
        ''')
        
        # 去除item选中时的虚线边框
        self.listWidget.setFocusPolicy(Qt.NoFocus)
        
        #self.listWidget.setFixedHeight(0)       # 将高度设置为0
        self.listWidget.setMaximumHeight(0)
        logger.debug(self.listWidget.height())   # 默认为30


        # 创建 QPushButton
        self.ignoreAllBtn = QPushButton('忽略全部', self)
        self.ignoreAllBtn.clicked.connect(self.ignoreAllSlot)
        self.openAllBtn = QPushButton('打开全部', self)
        self.openAllBtn.clicked.connect(self.openAllSlot)

        # 创建 QHBoxLayout 布局
        self.hbox = QHBoxLayout()
        self.hbox.addWidget(self.ignoreAllBtn)
        self.hbox.addWidget(self.openAllBtn)

        # 创建 QVBoxLayout 布局
        vbox = QVBoxLayout()
        vbox.addWidget(self.label)
        vbox.addWidget(self.listWidget)
        vbox.addLayout(self.hbox)

        # 设置窗口布局
        self.setLayout(vbox)

        #vbox.setSpacing(0)
        
        
        # 起始高度不包含listWidget
        self.orignalHeight = 88
        # 计算窗口内容的高度
        frameGeometryHeight = self.frameGeometry().height()
        frameSizeHeight = self.frameSize().height()
        contentHeight = frameGeometryHeight - frameSizeHeight
        logger.debug('orignalHeight: {}, window height: {} {} {}'.format(self.orignalHeight, 
            frameGeometryHeight, frameSizeHeight, contentHeight))
            
        # 默认位置宽度和高度
        logger.debug('label: {}, listWidget: {}, hbox: {}'.format(self.label.height(), self.listWidget.height(), self.ignoreAllBtn.height()))
        
        logger.debug('高度: {}'.format(self.frameGeometry().height()))
        logger.debug(self.frameSize().height())
        logger.debug(self.geometry().height())
        logger.debug(self.height())
        logger.debug(vbox.sizeHint().height())
        logger.debug(self.hbox.sizeHint().height())
        
        self.setGeometry(0, 0, 350, self.orignalHeight)
        self.setWindowTitle('消息提示窗口')

    def calcListWidgetHeight(self):
        """
        """
        
        listWidgetHeight = sum([self.listWidget.sizeHintForRow(i) for i in range(self.listWidget.count())]) + self.listWidget.frameWidth() * 2
        #return sum([self.listWidget.sizeHintForRow(i) for i in range(self.listWidget.count())])
        return listWidgetHeight

    def setFixedLeftBottom(self, leftBottom):
        """
        """
        
        self.orignalPoint = leftBottom

    def ignoreAllSlot(self):
        """
        """
        
        # 必须是倒序否则会删除不全有问题
        for i in range(self.listWidget.count() - 1, -1, -1):
            item = self.listWidget.item(i);
            # 用于从列表中删除一个项，并释放与该项相关联的小部件
            #self.listWidget.removeItemWidget(item);
            
            # 用于从列表中删除一个项，listWidget.count()会变化
            self.listWidget.takeItem(self.listWidget.row(item))
            
            # 只能删除一个修改一次高度，否则只会resize成删除一个的高度
            # 修改消息盒子的长度，恢复最初的高度
            self.resizeHeight()
        self.stopFlashingTrayIconSignal.emit()
        
    def openAllSlot(self):
        """
        """
        
        for i in range(self.listWidget.count() - 1, -1, -1):
            item = self.listWidget.item(i);
            self.itemClickedSlot(item);

    def itemClickedSlot(self, item):
        """
        """
        
        if item == None:
            logger.error('no item')
            return
        
        text = item.data(self.messageTextRole)
        #self.listWidget.removeItemWidget(item)
        self.listWidget.takeItem(self.listWidget.row(item))
        logger.info('getMessageCount: {}'.format(self.getMessageCount()))
        
        # 修改消息盒子的长度，每阅读一条消息，减少34pix
        self.resizeHeight()
        
        desktop = QDesktopWidget()
        logger.debug('桌面大小: {}'.format(desktop.screenGeometry()))
        # D:\Github\GitBook\gitbook\Python\pyqt5.md
        #screenGeometry = desktop.screenGeometry()
        #centerX = (screenGeometry.x() + screenGeometry.width() - self.width()) / 2
        #centerY = (screenGeometry.y() + screenGeometry.height() - self.height()) / 2
        #logger.info('中心位置:({}, {})'.format(centerX, centerY))
        #QMessageBox.warning(self, '消息', text).move(desktop.screenGeometry().center() - msgBox.rect().center())
        
        #msgBox = QMessageBox(self)
        #msgBox.setWindowTitle('消息')
        #msgBox.setText(text)
        #msgBox.setGeometry(0, 0, 100, 200)       # 设置对话框大小
        #msgBox.move(desktop.screenGeometry().center() - msgBox.rect().center())
        #msgBox.setIcon(QMessageBox.Information)  # 设置对话框类型为信息框
        #msgBox.show()

        if self.getMessageCount() == 0:
            self.stopFlashingTrayIconSignal.emit()

    def getMessageCount(self):
        """
        """
        
        return self.listWidget.count()
    
    def addToTipList(self, name, text):
        """添加信息到QListWidget
        """
        
        current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        name = '{} {}'.format(current_time, name)
        text = '{} {}'.format(current_time, text)
        
        item = QListWidgetItem(self.listWidget)
        item.setText(' {}'.format(name))
        item.setData(self.messageTextRole, text)
        self.listWidget.addItem(item)

        # 修改消息盒子的长度，每增加一条消息，增加19pix
        self.resizeHeight();
        self.startFlashingTrayIconSignal.emit(text)

    def resizeHeight(self):
        """
        """
        
         # 显示收到消息数量
        self.label.setText('新消息({})'.format(self.getMessageCount()));
        
        listWidgetHeight = self.calcListWidgetHeight()
        self.listWidget.setMaximumHeight(listWidgetHeight)
        
        height = self.orignalHeight + listWidgetHeight
        logger.debug('one row listWidget height: {}, {}'.format(self.listWidget.sizeHintForRow(0),
            self.listWidget.frameWidth()))

        self.resize(self.width(), int(height))
        logger.debug('消息提示窗口真实高度: {}, 计算高度: {}'.format(self.height(), int(height)))
        logger.debug('新位置: {} {}'.format(self.orignalPoint.x(), self.orignalPoint.y() - int(height)))
        
        # 根据新的大小移动窗口至原始位置
        leftTop = QPoint(self.orignalPoint.x(), self.orignalPoint.y() - self.height())
        self.move(leftTop)

def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    messageTipForm = Ui_MessageTipForm()
    
    rect = QDesktopWidget().geometry()
    trayIconPos = QPoint(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1)
    leftBottom = QPoint(trayIconPos.x() - messageTipForm.width()/2+1, trayIconPos.y() - 19)
    messageTipForm.setFixedLeftBottom(leftBottom)
    
    messageTipForm.addToTipList('张三', '来电话啦')
    messageTipForm.show()

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