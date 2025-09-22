#!/usr/bin/python3
# 声明脚本解释器（必须在第一行，确保服务器能正确执行）
#
# 文 件 名: result.cgi
# 文件描述: 用 Python 编写的 CGI 脚本，功能是接收 GET 请求参数并返回动态 HTML
# 作    者: HanKin
# 创建日期: 2025.09.17
# 修改日期：2025.09.17
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#
import sys,os
import urllib
length = os.getenv('CONTENT_LENGTH')

if length:
    postdata = sys.stdin.read(int(length))
    print("Content-type:text/html\n")
    print('<html>')
    print('<head>')
    print('<title>POST</title>')
    print('</head>')
    print('<body>')
    print('<h2> Your POST data: </h2>')
    print('<ul>')
    for data in postdata.split('&'):
        print('<li>'+data+'</li>')
    print('</ul>')
    print('</body>')
    print('</html>')
    
else:
    print("Content-type:text/html\n")
    print('no found')


