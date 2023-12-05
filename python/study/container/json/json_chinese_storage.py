# -*- coding: utf-8 -*-
"""
文 件 名: json_chinese_storage.py
文件描述: json存储中文字符
作    者: HanKin
创建日期: 2023.12.04
修改日期：2023.12.04

Copyright (c) 2023 HanKin. All rights reserved.
"""
import json

json_str = '{"vid_pid": "0c45:636d", "version": "5.5.3.15", "client_sn": "1KM4380152", "vendor": "\u7f57\u6280", "model": "c370", "arch": "x86", "device_type": "\u6444\u50cf\u5934", "usage": "\u914d\u7f6e\u540d\u5355", "os": "win7", "xc": "", "remark": "\u6d4b\u8bd5\u6d4b\u8bd5are you ok!", "result": false}'
json_obj = json.loads(json_str)
print(json_obj)

with open ("./deviceinfo_json1.json", "w") as f:
    json.dump(json_obj, f)

# encoding没有作用，起作用的是ensure_ascii参数，不将所有非 ASCII 字符转义为 Unicode 转义序列
with open ("./deviceinfo_json2.json", "w", encoding="gbk") as f:
    json.dump(json_obj, f, ensure_ascii=False)