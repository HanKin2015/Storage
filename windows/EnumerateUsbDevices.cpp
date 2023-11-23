// EnumerateUsbDevices.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <usbiodef.h>
#include <initguid.h>
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "winusb.lib")
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, \
	0xC0, 0x4F, 0xB9, 0x51, 0xED);

int main()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	// 获取所有USB设备的设备信息
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("SetupDiGetClassDevs failed (%d)\n", GetLastError());
		return 1;
	}

	// 枚举所有USB设备
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD DataT;
		char buf[1024];
		DWORD bufSize = sizeof(buf);

		// 获取设备描述
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("设备描述: %s\n", buf);
		}

		// 获取类 Guid
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("类 Guid: %s\n", buf);
		}
	}

	// 释放设备信息句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);
    return 0;
}

