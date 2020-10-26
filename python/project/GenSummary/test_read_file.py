# -*- coding: utf-8 -*-
"""
Created on Tue Aug  4 21:58:49 2020

@author: Administrator
"""

import os

print(os.getcwd())

try:
    f = open("./Blog/README.md", 'r', encoding='utf-8')
    print(f.readlines())
    f.close()
except Exception as ex:
    print(ex)
    pass
