/**
* 文 件 名: scsi_example.c
* 文件描述: scsi指令学习
* 作    者: HanKin
* 创建日期: 2023.08.16
* 修改日期：2023.08.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <scsi/sg.h>
#include <scsi/scsi.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main()
{
    int sg_fd;
    struct sg_io_hdr io_hdr;
    unsigned char cdb[16];
    unsigned char sense_buffer[32];
    unsigned char data_buffer[8];

    // 打开SG设备文件
    sg_fd = open("/dev/sg0", O_RDWR);
    if (sg_fd < 0) {
        perror("Failed to open SG device");
        return 1;
    }

    // 清空结构体
    memset(&io_hdr, 0, sizeof(struct sg_io_hdr));
    memset(cdb, 0, sizeof(cdb));
    memset(sense_buffer, 0, sizeof(sense_buffer));
    memset(data_buffer, 0, sizeof(data_buffer));

    // 填充SCSI CDB
    cdb[0] = 0x25;  // opcode
    // 其他字段根据需要进行填充

    // 设置SG_IO命令参数
    io_hdr.interface_id = 'S';
    io_hdr.cmd_len = sizeof(cdb);
    io_hdr.cmdp = cdb;
    io_hdr.sbp = sense_buffer;
    io_hdr.mx_sb_len = sizeof(sense_buffer);
    io_hdr.dxfer_direction = SG_DXFER_FROM_DEV;
    io_hdr.dxfer_len = sizeof(data_buffer);
    io_hdr.dxferp = data_buffer;
    io_hdr.timeout = 20000;  // 设置超时时间，单位为毫秒

    // 发送SCSI命令
    if (ioctl(sg_fd, SG_IO, &io_hdr) < 0) {
        perror("SCSI command failed");
        close(sg_fd);
        return 1;
    }

    // 解析返回结果
    if (io_hdr.status != 0) {
        fprintf(stderr, "SCSI command failed with status 0x%x\n", io_hdr.status);
        close(sg_fd);
        return 1;
    }

    // 处理返回的数据
    // 根据需要进行解析和处理data_buffer中的数据
    for (int i = 0; i < 8; i++) {
        printf("data_buffer[%d] = 0x%02x\n", i, data_buffer[i]);
    }

    // 关闭SG设备文件
    close(sg_fd);

    return 0;
}
