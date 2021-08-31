# -*- coding: utf-8 -*-
"""
Created on Thu May 13 22:26:12 2021

@author: hj159
"""

import requests
from os import getcwd

url = "https://github.com/someguy/brilliant/blob/master/somefile.txt"
directory = getcwd()
print("current directory: ", directory)
filename = directory + 'somefile.txt'
r = requests.get(url)

#print(r.content)

f = open(filename,'w')
f.write(r.content)