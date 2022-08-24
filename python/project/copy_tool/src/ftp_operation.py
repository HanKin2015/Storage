# -*- coding: utf-8 -*-
"""
文 件 名: ftp_operation.py
文件描述: ftp相关操作
作    者: HanKin
创建日期: 2020.11.01
修改日期：2022.08.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

from common import *

class MyFTP():
    def __init__(self):
        '''初始化
        1.建立连接
        2.创建远程工作目录
        '''
        
        logger.info('-----程序开始运行-----')
        logger.info('初始化建立ftp连接')
        ret = self.ftp_connect()
        if ret:
            logger.info('建立ftp连接成功')
            self.make_dir(remote_dir_path)
        else:
            logger.error('建立ftp连接失败')

    def make_dir(self, dir_path):
        """创建文件夹
        """
        #logging.debug(self.ftp.pwd())
        #logging.debug(self.ftp.dir())
        #logging.debug(self.ftp.getwelcome())
        logger.debug('dir_path: {}'.format(dir_path))
        try:
            self.ftp.mkd(dir_path)
            logger.info('创建文件夹[{}]成功'.format(dir_path))
        except Exception as err:
            logger.error('创建文件夹[{}]失败, error={}'.format(dir_path, str(err)))
        
    def remove_dir(self, dir_path):
        """删除文件夹
        """
        logger.debug('dir_path: {}'.format(dir_path))
        dir_res_details = []
        try:
            self.ftp.cwd(dir_path)
        except Exception as err:
            logger.error('进入ftp目录失败, error={}'.format(str(err)))
        self.ftp.dir('.', dir_res_details.append)  # 对当前目录进行dir()，将结果放入列表
        for elem in dir_res_details:
            print('elem = {}'.format(elem))
            if '<DIR>' in elem:
                dir_name = elem.split(' ')[-1]
                logger.info('开始删除{}文件夹'.format(dir_name))
                
                self.remove_dir(self.ftp.pwd() + '/' + dir_name)
                self.ftp.cwd('..')
                if dir_path[-1] == '/':
                    dir_path = dir_path[:-1]
                logger.info('删除空文件夹{}'.format(dir_path+'/'+dir_name))
                try:
                    self.ftp.rmd(dir_name)
                except ftplib.error_perm as err:
                    logger.error('删除文件夹失败, error={}'.format(err))
            else:
                file_name = elem.split(' ')[-1]
                logger.info('删除FTP目录{}下存在的文件:{}'.format(dir_path, file_name))
                self.ftp.delete(file_name)

    def ftp_connect(self):
        '''建立ftp连接
        True成功, False失败
        '''

        global ftp_ip, ftp_username, ftp_password

        self.ftp = ftplib.FTP()
        # ftp.set_debuglevel(2)
        
        # 判断本地是否存在ftp配置文件
        if os.path.exists(config_path):
            config = configparser.ConfigParser()
            config.read(config_path)
            if config.has_section('ftp'):
                ftp_ip = config.get('ftp', 'ip')
                ftp_username = config.get('ftp', 'username')
                ftp_password = config.get('ftp', 'password')
                logger.debug('本地存在ftp配置文件: ip[{}] username[{}] password[{}]'.format(ftp_ip, ftp_username, ftp_password))
        try:
            self.ftp.connect(ftp_ip, ftp_port)
            self.ftp.login(ftp_username, ftp_password)
            self.ftp.encoding = 'gbk'
        except Exception as ex:
            logger.error('登录ftp服务器({})失败, error={}'.format(ftp_ip, ex))
            messagebox.showinfo('警告', '建立ftp连接失败', icon='question')
            return False
        logger.info('登录ftp服务器({})成功'.format(ftp_ip))
        return True
        
    def download_file(self, local_file_path, remote_file_path):
        '''从ftp下载文件
            Parameters
        ----------
        local_path : str
            本地文件路径
        remote_path : str
            云端文件路径

        Returns
        -------
        bool
            成功返回True,失败False
            '''

        logger.info('正在下载文件{}到{}'.format(remote_file_path, local_file_path))
        bufsize = 1024
        fp = open(local_file_path, 'wb')
        try:
            self.ftp.retrbinary('RETR ' + remote_file_path, fp.write, bufsize)
        except Exception as err:
            logger.error('下载文件[{}]失败, err={}'.format(remote_file_path, err))
            return False
        #self.ftp.set_debuglevel(0)
        fp.close()
        return True

    def download_dir(self, download_path, remote_dir_path):
        try:
            self.ftp.cwd(remote_dir_path)
        except Exception as err:
            logger.warning(err)
            self.ftp_connect()
            self.ftp.cwd(remote_dir_path)
        files = self.ftp.nlst()
        # 一定要记得回到根目录，或者后面就不要添加绝对地址，最好回来，防止后面使用
        self.ftp.cwd('/')
        for file in files:
            local_file_path = download_path + file
            remote_file_path = remote_dir_path + file
            self.download_file(local_file_path, remote_file_path)

    def upload_dir(self, download_path, remote_dir_path):
        for root, dirs, files in os.walk(download_path):
            for file in files:
                local_file_path = os.path.join(root, file)
                remote_file_path = os.path.join(remote_dir_path, file)
                self.ftp.upload_file(local_file_path, remote_file_path)

    def upload_file(self, local_file_path, remote_file_path):
        '''从本地上传文件到ftp
            Parameters
        ----------
        local_path : str
            本地文件路径
        remote_path : str
            云端文件路径

        Returns
        -------
        bool
            成功返回True,失败False
            '''

        logger.info('正在上传文件{}到{}'.format(local_file_path, remote_file_path))
        bufsize = 1024
        fp = open(local_file_path, 'rb')
        try:
            self.ftp.storbinary('STOR ' + remote_file_path, fp, bufsize)
        except Exception as err:
            logger.error('上传文件失败, err={}'.format(err))
            self.ftp_connect()
            self.ftp.storbinary('STOR ' + remote_file_path, fp, bufsize)
        self.ftp.set_debuglevel(0)
        fp.close()

    def ftp_disconnect(self):
        logger.info('断开ftp连接')
        try:
            self.ftp.quit()
        except Exception as err:
            logger.error('断开ftp连接失败, error={}'.format(err))
