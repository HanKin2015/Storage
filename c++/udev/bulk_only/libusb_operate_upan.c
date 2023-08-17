/**
* 文 件 名: libusb_operate_upan.c
* 文件描述: libusb使用scsi操作U盘
* 备    注: gcc libusb_operate_upan.c -lusb-1.0
* 作    者: HanKin
* 创建日期: 2023.08.17
* 修改日期：2023.08.17
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <libusb-1.0/libusb.h>

#define BULK_TRANSFER_TIMEOUT 2000

// Section 5.1: Command Block Wrapper (CBW)
struct command_block_wrapper {
	uint8_t dCBWSignature[4];
	uint32_t dCBWTag;
	uint32_t dCBWDataTransferLength;
	uint8_t bmCBWFlags;
	uint8_t bCBWLUN;
	uint8_t bCBWCBLength;
	uint8_t CBWCB[16];
};

// Section 5.2: Command Status Wrapper (CSW)
struct command_status_wrapper {
	uint8_t dCSWSignature[4];
	uint32_t dCSWTag;
	uint32_t dCSWDataResidue;
	uint8_t bCSWStatus;
};

#define READ_BUFFER_LENGTH 524288

// USBC ==> 55 53 42 43
static uint8_t cbw_read[31] = {
    0x55, 0x53, 0x42, 0x43,
    0xb0, 0x39, 0x38, 0xed,
    0x00, 0x02, 0x00, 0x00,
    0x80, 0x00, 0x0a, 0x28,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

// USBC ==> 55 53 42 43
static uint8_t cbw_read_capacity[31] = {
    0x55, 0x53, 0x42, 0x43,
    0xb0, 0x39, 0x38, 0xed,
    0x08, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x0a, 0x25,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

static void display_buffer_hex(unsigned char *buffer, unsigned size)
{
	unsigned i, j, k;

	for (i=0; i<size; i+=16) {
		printf("\n  %08x  ", i);
		for(j=0,k=0; k<16; j++,k++) {
			if (i+j < size) {
				printf("%02x", buffer[i+j]);
			} else {
				printf("  ");
			}
			printf(" ");
		}
		printf(" ");
		for(j=0,k=0; k<16; j++,k++) {
			if (i+j < size) {
				if ((buffer[i+j] < 32) || (buffer[i+j] > 126)) {
					printf(".");
				} else {
					printf("%c", buffer[i+j]);
				}
			}
		}
	}
	printf("\n" );
}

static void test_device(uint16_t vid, uint16_t pid, uint8_t epin, uint8_t epout)
{
    libusb_device_handle *handle = NULL;
    uint8_t *data_buff = NULL;
    int actual_len = 0;
    int ret = -1;

    handle = libusb_open_device_with_vid_pid(NULL, vid, pid);
	if (handle == NULL) {
		printf("open device %04X:%04X failed\n", vid, pid);
		return;
	}

    libusb_set_auto_detach_kernel_driver(handle, 1);

    // 只打开0 interface
    ret = libusb_claim_interface(handle, 0);
    if (ret != LIBUSB_SUCCESS) {
        printf("libusb cliam interface 0 failed, %d %s\n", ret, libusb_strerror(ret));
        goto close_libusb;
    }

    data_buff = (uint8_t *)malloc(READ_BUFFER_LENGTH);
    assert(data_buff);

    // SCSI_READ=============================
    //cbw
    ret = libusb_bulk_transfer(handle, epout, cbw_read, sizeof(cbw_read), &actual_len, BULK_TRANSFER_TIMEOUT);
    printf("CBW read result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
    //data in
    ret = libusb_bulk_transfer(handle, epin, data_buff, READ_BUFFER_LENGTH, &actual_len, BULK_TRANSFER_TIMEOUT);
    printf("DATA read result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
    display_buffer_hex(data_buff, 64); // 仅打印64字节数据

    /*
    没有这一行结果就是：
    CBW read result=0, Success, actual_length=31
    DATA read result=0, Success, actual_length=512

      00000000  33 c0 fa 8e d8 8e d0 bc 00 7c 89 e6 06 57 8e c0  3........|...W..
      00000010  fb fc bf 00 06 b9 00 01 f3 a5 ea 1f 06 00 00 52  ...............R
      00000020  52 b4 41 bb aa 55 31 c9 30 f6 f9 cd 13 72 13 81  R.A..U1.0....r..
      00000030  fb 55 aa 75 0d d1 e9 73 09 66 c7 06 8d 06 b4 42  .U.u...s.f.....B
    CBW read_capcity result=0, Success, actual_length=31
    DATA read_capcity result=-8, Overflow, actual_length=0

      00000000  33 c0 fa 8e d8 8e d0 bc                          3.......
    CSW read_capcity result=-1, Input/Output Error, actual_length=0

      00000000  33 c0 fa 8e d8 8e d0 bc 00 7c 89 e6 06           3........|...

    添加了这一行结果就是：
    CBW read result=0, Success, actual_length=31
    DATA read result=0, Success, actual_length=512

      00000000  33 c0 fa 8e d8 8e d0 bc 00 7c 89 e6 06 57 8e c0  3........|...W..
      00000010  fb fc bf 00 06 b9 00 01 f3 a5 ea 1f 06 00 00 52  ...............R
      00000020  52 b4 41 bb aa 55 31 c9 30 f6 f9 cd 13 72 13 81  R.A..U1.0....r..
      00000030  fb 55 aa 75 0d d1 e9 73 09 66 c7 06 8d 06 b4 42  .U.u...s.f.....B
    CBW read_capcity result=0, Success, actual_length=31
    DATA read_capcity result=0, Success, actual_length=8

      00000000  07 33 f3 f3 00 00 02 00                          .3......
    CSW read_capcity result=0, Success, actual_length=13

      00000000  55 53 42 53 b0 39 38 ed 00 00 00 00 00           USBS.98......
    */
    //libusb_reset_device(handle);

    // SCSI_READ_CAPACITY=====================
    //cbw
    libusb_bulk_transfer(handle, epout, cbw_read_capacity, sizeof(cbw_read), &actual_len, BULK_TRANSFER_TIMEOUT);
    printf("CBW read_capcity result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
    //data in
    ret = libusb_bulk_transfer(handle, epin, data_buff, 8, &actual_len, BULK_TRANSFER_TIMEOUT);
    printf("DATA read_capcity result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
    display_buffer_hex(data_buff, 8);
    //csw
    ret = libusb_bulk_transfer(handle, epin, data_buff, 13, &actual_len, BULK_TRANSFER_TIMEOUT);
    printf("CSW read_capcity result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
    display_buffer_hex(data_buff, 13);

    free(data_buff);
    data_buff = NULL;
release_interface:
    libusb_release_interface(handle, 0);
close_libusb:
    libusb_close(handle);
}

int main(void)
{
    int ret = -1;
    ret = libusb_init(NULL);
	if (ret < 0) {
        printf("libusb_init failed, %d\n", ret);
        return ret;
    }

	test_device(0x0951, 0x1666, 0x81, 0x02);

    libusb_exit(NULL);
    return 0;
}
