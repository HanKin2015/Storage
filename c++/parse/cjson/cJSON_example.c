/*******************************************************************************
* 文 件 名: cJSON_example.c
* 文件描述: 系统学习cJSON库
* 备    注: gcc在编译时添加 -lm 参数来链接数学库
            gcc cJSON_example.c cJSON.c -lm
* 作    者: HanKin
* 创建日期: 2023.11.01
* 修改日期：2023.11.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

/*
输出会有个列表包含
[{
                "id":   "c1",
                "option":       "hejian",
                "fid":  "1"
        }, {
                "id":   "p1",
                "option":       "handsome",
                "fid":  "2"
        }]
*/
int example1()
{
    FILE *fp = fopen("cJSON_example.json", "w");
    cJSON *root=cJSON_CreateArray();
    cJSON *fld;

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());

    cJSON_AddStringToObject(fld, "id", "c1");
    cJSON_AddStringToObject(fld, "option", "hejian");
    cJSON_AddStringToObject(fld, "fid", "1");

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());
    cJSON_AddStringToObject(fld, "id", "p1");
    cJSON_AddStringToObject(fld, "option", "handsome");
    cJSON_AddStringToObject(fld, "fid", "2");  

    char *out = cJSON_Print(root);
    fprintf(fp, "%s", out);   
    fclose(fp);

    cJSON_Delete(root);
    free(out);

    out = NULL;
    root = NULL;
    return 0;
}

int example2()
{
    // 1、创建json对象根节点
    cJSON *RootObj = cJSON_CreateObject();
    if (!RootObj) {
      printf("cJSON_CreateObject failed!\n");
      return -1;
    }
    
    // 2、创建json对象列表
    cJSON *DeviceListObj = cJSON_CreateArray();
    
    // 3、临时json对象
    cJSON *TempObj = cJSON_CreateObject();
    
    // 4、添加内容
    cJSON_AddNumberToObject(TempObj, "bLength", 18);
    cJSON_AddNumberToObject(TempObj, "bcdUSB", 528);
    cJSON_AddStringToObject(TempObj, "product", "DataTraveler 3.0");
    
    // 5、组合
    cJSON_AddItemToArray(DeviceListObj, TempObj);
    cJSON_AddItemToObject(RootObj, "device_list", DeviceListObj);
    
    // 6、保存到文件
    FILE *fp = fopen("cJSON_example.json", "w");
    fprintf(fp, "%s", cJSON_Print(RootObj));   
    fclose(fp);
    fp = NULL;

    cJSON_Delete(RootObj);
    RootObj = NULL;
    return 0;
}

