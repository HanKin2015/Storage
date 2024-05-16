/*******************************************************************************
* 文 件 名: test_demo.c
* 文件描述: 根据本地文件内容动态调整，即打桩
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.15
* 修改日期：2024.05.15
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
FILE *vfp = fopen("/data/local/vpid", "r");
if (vfp) {
    int vid = 0, pid = 0;
    if (fscanf(vfp, "%x:%x\n", &vid, &pid) == 2) {
        if (dev->device_info.vendor_id == vid && dev->device_info.product_id == pid) {
            FILE *fp = fopen("/data/local/custom", "r");
            if (fp) {
                int ep= 0;
                while (fscanf(fp, "%x\n", &ep) == 1) {
                    INFO("set %04x:%0x4 ep %02x pipeline to false.\n", vid, pid, ep);
                    I2USBEP(dev, EP2I(ep))->pipeline = false;
                }
                fclose(fp);
                fp = NULL;
            } else {
                INFO("file /data/local/custom not exist, set %04x:%0x4 ep 0x82 0x85 0x01 pipeline to false.\n", vid, pid);
                I2USBEP(dev, EP2I(0x82))->pipeline = false;
                I2USBEP(dev, EP2I(0x85))->pipeline = false;
                I2USBEP(dev, EP2I(0x01))->pipeline = false;
            }
        }
    }
    fclose(vfp);
    vfp = NULL;
} else {
    INFO("file /data/local/vpid not exist\n");
}