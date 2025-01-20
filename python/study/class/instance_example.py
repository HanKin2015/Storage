# -*- coding: utf-8 -*-
"""
文 件 名: instance_example.py
文件描述: 单例模式
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import os
import json

class Common:
    """
    公共类
    """

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(Common, cls).__new__(cls)
            cls._instance.initialize()
        return cls._instance

    def initialize(self):
        """
        初始化配置
        """
        with open(r"D:\Demo\device_helper\config\device_helper.config", encoding='utf-8') as f:
            self.CONFIG = json.load(f)

        self.DECENTA_SN_LIST = self.CONFIG["BOX_SERIAL_NUMBERS"]["DECENTA_SN_LIST"]
        self.RK31_SN_LIST = self.CONFIG["BOX_SERIAL_NUMBERS"]["RK31_SN_LIST"]
        self.RK32_SN_LIST = self.CONFIG["BOX_SERIAL_NUMBERS"]["RK31_SN_LIST"]
        self.DEBIAN_ARM64_SN_LIST = self.CONFIG["BOX_SERIAL_NUMBERS"]["DEBIAN_ARM64_SN_LIST"]
        self.TCI_SN_LIST = self.CONFIG["BOX_SERIAL_NUMBERS"]["TCI_SN_LIST"]

# 使用示例
#common_instance = Common()  # 第一次调用，创建实例
#another_instance = Common()  # 再次调用，返回同一个实例

#print(common_instance is another_instance)  # 输出: True

instance = Common._instance
another_instance = Common()
print(instance is another_instance)   # 输出: False
#print(instance.RK31_SN_LIST)