// 老方式，但是实际情况是通过遍历所有的hub来获取usb设备的，不是在一个地方拿完所有的描述符信息
int example3()
{
    // 创建根节点
    cJSON *RootObj = cJSON_CreateObject();
    if (!RootObj) {
      printf("cJSON_CreateObject failed!\n");
      return -1;
    }
    
    // 创建设备列表
    cJSON *DeviceListObj = cJSON_CreateArray();
    
    for (int i = 0; i < 2; i++) {
        // 创建设备描述符对象
        cJSON *DevDescObj = cJSON_CreateObject();
        cJSON_AddNumberToObject(DevDescObj, "bLength", 18);
        cJSON_AddNumberToObject(DevDescObj, "bDescriptorType", 1);
        cJSON_AddNumberToObject(DevDescObj, "bNumConfigurations", 1);
        cJSON_AddStringToObject(DevDescObj, "product", "DataTraveler 3.0");
        cJSON_AddItemToArray(DeviceListObj, DevDescObj);
        
        // 创建配置描述符列表
        cJSON *ConfDescListObj = cJSON_CreateArray();
        cJSON *TempObj = cJSON_GetObjectItem(DevDescObj, "bNumConfigurations");
        if (TempObj->type == cJSON_NULL) {
            printf("TempObj type is cJSON_NULL\n");
            return -1;
        }
        int ConfDescCnt = TempObj->valueint;
        for (int j = 0; j < ConfDescCnt; j++) {
            // 创建配置描述符对象
            cJSON *ConfDescObj = cJSON_CreateObject();
            cJSON_AddNumberToObject(ConfDescObj, "bLength", 9);
            cJSON_AddNumberToObject(ConfDescObj, "bDescriptorType", 2);
            cJSON_AddNumberToObject(ConfDescObj, "bNumInterfaces", 1);
            cJSON_AddItemToArray(ConfDescListObj, ConfDescObj);
            
            // 创建接口描述符列表
            cJSON *InfDescListObj = cJSON_CreateArray();
            TempObj = cJSON_GetObjectItem(ConfDescObj, "bNumInterfaces");
            int InfDescCnt = TempObj->valueint;
            for (int k = 0; k < InfDescCnt; k++) {
                // 创建配置描述符对象
                cJSON *InfDescObj = cJSON_CreateObject();
                cJSON_AddNumberToObject(InfDescObj, "bLength", 9);
                cJSON_AddNumberToObject(InfDescObj, "bDescriptorType", 4);
                cJSON_AddNumberToObject(InfDescObj, "bNumEndpoints", 2);
                cJSON_AddItemToArray(InfDescListObj, InfDescObj);
                
                // 创建端点描述符列表
                cJSON *EpDescListObj = cJSON_CreateArray();
                TempObj = cJSON_GetObjectItem(InfDescObj, "bNumEndpoints");
                int EpDescCnt = TempObj->valueint;
                for (int l = 0; l < EpDescCnt; l++) {
                    // 创建端点描述符对象
                    cJSON *EpDescObj = cJSON_CreateObject();
                    cJSON_AddNumberToObject(EpDescObj, "bLength", 7);
                    cJSON_AddNumberToObject(EpDescObj, "bDescriptorType", 5);
                    cJSON_AddNumberToObject(EpDescObj, "bEndpointAddress", 129);
                    cJSON_AddItemToArray(EpDescListObj, EpDescObj);
                }
                cJSON_AddItemToArray(InfDescListObj, EpDescListObj);
            }
            cJSON_AddItemToArray(ConfDescListObj, InfDescListObj);
        }
        cJSON_AddItemToArray(DeviceListObj, ConfDescListObj);
    }
    cJSON_AddItemToObject(RootObj, "device_list", DeviceListObj);
    
    // 6、保存到文件
    FILE *Fp = fopen("cJSON_example.json", "w");
    char *DeviceInfo = cJSON_Print(RootObj);    // 直接写在fprintf函数里面会有内存泄漏
    fprintf(Fp, "%s", DeviceInfo);
    
    fclose(Fp);
    Fp = NULL;
    cJSON_Delete(RootObj);
    RootObj = NULL;
    free(DeviceInfo);
    DeviceInfo = NULL;
    return 0;
}

// 描述符类型
enum descriptor_type
{
	USB_DEVICE_DESCRIPTOR_TYPE,
	USB_CONFIGURATION_DESCRIPTOR_TYPE,
	USB_INTERFACE_DESCRIPTOR_TYPE,
	USB_ENDPOINT_DESCRIPTOR_TYPE
};

#define INFO(fmt, ...) printf("[INFO][device_helper](%s|%d)" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

//
// USB 1.1: 9.6.1 Device, Table 9-7. Standard Device Descriptor
// USB 2.0: 9.6.1 Device, Table 9-8. Standard Device Descriptor
// USB 3.0: 9.6.1 Device, Table 9-8. Standard Device Descriptor
//
typedef struct _USB_DEVICE_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    USHORT  bcdUSB;
    UCHAR   bDeviceClass;
    UCHAR   bDeviceSubClass;
    UCHAR   bDeviceProtocol;
    UCHAR   bMaxPacketSize0;
    USHORT  idVendor;
    USHORT  idProduct;
    USHORT  bcdDevice;
    UCHAR   iManufacturer;
    UCHAR   iProduct;
    UCHAR   iSerialNumber;
    UCHAR   bNumConfigurations;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;
