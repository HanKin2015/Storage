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
import pyautogui
from PIL import Image
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, \
    QVBoxLayout, QPushButton, QTreeView, QTextEdit, QAbstractItemView, \
    QMenuBar, QStatusBar, QMainWindow, QMenu, QAction, QLabel
from PyQt5.QtCore import QModelIndex, Qt
from PyQt5.QtGui import QStandardItemModel, QStandardItem
import resource

USB_CHECK_ICO = 'USBCheck.ico'
MSG_ICO = 'msg.ico'
APP_NAME = 'USB设备检查'