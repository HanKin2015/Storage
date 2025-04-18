#pragma once

typedef struct usbmagic_usb_channel_backend {
    void *priv;
    void (*writev)(void *priv);
} usbmagic_usb_channel_backend;

void test(usbmagic_usb_channel_backend backend)
{
    backend.writev(NULL);
}