import ftplib 
import socket 
import sys 

import paramiko

user = sys.argv[1] 
passwd = sys.argv[2]
host_name = '199.200.5.88'


try: 

    transport = paramiko.Transport((host_name, 22))
    transport.connect(username = user, password = passwd)
    sftp = paramiko.SFTPClient.from_transport(transport)
    hand = open('aa.txt','a+') 
    hand.write(user + ':' + passwd + '\n') 

except ftplib.error_perm: 
    print('passwd[{}] is wrong!'.format(passwd))

except EOFError:
    print('EOFError')
