# -*- coding: utf-8 -*-
"""
文 件 名: common.py
文件描述: 公共文件
作    者: HanKin
创建日期: 2023.03.10
修改日期：2023.03.10
Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
from PyQt5.QtWidgets import QInputDialog, QWidget, QMainWindow, QAction, QApplication
from PyQt5.QtWidgets import QMenu, QMessageBox, QSystemTrayIcon, qApp, QToolTip, QListWidgetItem
from PyQt5.QtWidgets import QLabel, QListWidget, QPushButton, QHBoxLayout, QVBoxLayout, QDesktopWidget
from PyQt5.QtCore import QThread, pyqtSignal, QMetaObject, QCoreApplication, Qt, QRect, QTimer, QPoint
from PyQt5.QtGui import QIcon, QPainter, QColor, QBrush, QCursor
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
import sys
import os
import base64
import pyautogui
from PIL import Image

#import resource_convert_to_pyfile
#resource_convert_to_pyfile.main()
import resource

USB_CAMERA_MONITOR_TOOL_ICO = 'usb_camera_monitor_tool.ico'
MSG_ICO = 'msg.ico'
TMP_SCREENSHOT_PNG = 'tmp.png'
APP_NAME = 'USB摄像头监控工具'