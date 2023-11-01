/*******************************************************************************
* 文 件 名: DeviceIoControlFailed.c
* 文件描述: 使用DeviceIoControl函数一直失败不只有我遇到这样的问题
* 作    者: HanKin
* 创建日期: 2023.10.31
* 修改日期：2023.10.31
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

int __cdecl main()
{
	gHubList.DeviceInfo = INVALID_HANDLE_VALUE;
	InitializeListHead(&gHubList.ListHead);
	gDeviceList.DeviceInfo = INVALID_HANDLE_VALUE;
	InitializeListHead(&gDeviceList.ListHead);

	// Enumerate all USB buses and populate the tree
	//
	EnumerateHostControllers();

	// 获取设备信息集合句柄
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE) {
		printf("无法获取设备信息集合句柄\n");
		return 1;
	}

	// 枚举设备信息集合中的设备
	DWORD index = 0;
	SP_DEVINFO_DATA devInfoData;
	devInfoData.cbSize = sizeof(devInfoData);

	while (SetupDiEnumDeviceInfo(hDevInfo, index++, &devInfoData)) {
		// 获取设备描述符
		DWORD dataType = 0;
		BYTE buffer[1024];
		DWORD bufferSize = sizeof(buffer);

		BOOL result = SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_DEVICEDESC, &dataType, buffer, bufferSize, &bufferSize);
		if (!result) {
			printf("无法获取设备描述符\n");
			continue;
		}

		// 输出设备描述符
		printf("设备描述符：%s\n", buffer);
	}

	// 枚举USB设备接口
	index = 0;
	SP_DEVICE_INTERFACE_DATA interfaceData;
	interfaceData.cbSize = sizeof(interfaceData);

	while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_USB_DEVICE, index++, &interfaceData)) {
		// 获取USB设备接口详细信息
		DWORD requiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, NULL, 0, &requiredSize, NULL);

		PSP_DEVICE_INTERFACE_DETAIL_DATA pDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
		pDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, pDetailData, requiredSize, NULL, NULL)) {
			printf("无法获取USB设备接口详细信息\n");
			free(pDetailData);
			continue;
		}

		printf("pDetailData->DevicePath %s\n", pDetailData->DevicePath);
		

		// 打开USB设备句柄
		HANDLE hDevice = CreateFile(pDetailData->DevicePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			printf("无法打开USB设备句柄，错误码：%d\n", error);
			free(pDetailData);
			continue;
		}

		// 获取连接信息
		USB_NODE_CONNECTION_INFORMATION_EX connectionInfo;
		connectionInfo.ConnectionIndex = 0; // 设备连接的端口索引号
		DWORD bytesReturned = 0;
		DWORD bytes_returned = 0;
		STORAGE_DEVICE_NUMBER device_num;

		BOOL result = DeviceIoControl(hDevice, IOCTL_STORAGE_GET_DEVICE_NUMBER,
			NULL, 0,
			&device_num, sizeof(device_num),
			&bytes_returned, (LPOVERLAPPED)NULL);
		if (!result) {
			printf("无法获取USB连接信息\n");
			CloseHandle(hDevice);
			return 1;
		}

		// 关闭USB设备句柄
		CloseHandle(hDevice);


		free(pDetailData);
	}

	// 销毁设备信息集合句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}