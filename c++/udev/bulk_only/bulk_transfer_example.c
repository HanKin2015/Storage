/**
* 文 件 名: bulk_transfer_example.c
* 文件描述: scsi指令学习
* 备    注: gcc bulk_transfer_example.c -lusb-1.0
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
#include <libusb-1.0/libusb.h>
#include <assert.h>

#define INFO(fmt, ...) printf("[INFO][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...) printf("[DEBUG][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("[WARN][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define ERROR(fmt, ...) printf("[ERROR][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)

#define USB_VENDOR_ID  0x0951
#define USB_PRODUCT_ID 0x1666

/*
 * 对于固定长度的cdb而言，其长度可以通过 opcode 的前三位的获得
 * 0 表示无法获得 指定 opcode 的cdb大小
 */
const uint8_t g_scsi_cdb_size_tbl[8] =
{
	6, 10, 10, 0,
	16, 12, 0, 0
};
#define SCSI_CDB_SIZE(opcode) g_scsi_cdb_size_tbl[((opcode) >> 5) & 7]

/*
 * scsi_cdb_XXXX10 表示 10 字节的 scsi 命令
 * scsi_data_XXXX10 表示 10 字节的 scsi 命令所需要传输的数据
 */

// READ CAPACITY
// requests that the device server transfer 8 bytes of parameter data describing
// the capacity and medium format of the direct-access block device to the
// data-in buffer.
// Ref: SCSI Commands Reference Manual.pdf (Page 126)
struct scsi_cdb_read_capacity10 {
    uint8_t opcode;
    uint8_t reserved1;
    uint32_t lba;
    uint8_t reserved2[3];
    uint8_t control;
};
struct scsi_data_read_capacity10 {
    uint32_t ret_lba;           // 当PMI 为0时, 表示最后一个逻辑块的地址
    uint32_t size_per_block;    // 每一个逻辑块的大小, 字节为单位
};

#define BULK_CBW_SIGNATURE_SIZE 4
#define BULK_CBW_SIGNATURE_0    'U'
#define BULK_CBW_SIGNATURE_1    'S'
#define BULK_CBW_SIGNATURE_2    'B'
#define BULK_CBW_SIGNATURE_3    'C'

#define BULK_CSW_SIGNATURE_SIZE 4
#define BULK_CSW_SIGNATURE_0    'U'
#define BULK_CSW_SIGNATURE_1    'S'
#define BULK_CSW_SIGNATURE_2    'B'
#define BULK_CSW_SIGNATURE_3    'S'

#pragma pack(push)
#pragma pack(1)
// Section 5.1: Command Block Wrapper (CBW)
struct cmd_block_wrapper {
    uint8_t dCBWSignature[BULK_CBW_SIGNATURE_SIZE];     // 0x43425355
    uint32_t dCBWTag;
    uint32_t dCBWDataTransferLength;
    uint8_t bmCBWFlags;
    uint8_t bCBWLUN;
    uint8_t bCBWCBLength;
    uint8_t CBWCB[16];
};

// Section 5.2: Command Status Wrapper (CSW)
struct cmd_status_wrapper {
    uint8_t dCSWSignature[BULK_CBW_SIGNATURE_SIZE];     // 0x53425355
    uint32_t dCSWTag;
    uint32_t dCSWDataResidue;
    uint8_t bCSWStatus;
};
#pragma pack(pop)

void set_cbw_signature(struct cmd_block_wrapper *cbw)
{
    if (cbw == NULL)
        return;
    cbw->dCBWSignature[0] = BULK_CBW_SIGNATURE_0;
    cbw->dCBWSignature[1] = BULK_CBW_SIGNATURE_1;
    cbw->dCBWSignature[2] = BULK_CBW_SIGNATURE_2;
    cbw->dCBWSignature[3] = BULK_CBW_SIGNATURE_3;
}

void set_csw_signature(struct cmd_status_wrapper *csw)
{
    if (csw == NULL)
        return;
    csw->dCSWSignature[0] = BULK_CSW_SIGNATURE_0;
    csw->dCSWSignature[1] = BULK_CSW_SIGNATURE_1;
    csw->dCSWSignature[2] = BULK_CSW_SIGNATURE_2;
    csw->dCSWSignature[3] = BULK_CSW_SIGNATURE_3;
}

/**
 * 将 cbw 结构体中的所有多字节字段从 host byte order 转换为 little endian
 * @param[in/out]   cbw
 */
void cbw_h2le(void *buf)
{
    struct cmd_block_wrapper *cbw = (struct cmd_block_wrapper*)buf;
    cbw->dCBWTag = htole32(cbw->dCBWTag);
    cbw->dCBWDataTransferLength = htole32(cbw->dCBWDataTransferLength);
}

/**
 * 进行bulk transfer 传输时，如果出现 LIBUSB_ERROR_PIPE 错误，则
 * libusb_clear_halt 该端点，重试。直到达到重试次数(5次)，返回。
 * @return
 *  see libusb_error
 */
int bulk_transfer_clear_halt(struct libusb_device_handle *dev_handle,
	unsigned char ep, unsigned char *data, int length, int *transferred,
	unsigned int timeout)
{
    #define BULK_RETRY_MAX 5

    int i = 0;
    int ret = 0;
    // 这里就不对超时错误进行重复传输了，使用前自己分配足够的时间
    while(i < BULK_RETRY_MAX) {
        ret = libusb_bulk_transfer(dev_handle, ep, data, length, transferred,
                                    timeout);
        INFO("libusb_bulk_transfer finish, ret %d, i %d, ep 0x%x, transferred %d\n",
            ret, i, ep, transferred == NULL ? -1 : *transferred);
        // LIBUSB_ERROR_OTHER -99
        // LIBUSB_ERROR_PIPE -9
        // LIBUSB_ERROR_IO -1
        if (ret != LIBUSB_ERROR_PIPE) {
            return ret;
        }
        INFO("libusb_clear_halt finish, ret %d, ep 0x%x\n",
                libusb_clear_halt(dev_handle, ep), ep);
        i++;
    }
    return ret;
}