//
// USB 1.1: 9.6.2 Configuration, Table 9-8. Standard Configuration Descriptor
// USB 2.0: 9.6.3 Configuration, Table 9-10. Standard Configuration Descriptor
// USB 3.0: 9.6.3 Configuration, Table 9-15. Standard Configuration Descriptor
//
typedef struct _USB_CONFIGURATION_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    USHORT  wTotalLength;
    UCHAR   bNumInterfaces;
    UCHAR   bConfigurationValue;
    UCHAR   iConfiguration;
    UCHAR   bmAttributes;
    UCHAR   MaxPower;
} USB_CONFIGURATION_DESCRIPTOR, *PUSB_CONFIGURATION_DESCRIPTOR;
//
// USB 1.1: 9.6.3 Interface, Table 9-9. Standard Interface Descriptor
// USB 2.0: 9.6.5 Interface, Table 9-12. Standard Interface Descriptor
// USB 3.0: 9.6.5 Interface, Table 9-17. Standard Interface Descriptor
//
typedef struct _USB_INTERFACE_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bInterfaceNumber;
    UCHAR   bAlternateSetting;
    UCHAR   bNumEndpoints;
    UCHAR   bInterfaceClass;
    UCHAR   bInterfaceSubClass;
    UCHAR   bInterfaceProtocol;
    UCHAR   iInterface;
} USB_INTERFACE_DESCRIPTOR, *PUSB_INTERFACE_DESCRIPTOR;
//
// USB 1.1: 9.6.4 Endpoint, Table 9-10. Standard Endpoint Descriptor
// USB 2.0: 9.6.6 Endpoint, Table 9-13. Standard Endpoint Descriptor
// USB 3.0: 9.6.6 Endpoint, Table 9-18. Standard Endpoint Descriptor
//
typedef struct _USB_ENDPOINT_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bEndpointAddress;
    UCHAR   bmAttributes;
    USHORT  wMaxPacketSize;
    UCHAR   bInterval;
} USB_ENDPOINT_DESCRIPTOR, *PUSB_ENDPOINT_DESCRIPTOR;

