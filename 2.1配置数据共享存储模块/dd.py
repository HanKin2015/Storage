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
    servername = "Demo.exe"
 
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
 
 
if __name__ == '__main__':
    os.startfile(".\dist\Demo\Demo.exe")
    MonitorServer().execute()
