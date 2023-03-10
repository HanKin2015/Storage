# -*- coding: utf-8 -*-
"""
文 件 名: PyQt5_version.py
文件描述: 注意一点，conda list中有个pyqt版本很低，也无法进行升级
作    者: HanKin
创建日期: 2023.03.10
修改日期：2023.03.10

Copyright (c) 2023 HanKin. All rights reserved.
"""

from PyQt5.QtCore import QT_VERSION_STR
from PyQt5.Qt import PYQT_VERSION_STR

print('Qt 版本号：', QT_VERSION_STR)
print('PyQt 版本号：', PYQT_VERSION_STR)