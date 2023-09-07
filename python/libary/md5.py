#!/usr/bin/env python
# -*- coding: utf-8 -*-

import hashlib
import os

def get_file_md5(file_path):
    """获取文件md5值

    通过hashlib库计算文件的md5值
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的md5值
    """

    if not os.path.isfile(file_path):
        return None
    m = hashlib.md5()   #创建md5对象
    with open(file_path,'rb') as fobj:
        while True:
            data = fobj.read(4096)
            if not data:
                break
            m.update(data)  #更新md5对象
    return m.hexdigest()    #返回md5值

def get_str_md5(string):
    """获取字符串md5值

    通过hashlib库计算字符串的md5值
    
    Parameters
    ------------
    string : str
        字符串

    Returns
    -------
    str
        返回字符串的md5值
    """
    
    m = hashlib.md5(string) #创建md5对象
    return m.hexdigest()