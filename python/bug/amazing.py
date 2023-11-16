import json
import time
import logging
import sys
import os

def check_json_file_valid():
    with open(r"D:\Users\User\Desktop\manual_troubleshooting.json", encoding="utf-8") as f:
        vdc_policy_guidance = json.load(f)

def get_logger():
    logger = logging.getLogger('patrol')
    # 指定logger输出格式
    formatter = logging.Formatter('%(asctime)s %(name)s %(filename)s %(lineno)s %(levelname)-4s: %(message)s')
    # 文件日志
    log_file = 'patrol.log'
    file_handler = logging.FileHandler(log_file, encoding="utf-8")
    # 指定输出格式
    file_handler.setFormatter(formatter)
    # 为logger添加的日志处理器
    logger.addHandler(file_handler)

    # 控制台日志
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.formatter = formatter  # 也可以直接给formatter赋值
    logger.addHandler(console_handler)

    # 指定日志的最低输出级别
    logger.setLevel(logging.DEBUG)
    return logger

def launch():
    os.popen("usbview.exe")

def get_port_status():
    """
    获取端口状态
    :return: 直接返回查询结果
    """
    # 完全匹配8001端口
    find_port = 'netstat -aon|findstr :8971'
    p = os.popen(find_port, 'r')
    text = p.readlines()
    p.close()
    if text:
        for task in text[:]:
            if task.strip()[-1] == '0' or 'LISTENING' not in task.strip():
                text.remove(task)
        return text
    return text

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    logger = get_logger()

    text = get_port_status()
    print(1)
    if text:
        print(2)
        logger.error("hello")
    else:
        logger.error("world")
        launch()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

"""
没有想通，自己环境也没有复现问题，在同事环境出现：
popen失败没有报任何错误，会出现打印：
1
world
hello
很神奇的事情，绕过print打印，主要是奇迹般的打印出hello
想不通想不通
"""