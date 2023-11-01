/*******************************************************************************
* 文 件 名: read_write.cpp
* 文件描述: 探究读写文件速度效率
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <usbiodef.h>
#include <usbioctl.h>
#include <winioctl.h>
#include <hidsdi.h>

// 定义GUID_DEVINTERFACE_HID宏
DEFINE_GUID(GUID_DEVINTERFACE_HID, 0x4D1E55B2, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30);

int __cdecl main()
{
	// 获取HID设备信息集合句柄
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_HID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE) {
		printf("无法获取HID设备信息集合句柄\n");
		return 1;
	}

	// 枚举HID设备接口
	DWORD index = 0;
	SP_DEVICE_INTERFACE_DATA interfaceData;
	interfaceData.cbSize = sizeof(interfaceData);

	while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_HID, index++, &interfaceData)) {
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

		// 打开HID设备句柄
		HANDLE hDevice = CreateFile(pDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			printf("无法打开HID设备句柄，错误码：%d\n", error);
			free(pDetailData);
			continue;
		}

		// 获取HID设备属性
		HIDD_ATTRIBUTES attributes;
		attributes.Size = sizeof(HIDD_ATTRIBUTES);

		BOOL result = HidD_GetAttributes(hDevice, &attributes);
		if (!result) {
			printf("无法获取HID设备属性\n");
			CloseHandle(hDevice);
			free(pDetailData);
			continue;
		}

		// 输出HID设备属性
		printf("HID设备属性：\n");
		printf("Vendor ID: 0x%04X\n", attributes.VendorID);
		printf("Product ID: 0x%04X\n", attributes.ProductID);
		printf("Version Number: 0x%04X\n", attributes.VersionNumber);

		// 关闭HID设备句柄
		CloseHandle(hDevice);

		free(pDetailData);
	}

	// 销毁HID设备信息集合句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);
    return 0;
}