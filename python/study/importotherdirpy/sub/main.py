import sys
import os

# 得到当前根目录
o_path = os.getcwd() # 返回当前工作目录
sys.path.append('../') # 添加自己指定的搜索路径
import mod1
from lib import mod2
import lib.mod2