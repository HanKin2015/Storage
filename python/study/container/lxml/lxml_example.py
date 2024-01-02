# -*- coding: utf-8 -*-
"""
文 件 名: lxml_example.py
文件描述: 打开xml文件并解析
作    者: HanKin
创建日期: 2024.01.02
修改日期：2024.01.02

Copyright (c) 2024 HanKin. All rights reserved.
"""
from lxml import etree

def lxml_example():
    with open("./data.xml", "r", encoding="utf-8") as f:
        data_xml = f.read()
    try:
        tree = etree.XML(data_xml)
    except Exception as err:
        print("数据文件格式异常，不是标准的xml格式, {}".format(err))
        return
    usb_list = []
    
    # usb list data标签
    usb_device_rule = tree.xpath("//UsbDeviceRule")[0]
    print(usb_device_rule.get("MaxMap"), usb_device_rule.get("ClassFilter"))
    
    # 列表标签
    usb_list = tree.xpath("//UsbList//Dev")
    print(len(usb_list))
    for usb in usb_list:
        print(usb.get("ID"), usb.get("Desc"), usb.get("Ep"), usb.get("Aligned"))

    # 根标签
    root = tree.xpath("//DataContent")[0]
    print(root.get("EnableVirPrint"), root.get("EnableUSBWrite"))
    
    # 是不是前面规范的写法应该是
    usb_list = tree.xpath("//DataContent//UsbList//Dev")
    print(len(usb_list))
    for usb in usb_list:
        print(usb.get("ID"), usb.get("Desc"), usb.get("Ep"), usb.get("Aligned"))

import lxml
def debug():
    with open("./data.xml", "r", encoding="utf-8") as f:
        data_xml = f.read()
    tree = lxml.etree.XML(data_xml)
    print("debug success")

if __name__ == '__main__':
    lxml_example()
    debug()