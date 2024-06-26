// LibusbExample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "libusb.h"

static void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0, j = 0;
	uint8_t path[8];

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}

		printf("%04x:%04x (bus %d, device %d)",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++)
				printf(".%d", path[j]);
		}
		printf("\n");
	}
}

#include <SetupAPI.h>
#include <usbiodef.h>
#include <initguid.h>
#include <hidsdi.h>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "hid.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	libusb_device **devs;
	int r;
	ssize_t cnt;

	r = libusb_init(NULL);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

	print_devs(devs);
	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);

	// 获取 HID 类型设备信息集句柄
	GUID HidGuid;
	HidD_GetHidGuid(&HidGuid);
	HDEVINFO hDevInfo = SetupDiGetClassDevs(
		&HidGuid,					// 只查找 HID 类型设备(查找所有则设置为NULL，并修改 Flag 参数)
		NULL,						// 枚举指定类型的设备
		NULL,						// 设备关联的顶级窗口句柄
		DIGCF_DEVICEINTERFACE |		// 指定设备接口
		DIGCF_PRESENT				// 只返回当前系统中存在的设备
	);
	if (hDevInfo == INVALID_HANDLE_VALUE) {
		printf("无法获取HID设备信息集合句柄\n");
		return 1;
	}

	// 枚举HID设备接口
	DWORD index = 0;
	SP_DEVICE_INTERFACE_DATA interfaceData = { 0 };
	interfaceData.cbSize = sizeof(interfaceData);

	while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &HidGuid, index++, &interfaceData)) {
		// 获取HID设备接口详细信息
		DWORD requiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, NULL, 0, &requiredSize, NULL);

		PSP_DEVICE_INTERFACE_DETAIL_DATA pDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
		pDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, pDetailData, requiredSize, NULL, NULL)) {
			printf("无法获取HID设备接口详细信息\n");
			free(pDetailData);
			continue;
		}

		printf("pDetailData->DevicePath %ws\n", pDetailData->DevicePath);

		// 打开HID设备句柄
		HANDLE hDevice = CreateFile(
			pDetailData->DevicePath,				// 设备名称
			GENERIC_READ | GENERIC_WRITE,			// 访问权限
			FILE_SHARE_READ | FILE_SHARE_WRITE,		// 分享权限
			NULL,									// 返回的句柄不能被继承
			OPEN_EXISTING,							// 仅当设备存在时打开
			FILE_ATTRIBUTE_NORMAL,					// 不设置其他属性
			NULL									// 不设置扩展属性
		);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			//ERROR_INSUFFICIENT_BUFFER
			printf("无法打开HID设备句柄，错误码：%d\n", error);
			free(pDetailData);
			continue;
		}

		// 获取HID设备字符串描述符
		WCHAR manufacturerString[1024] = { 0 };
		WCHAR productString[1024] = { 0 };
		WCHAR serialString[1024] = { 0 };

		BOOL result = HidD_GetIndexedString(hDevice, 1, manufacturerString, 1024);
		result = HidD_GetProductString(hDevice, productString, 1024);
		result = HidD_GetManufacturerString(hDevice, serialString, 1024);	// 未找到有产品序列号设备
		if (!result) {
			printf("无法获取HID设备字符串描述符, %d\n", GetLastError());
			CloseHandle(hDevice);
			free(pDetailData);
			continue;
		}
		printf("HID设备厂商字符串描述符(%d)：%ws\n", wcslen(manufacturerString), manufacturerString);
		printf("HID设备产品字符串描述符(%d)：%ws\n", wcslen(productString), productString);
		printf("HID设备序列字符串描述符(%d)：%ws\n", wcslen(serialString), serialString);

		// 获取设备接口的 PID、VID
		HIDD_ATTRIBUTES hidAttributes = { 0 };
		hidAttributes.Size = sizeof(hidAttributes);
		if (!HidD_GetAttributes(
			hDevice,			// 设备句柄
			&hidAttributes		// [OUT] HIDD_ATTRIBUTES 结构体指针
		)) 
		{
			printf("HidD_GetAttributes failed : %d\n", GetLastError());
			CloseHandle(hDevice);
			free(pDetailData);
			continue;
		}
		printf("Vendor ID	: 0x%04X\n", hidAttributes.VendorID);
		printf("Product ID	: 0x%04X\n", hidAttributes.ProductID);
		printf("Version Number	: 0x%04X\n", hidAttributes.VersionNumber);

		// 关闭HID设备句柄
		CloseHandle(hDevice);

		free(pDetailData);
	}

	// 销毁HID设备信息集合句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

