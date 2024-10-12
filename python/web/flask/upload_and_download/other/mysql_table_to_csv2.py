# -*- coding: utf-8 -*-
"""
文 件 名: mysql_table_to_csv2.py
文件描述: MySQL数据库表导出到csv文件中
作    者: HanKin
创建日期: 2024.10.11
修改日期：2024.10.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pandas as pd
from sqlalchemy import create_engine

# 创建数据库连接
# 替换以下信息为你的数据库信息
username = 'root'
password = 'sangfor'
host = 'localhost'
port = '3306'  # 默认 MySQL 端口
database = 'reports_db'

# 创建连接字符串
connection_string = f'mysql+mysqlconnector://{username}:{password}@{host}:{port}/{database}'

# 创建 SQLAlchemy 引擎
engine = create_engine(connection_string)

# 定义查询
query = 'SELECT * FROM total'

# 使用 Pandas 读取 SQL 查询结果
df = pd.read_sql(query, engine)

# 将 DataFrame 导出为 CSV 文件
df.to_csv('total.csv', index=False)

print("Data exported to CSV successfully.")
