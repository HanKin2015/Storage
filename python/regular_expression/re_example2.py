# -*- coding: utf-8 -*-
"""
文 件 名: re_example2.py
文件描述: 学习正则表达式
作    者: HanKin
创建日期: 2023.09.28
修改日期：2023.09.28

Copyright (c) 2023 HanKin. All rights reserved.
"""

import re
import time
import json

def test1():
    """对于字符串"1,*,*;3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    对于字符串"3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    匹配是否存在1,*,*字符串
    """
    
    str1 = "1,*,*;3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    str2 = "3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    # 错误的方式
    if "1,*,*" in str1:
        print("str1 exist 1,*,* string")
    # 正确的方式
    if "1,*,*" in str2.split(";"):
        print("str2 exist 1,*,* string")

    # 使用正则
    pattern = r"\b1,*,*\b"
    
    match = re.search(pattern, str1)
    if match:
        print("字符串str1中包含'1,*,*'")
    else:
        print("字符串str1中不包含'1,*,*'")

    match = re.search(pattern, str2)
    if match:
        print("字符串str2中包含'1,*,*'")
    else:
        print("字符串str2中不包含'1,*,*'")

def test2(data):
    """
    对于字符串'{"vm_name":"win10lqb0002_test","status":"正常工作，已经接入","version":"5.5.3.54","vm_name":"win10-21H20001_test","status":"正常工作","version":"5.5.3.54"}'
    我想把它切割成两个json对象，由于键值的重复，导致不能直接转换成json对象
    """
    
    # 使用正则表达式找到"vm_name"前面的逗号
    pattern = r'(?<=,)(?="vm_name")'
    match = re.search(pattern, data)

    if match:
        #comma_index = match.start()
        #print("逗号位置: {}".format(comma_index))
        pass
    else:
        print("逗号未找到")

    split_data = re.split(pattern, data)
    #print(split_data)

    for index, agent in enumerate(split_data):
        agent = agent.strip("{},\n")
        agent = "{" + agent + "}"
        print("agent string{}: {}".format(index+1, agent))
        print("agent json format <{}>".format(agent))
        json_obj = json.loads(agent)
        print(json_obj)

def main():
    data = '{"vm_name":"win10lqb0002_test","status":"正常工作，已经接入","version":"5.5.3.54","vm_name":"win10-21H20001_test","status":"正常工作","version":"5.5.3.54"}'
    test2(data)
    
    # 测试test2方法是不是存在bug
    data = '{"vm_name":"win10lqb0002_test","status":"正常工作，已经接入","version":"5.5.3.54"}\n'
    test2(data)

if __name__ == '__main__':
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
 