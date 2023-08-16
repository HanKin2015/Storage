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

static int deal_datain(struct cmd_block_wrapper *cbw,
    unsigned char *data, int data_size)
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    assert(dev_handle);
    
    unsigned int timeout = 5000;
    unsigned char ep = 0x81;
    // 发送cbw
    int transferred = 0;
    int length = data_size;
    int ret = libusb_bulk_transfer(dev_handle, ep, data, length, &transferred, timeout);
    INFO("libusb_bulk_transfer finish, ret %d, ep 0x%x, transferred %d\n",
            ret, ep, transferred == 0 ? -1 : transferred);
    // LIBUSB_ERROR_OTHER -99
    // LIBUSB_ERROR_PIPE -9
    // LIBUSB_ERROR_IO -1
    if (ret == LIBUSB_SUCCESS) {
        struct scsi_data_read_capacity10 *read_capacity10data = (struct scsi_data_read_capacity10 *)data;
        INFO("deal_datain success, size_per_sector=%d, all_sector_count=%d\n",
            read_capacity10data->size_per_block, read_capacity10data->ret_lba);
        return 0;
    }
    ERROR("deal_datain failed\n");
    libusb_exit(ctx);
    return -1;
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
    cbw.dCBWTag = 1;
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
        ERROR("usbacc_read_capacity, ret=%d\n", ret);
        return ret;
    }
    INFO("usbacc_read_capacity ok, size_per_sector=%d, all_sector_count=%d\n",
        read_capacity10data.size_per_block, read_capacity10data.ret_lba);
    return 0;
}