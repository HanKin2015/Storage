import os 
import time 
import threading
import time

class mythread(threading.Thread): 
    def __init__(self,command): 
        threading.Thread.__init__(self) 
        self.command = command 

    def run(self): 
        kk=os.system(self.command)
        

start = time.time()
      
ushand = open('user.txt', 'r') 
pshand = open('passwd.txt', 'r') 
listuser = [] 
listpass = [] 
for us in open('user.txt', 'r'): 
    lineus = ushand.readline().strip('\n') 
    listuser.append(lineus) 
for ps in open('passwd.txt', 'r'): 
    lineps = pshand.readline().strip('\n') 
    listpass.append(lineps) 

for i in listuser: 
    for j in listpass: 
        command = 'ftp.py %s %s' %(i, j) 
        print(command) 
        my_thread = mythread(command) 
        my_thread.start() 
        time.sleep(0.5) 

end = time.time()
print('共用时{}.'.format(end - start))