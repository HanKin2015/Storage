"""
文 件 名: sqlite3_example.py
文件描述: python操作sqlite3
备    注: https://blog.csdn.net/yprufeng/article/details/131433167
作    者: HanKin
创建日期: 2023.11.13
修改日期：2023.11.13

Copyright (c) 2023 HanKin. All rights reserved.
"""

# sqlite3数据库
import sqlite3
 
class MySqlite(object):
    """
    初始化数据库连接
    """
    def __init__(self):
        # 连接数据库
        db_file = 'app.sqlite'
        self.conn = sqlite3.connect(db_file)
 
    """
    关闭数据库连接
    """
    def close(self):
        self.conn.close()

connection = sqlite3.connect("database.db")
cursor = connection.cursor()
cursor.execute("SELECT * FROM students")
data = cursor.fetchall()
for row in data:
    print(row)
connection.close()