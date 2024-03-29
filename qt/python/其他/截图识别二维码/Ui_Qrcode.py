from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 460)
        MainWindow.setMinimumSize(QtCore.QSize(800, 460))
        MainWindow.setMaximumSize(QtCore.QSize(800, 460))
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        
        self.SaveButton = QtWidgets.QPushButton(self.centralwidget)
        self.SaveButton.setGeometry(QtCore.QRect(570, 160, 200, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.SaveButton.setFont(font)
        self.SaveButton.setObjectName("SaveButton")
        
        self.VideoLabel = QtWidgets.QLabel(self.centralwidget)
        self.VideoLabel.setGeometry(QtCore.QRect(30, 20, 500, 360))
        self.VideoLabel.setMinimumSize(QtCore.QSize(480, 360))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.VideoLabel.setFont(font)
        self.VideoLabel.setStyleSheet("background-color:#D1D1D1")
        self.VideoLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.VideoLabel.setObjectName("VideoLabel")
        self.VideoLabel.setScaledContents(True)
        
        self.ImageLabel = QtWidgets.QLabel(self.centralwidget)
        self.ImageLabel.setGeometry(QtCore.QRect(570, 230, 200, 150))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.ImageLabel.setFont(font)
        self.ImageLabel.setStyleSheet("background-color:#D1D1D1")
        self.ImageLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.ImageLabel.setObjectName("ImageLabel")
        
        self.PauseButton = QtWidgets.QPushButton(self.centralwidget)
        self.PauseButton.setGeometry(QtCore.QRect(570, 20, 200, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.PauseButton.setFont(font)
        self.PauseButton.setObjectName("PauseButton")
        
        self.RecognitionButton = QtWidgets.QPushButton(self.centralwidget)
        self.RecognitionButton.setGeometry(QtCore.QRect(570, 90, 200, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.RecognitionButton.setFont(font)
        self.RecognitionButton.setObjectName("RecognitionButton")
        
        self.DataLabel = QtWidgets.QLabel(self.centralwidget)
        self.DataLabel.setGeometry(QtCore.QRect(30, 400, 741, 41))
        self.DataLabel.setStyleSheet("background-color:#E1E1E1")
        self.DataLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.DataLabel.setObjectName("DataLabel")
        self.DataLabel.setTextInteractionFlags(QtCore.Qt.TextSelectableByMouse)
        
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "截图识别二维码"))
        self.SaveButton.setText(_translate("MainWindow", "保存二维码"))
        self.VideoLabel.setText(_translate("MainWindow", "截图展示区域"))
        self.ImageLabel.setText(_translate("MainWindow", "二维码截取区"))
        self.PauseButton.setText(_translate("MainWindow", "开启截图"))
        self.RecognitionButton.setText(_translate("MainWindow", "识别二维码"))
        self.DataLabel.setText(_translate("MainWindow", "数据展示"))
        