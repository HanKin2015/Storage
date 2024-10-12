# -*- coding: utf-8 -*-
"""
文 件 名: read_sql_file.py
文件描述: 读取mysqldump命令导出的数据表内容
作    者: HanKin
创建日期: 2024.10.12
修改日期：2024.10.12

Copyright (c) 2024 HanKin. All rights reserved.
"""
import csv
import re

def sql_to_csv(sql_file_path, csv_file_path):
    # 正则表达式匹配 CREATE TABLE 和 INSERT 语句
    create_table_pattern = re.compile(
        r"CREATE TABLE `?(\w+)`? \((.*?)\)\s*ENGINE=", re.DOTALL)
    insert_stmt_pattern = re.compile(
        r"INSERT INTO `?(\w+)`? VALUES\s*\((.*?)\);", re.DOTALL)

    # 打开 SQL 文件并读取内容
    with open(sql_file_path, 'r', encoding='utf-8') as sql_file:
        sql_content = sql_file.read()

    # 查找 CREATE TABLE 语句以提取列名
    create_table_match = create_table_pattern.search(sql_content)
    if not create_table_match:
        print("No CREATE TABLE statement found in the SQL file.")
        return

    table_name, columns_def = create_table_match.groups()
    # 提取列名，排除 PRIMARY KEY 和其他约束
    columns = re.findall(r"`(\w+)`\s+\w+", columns_def)
    print(columns)

    # 查找所有 INSERT 语句
    matches = insert_stmt_pattern.findall(sql_content)
    if not matches:
        print("No INSERT statements found in the SQL file.")
        return

    # 准备 CSV 文件
    with open(csv_file_path, 'w', newline='', encoding='utf-8') as csv_file:
        writer = csv.writer(csv_file)

        # 写入列名
        writer.writerow(columns)

        # 写入数据行
        for _, values in matches:
            # 解析每组值
            values_list = re.findall(r"\((.*?)\)", values, re.DOTALL)
            for value_tuple in values_list:
                # 解析每个值
                values = [val.strip().strip("'") for val in value_tuple.split(',')]
                writer.writerow(values)

    print(f"Data exported to {csv_file_path} successfully.")

# 调用函数，传入 SQL 文件路径和目标 CSV 文件路径
sql_to_csv('total.sql', 'output.csv')
