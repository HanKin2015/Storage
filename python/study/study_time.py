#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import time  # 引入time模块
import calendar
import datetime
 
ticks = time.time()
print("当前时间戳为:", ticks)

# 获取当前时间
localtime = time.localtime(time.time())
print("本地时间为 :", localtime)

# 获取格式化的时间
localtime = time.asctime( time.localtime(time.time()) )
print("本地时间为 :", localtime)

# 格式化成2016-03-20 11:45:39形式
print time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 
 
# 格式化成Sat Mar 28 22:24:24 2016形式
print time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()) 
  
# 将格式字符串转换为时间戳
a = "Sat Mar 28 22:24:24 2016"
print time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"))

# 获取某月日历
cal = calendar.month(2016, 1)
print "以下输出2016年1月份的日历:"
print cal

# 使用datetime模块来获取当前的日期和时间
i = datetime.datetime.now()
print ("当前的日期和时间是 %s" % i)
print ("ISO格式的日期和时间是 %s" % i.isoformat() )
print ("当前的年份是 %s" %i.year)
print ("当前的月份是 %s" %i.month)
print ("当前的日期是  %s" %i.day)
print ("dd/mm/yyyy 格式是  %s/%s/%s" % (i.day, i.month, i.year) )
print ("当前小时是 %s" %i.hour)
print ("当前分钟是 %s" %i.minute)
print ("当前秒是  %s" %i.second)