static int deal_datain(struct cmd_block_wrapper *cbw,
    unsigned char *data, int data_size)
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数获取libusb_device_handle
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    assert(dev_handle);
    
    // 替换usbfs驱动进行操作
    libusb_set_auto_detach_kernel_driver(dev_handle, 1);
    // 只打开0 interface
    int ret = libusb_claim_interface(dev_handle, 0);
    if (ret != LIBUSB_SUCCESS) {
        printf("libusb cliam interface 0 failed, %d %s\n", ret, libusb_strerror(ret));
        goto close_libusb;
    }
    
    unsigned int timeout = 5000;
    unsigned char ep_in  = 0x81;
    unsigned char ep_out = 0x02;
    
    // 发送cbw
    INFO("%02x %02x %02x %02x %08x %08x %02x %02x %02x\n", cbw->dCBWSignature[0], cbw->dCBWSignature[1],
        cbw->dCBWSignature[2], cbw->dCBWSignature[3], cbw->dCBWTag, cbw->dCBWDataTransferLength,
        cbw->bmCBWFlags, cbw->bCBWLUN, cbw->bCBWCBLength);
    for (int i = 0; i < 16; i++) {
        INFO("%02x\n", cbw->CBWCB[i]);
    }
    INFO("%d %d\n", data_size, sizeof(*cbw));
    
    int transferred = 0;
    ret = bulk_transfer_clear_halt(dev_handle, ep_out, (unsigned char*)cbw,
            sizeof(*cbw), &transferred, timeout);
    INFO("CBW bulk_transfer_clear_halt cbw finish, ret %d, ep_out 0x%x, transferred 0x%x\n",
        ret, ep_out, transferred);
    if (ret != LIBUSB_SUCCESS) {
        ERROR("bulk_transfer_clear_halt cbw fail, ret=%d, actual_length=%d\n",
            ret, transferred);
        return -1;
    }

    // data_in（LIBUSB_ERROR_TIMEOUT -7）
    transferred = 0;
    ret = libusb_bulk_transfer(dev_handle, ep_in, data, data_size,
        &transferred, timeout);
    INFO("DATA bulk_transfer_clear_halt data-in finish, ret %d, ep_in 0x%x, actual_length 0x%x\n",
        ret, ep_in, transferred);
    
    // 处理csw
    struct cmd_status_wrapper csw;
    transferred = 0;
    ret = bulk_transfer_clear_halt(dev_handle, ep_in, (unsigned char*)&csw,
            sizeof(csw), &transferred, timeout);
    INFO("CSW bulk_transfer_clear_halt csw finish, ret %d, ep_in 0x%x, actual_length 0x%x\n",
        ret, ep_in, transferred);
    if (ret != LIBUSB_SUCCESS) {
        ERROR("bulk_transfer_clear_halt cbw fail, ret=%d, actual_length=%d\n",
            ret, transferred);
        return -1;
    }
    
    INFO("deal_datain done\n");
    
release_interface:
    libusb_release_interface(dev_handle, 0);
close_libusb:
    libusb_close(dev_handle);
exit_libusb:
    libusb_exit(ctx);
    return 0;
}

static int read_capacity(struct scsi_data_read_capacity10 *data)
{
    int ret = 0;
    struct scsi_cdb_read_capacity10 cdb;    // Command Descriptor Block
    struct cmd_block_wrapper cbw;

    // 构造 scsi cdb
    memset(&cdb, 0, sizeof(cdb));
    cdb.opcode = READ_CAPACITY;
    cdb.lba= 0;

    // 构造 cbw
    memset(&cbw, 0,  sizeof(cbw));
    set_cbw_signature(&cbw);
    cbw.dCBWTag = 0xed3839b0;
    cbw.dCBWDataTransferLength = sizeof(*data);
    cbw.bmCBWFlags = LIBUSB_ENDPOINT_IN;
    cbw.bCBWLUN = 0;
    cbw.bCBWCBLength = SCSI_CDB_SIZE(cdb.opcode);
    // 转换字节序
    memcpy(cbw.CBWCB, &cdb, sizeof(cdb));
    // cbw 在传输中多字节字段均使用 little endian(即最低有效位在低地址)
    cbw_h2le(&cbw);
    ret = deal_datain(&cbw, (unsigned char*)data, sizeof(cbw));
    INFO("read_capacity deal_datain finish, ret %d\n", ret);
    if (ret != 0) {
        ERROR("deal_datain fail, ret %d\n", ret);
        return -1;
    }
    
    // 打印出结果
    data->ret_lba = be32toh(data->ret_lba);
    data->size_per_block = be32toh(data->size_per_block);
    INFO("last_block_lba=0x%x, size_per_block=0x%x\n",
        data->ret_lba, data->size_per_block);
    return 0;
}

int main(int argc, char *argv[])
{
    struct scsi_data_read_capacity10 read_capacity10data = {0, 0};
    int ret = read_capacity(&read_capacity10data);
    if (ret != 0) {
        ERROR("read_capacity, ret=%d\n", ret);
        return ret;
    }
    INFO("read_capacity ok, size_per_sector=%d, all_sector_count=%d\n",
        read_capacity10data.size_per_block, read_capacity10data.ret_lba);
    return 0;
}