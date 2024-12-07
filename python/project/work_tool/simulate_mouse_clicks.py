# -*- coding: utf-8 -*-
"""
文 件 名: simulate_mouse_clicks.py
文件描述: 模拟鼠标点击实现自动化
备    注: 可能是某个库（例如 pyautogui 或 pynput）在内部使用了 OpenCV
作    者: HanKin
创建日期: 2024.11.21
修改日期：2024.11.21

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pyautogui
import time
import glob
import configparser
from pynput import mouse
import threading
import os
import datetime
from log import logger

def show_error(message):
    # 创建一个隐藏的主窗口
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口

    # 弹出错误提示框
    messagebox.showerror("错误", message)
    logger.info(message)

    # 销毁主窗口
    root.destroy()

def on_click(x, y, button, pressed):
    """
    定义鼠标点击事件的回调函数
    """
    if pressed:  # 只在按下鼠标时输出位置
        logger.info(f'鼠标点击位置: ({x}, {y})')

def stop_listener(listener):
    """
    定义一个函数来停止监听器
    """
    listener.stop()  # 停止监听器
    logger.info("监听器已停止。")

def listen_mouse_position():
    """
    使用全局变量控制监听器
    """
    # 创建鼠标监听器
    listener = mouse.Listener(on_click=on_click)

    # 启动监听器
    listener.start()

    # 设置定时器，20秒后停止监听器
    logger.info('捕捉鼠标点击事件20秒...')
    timer = threading.Timer(20, stop_listener, args=(listener,))
    timer.start()

    # 等待监听器结束
    listener.join()

def count_dmp_files_in_temp():
    # 获取系统的临时目录
    temp_dir = os.environ.get('TEMP')  # 或者使用 os.path.join(os.path.expanduser('~'), 'AppData', 'Local', 'Temp')
    
    # 查找所有的 .dmp 文件
    dmp_files = glob.glob(os.path.join(temp_dir, '*.dmp'))
    
    # 返回 .dmp 文件的数量
    return len(dmp_files)

def auto_test(config_parser):
    """
    自动化测试
    """
    mouse_config = {key: config_parser.getint('mouse', key) for key in config_parser.options('mouse')}
    pos_x1 = mouse_config.get('pos_x1')
    pos_y1 = mouse_config.get('pos_y1')
    wait_time1 = mouse_config.get('wait_time1')
    pos_x2 = mouse_config.get('pos_x2')
    pos_y2 = mouse_config.get('pos_y2')
    wait_time2 = mouse_config.get('wait_time2')
    test_cnt = mouse_config.get('test_cnt')

    logger.info('自动化测试{}次: 点击({}, {}), 休息{}秒, 点击({}, {}), 休息{}秒'.format(test_cnt,
        pos_x1, pos_y1, wait_time1, pos_x2, pos_y2, wait_time2))

    init_dmp_count = count_dmp_files_in_temp()
    logger.info('在 %temp% 目录下找到 {} 个 .dmp 文件'.format(init_dmp_count))
    test_index = 0
    while test_index < test_cnt:
        test_index += 1
        logger.info('正在进行第 {} 次测试...'.format(test_index))
        pyautogui.click(x=pos_x1, y=pos_y1)
        time.sleep(wait_time1)
        pyautogui.click(x=pos_x2, y=pos_y2)
        time.sleep(wait_time2)
        dmp_count = count_dmp_files_in_temp()
        if dmp_count > init_dmp_count:
            logger.info('生成了dump文件请查收!')
            show_error('生成了dump文件请查收!')
            break

def main():
    """主函数
    """
    config_parser = configparser.ConfigParser(allow_no_value=True, strict=False)
    config_parser.read('./conf.ini')
    if not config_parser.has_section('mouse'):
        logger.info('conf.ini has no mouse section')
        return
    
    listen_mouse_pos = config_parser.getint('mouse', 'listen_mouse_pos')
    if listen_mouse_pos:
        listen_mouse_position()
    else:
        auto_test(config_parser)

def debug():
    """调试
    """
    dmp_count = count_dmp_files_in_temp()
    logger.info(f"在 %temp% 目录下找到 {dmp_count} 个 .dmp 文件。")

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    os.system('pause')