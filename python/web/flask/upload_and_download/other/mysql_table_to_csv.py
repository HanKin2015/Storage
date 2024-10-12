# -*- coding: utf-8 -*-
"""
文 件 名: mysql_table_to_csv.py
文件描述: MySQL数据库表导出到csv文件中
备    注: Pandas 建议使用 SQLAlchemy 的连接对象或数据库 URI 字符串来进行数据库操作，因为这样可以更好地支持多种数据库类型，并提供更强大的功能和兼容性
作    者: HanKin
创建日期: 2024.10.11
修改日期：2024.10.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pandas as pd
import mysql.connector

# 连接到 MySQL 数据库
conn = mysql.connector.connect(
    host='localhost',
    user='root',
    password='sangfor',
    database='reports_db'
)

# 查询数据
query = "SELECT * FROM total"
df = pd.read_sql(query, conn)

# 导出为 CSV 文件
df.to_csv('total.csv', index=False)

# 关闭连接
conn.close()