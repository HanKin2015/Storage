# -*- coding: utf-8 -*-
"""
Created on Sat Nov 21 12:04:41 2020

@author: hankin
"""

import os

def main(root_dir, level=1): 
    if level==1:
        print(root_dir) 
    for lists in os.listdir(root_dir): 
        path = os.path.join(root_dir, lists) 
        print('│  '*(level-1)+'│--'+lists)
        if os.path.isdir(path): 
            main(path, level+1) 

if __name__=="__main__":
    root_dir = 'D:/Github/Storage/python/project/'
    main(root_dir)



