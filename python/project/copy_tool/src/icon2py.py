# -*- coding: utf-8 -*-
"""
Created on Sat Sep 12 13:33:13 2020

@author: HanKin
"""

import base64

icon_file_path = './icon/copy_tool.ico'
target_py_file = './icon.py'

icon = open(icon_file_path, 'rb')
icon_str = base64.b64encode(icon.read())
icon_content = 'icon_img = ' + str(icon_str)

wf = open(target_py_file, 'w+')
wf.write(icon_content)
icon.close()
wf.close()
