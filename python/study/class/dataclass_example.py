# -*- coding: utf-8 -*-
"""
文 件 名: dataclass_example.py
文件描述: 数据类
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import os
import json
from dataclasses import dataclass

@dataclass
class Config:
    DECENTA_SN_LIST: list
    RK31_SN_LIST: list
    RK32_SN_LIST: list
    DEBIAN_ARM64_SN_LIST: list
    TCI_SN_LIST: list

class Common:
    """
    公共类
    """

    def __init__(self, device_dir):
        self.config_filepath = os.path.join(device_dir, "config/device_helper.config")
        with open(self.config_filepath, encoding='utf-8') as f:
            config_data = json.load(f)

        self.config = Config(
            DECENTA_SN_LIST=config_data["BOX_SERIAL_NUMBERS"]["DECENTA_SN_LIST"],
            RK31_SN_LIST=config_data["BOX_SERIAL_NUMBERS"]["RK31_SN_LIST"],
            RK32_SN_LIST=config_data["BOX_SERIAL_NUMBERS"]["RK32_SN_LIST"],
            DEBIAN_ARM64_SN_LIST=config_data["BOX_SERIAL_NUMBERS"]["DEBIAN_ARM64_SN_LIST"],
            TCI_SN_LIST=config_data["BOX_SERIAL_NUMBERS"]["TCI_SN_LIST"]
        )

# 使用示例
device_directory = "/path/to/device"
common_instance = Common(device_directory)  # 需要实例化
print(common_instance.config.DECENTA_SN_LIST)  # 访问数据类中的数据
