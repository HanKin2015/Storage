# -*- coding: utf-8 -*-
"""
文 件 名: check_service_status.py
文件描述: 检查服务状态
作    者: HanKin
创建日期: 2025.03.04
修改日期：2025.03.04

Copyright (c) 2025 HanKin. All rights reserved.
"""
import winreg

def regedit_interface(registry, reg_path, item):
	"""
	注册表操作接口
	:param registry: 注册表根路径
	:param reg_path: 注册表路径
	:param item: 注册表项
	:return str: 注册表项的值
	"""
	# 打开注册表
	reg = winreg.ConnectRegistry(None, registry)
	key = None
	value = None
	try:
		# 打开指定路径下的键
		key = winreg.OpenKey(reg, reg_path)
		# 读取键值
		value = winreg.QueryValueEx(key, item)
		# 输出键值
		print(value)
	except Exception as error:
		print('{}\{}, {}'.format(key, value, error))

	# 关闭键和注册表
	if key:
		winreg.CloseKey(key)
	winreg.CloseKey(reg)
	return value
	
def check_service_status():
	"""
	查看服务状态
	:return detection_list: 检查结果
	"""
	detection_list = []

	# 查看sfusbhub服务状态
	registry = winreg.HKEY_LOCAL_MACHINE
	reg_path = r"SYSTEM\CurrentControlSet\Services\sfusbhub"
	item     = "Start"
	value    = regedit_interface(registry, reg_path, item)
	if value:
		if int(value[0]) == 4:
			detection_list.append({"level": "error", "content": "查看sfusbhub服务状态", "cause": "禁用状态",
							   "suggestion": "该服务异常，请检测本地是否安装了杀软软件，恢复方式为重装"})
	else:
		detection_list.append({"level": "error", "content": "查看sfusbhub服务状态", "cause": "服务不存在",
							   "suggestion": "该服务异常，请检测本地是否安装了杀软软件，恢复方式为重装"})
	return detection_list

print(check_service_status())