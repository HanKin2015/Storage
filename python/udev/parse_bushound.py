# -*- coding: utf-8 -*-
"""
文 件 名: parse_bushound.py
文件描述: 解析bushound软件保存的usb数据包数据
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def convert_unified_unit(time_str):
    """转换成统一单位ms
    """
    
    time_str = time_str.strip()
    if time_str == '':
        return None
    #print('time string: {}'.format(time_str))
    time_num = float(time_str[:-2])
    time_unit= time_str[-2:]
    #print(time_num, time_unit)
    
    if time_unit == 'us':
        time_num /= 1000
    elif time_unit == 'sc':
        time_num *= 1000
    elif time_unit == 'ms':
        time_num = time_num
    else:
        print('unexpect time unit [ {} ]'.format(time_unit))
        return None
    #print(time_num)
    return time_num
    
def main():
    """主函数
    """
    
    line_number = 0
    line_len_set = set()
    time_list = []
    with open(r'D:\Users\Administrator\Desktop\vm.txt', 'r') as f:
        while True:
            #if line_number > 10:
            #    break
                
            line = f.readline()
            if line:
                line_number += 1
                #print(type(line), line)
                if 'IN' in line or 'OUT' in line:
                    #print(len(line), line)
                    line_len_set.add(len(line))
                    if len(line) > 130:
                        #print(line[115:123])
                        #print('{}[{}]: {}'.format(len(line), line_number, line))
                        time_num = convert_unified_unit(line[115:123])
                        if time_num == None:
                            print('{} line time unit unexpect'.format(line_number))
                            continue
                        time_list.append(time_num)
            else:
                break
    print(line_len_set)
    print('time_sum: {} ms'.format(round(sum(time_list), 2)))
    print('time max: {}, time min: {}, time count: {}'.format(max(time_list), min(time_list), len(time_list)))

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))