# -*- coding: utf-8 -*-
"""
文 件 名: join_use_in_set.py
文件描述: join可以连接list和set集合
作    者: HanKin
创建日期: 2023.12.21
修改日期：2023.12.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
import json

with open(r"D:\Demo\additional_data\device_helper\manual_troubleshooting.json", encoding="utf-8") as f:
    json.load(f)

tips_set = set()
tips_set.add("hello")
tips_set.add("python")
tips_set.add("world")
tips_set.add("hello")
tips_set.add("python")
tips_set.add("world")
tips_set.add("建议更换虚拟机模板或者终端进行对比测试")
tips_set.add("建议更换虚拟机模板或者终端进行对比测试")
tips_set.add("需要使用业务软件使用外设的请以管理员身份打开业务软件")
tips_set.add("需要使用业务软件使用外设的请以管理员身份打开业务软件")
tips = "\n".join(tips_set)
print(tips)

tips_list = []
tips_list.append("- hello\n- world")
tips_list.append("- hello\n- python")
tips_list.append("- english\n- world")
tips = "\n".join(tips_list)
tips = "\n".join(set(tips.split("\n")))
print(tips)