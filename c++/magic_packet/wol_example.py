# -*- coding: utf-8 -*-
"""
文 件 名: wol_example.py
文件描述: wol网络唤醒
备    注: https://blog.csdn.net/qq_35150992/article/details/139954614
作    者: HanKin
创建日期: 2024.09.18
修改日期：2024.09.18

Copyright (c) 2024 HanKin. All rights reserved.
"""
import socket
import struct
 
def send_wol_packet(mac_address, broadcast_address='192.168.1.255'):
    # 检查MAC地址的格式并转换为字节
    if len(mac_address) == 12:
        pass
    elif len(mac_address) == 17:
        mac_address = mac_address.replace(mac_address[2], '')
    else:
        raise ValueError("MAC地址格式错误")
 
    print(mac_address)  # mac_address[2]为:
 
    # 将MAC地址转换为字节
    mac_bytes = bytes.fromhex(mac_address)
 
    # 构建魔法包
    magic_packet = b'\xff' * 6 + mac_bytes * 16
 
    # 创建一个UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
    # 允许广播
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
 
    # 发送魔法包，设置为 9，这是一个常用的WoL端口
    sock.sendto(magic_packet, (broadcast_address, 9))
    # sock.sendto(magic_packet, (ip_address, port))
 
    # 关闭socket
    sock.close()
    print("mac: {}, broadcast: {}:{}, 发送成功啦~".format(mac_address, broadcast_address, 9))
 
# 示例使用
mac_address = 'FE:FC:FE:C0:0D:6B'
broadcast_address = '255.255.255.255'  # 替换为你的VPN子网的广播地址
send_wol_packet(mac_address, broadcast_address)