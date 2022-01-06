# -*- coding: utf-8 -*-
import psutil
import os
import logging
 
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='d:/monitor/monitor.log',
                    filemode='a')
 
# PROCESS_RE = re.compile("pid=\d{1,4},\sname='\S{1,20}'") # 采用正则，获取数据 pid=x/xx/xxx/xxxx, name=[1~20个字符，
 
 
# 监控windows系统所有进程服务任务。定时任务执行，发现run.pid进程号系统中不存在，执行命令python Demo.py启动程序
# author 胖胖的alex 2017/09/1
class MonitorServer:
 
    pidNotHandle = []
    servername = "server.exe"
 
    def __init__(self):
        self.pidNotHandle = list(psutil.process_iter())  # 获取当前计算机的pid
 
    def execute(self):
        pid = []
        for each in self.pidNotHandle:
            a = str(each)  # each 是 class类型，可用type(each)查看类型
            # a 数据样式为：psutil.Process(pid=0, name='System Idle Process')
            pid.append(a[15:-1])  # 只取括号内部分；pid=0, name='System Idle Process'
 
        status = 0  # 被监控程序进程存在状态，0不存在，1存在
        for each in pid:
            nameposition = each.find("name")  # 获取name的位置；name='System Idle Process'
            #print(nameposition)
            #print(each)
            namevalue = each[nameposition + 6:-21]  # 获取name值；System Idle Process
            pidposition = each.find("pid")
            pidvalue = each[pidposition + 4:nameposition-2]
            #print("name="+namevalue + ", pid="+pidvalue+"\n")
            
            if namevalue == self.servername:
                status = 1
                print("发现进程==============name=" + namevalue + ", pid=" + pidvalue + "\n")
                break
 
        if status == 0:  # 进程不存在，重新启动程序
            cmd = "E:/mywork/python/workspace/monitor/dist/DemoServer/" + self.servername
            os.popen(cmd)
            print("重启程序.............")
 
        print("ending.............")
        return 0
 
import time, socket
 
if __name__ == '__main__':
    s = "3,connect,54"
    if s.find("conn4ect")==-1:
        print("okook")

    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    try:
        client.connect(('127.0.0.1', 34334))
    except:
        print("nonono")


    g_clientserver_ports = set()
    with open("./data/pids.run", "r") as f:
        tmp = f.readlines()
        for i in range(0, len(tmp)):
            g_clientserver_ports.add(tmp[i].rstrip('\n'))
    print(len(g_clientserver_ports))
    print(g_clientserver_ports)


    os.system('taskkill /f /im %s' % 'server.exe')

    ret = os.startfile(".\\dist\\server\\server.exe")
    print(ret)
    time.sleep(0.5)
    with open("./data/pid.tmp", "r") as f:
        self_server_pid = int(f.read())
        print(self_server_pid)
    #ret = os.popen(".\\dist\\server\\server.exe")
    #print(ret)
    MonitorServer().execute()
    input("d=")
    os.popen('taskkill.exe /f /pid:'+str(self_server_pid))

    #os.system('taskkill /f /im %s' % 'server.exe')
    MonitorServer().execute()
