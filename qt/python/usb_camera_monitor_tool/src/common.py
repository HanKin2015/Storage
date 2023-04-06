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
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, \
    QVBoxLayout, QPushButton, QTreeView, QTextEdit, QAbstractItemView, \
    QMenuBar, QStatusBar, QMainWindow, QMenu, QAction, QLabel, QMessageBox, \
    QDesktopWidget, qApp, QSystemTrayIcon, QListWidgetItem, QListWidget, \
    QToolTip, QInputDialog
from PyQt5.QtCore import QModelIndex, Qt, QCoreApplication, pyqtSignal, QThread, \
    QTimer, QMetaObject, QPoint, QRect
from PyQt5.QtGui import QStandardItemModel, QStandardItem, QIcon, \
    QCursor, QPainter, QColor, QBrush
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
import sys
import os
import base64
import pyautogui
from PIL import Image
from hack_interface import *

#import resource_convert_to_pyfile
#resource_convert_to_pyfile.main()
import resource

USB_CAMERA_MONITOR_TOOL_ICO = 'usb_camera_monitor_tool.ico'
MSG_ICO = 'msg.ico'
TMP_SCREENSHOT_PNG = 'tmp.png'
APP_NAME = 'USB摄像头监控工具'