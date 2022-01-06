# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 13:35:12 2020

@author: Administrator
"""

from multiprocessing.dummy import Pool as ThreadPool
import configure_data_share_storage
import argparse
import os

#设置进程并发数量
g_thread_num = 1

#任务数量
def TaskNum():
    return [i for i in range(1,3)]

#具体的任务
def RunTask(case_id):
    configure_data_share_storage.main()

#测试多进程并发操作
def TestMultProcess():
    pool = ThreadPool(g_thread_num)
    pool.map(RunTask, TaskNum())
    pool.close()
    pool.join()      

#解析参数
def ParseArgument():
    argument_parser = argparse.ArgumentParser(description="配置数据共享存储模块")   
    
    argument_parser.add_argument("-a", "--AddConfData", action='store_true', help="增加配置数据")
    argument_parser.add_argument("-d", "--DelConfData", action='store_true', help="删除配置数据")
    argument_parser.add_argument("-c", "--ChgConfData", action='store_true', help="修改配置数据")
    argument_parser.add_argument("-q", "--QuyConfData", dest="data", action='store', help="查询配置数据")
    args = argument_parser.parse_args()
    if args.data:
        print(args.data)
        
def Operation():
    while True:
        print("\n\t\t当前进程ID: {} \n \
               默认数据表有：'employees' 'svnAccounts' \n \
               增加配置数据: a ('employees', 22200, 'Bill', 20000) \n \
               删除配置数据：d ('employees', 22200) \n \
               修改配置数据：c ('employees', 222000, 'salary', 250) \n \
               查询配置数据：q ('employees') \n \
               退出： e \n".format(os.getpid()))
        str = input("请输入：");
        print ("你输入的内容是: ", str)
        opt = str.strip()[0:1]
        content = str.strip()[1:]
        print(content)
        content = content.replace('(', '')
        content = content.replace(')', '')
        data = content.split(',')
        data = [elem.strip() for elem in data]

        if opt=='e':
            break;
        if opt=='a':
            conf_data = (data[1], data[2], data[3])
            configure_data_share_storage.AddConfData(data[0], conf_data)
        if opt=='q':
            configure_data_share_storage.QuyConfData(data[0])
            

def main():
    #打开日志
    configure_data_share_storage.OpenLog()
    #连接数据库
    configure_data_share_storage.ConnectSqlite()
    #创建数据表
    configure_data_share_storage.CreateTable()

    #测试
    with open("./pid.txt", "a") as f:
        f.write(str(os.getpid()))
        f.write("\n")
    Operation()
    
    #关闭数据库
    configure_data_share_storage.CloseSqlite()
    #关闭日志
    configure_data_share_storage.CloseLog()

if __name__=='__main__':
    ParseArgument()
    main()
    
    
    
    
    
    
    