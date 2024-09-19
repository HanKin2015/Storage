/*******************************************************************************
* 文 件 名: wol_example.c
* 文件描述: wol网络唤醒
* 备    注: 请注意，发送广播包通常需要管理员权限，因此需要使用 sudo 运行程序
* 作    者: HanKin
* 创建日期: 2024.09.18
* 修改日期：2024.09.18
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 生成魔术包
void create_magic_packet(uint8_t *packet, const uint8_t *mac_addr) {
    // 前导码：6个字节的0xFF
    memset(packet, 0xFF, 6);

    // MAC地址重复16次
    for (int i = 0; i < 16; i++) {
        memcpy(packet + 6 + i * 6, mac_addr, 6);
    }
    return;
}

// 发送魔术包
void send_magic_packet(const uint8_t *packet, const char *broadcast_ip, int port) {
    int sockfd;
    struct sockaddr_in addr;

    // 创建UDP套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置广播选项
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 设置目标地址
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(broadcast_ip);

    // 发送魔术包
    if (sendto(sockfd, packet, 102, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);
}

// 发送魔术包
void send_magic_packet1(const char *broadcast, int port, const char *mac_address)
{
    assert(broadcast);
    assert(mac_address);
    
    int ret = 0;
    const uint32_t magic_data_len      = 102;   // 魔术包的大小 6 + 6 * 16 = 102
    const uint32_t mac_addr_byte_len   = 6;     // MAC地址是6字节（48位）。MAC地址由12个16进制数组成，每2个16进制数之间用冒号隔开
    const uint32_t mac_addr_repeat_cnt = 16;    // 魔术包需要重复16次mac地址

    // 魔术包相关变量
	uint8_t mac_addr[6] = { 0 };        // 数字形式的mac地址数组
    uint8_t magic_packet[102] = { 0 };  // 魔术包
    int magic_packet_pos = 0;           // 魔术包每次填充的位置


    // 判断Mac地址格式，已验证（非法十六进制以及缺失片段），这种写法判断没有问题
    ret = sscanf(mac_address, "%2x:%2x:%2x:%2x:%2x:%2x", &mac_addr[0], &mac_addr[1], &mac_addr[2], &mac_addr[3]
        , &mac_addr[4], &mac_addr[5]);
    if (ret != mac_addr_byte_len) {
        printf("Invalid mac address chMac:%s", mac_address);
        goto _fin;
    }

    // 构造Magic Packet (包格式: "FFFFFFFFFFFF" + 重复16次mac地址)
    // 在魔术包开头填充6个ff
    memset(magic_packet, 0xff, mac_addr_byte_len);
    // 填充16次mac地址
    magic_packet_pos = mac_addr_byte_len; // 记录每次填充的位置
    for (int i = 0; i < mac_addr_repeat_cnt; i++) {
        memcpy(magic_packet + magic_packet_pos, mac_addr, mac_addr_byte_len);
        magic_packet_pos += mac_addr_byte_len;
    }
    for (int i = 0; i < magic_data_len; i++) {
        printf("%d: %02x\n", i, magic_packet[i]);
    }

    send_magic_packet(magic_packet, broadcast, port);

_fin:
    return;
}

int main(int argc, char *argv[])
{   
    // 目标计算机的MAC地址
    const uint8_t mac_addr[6] = {0xA4, 0x17, 0x91, 0x04, 0x01, 0x87};

    // 广播地址和端口
    const char *broadcast_ip = "255.255.255.255";
    int port = 9;   // 设置为 9，这是一个常用的WoL端口

    // 创建魔术包
    uint8_t packet[102];
    create_magic_packet(packet, mac_addr);

    // 发送魔术包
    //send_magic_packet(packet, broadcast_ip, port);

    printf("Magic packet sent to %s:%d\n", broadcast_ip, port);
    
    const char *mac_address = "a4:17:91:04:01:87";
    send_magic_packet1(broadcast_ip, port, mac_address);
    return 0;
}
