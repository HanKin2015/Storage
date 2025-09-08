#!/usr/bin/env python3
# 声明脚本解释器（必须在第一行，确保服务器能正确执行）
#
# 文 件 名: hello.cgi
# 文件描述: 用 Python 编写的 CGI 脚本，功能是接收 GET 请求参数并返回动态 HTML
# 作    者: HanKin
# 创建日期: 2025.09.05
# 修改日期：2025.09.05
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

import os
import cgi

# 输出HTTP响应头（必须以空行结束，告诉服务器后续是内容）
print("Content-Type: text/html; charset=utf-8")
print()  # 空行分隔响应头和内容

# 读取CGI环境变量（来自服务器）
request_method = os.environ.get('REQUEST_METHOD', 'GET')
remote_addr = os.environ.get('REMOTE_ADDR', '未知IP')

# 解析GET参数（如URL中的?name=xxx）
form = cgi.FieldStorage()
name = form.getvalue('name', 'Guest')  # 若没有name参数，默认值为Guest

# 生成HTML响应内容
print(f"""
<html>
<head>
    <title>CGI示例</title>
</head>
<body>
    <h1>Hello, {name}!</h1>
    <p>请求方法: {request_method}</p>
    <p>你的IP: {remote_addr}</p>
    <form method="get" action="hello.cgi">
        输入姓名: <input type="text" name="name">
        <input type="submit" value="提交">
    </form>
</body>
</html>
""")
