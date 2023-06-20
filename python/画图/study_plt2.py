#!/usr/bin/python
#coding: utf-8
 
import numpy as np 
import matplotlib.pyplot as plt 
 
x = np.arange(1, 11, 1)
 
fig = plt.figure()
ax = fig.add_subplot(111)
 
# 面向对象的方式中有三种显示label的方法
 
# # 第一种
# # l后面不加逗号会出错，一定要注意
# l, = ax.plot(x, x * 2)
# l.set_label("Demo")
# ax.legend(loc = 0)
 
# 第二种
# ax.plot(x, x * 2, label = "Demo")
# ax.legend(loc = 0)
 
# 第三种
ax.plot(x, x * 2)
ax.legend(['Demo'], loc = 0)
 
 
plt.show()