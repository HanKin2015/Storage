# -*- coding: utf-8 -*-
"""
文 件 名: study_re.py
文件描述: 学习正则表达式
作    者: HanKin
创建日期: 2022.07.18
修改日期：2022.07.18

Copyright (c) 2022 HanKin. All rights reserved.
"""

import re
import time

def match_search_example():
    """
    (0, 3)
    <re.Match object; span=(0, 3), match='www'>
    None
    (0, 3)
    (11, 14)
    """

    print(re.match('www', 'www.runoob.com').span())   # 在起始位置匹配
    print(re.match('www', 'www.runoob.com'))          # 在起始位置匹配
    print(re.match('com', 'www.runoob.com'))          # 不在起始位置匹配
    
    print(re.search('www', 'www.runoob.com').span())  # 在起始位置匹配
    print(re.search('com', 'www.runoob.com').span())  # 不在起始位置匹配

def match_group_example():
    """
    matchObj.group() :  Cats are smarter than dogs
    matchObj.group(1) :  Cats
    matchObj.group(2) :  smarter
    """

    line = "Cats are smarter than dogs"
     
    matchObj = re.match( r'(.*) are (.*?) .*', line, re.M|re.I)
     
    if matchObj:
       print("matchObj.group() : ", matchObj.group())
       print("matchObj.group(1) : ", matchObj.group(1))
       print("matchObj.group(2) : ", matchObj.group(2))
    else:
       print("No match!!")

def search_group_example():
    """
    searchObj.group() :  ---- Cats are smarter than dogs ----
    searchObj.group(1) :  ---- Cats
    searchObj.group(2) :  smarter
    """
    
    line = "---- Cats are smarter than dogs ----";
     
    searchObj = re.search( r'(.*) are (.*?) .*', line, re.M|re.I)
     
    if searchObj:
       print("searchObj.group() : ", searchObj.group())
       print("searchObj.group(1) : ", searchObj.group(1))
       print("searchObj.group(2) : ", searchObj.group(2))
    else:
       print("Nothing found!!")

def sub_example():
    """
    电话号码是:  2004-959-559
    电话号码是 :  2004959559
    """

    phone = "2004-959-559 # 这是一个国外电话号码"
     
    # 删除字符串中的 Python注释 
    num = re.sub(r'#.*$', "", phone)
    print("电话号码是: ", num)
     
    # 删除非数字(-)的字符串 
    num = re.sub(r'\D', "", phone)
    print("电话号码是 : ", num)

# 将匹配的数字乘以 2
def double(matched):
    value = int(matched.group('value'))
    return str(value * 2)
def repl_example():
    """
    A46G8HFD1134
    """
    
    s = 'A23G4HFD567'
    print(re.sub('(?P<value>\d+)', double, s))

def compile_example1():
    """
    None
    None
    <re.Match object; span=(3, 5), match='12'>
    12
    3
    5
    (3, 5)
    """

    pattern = re.compile(r'\d+')                    # 用于匹配至少一个数字
    m = pattern.match('one12twothree34four')        # 查找头部，没有匹配
    print(m)

    m = pattern.match('one12twothree34four', 2, 10) # 从'e'的位置开始匹配，没有匹配
    print(m)
    
    m = pattern.match('one12twothree34four', 3, 10) # 从'1'的位置开始匹配，正好匹配
    print(m)                                        # 返回一个 Match 对象

    print(m.group(0))   # 可省略 0
    print(m.start(0))   # 可省略 0
    print(m.end(0))     # 可省略 0
    print(m.span(0))    # 可省略 0

def compile_example2():
    """
    <re.Match object; span=(0, 11), match='Hello World'>
    Hello World
    (0, 11)
    Hello
    (0, 5)
    World
    (6, 11)
    ('Hello', 'World')
    """

    pattern = re.compile(r'([a-z]+) ([a-z]+)', re.I)   # re.I 表示忽略大小写
    m = pattern.match('Hello World Wide Web')
    print(m)            # 匹配成功，返回一个 Match 对象

    print(m.group(0))   # 返回匹配成功的整个子串
    print(m.span(0))    # 返回匹配成功的整个子串的索引
    print(m.group(1))   # 返回第一个分组匹配成功的子串
    print(m.span(1))    # 返回第一个分组匹配成功的子串的索引
    print(m.group(2))   # 返回第二个分组匹配成功的子串
    print(m.span(2))    # 返回第二个分组匹配成功的子串
    print(m.groups())   # 等价于 (m.group(1), m.group(2), ...)
    
    # IndexError: no such group
    #m.group(3)         # 不存在第三个分组

def findall_example():
    """
    ['123', '456']
    ['88', '12']
    [('width', '20'), ('height', '10')]
    """

    pattern = re.compile(r'\d+')   # 查找数字
    result1 = pattern.findall('runoob 123 google 456')
    result2 = pattern.findall('run88oob123google456', 0, 10)
    print(result1)
    print(result2)
    
    # 多个匹配模式，返回元组列表
    result = re.findall(r'(\w+)=(\d+)', 'set width=20 and height=10')
    print(result)   

def finditer_example():
    """
    12 
    32 
    43 
    3
    """
    
    it = re.finditer(r"\d+", "12a32bc43jf3") 
    for match in it: 
        print (match.group())

def split_example():
    """
    ['runoob', 'runoob', 'runoob', '']
    ['', ' ', 'runoob', ', ', 'runoob', ', ', 'runoob', '.', '']
    ['', 'runoob, runoob, runoob.']
    ['hello world']
    """

    print(re.split('\W+', 'runoob, runoob, runoob.'))
    print(re.split('(\W+)', ' runoob, runoob, runoob.'))
    print(re.split('\W+', ' runoob, runoob, runoob.', 1))
    print(re.split('a*', 'hello world'))   # 对于一个找不到匹配的字符串而言，split 不会对其作出分割

def test():
    """
    '(?P...)' 分组匹配
    例：身份证 1102231990xxxxxxxx
    
    {'province': '110', 'city': '223', 'born_year': '1990'}
    直接将匹配结果直接转为字典模式，方便使用。
    """

    s = '1102231990xxxxxxxx'
    res = re.search('(?P<province>\d{3})(?P<city>\d{3})(?P<born_year>\d{4})',s)
    print(res.groupdict())

def main():
    match_search_example()
    match_group_example()
    search_group_example()
    sub_example()
    repl_example()
    compile_example1()
    compile_example2()
    findall_example()
    finditer_example()
    split_example()
    test()

if __name__ == '__main__':
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
 