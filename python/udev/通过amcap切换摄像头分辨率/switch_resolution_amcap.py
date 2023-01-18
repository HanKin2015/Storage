# -*- coding: utf-8 -*-
"""
文 件 名: switch_resolution_amcap.py
文件描述: 通过amcap切换摄像头分辨率
作    者: HanKin
创建日期: 2023.01.17
修改日期：2023.01.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
from time import sleep
import os
import subprocess
from log import logger
import time

# 获取摄像头分辨率信息工具
VIDEO_INFO_TOOL = "getvideoinfo.exe"

# amcap工具
AMCAP_API_TOOL = "amcap_api.exe"

def run_cmd(cmd):
    res_obj = os.popen(cmd)
    res = res_obj.read()
    res_obj.close
    return res

def set_resolution(width, hight, vidpid, format_value, devicename, write_content):
    cmd = "{AMCAP_API_TOOL} -set_resolution {width} {hight} \"{devicename}\" {format_value} {videodevice2}".format(AMCAP_API_TOOL=AMCAP_API_TOOL, width=width, hight=hight, devicename=devicename, format_value=format_value, videodevice2=write_content)
    logger.debug('set_resolution params: {}'.format(cmd))
    subprocess.Popen(cmd)

def switch_the_resolution(wait_time, is_camera="0", is_devices=None):
    """切换分辨率
    wait_time  切换间隔时间
    is_camera  是否拍照
    is_devices 指定的摄像头设备
    """
    
    logger.info('当前配置: 切换时间间隔 {} s, 是否拍照 {}, 是否指定摄像头设备 {}'.format(wait_time, is_camera, is_devices))
    
    resolution_res = run_cmd(VIDEO_INFO_TOOL)
    logger.info('getvideoinfo.exe run result: {}'.format(resolution_res))
    
    mjpg_list = []
    yuy2_list = []
    vidpid = ""
    devicename = ""
    if "MEDIASUBTYPE" in resolution_res and "devicename" in resolution_res:
        if "MJPG" in resolution_res:
            mjpg_list = resolution_res.split("MJPG-")[1].split(", &&")[0].split(",")
        if "YUY2" in resolution_res:
            yuy2_list = resolution_res.split("YUY2-")[1].split(",")[:-2]
        vidpid = "{}_{}".format(resolution_res.split("vid_")[1].split("&")[0], resolution_res.split("pid_")[1].split("&")[0])
        devicename = resolution_res.split("devicename:")[1].split(" &&")[0]
        write_content = resolution_res.split("&&")[1].split("MonikerName:")[1] 
    else:
        logger.error("未获取到高拍仪设备, 请检查是否接入")
        return False

    # 打开高拍仪
    cmd = "{} -open".format(AMCAP_API_TOOL)
    subprocess.Popen(cmd)
    sleep(20)
    
    logger.info('获取摄像头分辨率列表完成, 共有{}种MJPG格式, {}种YUY2格式'.format(len(mjpg_list), len(yuy2_list)))

    # 如果有device，用传进来的
    if is_devices:
        devicename = is_devices
    
    # 记录切换完成所有分辨率次数
    index = 1
    while True:
        logger.info("这是第{}此开启总任务".format(index))
        if len(mjpg_list) > 0:
            for resolution in mjpg_list:
                width = resolution.split("*")[0]
                hight = resolution.split("*")[1]
                logger.info("开始切换mjpg分辨率{}*{}".format(width,hight))
                set_resolution(width, hight, vidpid, "47504a4d-0000-0010-8000-00aa00389b71", devicename, write_content)
                sleep(wait_time)
                if is_camera == "1":
                    cmd = "{} -snapshot".format(AMCAP_API_TOOL)
                    subprocess.Popen(cmd)
                return
        if len(yuy2_list) > 0:
            for resolution in yuy2_list:
                width = resolution.split("*")[0]
                hight = resolution.split("*")[1]
                logger.info("开始切换yuy2分辨率{}*{}".format(width,hight))
                set_resolution(width, hight, vidpid, "32595559-0000-0010-8000-00aa00389b71", devicename, write_content)
                sleep(wait_time)
                if is_camera == "1":
                    cmd = "{} -snapshot".format(AMCAP_API_TOOL)
                    subprocess.Popen(cmd)
        index += 1

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    params = sys.argv
    if len(params) < 2:
        switch_the_resolution(30)
    elif len(params) == 2:
        switch_the_resolution(int(params[1]))
    elif len(params) == 3:
        switch_the_resolution(int(params[1]), params[2])
    elif len(params) > 3:
        switch_the_resolution(int(params[1]), params[2], params[3])
    #main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))

