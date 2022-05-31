#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "libusb.h"


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

static uint8_t cbw_read[] = {
    0x55, 0x53, 0x42, 0x43,
    0x10, 0x30, 0x6e, 0x96,
    0x00, 0x00, 0x08, 0x00,
    0x80, 0x00, 0x0a, 0x28,
    0x00, 0x01, 0x93, 0x7b,
    0x00, 0x00, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

static uint8_t cbw_read_capacity[] = {
    0x55, 0x53, 0x42, 0x43,
    0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x08, 0x00,
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
    printf("DATA read_capcity result=%d, %s, actual_length=%d\n", ret, libusb_strerror(ret), actual_len);
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

    //test_device(0x325d, 0x6410, 0x81, 0x02);
	test_device(0x090c, 0x1000, 0x82, 0x01);

    libusb_exit(NULL);
    return 0;
}
