/*******************************************************************************
* 文 件 名: DeviceIoControlSuccess.c
* 文件描述: 尝试了不同的设备
* 备    注: DeviceIoControl函数是可以使用的
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
		

		// 打开USB设备句柄（hub、U盘、摄像头、hid）
		//HANDLE hDevice = CreateFile("\\\\?\\USB#ROOT_HUB30#4&15bfe49e&0&0#{f18a0e88-c30c-11d0-8815-00a0c906bed8}",
		//HANDLE hDevice = CreateFile("\\\\?\\USB#VID_465A&PID_1053#5&2c75506a&0&13#{a5dcbf10-6530-11d2-901f-00c04fb951ed}",
		HANDLE hDevice = CreateFile("\\\\?\\USB#VID_0C45&PID_636D#SN0001#{a5dcbf10-6530-11d2-901f-00c04fb951ed}",
			0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			ERROR("无法打开USB设备句柄，错误码：%d\n", error);
			free(pDetailData);
			continue;
		}

		// 获取连接信息
		USB_NODE_CONNECTION_INFORMATION_EX connectionInfo;
		connectionInfo.ConnectionIndex = 13; // 设备连接的端口索引号
		DWORD bytesReturned = 0;

		PUSB_NODE_INFORMATION hubInfo = NULL;
		hubInfo = (PUSB_NODE_INFORMATION)malloc(sizeof(USB_NODE_INFORMATION));
		ULONG nBytes = 0;
		BOOL result = DeviceIoControl(hDevice,
									  IOCTL_USB_GET_NODE_INFORMATION,
									  hubInfo,
									  sizeof(USB_NODE_INFORMATION),
									  hubInfo,
									  sizeof(USB_NODE_INFORMATION),
									  &nBytes,
									  NULL); 
		if (!result) {
			DWORD dwError = GetLastError();
			// ERROR_INSUFFICIENT_BUFFER
			ERROR("hHubDevice DeviceIoControl failed, dwError %lu", dwError);
			dwError = ERROR_INSUFFICIENT_BUFFER;
			printf("无法获取USB连接信息\n");
			CloseHandle(hDevice);
			return 1;
		}
		else {
			INFO("NodeType: %lu", hubInfo->NodeType);
		}

		DWORD bytes_returned = 0;
		STORAGE_DEVICE_NUMBER device_num;
		result = DeviceIoControl(hDevice, IOCTL_STORAGE_GET_DEVICE_NUMBER,
			NULL, 0,
			&device_num, sizeof(device_num),
			&bytes_returned, (LPOVERLAPPED)NULL);
		if (!result) {
			printf("无法获取USB连接信息\n");
			CloseHandle(hDevice);
			return 1;
		}
		else {
			INFO("%lu %lu %lu", device_num.DeviceNumber, device_num.DeviceType, device_num.PartitionNumber);
		}

		// 获取设备描述符
		ULONG nBytesEx = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) +
			(sizeof(USB_PIPE_INFO) * 30);
		PUSB_NODE_CONNECTION_INFORMATION_EX connectionInfoEx = (PUSB_NODE_CONNECTION_INFORMATION_EX)malloc(nBytesEx);
		connectionInfoEx->ConnectionIndex = index;

		result = DeviceIoControl(hDevice,
			IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
			connectionInfoEx,
			nBytesEx,
			connectionInfoEx,
			nBytesEx,
			&nBytesEx,
			NULL);
		if (!result) {
			printf("无法获取USB连接信息\n");
			CloseHandle(hDevice);
			return 1;
		}
		else {
			INFO("speed %d", connectionInfoEx->Speed);
			ERROR("vid:pid %04x:%04x", connectionInfoEx->DeviceDescriptor.idVendor,
				connectionInfoEx->DeviceDescriptor.idProduct);
		}

		// 关闭USB设备句柄
		CloseHandle(hDevice);


		free(pDetailData);
	}

	// 销毁设备信息集合句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}