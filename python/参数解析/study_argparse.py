# -*- coding: utf-8 -*-
"""
文 件 名: study_argparse.py
文件描述: 学习参数解析
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.03.14

Copyright (c) 2022 HanKin. All rights reserved.
"""

import argparse

def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    # 1、创建一个解析器，默认的程序名为study_argparse.py，prog属性可修改这值
    parser = argparse.ArgumentParser(description='欢迎使用优质男性信息采集系统', prog='myprogram')
    
    # 2、打印帮助信息
    #parser.print_help()
    
    # type是要传入的参数的数据类型，有str、int、
    # help是该参数的提示信息
    parser.add_argument('name', type=str, help='姓名')
    parser.add_argument('age',  type=int, help='年龄')
    parser.add_argument("-a", "--AddConfData", action='store_true', help="增加配置数据")
    parser.add_argument("-d", "--DelConfData", action='store_true', help="删除配置数据")
    parser.add_argument("-c", "--ChgConfData", action='store_true', help="修改配置数据")
    parser.add_argument("-q", dest="data", action='store', help="查询配置数据")
    parser.add_argument("-x", default=False, dest="x",action='store_true', help="进入交互界面")
    parser.add_argument('integers', metavar='N', type=int, nargs='+',
                    help='an integer for the accumulator')
    parser.add_argument('--sum', dest='accumulate', action='store_const',
                    const=sum, default=max,
                    help='sum the integers (default: find the max)')
    
    args = parser.parse_args()
    if args.data:
        print(args.data)
    if args.x:
        pass

    #获得传入的参数
    print(args)
    
if __name__ == '__main__':
    argument_parser()