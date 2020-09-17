# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:06:41 2020

@target:
    实现一个配置数据共享存储模块

    要求：
    1.对外支持多线程/多进程的数据安全读写访问；
    2.对外提供数据更改通知机制，能及时让外部获取数据的变化。
    3.数据存储要求支持加密安全，加密算法要求可扩展；

    说明：
    1.配置数据存储在SQLite里，模块读取出来后转换为JSON格式给业务模块使用

@author: 何健29996
@description:
    1、监听127.0.0.1:8384端口
    2、后台服务程序，负责操作后台数据库:增删改查
    3、数据修改通知机制，注册机制
"""
import socket
import time
import win32api, win32con 
import logging
import sqlite3_operation_library
import encryption_algorithm_library
import os
 
# 服务监听配置
ip_port = ('127.0.0.1',8384)
listen_client_maxcnt = 5
buffer_size = 1024
# 创建一个TCP套接字
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)   # 套接字类型AF_INET, socket.SOCK_STREAM   tcp协议，基于流式的协议
server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)  # 对socket的配置重用ip和端口号
# 绑定端口号
server.bind(ip_port)  # 写哪个ip就要运行在哪台机器上
# 设置半连接池
server.listen(listen_client_maxcnt)  # 最多可以连接多少个客户端

#路径
g_data_path = "./data"
g_log_path = "./log"
if not os.path.exists(g_data_path):
    os.makedirs(g_log_path)

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./log/service.log',
                    filemode='a')



#打开日志
sqlite3_operation_library.OpenLog()
#连接数据库
sqlite3_operation_library.ConnectSqlite()
#创建数据表
sqlite3_operation_library.CreateTable()

#创建必需的文件夹：日志和数据
try:
    os.mkdir("log")
except:
    pass
try:
    os.mkdir("data")
except:
    pass

#设置进程并发数量
g_thread_num = 1

#任务数量
def TaskNum():
    return [i for i in range(1,3)]

#具体的任务
def RunTask(case_id):
    sqlite3_operation_library.main()

#测试多进程并发操作
def TestMultProcess():
    pool = ThreadPool(g_thread_num)
    pool.map(RunTask, TaskNum())
    pool.close()
    pool.join()      

#所有连接端口=进程号+5000
g_clientserver_ports = set()
"""
with open("./data/pids.run", "r") as f:
    tmp = f.readlines()
    for i in range(0, len(tmp)):
        g_clientserver_ports.add(tmp[i].rstrip('\n'))
print(len(g_clientserver_ports))
#print(g_clientserver_ports)
"""
    
def send_message(msg, pid, ports):
    if not msg:
        logging.error("空的消息")
        print("空的消息")
        return False 
    if len(ports) <= 0:
        logging.error("无端口")
        print("无端口")
        return False
    
    for port in ports:
        print("检测端口{}是否开启".format(port))
        try:
            client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            client.connect(('127.0.0.1', port))
            print("---端口{}开启---".format(port))
        except:
            print("当前端口{}未开启".format(port))
            client.close()
            continue

        send_msg = "{},{}".format(pid, msg)
        client.send(send_msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
        logging.info("发送消息 {} 成功".format(send_msg))
        print("发送消息 {} 成功".format(send_msg))
        client.close()
    return True

def parse_data(recv_data):
    """解析数据

    """
    print("解密前数据:{}".format(recv_data))
    
    #对数据进行rsa解密
    recv_data = encryption_algorithm_library.RsaDecode(recv_data)
    print("解密后数据:{}".format(recv_data))

    idx = recv_data.find(",")
    pid = recv_data[:idx]

    recv_data = recv_data[idx+1:]

    idx = recv_data.find(" ")
    if idx == -1:
        opt = recv_data.strip()
    else:
        opt = recv_data.strip()[:idx]  

    content = recv_data.strip()[idx:]
    #print(content)

    # 去掉前后的括号和引号
    elim = ['(', ')', '\'', '\"']
    for elem in elim:
        content = content.replace(elem, '')

    conf_data = content.split(',')
    conf_data = [elem.strip() for elem in conf_data]

    return pid, opt, conf_data

def operation_database(opt, conf_data=None):
    ret = None

    table_name = conf_data[0]
    if opt == "add":
        data = (conf_data[1], conf_data[2], conf_data[3])
        print(data)
        sqlite3_operation_library.AddConfData(table_name, data)
    if opt == "qry":
        ret = sqlite3_operation_library.QuyConfData(table_name)
    if opt == "del":
        sqlite3_operation_library.DelConfData(table_name, int(conf_data[1]))
    if opt == "chg":
        sqlite3_operation_library.ChgConfData(table_name, conf_data[1], conf_data[2], conf_data[3])
    return ret


while True:
    print("开始监听('127.0.0.1',8384)......")
    # 阻塞等待，创建连接
    con,address = server.accept()  # 在这个位置进行等待，监听端口号 

    try:
        # 接受套接字的大小，怎么发就怎么收
        msg = con.recv(buffer_size).decode('utf-8')
        con.close()

        pid, opt, conf_data = parse_data(msg)
        ret = operation_database(opt, conf_data)
        if ret:
            print("发送查询结果:{}".format(ret))
            send_message(ret, pid, g_clientserver_ports)
            continue


        if opt=="connect":
            #global g_ports
            g_clientserver_ports.add(int(pid) + 5000)
            print("有进程连接{},现在共有{}个进程连接".format(pid, len(g_clientserver_ports)))
            continue
        logging.info("服务器收到进程{}的消息: {}".format(pid, opt))
        print("{}服务器收到进程{}的消息: {}".format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()), pid, opt))
        
        if opt=="closeserver":
            logging.info("关闭后台服务消息")
            break
        if opt=="notify":
            print("发送消息")
            SendMessage("notify", pid, g_clientserver_ports)
            continue
        
    except Exception as e:
        logging.error("出现异常断开连接")
        logging.info("断开连接")
        print("断开连接")
        break
    

#关闭数据库
sqlite3_operation_library.CloseSqlite()
#关闭日志
sqlite3_operation_library.CloseLog()    
import os
os.system('taskkill /f /im %s' % 'server.exe')
    
# 关闭服务器
server.close()
logging.info("服务端关闭成功")
print("服务端关闭成功")

