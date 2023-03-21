#include <stdio.h>
#include <libusb-1.0/libusb.h>

int main(int argc, char **argv) {
    libusb_device **devs;
    libusb_device_handle *dev_handle;
    struct libusb_device_descriptor desc;
    int r, i;

    // Initialize libusb
    r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "libusb_init error: %s\n", libusb_error_name(r));
        return 1;
    }

    // Get the list of USB devices
    r = libusb_get_device_list(NULL, &devs);
    if (r < 0) {
        fprintf(stderr, "libusb_get_device_list error: %s\n", libusb_error_name(r));
        libusb_exit(NULL);
        return 1;
    }

    // Open the first USB device
    dev_handle = libusb_open_device_with_vid_pid(NULL, 0x1234, 0x5678);
    if (dev_handle == NULL) {
        fprintf(stderr, "libusb_open_device_with_vid_pid error\n");
        libusb_free_device_list(devs, 1);
        libusb_exit(NULL);
        return 1;
    }

    // Get the device descriptor
    r = libusb_get_device_descriptor(libusb_get_device(dev_handle), &desc);
    if (r < 0) {
        fprintf(stderr, "libusb_get_device_descriptor error: %s\n", libusb_error_name(r));
        libusb_close(dev_handle);
        libusb_free_device_list(devs, 1);
        libusb_exit(NULL);
        return 1;
    }

    // Print the descriptor information
    printf("Vendor ID: 0x%04x\n", desc.idVendor);
    printf("Product ID: 0x%04x\n", desc.idProduct);
    printf("Device Class: 0x%02x\n", desc.bDeviceClass);
    printf("Device Subclass: 0x%02x\n", desc.bDeviceSubClass);
    printf("Device Protocol: 0x%02x\n", desc.bDeviceProtocol);

    // Close the USB device and free the device list
    libusb_close(dev_handle);
    libusb_free_device_list(devs, 1);

    // Exit libusb
    libusb_exit(NULL);

    return 0;
}

