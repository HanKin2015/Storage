import ftplib 
import socket 
import sys 

try: 
    user = sys.argv[1] 
    passwd = sys.argv[2]
    ftp = ftplib.FTP('199.200.5.88') 
    ftp.login(user,passwd) 
    hand = open('aa.txt','a+') 
    hand.write(user + ':' + passwd + '\n') 

except ftplib.error_perm: 
    print('passwd[{}] is wrong!'.format(passwd))

except EOFError:
    print('EOFError')
