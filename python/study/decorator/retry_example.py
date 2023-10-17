# -*- coding: utf-8 -*-
"""
文 件 名: retry_example.py
文件描述: retry装饰器
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""

from retrying import retry
import time

number = -1

@retry(stop_max_attempt_number=5, wait_fixed=2000)
def my_func():
    """
    ******** starting ********
    division by zero
    process spend 2.003 s.
    """
    try:
        global number
        number += 1
        result = 100 / number
    except Exception as err:
        print(err)
    return result

@retry(stop_max_attempt_number=5)
def my_func2():
    """
    说明时间间隔几乎没有
    ******** starting ********
    division by zero
    process spend 0.0 s.
    """
    try:
        global number
        number += 1
        result = 100 / number
    except Exception as err:
        print(err)
    return result

import traceback
@retry(stop_max_attempt_number=5)
def my_func3():
    """
    抛出异常重试
    ******** starting ********
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    Traceback (most recent call last):
      File "retry_example.py", line 60, in my_func3
        result = 100 / 0
    ZeroDivisionError: division by zero

    During handling of the above exception, another exception occurred:

    Traceback (most recent call last):
      File "retry_example.py", line 80, in <module>
        main()
      File "retry_example.py", line 71, in main
        my_func3()
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 56, in wrapped_f
        return Retrying(*dargs, **dkw).call(f, *args, **kw)
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 266, in call
        raise attempt.get()
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 301, in get
        six.reraise(self.value[0], self.value[1], self.value[2])
      File "C:\ProgramData\Anaconda3\lib\site-packages\six.py", line 703, in reraise
        raise value
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 251, in call
        attempt = Attempt(fn(*args, **kwargs), attempt_number, False)
      File "retry_example.py", line 64, in my_func3
        raise Exception("操作失败")
    Exception: 操作失败
    """
    print("******** my_func3 ********")
    result = -1
    try:
        result = 100 / 0
    except Exception as err:
        print(err)
        #print(traceback.format_exc())
        raise Exception("操作失败")
    return result

@retry(stop_max_attempt_number=5, retry_on_result=lambda result: result is None)
def my_func4():
    """
    指定返回值进行重试
    ******** starting ********
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    ******** my_func3 ********
    division by zero
    Traceback (most recent call last):
      File "retry_example.py", line 98, in <module>
        main()
      File "retry_example.py", line 89, in main
        my_func4()
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 56, in wrapped_f
        return Retrying(*dargs, **dkw).call(f, *args, **kw)
      File "C:\ProgramData\Anaconda3\lib\site-packages\retrying.py", line 268, in call
        raise RetryError(attempt)
    retrying.RetryError: RetryError[Attempts: 5, Value: None]
    """
    print("******** my_func3 ********")
    result = -1
    try:
        result = 100 / 0
    except Exception as err:
        print(err)
        return None
    return result

def my_func5(conn, cmd, has_ret_value=True, key=None):
    """
    老老实实写重试函数

    执行命令，重试5次，睡眠间隔0.5秒
    :param conn: 连接对象
    :param cmd: 命令
    :param has_ret_value: 执行的命令是否会生成ret_value文件存储命令执行状态
    :param key: 命令执行结果中需要获取值的键
    :return status: 命令执行状态
    :return result: 命令返回的结果
    """
    status = "0"
    result = ""
    retry_count = 0
    while retry_count < 5:
        result = conn.exec_command(cmd)
        if has_ret_value:
            status = conn.exec_command("cat /stmp/device_helper/ret_value").replace('\n', '')
            if status == "0":
                break
            logger.debug("exec command failed, status {}".format(status))
        else:
            result = json.loads(result).get(key, "")
            if result != "":
                break
        logger.debug("exec command failed, retry_count {}".format(retry_count))
        retry_count += 1
        time.sleep(0.5)
    return status, result

def main():
    """主函数
    """

    my_func4()

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))