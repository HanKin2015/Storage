# -*- coding: utf-8 -*-
"""
文 件 名: common.py
文件描述: 公共文件
作    者: HanKin
创建日期: 2023.03.20
修改日期：2023.03.20
Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
import sys
import os
import base64
from PIL import Image
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, \
    QVBoxLayout, QPushButton, QTreeView, QTextEdit, QAbstractItemView, \
    QMenuBar, QStatusBar, QMainWindow, QMenu, QAction, QLabel, QMessageBox, \
    QDesktopWidget, qApp, QTabWidget, QSystemTrayIcon, QToolTip, QListWidgetItem, \
    QListWidget, QInputDialog, QStyledItemDelegate, QLineEdit, QFrame, \
    QComboBox, QFormLayout, QSizePolicy, QGridLayout, QGroupBox, QFileDialog, \
    QToolBar, QRadioButton, QDialog, QTableView
from PyQt5.QtCore import QModelIndex, Qt, QCoreApplication, QMetaObject, QThread, \
    pyqtSignal, QRect, QTimer, QPoint, QObject, QEvent
from PyQt5.QtGui import QStandardItemModel, QStandardItem, QIcon, \
    QPainter, QColor, QBrush, QPen, QFont, QCursor, QGuiApplication
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
from  PyQt5.QtChart import QChart, QChartView, QPieSeries, QPieSlice
import resource
from concurrent.futures import ThreadPoolExecutor
from subprocess import Popen, PIPE
import datetime
#import random
import pyautogui
import psutil
import platform
import math
import pyzbar.pyzbar as pyzbar

OFFICE_ASSISTANT_ICO = 'office_assistant.ico'
USB_CHECK_ICO        = 'udev_check.ico'
CAMERA_MONITOR_ICO   = 'camera_monitor.ico'
UDEV_DETECT_ICO      = 'udev_detect.ico'

MSG_PNG              = 'msg.png'
TEST_PNG             = 'test.png'
HELP_PNG             = 'help.png'
ABOUT_PNG            = 'about.png'
EXIT_PNG             = 'exit.png'
TMP_SCREENSHOT_PNG   = 'tmp.png'

APP_NAME = '办公助手'

# 简化版本
LITE_VERSION = True

#if not LITE_VERSION:
#    import numpy as np