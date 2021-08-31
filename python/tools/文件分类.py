# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import os,shutil

path = './'
#type_names = ['pdf', 'png']  # file type
files = os.listdir(path)

for file in files:
    folder_name = file.split('.')[-1]  # get last type
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
    shutil.move(file, folder_name)
    
print('done')