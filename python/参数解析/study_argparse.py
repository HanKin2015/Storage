# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy_v2.py
文件描述: U盘自动拷贝文件(在电脑上面运行)
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

import argparse

def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    # 1、创建一个解析器
    parser = argparse.ArgumentParser(description='欢迎使用U盘自动拷贝文件脚本', prog='myprogram')
    
    # 2、默认的程序名(默认为study_argparse
    #parser.print_help()
    
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('upan_path', type=str, help='U盘路径')
    parser.add_argument('file_size', type=str, help='U盘路径')
    parser.add_argument("-a", "--AddConfData", action='store_true', help="增加配置数据")
    parser.add_argument("-d", "--DelConfData", action='store_true', help="删除配置数据")
    parser.add_argument("-c", "--ChgConfData", action='store_true', help="修改配置数据")
    parser.add_argument("-q", dest="data", action='store', help="查询配置数据")
    parser.add_argument("-x", default=False, dest="x",action='store_true', help="进入交互界面")
    args = parser.parse_args()
    if args.data:
        print(args.data)
    if args.x:
        pass

    #获得传入的参数
    print(args)
    
if __name__ == '__main__':
    argument_parser()