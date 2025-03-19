/*******************************************************************************
* 文 件 名: send_SCSI_to_upan.cpp
* 文件描述: 向U盘发送SCSI指令
* 作    者: HanKin
* 创建日期: 2025.03.17
* 修改日期：2025.03.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/sg.h>
#include <sys/ioctl.h>
#include <errno.h>

#define SG_DEVICE "/dev/sg0"  // SCSI Generic 设备文件
#define SCSI_CMD_LEN 6         // SCSI 命令长度

int main() {
    int fd;
    struct sg_io_hdr io_hdr;
    unsigned char cmd[SCSI_CMD_LEN];  // SCSI 命令
    unsigned char sense_buffer[32];     // 用于存储错误信息
    unsigned char data_buffer[512];      // 数据缓冲区

    // 打开 SCSI Generic 设备
    fd = open(SG_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Error opening SCSI Generic device");
        return EXIT_FAILURE;
    }

    // 初始化 SCSI 命令（示例：读取10个扇区）
    memset(cmd, 0, SCSI_CMD_LEN);
    cmd[0] = 0x28;  // SCSI 读取命令
    cmd[2] = 0;     // LBA 高字节
    cmd[3] = 0;     // LBA 中字节
    cmd[4] = 0;     // LBA 低字节
    cmd[7] = 10;    // 读取的扇区数

    // 初始化 SCSI I/O 头
    memset(&io_hdr, 0, sizeof(io_hdr));
    io_hdr.interface_id = 'S';
    io_hdr.dxfer_direction = SG_DXFER_FROM_DEV; // 从设备读取数据
    io_hdr.dxfer_len = sizeof(data_buffer);     // 数据缓冲区长度
    io_hdr.dxferp = data_buffer;                 // 数据缓冲区指针
    io_hdr.cmd_len = SCSI_CMD_LEN;              // SCSI 命令长度
    io_hdr.cmdp = cmd;                          // SCSI 命令指针
    io_hdr.sense = sense_buffer;                // 错误信息缓冲区
    io_hdr.sense_len = sizeof(sense_buffer);    // 错误信息缓冲区长度
    io_hdr.timeout = 10000;                     // 超时时间（毫秒）

    // 发送 SCSI 命令
    if (ioctl(fd, SG_IO, &io_hdr) < 0) {
        perror("Error sending SCSI command");
        close(fd);
        return EXIT_FAILURE;
    }

    // 检查 SCSI 命令的返回状态
    if (io_hdr.status != 0) {
        fprintf(stderr, "SCSI command failed with status: %d\n", io_hdr.status);
        close(fd);
        return EXIT_FAILURE;
    }

    // 处理读取的数据
    printf("Data read from device:\n");
    for (int i = 0; i < sizeof(data_buffer); i++) {
        printf("%02x ", data_buffer[i]);
    }
    printf("\n");

    // 关闭设备
    close(fd);
    return EXIT_SUCCESS;
}
