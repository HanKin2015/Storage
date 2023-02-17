# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.02.15

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import re

def remove_eference_dimension(file_path):
    """移除引用标注
    """

    # 读取中文时需要添加编码utf-8
    with open(file_path, 'r', encoding = 'utf-8') as f:
        lines = f.readlines()
    print('{} have {} lines'.format(file_path, len(lines)))
    with open(file_path, 'w', encoding = 'utf-8') as f:
        # 生成正则对象
        pat = re.compile(r"(\[[0-9]+-?[0-9]*\])")
        # 计行数
        modify_count = 0
        for line in lines:
            #print(line)
            ret = pat.findall(line)
            if len(ret):
                print(ret)
                line = pat.sub('', line)
                #print(line)
                #print(pat.sub('', line))
                modify_count += 1
            #if 'TCL' in line:
            #     line = line.replace('TCL', 'HJ')
            f.write(line)
        print('modify_count = {}'.format(modify_count))
    return

def main():
    """主函数
    """
    
    # 一定需要双反斜线，否则报错OSError: [Errno 22] Invalid argument: 'D:\\Github\\GitBook\\gitbook\\Entertainment\television.md'
    # 开始很纳闷，为啥只有前面自动添加了反斜线，最后一个没有，恍然大悟猜测可能是\t有其他含义
    #file_path = 'D:\Github\GitBook\gitbook\Entertainment\wedding.md'    # 验证一下，测试正常，就是由于\t有含义导致
    file_path = 'D:\\Github\\GitBook\\gitbook\\Others\\test.md'
    remove_eference_dimension(file_path)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    
"""
(base) D:\Github\Storage\python\文件操作\移除引用标注>python remove_reference_dimension.py
******** starting ********
D:\Github\GitBook\gitbook\Others\test.md have 1124 lines
['[13]']
['[1-2]']
['[3-4]']
['[1]', '[2]']
['[3]', '[35]']
['[36]']
['[1]']
['[3]']
['[1]', '[2]', '[3]', '[4]']
['[5-6]', '[8]']
['[10-11]', '[12]', '[107]']
['[13]']
['[4]']
['[7]']
['[9]']
['[19]']
['[16]']
['[1]', '[2]']
['[1]']
['[1]']
['[1]', '[18]', '[2]', '[3]', '[4]', '[5]', '[19]', '[22]']
['[1]', '[2]', '[2]', '[4]']
['[8]', '[1]', '[4]', '[2]', '[1]', '[3]']
['[1]']
['[1]']
['[2]']
['[1]']
['[3]']
['[1]']
['[2]']
['[3]']
['[1]']
['[4]']
['[1]', '[5]']
['[1-7]']
['[3]']
['[1]', '[2]', '[3]', '[4]', '[5]', '[1]', '[6]', '[7]', '[6]', '[9]', '[1]', '[1]']
['[1]']
['[2]']
['[3]']
['[1]']
['[1]', '[2]', '[1]', '[3]', '[4]', '[5]']
['[1]']
['[1-2]']
['[3-5]']
['[6]', '[7]', '[8]', '[9]']
['[1]']
['[2]']
['[3]']
['[1]', '[2]', '[3]']
['[1]']
['[1]']
['[2]']
['[1]']
['[1-3]', '[4-5]']
['[1]']
['[1]', '[2]']
['[1]', '[2]']
['[2]']
['[1]', '[3]']
['[4]']
['[1]']
['[1-3]']
['[4]']
['[5]']
['[6]']
['[7]']
['[1]', '[1]']
['[1]']
['[1]']
['[1]']
['[1-3]']
['[4]', '[5-7]']
['[1-4]']
['[5-6]']
['[1]']
['[1]', '[2]', '[3-4]', '[5]']
['[6]']
['[3]']
['[4]']
['[1-3]', '[1]']
['[1]']
['[1]']
['[2]', '[3]', '[5]']
['[1]']
modify_count = 85
process spend 0.053 s.
"""