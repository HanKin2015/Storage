# -*- coding: utf-8 -*-
"""
文 件 名: duplicate_key.py
文件描述: 重复键值的情况
作    者: HanKin
创建日期: 2023.10.16
修改日期：2023.10.16

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import json

def main():
    """主函数
    """

    my_str = '{"vm_name":"win10lqb0002_test","status":"等待Agent接入","agent_version":"","vm_name":"win10-21H20001_test","status":"已关机","agent_version":""}'
    
    my_dict = json.loads(my_str)
    print(my_dict)

def debug():
    """调试
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

