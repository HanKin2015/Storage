# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:06:41 2020

@author: 何健29996
@description:
    实现一个配置数据共享存储模块

    要求：
    1.对外支持多线程/多进程的数据安全读写访问；
    2.对外提供数据更改通知机制，能及时让外部获取数据的变化。
    3.数据存储要求支持加密安全，加密算法要求可扩展；

    说明：
    1.配置数据存储在SQLite里，模块读取出来后转换为JSON格式给业务模块使用
"""
import socket
import time
import win32api, win32con 
import logging
import os, sys
import sqlite3
import json
import win32api, win32con 
import threading
import socket_library
import encryption_algorithm_library

# 日志和数据文件夹路径
data_path = './data'
log_path = './log'
log_name = '/confdata_sharestroage_service.log'

# 服务监听配置
ip = '127.0.0.1'
server_port = 8384
listen_client_maxcnt = 5
buffer_size = 1024

# 连接的服务端端口
connect_ports = set()
# 端口操作的表名
port_operate_table = dict()

# 建立必要的文件夹
if not os.path.exists(data_path):
    os.makedirs(data_path)
if not os.path.exists(log_path):
    os.makedirs(log_path)

# 配置日志
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename=log_path+log_name,
                    filemode='a')

# 数据库名称
database_name = "/confdatashare.db"

# 数据库游标
global database, database_cursor

def client_login(pid, table_name):
	"""客户端登录.
	
	客户端接入的时候通知服务端连接.
	
	parameters
	------------
	pid : int
		进程pid
	table_name : str
		当前客户端监听的数据表名称
		
	Returns
	------------
	client_obj : object
		客户端socket对象
	"""
	
	# 创建客户端socket套接字
	client_obj = client_socket_library()
	# 开启客户端socket守护线程
	port = int(pid) + 5000
	start_socket_thread(client_obj, ip, port)
	# 客户端发送连接请求
	client_obj.send_message(ip, server_port, "connect", pid)

	port_operate_table[port] = table_name
	connect_ports.add(port)
	logging.info("客户端{}登录成功，监听数据表:port = {}, table_name = {}".format(pid, port, table_name))
	return client_obj

def client_logout(client_obj, pid):
	"""客户端登录.
	
	客户端退出的时候通知服务端断开连接.
	Parameters
	------------
	client_obj : object
		客户端socket对象
	pid : int
		客户端进程pid
	"""
	
	client_obj.send_message(ip, server_port, "connect", pid)

def connect_sqlite():
	"""连接sqlite数据库.

	连接数据库,并初始化数据库游标.

	Returns
    -------
    bool
        成功返回True,失败False

	"""

	global database, database_cursor
	try:
	    logging.info("connect databases - {}.".format(data_path + database_name))
	    database = sqlite3.connect(data_path + database_name)
	except:
	    logging.error("connect database failed.")
	    return False
	    
	database_cursor = database.cursor()
	return True

def close_sqlite():
	"""关闭sqlite数据库.
	"""

	database.close()
	logging.info("close databases sucess.")

def create_table(table_name, sql):
	"""创建数据表.

	Parameters
    ----------
    table_name : str
        创建的表的名称
    sql : str
        合法的sql语句

    Returns
    -------
    bool
        成功返回True,失败False

	"""

	try:
	    database_cursor.execute(sql)
	except:
	    logging.error("create {} table failed.".format(table_name))
	    return False  

	logging.info("create {} table sucess.".format(table_name))
	return True

def add_confdata(table_name, conf_data):
	"""增加配置数据.
	Parameters
    ----------
    table_name : str
        数据表名称
    conf_data : str
        配置数据

    Returns
    -------
    bool
        成功返回True,失败返回False
	"""

	if isinstance(conf_data, tuple) == False:
	    logging.error("configure data is not tuple type, it's {} type".format(type(conf_data)))
	    return False
	if len(conf_data) != 3:
	    logging.error("configure data size don't eqaul 3")
	    return False

	try:
	    sql = "insert or replace into {} values (?,?,?)".format(table_name)
	    database.execute(sql, conf_data)
	    database.commit()
	except:
	    logging.error("insert configure data into {} failed.".format(table_name))
	    return False
	logging.info("insert configure data into {} success.".format(table_name))

	# 数据库修改通知机制触发
	send_change_notify(table_name, ip)
	return True

def del_confdata(table_name, primary_key):
	"""删除配置数据.
	Parameters
    ----------
    table_name : str
        数据表名称
    primary_key : int
        主键

    Returns
    -------
    bool
        成功返回True,失败返回False
	"""

	sql = "delete from {} where jobNumber={}".format(table_name, primary_key)
	try:
	    database_cursor.execute(sql)  
	    database.commit()
	except:
	    logging.error("detele jobNumber({}) from {} table failed".format(primary_key, table_name))
	    return False
	logging.info("detele jobNumber({}) from {} table success".format(primary_key, table_name))

	# 数据库修改通知机制触发
	send_change_notify(table_name, ip)
	return True

def chg_confdata(table_name, primary_key, column_name, value):
	"""修改配置数据.
	Parameters
    ----------
    table_name : str
        数据表名称
    primary_key : str
        配置数据
    column_name : str
    	需要修改的配置列名
    value : str
    	修改后的值

    Returns
    -------
    bool
        成功返回True,失败返回False
	"""
    
	logging.info("change data")
	sql = "update {} set {}={} where jobNumber={}".format(table_name, column_name, int(value), int(primary_key))

	try:
	    database_cursor.execute(sql)
	    database.commit()
	except:
	    logging.error("update {} table failed.".format(table_name))
	    return False
	logging.info("update {} table success.".format(table_name))

	# 数据库修改通知机制触发
	send_change_notify(table_name, ip)
	return True

def qry_confdata(table_name):
	"""查询配置数据.
	Parameters
    ----------
    table_name : str
        数据表名称

    Returns
    -------
    result_json : str
        json格式的数据表内容
	"""

	sql = "select * from {}".format(table_name)
	try:
	    database_cursor.execute(sql)
	except:
	    logging.error("query {} table failed.".format(table_name))
	    return None
	result = database_cursor.fetchall()
	column_name = ["jobNumber", "firstName", "salary"]
	result_json = []
	for elem in result:
	    elem_json = json.dumps(dict(zip(column_name, elem)))
	    result_json.append(elem_json)
	result_json = '\n\t'.join(result_json)
	result_json = "[\n\"{}\":[ \n\t{}\n\t]\n]".format(table_name, result_json)
	logging.info("query configure data result: \n{}".format(result_json))
	return result_json

def test_sqllite():
	"""测试sqlite数据库.
	"""
	connect_sqlite()
	table_name = 'hejian'
	sql = "create table if not exists {} ( \
		jobNumber integer primary key, \
		firstName varchar(10), \
		salary integer)".format(table_name)

	create_table(table_name, sql)
	employees_message = [(100000, "Bill", 20000), (100001, "George", 25000), (100002, "Thomas", 30000)]
	for employe in employees_message:
	    add_confdata("employees", employe)
	del_confdata("employees", 1)
	chg_confdata("employees", 100001, "salary", 250)
	qry_confdata("employees") 
	close_sqlite()  
	
def start_socket_thread(socket_handle, ip, port):
	"""开启socket通信线程.
	
	守护线程，负责接收消息.
	
	"""
	
	socket_thread = threading.Thread(target=socket_handle.recv_message, args=(ip, port))
	socket_thread.setDaemon(True)
	socket_thread.start()
	return True

class server_socket_library(socket_library.socket_library):
	"""服务端继承socket_library.
	
	重写socket_library的parse_msg方法.
	
	"""
	
	def parse_msg(self, pid, msg):
		"""解析消息.
		
		服务端对接收的消息进行解析，主要是客户端连接和断开的消息.
		
		Parameters
		----------
		pid : int
			哪个进程发来的消息
		msg : str
			消息内容
		"""
		
		port = int(pid) + 5000
		logging.info("收到进程{}端口{}的消息:{}".format(pid, port, msg))
		global connect_ports
		if msg == "connect":
			connect_ports.add(port)
			logging.info("添加端口[{}]成功, connect_ports = [{}]".format(port, connect_ports))
		if msg == "close":
			connect_ports.remove(port)
			logging.info("移除端口[{}]成功, connect_ports = [{}]".format(port, connect_ports))

class client_socket_library(socket_library.socket_library):
	"""客户端继承socket_library.
	
	重写socket_library的parse_msg方法.
	
	"""
	
	def parse_msg(self, pid, msg):
		"""解析消息.
		
		客户端对接收的消息进行解析，主要是弹出数据库内容修改通知框
		
		Parameters
		----------
		pid : int
			哪个进程发来的消息
		msg : str
			消息内容，格式应该为change,table_name
		"""
		
		logging.info("收到服务端进程{}的消息:{}".format(pid, msg))
		msg = msg.strip().split(',')
		if len(msg) != 2:
			logging.error("消息长度错误，长度为{}".format(len(msg)))
			return False
		if msg[0] == "change":
				content = "进程{}对数据表{}有数据修改".format(pid, msg[1])
				title = "数据更改通知"
				win32api.MessageBox(0, content, title, win32con.MB_OK)
		return True

def send_change_notify(table_name, ip, pid=2020):
	"""发送修改通知.
	
	数据库修改通知机制.
	
	Parameters
	----------
	table_name : str
		数据表名称
	ip : str
		ip地址
	pid : int
		数据表被哪个进程修改
	"""
	
	socket_handle = client_socket_library()
	logging.info("connect_ports = [{}]".format(connect_ports))
	for port in connect_ports:
		if port_operate_table[port] == table_name:
			logging.info("端口{}对数据表{}有业务监控".format(port, table_name))
			msg = "change,{}".format(table_name)
			socket_handle.send_message(ip, port, msg, pid)

def main():
	test_sqllite()
	register_table(234, 'hejian')
	register_table(12, 'tangliu')
	print(connect_ports)
	print(port_operate_table[234])
	
	

if __name__ == '__main__':
    main()





