# -*- coding: utf-8 -*-
"""
Created on Sat Jul  4 16:30:36 2020

@author: hejian29996
@description: 
    客户端调用接口样例程序
"""

import encryption_algorithm_library				# 算法加密库
import configure_data_share_storage_service		# 配置数据共享存储服务库
import os, time

current_pid = os.getpid()
ip = '127.0.0.1'
server_port = 8384
print('当前进程:{}'.format(current_pid))

def main():
	table_name = 'employees'
	sql = "create table if not exists {} ( \
		jobNumber integer primary key, \
		firstName varchar(10), \
		salary integer)".format(table_name)
		
	# 客户端登录
	client_socket_obj = configure_data_share_storage_service.client_login(current_pid, table_name)

	# 客户端打开数据库
	configure_data_share_storage_service.connect_sqlite()
	
	# 客户端创建数据表
	configure_data_share_storage_service.create_table(table_name, sql)

	# 客户端增加配置数据
	configure_data_share_storage_service.add_confdata(table_name, (1314, "whl", 20000))

	# 客户端修改配置数据
	configure_data_share_storage_service.chg_confdata(table_name, 1314, "salary", 250)
	print(configure_data_share_storage_service.qry_confdata(table_name), '\n')

	# 客户端删除配置数据
	configure_data_share_storage_service.del_confdata(table_name, 1314)

	# 客户端查询配置数据
	ret = configure_data_share_storage_service.qry_confdata(table_name)
	print(ret)

	# 客户端关闭数据库
	configure_data_share_storage_service.close_sqlite()
	
	# 客户端退出
	configure_data_share_storage_service.client_logout(client_socket_obj, current_pid)

if __name__ == '__main__':
    main()
    time.sleep(10)
