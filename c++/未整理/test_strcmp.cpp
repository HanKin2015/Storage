#include <stdio.h>
#include <string.h>

int main()
{
    char devpath[] = "1-1";
    int usb_idx = -1;

    if (!strcmp(devpath, "1-1.1")) {
        usb_idx = 10;
    } else if (!strcmp(devpath, "1-1.2")) {
        usb_idx = 11;
    } else if (!strcmp(devpath, "1-1.3")) {
        usb_idx = 12;
    } else if (!strcmp(devpath, "1-1.4")) {
        usb_idx = 13;
    }
    printf("usb_idx = %d\n", usb_idx);
    return 0;
}