cJSON *gDeviceListObj   = NULL; // 设备列表
cJSON *gConfDescListObj = NULL; // 配置描述符列表
cJSON *gInfDescListObj  = NULL; // 接口描述符列表
cJSON *gEpDescListObj   = NULL; // 端点描述符列表
int example4(void *Descriptor, int DescriptorType)
{
    PUSB_DEVICE_DESCRIPTOR        deviceDesc        = NULL;
    PUSB_CONFIGURATION_DESCRIPTOR configurationDesc = NULL;
    PUSB_INTERFACE_DESCRIPTOR     interfaceDesc     = NULL;
    PUSB_ENDPOINT_DESCRIPTOR      endpointDesc      = NULL;
    
    // 创建描述符json对象
    cJSON *DescObj = cJSON_CreateObject();
    switch(DescriptorType)
    {
    case USB_DEVICE_DESCRIPTOR_TYPE:
        deviceDesc = (PUSB_DEVICE_DESCRIPTOR)Descriptor;
        INFO("---------------------- Device Descriptor ----------------------");
        INFO("bLength			    : 0x%02x", deviceDesc->bLength);
        INFO("bDescriptorType	    : 0x%02x", deviceDesc->bDescriptorType);
        INFO("bcdUSB	     	    : 0x%x", deviceDesc->bcdUSB);
        INFO("idVendor			    : 0x%04x", deviceDesc->idVendor);
        INFO("idProduct			    : 0x%04x", deviceDesc->idProduct);
        INFO("");
        
        cJSON_AddNumberToObject(DescObj, "bLength", deviceDesc->bLength);
        cJSON_AddNumberToObject(DescObj, "bDescriptorType", deviceDesc->bDescriptorType);
        cJSON_AddNumberToObject(DescObj, "bcdUSB", deviceDesc->bcdUSB);
        cJSON_AddNumberToObject(DescObj, "bDeviceClass", deviceDesc->bDeviceClass);
        cJSON_AddNumberToObject(DescObj, "bDeviceSubClass", deviceDesc->bDeviceSubClass);
        cJSON_AddNumberToObject(DescObj, "bDeviceProtocol", deviceDesc->bDeviceProtocol);
        cJSON_AddNumberToObject(DescObj, "bMaxPacketSize0", deviceDesc->bMaxPacketSize0);
        cJSON_AddNumberToObject(DescObj, "idVendor", deviceDesc->idVendor);
        cJSON_AddNumberToObject(DescObj, "idProduct", deviceDesc->idProduct);
        cJSON_AddNumberToObject(DescObj, "bcdDevice", deviceDesc->bcdDevice);
        cJSON_AddNumberToObject(DescObj, "iManufacturer", deviceDesc->iManufacturer);
        cJSON_AddNumberToObject(DescObj, "iProduct", deviceDesc->iProduct);
        cJSON_AddNumberToObject(DescObj, "iSerialNumber", deviceDesc->iSerialNumber);
        cJSON_AddNumberToObject(DescObj, "bNumConfigurations", deviceDesc->bNumConfigurations);
        cJSON_AddStringToObject(DescObj, "product", "DataTraveler 3.0");
        cJSON_AddItemToArray(gDeviceListObj, DescObj);
        break;
    case USB_CONFIGURATION_DESCRIPTOR_TYPE:
        configurationDesc = (PUSB_CONFIGURATION_DESCRIPTOR)Descriptor;
        INFO("-------------------- Configuration Descriptor --------------------");
        INFO("bLength			    : 0x%02x", configurationDesc->bLength);
        INFO("bDescriptorType		: 0x%02x", configurationDesc->bDescriptorType);
        INFO("bTotalLength			: 0x%04x", configurationDesc->wTotalLength);
        INFO("bNumInterfaces		: 0x%02x", configurationDesc->bNumInterfaces);
        INFO("bConfigurationValue	: 0x%02x", configurationDesc->bConfigurationValue);
        INFO("");
        
        cJSON_AddNumberToObject(DescObj, "bLength", configurationDesc->bLength);
        cJSON_AddNumberToObject(DescObj, "bDescriptorType", configurationDesc->bDescriptorType);
        cJSON_AddNumberToObject(DescObj, "wTotalLength", configurationDesc->wTotalLength);
        cJSON_AddNumberToObject(DescObj, "bNumInterfaces", configurationDesc->bNumInterfaces);
        cJSON_AddNumberToObject(DescObj, "bConfigurationValue", configurationDesc->bConfigurationValue);
        cJSON_AddNumberToObject(DescObj, "iConfiguration", configurationDesc->iConfiguration);
        cJSON_AddNumberToObject(DescObj, "bmAttributes", configurationDesc->bmAttributes);
        cJSON_AddNumberToObject(DescObj, "MaxPower", configurationDesc->MaxPower);
        cJSON_AddItemToArray(gConfDescListObj, DescObj);
        break;
    case USB_INTERFACE_DESCRIPTOR_TYPE:
        interfaceDesc = (PUSB_INTERFACE_DESCRIPTOR)Descriptor;
        INFO("----------------- Interface Descriptor -----------------");
        INFO("bLength			    : 0x%02x", interfaceDesc->bLength);
        INFO("bDescriptorType		: 0x%02x", interfaceDesc->bDescriptorType);
        INFO("bInterfaceNumber	    : 0x%02x", interfaceDesc->bInterfaceNumber);
        INFO("bAlternateSetting		: 0x%02x", interfaceDesc->bAlternateSetting);
        INFO("bNumEndpoints			: 0x%02x", interfaceDesc->bNumEndpoints);
        INFO("bInterfaceClass		: 0x%02x", interfaceDesc->bInterfaceClass);
        INFO("");
        
        cJSON_AddNumberToObject(DescObj, "bLength", interfaceDesc->bLength);
        cJSON_AddNumberToObject(DescObj, "bDescriptorType", interfaceDesc->bDescriptorType);
        cJSON_AddNumberToObject(DescObj, "bInterfaceNumber", interfaceDesc->bInterfaceNumber);
        cJSON_AddNumberToObject(DescObj, "bAlternateSetting", interfaceDesc->bAlternateSetting);
        cJSON_AddNumberToObject(DescObj, "bNumEndpoints", interfaceDesc->bNumEndpoints);
        cJSON_AddNumberToObject(DescObj, "bInterfaceClass", interfaceDesc->bInterfaceClass);
        cJSON_AddNumberToObject(DescObj, "bInterfaceSubClass", interfaceDesc->bInterfaceSubClass);
        cJSON_AddNumberToObject(DescObj, "bInterfaceProtocol", interfaceDesc->bInterfaceProtocol);
        cJSON_AddNumberToObject(DescObj, "iInterface", interfaceDesc->iInterface);
        cJSON_AddItemToArray(gInfDescListObj, DescObj);
        break;
    case USB_ENDPOINT_DESCRIPTOR_TYPE:
        endpointDesc = (PUSB_ENDPOINT_DESCRIPTOR)Descriptor;
        INFO("----------------- Endpoint Descriptor -----------------");
        INFO("bLength			    : 0x%02x", endpointDesc->bLength);
        INFO("bDescriptorType	    : 0x%02x", endpointDesc->bDescriptorType);
        INFO("bEndpointAddress      : 0x%02x", endpointDesc->bEndpointAddress);
        INFO("bmAttributes		    : 0x%02x", endpointDesc->bmAttributes);
        INFO("wMaxPacketSize	    : 0x%04x", endpointDesc->wMaxPacketSize);
        INFO("bInterval			    : 0x%02x", endpointDesc->bInterval);
        INFO("");
        
        cJSON_AddNumberToObject(DescObj, "bLength", endpointDesc->bLength);
        cJSON_AddNumberToObject(DescObj, "bDescriptorType", endpointDesc->bDescriptorType);
        cJSON_AddNumberToObject(DescObj, "bEndpointAddress", endpointDesc->bEndpointAddress);
        cJSON_AddNumberToObject(DescObj, "bmAttributes", endpointDesc->bmAttributes);
        cJSON_AddNumberToObject(DescObj, "wMaxPacketSize", endpointDesc->wMaxPacketSize);
        cJSON_AddNumberToObject(DescObj, "bInterval", endpointDesc->bInterval);
        //cJSON_AddNumberToObject(DescObj, "bRefresh", endpointDesc->bRefresh);
        //cJSON_AddNumberToObject(DescObj, "bSynchAddress", endpointDesc->bSynchAddress);
        cJSON_AddItemToArray(gEpDescListObj, DescObj);
        break;
    default:
        break;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    gDeviceListObj   = cJSON_CreateArray();
    gConfDescListObj = cJSON_CreateArray();
    gInfDescListObj  = cJSON_CreateArray();
    gEpDescListObj   = cJSON_CreateArray();
    
    char deviceDesc[] = {0x12, 0x01, 0x20, 0x03, 0x00, 0x00, 0x00, 0x09, 0x51, 0x09, 0x66, 0x16, 0x01, 0x00, 0x01, 0x02, 0x03, 0x01};
    char confDesc[] = {0x09, 0x02, 0x2c, 0x00, 0x01, 0x01, 0x00, 0x80, 0x25};
    char interfaceDesc[] = {0x09, 0x04, 0x00, 0x00, 0x02, 0x08, 0x06, 0x50, 0x00};
    char endpointDesc1[] = {0x07, 0x05, 0x81, 0x02, 0x00, 0x04, 0x00};
    char endpointDesc2[] = {0x07, 0x05, 0x02, 0x02, 0x00, 0x04, 0x00};
    
    // 第一个设备
    example4(deviceDesc, USB_DEVICE_DESCRIPTOR_TYPE);
    example4(confDesc, USB_CONFIGURATION_DESCRIPTOR_TYPE);
    example4(interfaceDesc, USB_INTERFACE_DESCRIPTOR_TYPE);
    example4(endpointDesc1, USB_ENDPOINT_DESCRIPTOR_TYPE);
    example4(endpointDesc2, USB_ENDPOINT_DESCRIPTOR_TYPE);
    cJSON_AddItemToArray(gInfDescListObj, gEpDescListObj);
    cJSON_AddItemToArray(gConfDescListObj, gInfDescListObj);
    cJSON_AddItemToArray(gDeviceListObj, gConfDescListObj);
    
    // 第二个设备
    //cJSON_Delete(gConfDescListObj);   // 不能做释放删除操作，否则会破坏原先的数值，经过检测无内存泄露
    gConfDescListObj = cJSON_CreateArray();
    gInfDescListObj  = cJSON_CreateArray();
    gEpDescListObj   = cJSON_CreateArray();
    example4(deviceDesc, USB_DEVICE_DESCRIPTOR_TYPE);
    example4(confDesc, USB_CONFIGURATION_DESCRIPTOR_TYPE);
    example4(interfaceDesc, USB_INTERFACE_DESCRIPTOR_TYPE);
    example4(endpointDesc1, USB_ENDPOINT_DESCRIPTOR_TYPE);
    example4(endpointDesc2, USB_ENDPOINT_DESCRIPTOR_TYPE);
    cJSON_AddItemToArray(gInfDescListObj, gEpDescListObj);
    cJSON_AddItemToArray(gConfDescListObj, gInfDescListObj);
    cJSON_AddItemToArray(gDeviceListObj, gConfDescListObj);
    
    cJSON *RootObj = cJSON_CreateObject();
    cJSON_AddItemToObject(RootObj, "device_list", gDeviceListObj);
    
    // 保存到文件
    FILE *Fp = fopen("cJSON_example.json", "w");
    char *DeviceInfo = cJSON_Print(RootObj);    // 直接写在fprintf函数里面会有内存泄漏
    fprintf(Fp, "%s", DeviceInfo);
    
    fclose(Fp);
    Fp = NULL;
    cJSON_Delete(RootObj);
    RootObj = NULL;
    free(DeviceInfo);
    DeviceInfo = NULL;
    return 0;
}
