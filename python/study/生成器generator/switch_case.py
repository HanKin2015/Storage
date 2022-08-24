# -*- coding: utf-8 -*-
"""
文 件 名: switch_case.py
文件描述: python中没有switch case用法
作    者: HanKin
创建日期: 2022.08.22
修改日期：2022.08.22

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import sys
import math

'''
字典用法扩展: 用字典映射简单的switch case 语句
其他语言中有switch case用法,但是python中没有,不过可以用字典映射来代替
如下:
------------------伪代码分割线------------------
# 功能:实现输入数字0-7,打印出相应的英文星期几
day = 0

swhitc (day):
{
    case 0:
    dayName = 'Monday'
    break

    case 1:
    dayName = 'Tuesday'
    break

    case 2:
    dayName = 'Wednesday'
    break

    case 3:
    dayName = 'Thursday'
    break

    case 4:
    dayName = 'Friday'
    break

    case 5:
    dayName = 'Saturday'
    break

    case 6:
    dayName = 'Sunday'
    break

    default:
    dayName = 'Unknow'
}
------------------伪代码分割线------------------
'''

'''
# -----简单的字典映射switch case-----
# 可用字典映射来实现以上代码的 switch case 功能

day = 1

likeswitch = {
    0 : 'Monday',
    1 : 'Tuesday',
    2 : 'Wednesday'
    3 : 'Thursday'
    4 : 'Friday'
    5 : 'Saturday'
    6 : 'Sunday'
}

# 这里是用get()方法,是为了在字典中如果没有找到key时,就返回'Unknow',
# 相当于switch case 中的default
day_name = likeswitch.get(day,'Unknow')  #这里用到了字典中的get()方法.

print(day_name)
# 运行结果:Tuesday
# -----简单的字典映射switch case-----
'''

# -----字典映射复杂的switch case----
# switch中,case下面可以写代码块,其实Python的字典也可以.

print('请输入您想翻译星期几:')
userinput = input("输入星期几(如星期一)：")     #输入 '星期一'
#userinput = raw_input("输入星期几(如星期一)：")    # Python2.x

def translateMonday():
    return 'Monday'

def translateTuesday():
    return 'Tuesday'

def translateWednesday():
    return 'Wednesday'

def translateThursday():
    return 'Thursday'

def translateFriday():
    return 'Friday'

def translateSaturday():
    return 'Saturday'

def translateSunday():
    return 'Sunday'

def unknow():
    return '请输入正确的信息'

# 从这里可以得出,字典的value也可以是函数.
# value的值,直接写函数名
# 这里的key是字符串,value是函数
chineseName = {
    '星期一': translateMonday,
    '星期二': translateTuesday,
    '星期三': translateWednesday,
    '星期四': translateThursday,
    '星期五': translateFriday,
    '星期六': translateSaturday,
    '星期日': translateSunday
}

# 注意这里的第二个参数也必须是一个函数,否则会报错的.
# get()方法后面还有一个()
englishName = chineseName.get(userinput,unknow)()

print(englishName)


# 输入信息: 星期一
# 输出结果: Monday
# 扩展了字典中 key和value的知识点,value可以是函数,那么就可以用这样的方法来实现比较复杂的业务逻辑了.
# 完美代替了switch case