# -*- coding: utf-8 -*-
"""
Created on Sat Jul  4 16:30:36 2020

@author: hejian29996
@description: 
    1、对sqlite3数据库的具体操作:增删改查
    2、

"""

import sqlite3
import logging
from concurrent_log_handler import ConcurrentRotatingFileHandler
import encryption_algorithm_library
import sys


#路径
g_data_path = "./data"
g_log_path = "./log"
#数据库名称
g_databases_name = "confdatashare.db"
#数据表名称
g_employees_tablename = "employees"
g_svnaccounts_tablename = "svnAccounts"
#日志名称
g_log_name = "database_operation.log"
#日志自动备份数量
g_log_backup_count = 3
#单个日志大小500k
g_log_size = 500*1024

#数据库游标
global g_databases, g_databases_cursor

#日志变量
global g_logger, g_handler, g_console


def OpenLog():
    """打开日志.

    sqlite3数据库操作日志，日志存放在log/database_operation.log.

    Parameters
    ----------
    null

    Returns
    -------
    null

    """
    
    global g_logger, g_handler, g_console
    g_logger = logging.getLogger(__name__)
    g_logger.setLevel(level = logging.INFO)
    # 定义一个RotatingFileHandler，最多备份3个日志文件，每个日志文件最大5K
    g_handler = ConcurrentRotatingFileHandler(g_log_name,"a", maxBytes=g_log_size, backupCount=g_log_backup_count)
    g_handler.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    g_handler.setFormatter(formatter)
     
    g_console = logging.StreamHandler()
    g_console.setLevel(logging.INFO)
    g_console.setFormatter(formatter)
     
    g_logger.addHandler(g_handler)
    g_logger.addHandler(g_console)
    
    g_logger.info("open log sucess.")
    

def CloseLog():
    """打开日志.

    sqlite3数据库操作日志，日志存放在log/database_operation.log.

    Parameters
    ----------
    arg1 : int
        arg1的参数说明
    arg2 : str
        arg2的参数说明

    Returns
    -------
    bool
        返回值说明

    """
    
    global g_logger, g_handler, g_console
    g_logger.info("close log.")
    g_logger.removeHandler(g_handler)
    g_logger.removeHandler(g_console)


#增加配置数据
def AddConfData(table_name, conf_data):
    if isinstance(conf_data, tuple) == False:
        g_logger.error("configure data is not tuple type, it's {} type".format(type(conf_data)))
        return False
    if len(conf_data) != 3:
        g_logger.error("configure data size don't eqaul 3")
        return False
    
    global g_databases
    try:
        sql = "insert or replace into {} values (?,?,?)".format(table_name)
        g_databases.execute(sql, conf_data)
        g_databases.commit()
    except:
        g_logger.error("insert configure data into {} failed.".format(table_name))
        return False
    g_logger.info("insert configure data into {} success.".format(table_name))
    return True

#删除配置数据
def DelConfData(table_name, job_number):
    global g_databases_cursor, g_databases
    sql = "delete from {} where jobNumber={}".format(table_name, job_number)
    try:
        g_databases_cursor.execute(sql)  
        g_databases.commit()
    except:
        g_logger.error("detele jobNumber({}) from {} table failed".format(job_number, table_name))
        return False
    g_logger.info("detele jobNumber({}) from {} table success".format(job_number, table_name))
    return True

#修改配置数据
def ChgConfData(table_name, job_number, column_name, value):
    
    g_logger.info("change data")
    global g_databases_cursor, g_databases
    sql = "update {} set {}={} where jobNumber={}".format(table_name, column_name, int(value), int(job_number))
    #print(sql)
    try:
        g_databases_cursor.execute(sql)
        g_databases.commit()
    except:
        g_logger.error("update {} table failed.".format(table_name))
        return False
    g_logger.info("update {} table success.".format(table_name))
    return True

import json
#查询配置数据
def QuyConfData(table_name):
    sql = "select * from {}".format(table_name)
    try:
        g_databases_cursor.execute(sql)
    except:
        g_logger.error("query {} table failed.".format(table_name))
        return None
    result = g_databases_cursor.fetchall()
    column_name = ["jobNumber", "firstName", "salary"]
    result_json = []
    for elem in result:
        elem_json = json.dumps(dict(zip(column_name, elem)))
        result_json.append(elem_json)
    result_json = '\n'.join(result_json)
    g_logger.info("query configure data result: \n[\n\"{}\":[ \n{}\n]\n]".format(table_name, result_json))
    return result_json



#通知修改机制
    
#创建数据表
def CreateTable():
    try:
        g_logger.info("if not exists create table - {}".format(g_employees_tablename))
        sql = "create table if not exists {} ( \
                jobNumber integer primary key, \
                firstName varchar(10), \
                salary integer)".format(g_employees_tablename)
        g_databases_cursor.execute(sql)
    except:
        g_logger.error("create {} table failed.".format(g_employees_tablename))
        return False  
    
    try:
        g_logger.info("if not exists create table - {}".format(g_svnaccounts_tablename))
        sql = "create table if not exists {} ( \
                jobNumber integer primary key, \
                user varchar(20), \
                pwd varchar(20))".format(g_svnaccounts_tablename)
        g_databases_cursor.execute(sql)
    except:
        g_logger.error("create {} table failed.".format(g_svnaccounts_tablename))
        return False
    g_logger.info("create all tables sucess.")
    return True

#连接sqlite数据库
def ConnectSqlite():
    global g_databases, g_databases_cursor
    try:
        g_logger.info("connect databases - {}.".format(g_databases_name))
        g_databases = sqlite3.connect(g_databases_name)
    except:
        g_logger.error("connect database failed.")
        return False
        
    g_databases_cursor = g_databases.cursor()
    return True

#关闭sqlite数据库
def CloseSqlite():
    g_databases.close()
    g_logger.info("close databases sucess.")

def Test():
    employees_message = [(100000, "Bill", 20000), (100001, "George", 25000), (100002, "Thomas", 30000)]
    for employe in employees_message:
        AddConfData(g_employees_tablename, employe)
    svnaccounts_message = [(10000, "bill123", 123456), (100001, "george123", 123456), (10002, "thomas123", 123456)]
    for svnaccount in svnaccounts_message:
        AddConfData(g_svnaccounts_tablename, svnaccount)
    DelConfData(g_employees_tablename, 1)
    ChgConfData(g_employees_tablename, 100001, "salary", 250)
    QuyConfData(g_employees_tablename)   
    
def main():
    #打开日志
    OpenLog()
    #连接数据库
    ConnectSqlite()
    #创建数据表
    CreateTable()

    #测试
    Test()
    
    #关闭数据库
    CloseSqlite()
    #关闭日志
    CloseLog()

if __name__ == '__main__':
    main()

