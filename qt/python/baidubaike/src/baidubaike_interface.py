# -*- coding: utf-8 -*-
"""
文 件 名: baidubaike_interface.py
文件描述: 接口类
作    者: HanKin
创建日期: 2023.04.17
修改日期：2023.04.18

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

def remove_eference_dimension(file_path):
    """移除引用标注
    """

    # 读取中文时需要添加编码utf-8
    with open(file_path, 'r', encoding = 'utf-8') as f:
        lines = f.readlines()
    logger.info('{} have {} lines'.format(file_path, len(lines)))
    with open(file_path, 'w', encoding = 'utf-8') as f:
        # 生成正则对象
        pat = re.compile(r"(\[[0-9]+-?[0-9]*\])")
        # 计行数
        modify_count = 0
        for line in lines:
            #logger.info(line)
            ret = pat.findall(line)
            if len(ret):
                logger.info(ret)
                line = pat.sub('', line)
                #logger.info(line)
                #logger.info(pat.sub('', line))
                modify_count += 1
            #if 'TCL' in line:
            #     line = line.replace('TCL', 'HJ')
            f.write(line)
        logger.info('modify_count = {}'.format(modify_count))
    return

def parse_content(file_path):
    """
    """
    
    with open(file_path, 'r', encoding = 'utf-8') as f:
        lines = f.readlines()
    logger.info('{} have {} lines'.format(file_path, len(lines)))

    entry_list = []
    key   = None
    value = ''
    for line in lines:
        if line.find('#') != -1:
            if key != None:
                value = value.strip()
                entry_list.append((key, value))
            key = line[1:].strip()
            value = ''
        else:
            value += line
    
    for entry in entry_list:
        logger.debug(entry[0])
        logger.debug(entry[1])
        logger.debug('')
        
    logger.info('there are {} entries'.format(len(entry_list)))
    return entry_list

def db_import(entry_list):
    """数据库导入
    """
    
    # 连接到数据库
    conn = sqlite3.connect(DATABASE_PATH)

    # 创建一个表
    conn.execute('''CREATE TABLE IF NOT EXISTS wikipedia
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                 key TEXT NOT NULL UNIQUE,
                 value TEXT NOT NULL);''')

    # 插入数据
    for entry in entry_list:
        try:
            conn.execute("INSERT INTO wikipedia (key, value) VALUES (?, ?)", (entry[0], entry[1]))
        except sqlite3.IntegrityError as err:
            logger.debug('[{}] sqlite3.IntegrityError ignore, {}'.format(entry[0], err))
        except Exception as err:
            logger.error('[{}] there is a other exception, {}'.format(entry[0], err))
        finally:
            # 无论是否发生异常，都会执行的代码
            logger.debug('[{}] insert success'.format(entry[0]))

    # 提交更改并关闭连接
    conn.commit()
    conn.close()

def db_query(key):
    """
    """
    
    conn = sqlite3.connect(DATABASE_PATH)
    cursor = conn.execute("SELECT id, key, value FROM wikipedia WHERE key=?", (key,))
    #results = cursor.fetchall()
    #logger.info(len(results))
    
    value = ''
    for row in cursor:
        logger.debug("ID = {}, KEY = {}, VALUE = {}".format(row[0], row[1], row[2]))
        value = row[2]
    conn.close()
    logger.debug(value)
    return value

def get_wikipedia_entries():
    """
    """
    
    if not os.path.exists(DATABASE_PATH):
        return []
    
    conn = sqlite3.connect(DATABASE_PATH)
    cursor = conn.execute("SELECT key FROM wikipedia")
    
    key_list = []
    for row in cursor:
        key_list.append(row[0])
    logger.info('there are {} wikipedia entries'.format(len(key_list)))
    
    conn.close()
    return key_list

def main():
    """主函数
    """
    
    file_path = 'D:\\Github\\Storage\\qt\\python\\baidubaike\\src\\baidubaike.md'
    remove_eference_dimension(file_path)
    
    entry_list = parse_content(file_path)
    logger.debug(entry_list)
    
    db_import(entry_list)
    db_query('释迦牟尼')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))