# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 13:35:12 2020

@author: hejian29996
@description:
    封装对外开放的api接口
"""

from multiprocessing.dummy import Pool as ThreadPool
import argparse
import os
import socket
import logging
import sys
import time
import encryption_algorithm_library
import server
import threading

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./log/client.log',
                    filemode='a')

#后台服务端监听端口
g_localhost = '127.0.0.1'
g_port = 8384

#g_port = sys.argv[1]


def parse_argument():
    """解析参数
    
    
    """
    argument_parser = argparse.ArgumentParser(description="配置数据共享存储模块")   
    
    argument_parser.add_argument("-a", "--AddConfData", action='store_true', help="增加配置数据")
    argument_parser.add_argument("-d", "--DelConfData", action='store_true', help="删除配置数据")
    argument_parser.add_argument("-c", "--ChgConfData", action='store_true', help="修改配置数据")
    argument_parser.add_argument("-q", dest="data", action='store', help="查询配置数据")
    argument_parser.add_argument("-x", default=False, dest="x",action='store_true', help="进入交互界面")
    args = argument_parser.parse_args()
    if args.data:
        print(args.data)
    if args.x:
        operation_display()

def check_content_valid(content):
    """内容检查.

    检查内容是否有效.

    Parameters
    ----------
    input_content: str
        输入内容
    Returns
    ----------
    bool
        内容合法返回True，非法返回
    """
    print("当前内容为：{}".format(content))
    idx = content.find(" ")
    if idx == -1:
        opt = content.strip()
    else:
        opt = content.strip()[:idx] 
    valid_content = ["add", "del", "chg", "qry", "closeserver", "exit", "notify"]
    if opt in valid_content:
        return True
    return False
        
def operation_display():
    """操作界面显示.

    操作提示界面输入框.
    """
    while True:
        print("\n\t\t当前进程ID: {} \n \
               默认数据表有：'employees' 'svnAccounts' \n \
               增加配置数据：add ('employees', 22200, 'Bill', 20000) \n \
               删除配置数据：del ('employees', 22200) \n \
               修改配置数据：chg ('employees', 222000, 'salary', 250) \n \
               查询配置数据：qry ('employees') \n \
               关闭后台服务：closeserver \n \
               测试数据更改通知机制：notify \n \
               退出： exit \n".format(os.getpid()))
        input_content = input("请输入：");
        print ("你输入的内容是: ", input_content)
        
        # 判读输入操作的合法性
        ret = check_content_valid(input_content)
        if not ret:
            print("输入不合法，请重新输入.")
            continue

        if input_content == "exit":
            logging.info("exit client.")
            break;
        
        # 发送操作消息
        send_message(input_content)

global g_self_server_pid


global g_server_thread

def start_server_thread():
    global g_server_thread
    g_server_thread = threading.Thread(target=server.recv_msg)
    g_server_thread.setDaemon(True)
    g_server_thread.start()
    return True

def init():
    global g_self_server_pid, g_server_thread
    #os.popen(".\\dist\\server\\server.exe")
    start_server_thread()

    time.sleep(0.5)
    with open("./data/pid.tmp", "r") as f:
        g_self_server_pid = f.read()
        #print(g_self_server_pid)

    ret = send_message("{},connect".format(g_self_server_pid))

    with open("./pid.txt", "a") as f:
        f.write(str(os.getpid()))
        f.write("\n")

    return ret

def main():
    
    operation_display()
    
  

#---------------------------------



#当前进程pid
g_current_pid = os.getpid()

def help():
    print("\n\t配置数据共享存储\n \
           默认数据表有：'employees' 'svnAccounts' \n \
           增加配置数据：add ('employees', 22200, 'Bill', 20000) \n \
           删除配置数据：del ('employees', 22200) \n \
           修改配置数据：chg ('employees', 222000, 'salary', 250) \n \
           查询配置数据：qry ('employees') \n \
           关闭后台服务：closeserver \n \
           测试数据更改通知机制：notify \n")

def execute_cmd(cmd):
    """执行命令

    执行操作命令


    """
    if not init():
        return False

    ret = check_content_valid(cmd)
    if not ret:
        print("输入的指令不合理，请仔细看操作示例help()函数")
        return False
    send_message(cmd)
    return True


def send_message(msg):
    """发送操作消息

    向服务端发送消息，服务端监听端口127.0.0.1:8384
    
    Parameters
    ----------
    msg : str
        消息内容

    Returns
    ----------
    bool
        发送成功为True，发送失败为False
    """
    
    try:
        client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        client.connect((g_localhost,int(g_port)))
    except:
        print("配置数据共享存储服务端程序未启动")
        return False
    
    if not msg:
        logging.error("输入了空的消息")
        client.close()
        return False 
    if msg.find("connect")==-1:
        msg = "{},{}".format(g_current_pid, msg)

    encryption_msg = encryption_algorithm_library.RsaEncode(msg)
    #print("加密后的数据：{}".format(encryption_msg))
    client.send(encryption_msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
    logging.info("发送消息 {} 成功".format(encryption_msg))
    
    client.close()
    logging.info("关闭连接成功")
    return True

    

if __name__=='__main__':
    # 初始化：拉起自身的server
    ret = init()
    if not ret:
        print("程序无法启动.")
        sys.exit()
    parse_argument()
    #main()
    #os.popen('taskkill.exe /f /pid:'+str(g_self_server_pid))  

    
    
    
    
    