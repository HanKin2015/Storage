# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect_interface.py
文件描述: USB设备检测接口类
作    者: HanKin
创建日期: 2023.05.25
修改日期：2023.05.25

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
from PyQt5.QtCore import QThread, pyqtSignal
import platform

def get_udev_info_list():
    """获取USB设备的信息列表（包含Hub和USB设备）
    不能在线程中执行，否则会有报错，行不通
    """
    
    wmi = win32com.client.GetObject("winmgmts:")
    logger.debug(wmi)  # <COMObject winmgmts:>
    
    udev_info_list = []
    for pnp in wmi.InstancesOf("Win32_PnPEntity"):
        if 'USB\\VID' in pnp.DeviceID and pnp.DeviceID.count('&') <= 4:
            for prop in pnp.Properties_:
                logger.debug('{} : {}'.format(prop.Name, prop.Value))
            logger.debug('')

            udev_info = dict({'Name': pnp.Name,
                                 'deviceID': pnp.deviceID,
                                 'Service': pnp.Service,
                                 'ConfigManagerErrorCode': pnp.ConfigManagerErrorCode,
                                 'Status': pnp.Status,
                                 'HardWareID': pnp.HardWareID,
                                 'SystemName': pnp.SystemName})
            if platform.system() == 'Windows':
                win_ver = platform.win32_ver()
                if win_ver[0] == '7':
                    logger.debug('当前系统为Windows 7')
                    udev_info['PNPClass'] = 'USB'
                else:
                    logger.debug('当前系统为Windows，但不是Windows 7')
                    udev_info['PNPClass'] = pnp.PNPClass
            else:
                logger.error('当前系统不是Windows')

            udev_info_list.append(udev_info)
    for udev_info in udev_info_list:
        for key, value in udev_info.items():
            logger.debug('{}: {}'.format(key, value))
        logger.debug('')

    # 通知给子进程
    logger.debug(udev_info_list)
    return udev_info_list

class Thread_UdevDetect(QThread):
    hotplugSignal = pyqtSignal(str)
    getUdevInfoListSignal = pyqtSignal()

    def __init__(self):
        super(Thread_UdevDetect, self).__init__()
        self.is_on = False
        self.udev_info_list = []

    def run(self):
        self.getUdevInfoListSignal.emit()
        self.sleep(1)   # 等待信号消息处理完成
        logger.info('there are {} hub and usb devices now'.format(len(self.udev_info_list)))
        last_udev_info_list = self.udev_info_list
        while self.is_on:
            self.sleep(1)
            
            self.getUdevInfoListSignal.emit()
            diff_count = len(self.udev_info_list) - len(last_udev_info_list)
            if diff_count == 0:
                continue
            
            hwID = self.print_hotplug_udev_info(diff_count, last_udev_info_list, self.udev_info_list)
            if hwID != None:
                vid_idx = hwID[0].find('VID_')
                vid = hwID[0][vid_idx+4:vid_idx+8]
                pid_idx = hwID[0].find('PID_')
                pid = hwID[0][pid_idx+4:pid_idx+8]
                vpid = '{}:{}'.format(vid, pid)
                self.hotplugSignal.emit('{} hotplug in'.format(vpid) if diff_count > 0 else '{} hotplug out'.format(vpid))
            logger.warning('there are {} usb devices which are hogplug {}'.format(abs(diff_count), 'in' if diff_count > 0 else 'out'))
            last_udev_info_list = self.udev_info_list

    def print_udev_info(self, udev_info):
        """打印USB设备信息
        """
        
        for key, value in udev_info.items():
            logger.debug('{}: {}'.format(key, value))
        return

    def print_hotplug_udev_info(self, diff_count, udev_info_list, current_udev_info_list):
        """打印出热插拔的设备信息
        """
        
        logger.info('=============== Hotplug USB Device ===============')
        if diff_count > 0:
            udev_info_list, current_udev_info_list = current_udev_info_list, udev_info_list
        for udev_info in udev_info_list:
            if udev_info not in current_udev_info_list:
                self.print_udev_info(udev_info)
                return udev_info['HardWareID']
        logger.info('=============== Hotplug USB Device ===============')
        return None

def main():
    """主函数
    """

    get_udev_info_list()
    # USB设备检测线程
    udevDetect = Thread_UdevDetect()
    udevDetect.hotplugSignal.connect(get_udev_info_list)
    udevDetect.getUdevInfoListSignal.connect(get_udev_info_list)
    udevDetect.is_on = True
    udevDetect.start()
    time.sleep(60)  # 不行，单线程这样没法处理get_udev_info_list函数

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))