/*******************************************************************************
* 文 件 名: GiveUp.c
* 文件描述: 最后的顽抗，还是放弃了，根本行不通
* 备    注: 发现可以通过驱动器号操作U盘
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

int test()
{
	HANDLE hDevice;
	TCHAR szDrive[] = _T("\\\\.\\G:"); // U盘的驱动器号
	DWORD dwRet;

	hDevice = CreateFile(szDrive, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Failed to open device, error: %d\n"), GetLastError());
		return 1;
	}

	STORAGE_DEVICE_NUMBER sdn;
	if (DeviceIoControl(hDevice, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, &sdn, sizeof(sdn), &dwRet, NULL))
	{
		_tprintf(_T("U盘序列号: %d\n"), sdn.DeviceNumber);
		INFO("%lu %lu %lu", sdn.DeviceNumber, sdn.DeviceType, sdn.PartitionNumber);
	}
	else
	{
		_tprintf(_T("Failed to get device number, error: %d\n"), GetLastError());
	}

	// 获取设备描述符
	ULONG nBytesEx = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) +
		(sizeof(USB_PIPE_INFO) * 30);
	PUSB_NODE_CONNECTION_INFORMATION_EX connectionInfoEx = (PUSB_NODE_CONNECTION_INFORMATION_EX)malloc(nBytesEx);
	//connectionInfoEx->ConnectionIndex = 0;

	BOOL result = DeviceIoControl(hDevice,
		IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
		connectionInfoEx,
		nBytesEx,
		connectionInfoEx,
		nBytesEx,
		&nBytesEx,
		NULL);
	if (!result) {
		DWORD dwError = GetLastError();
		ERROR("DeviceIoControl failed, dwError %lu", dwError);
		CloseHandle(hDevice);
		return 1;
	}
	else {
		INFO("speed %d", connectionInfoEx->Speed);
		ERROR("vid:pid %04x:%04x", connectionInfoEx->DeviceDescriptor.idVendor,
			connectionInfoEx->DeviceDescriptor.idProduct);
	}

	CloseHandle(hDevice);
	return 0;
}

int test2()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA devInfoData;
	DWORD i;

	// 初始化设备信息集合
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("Failed to get device information, error: %d\n", GetLastError());
		return 1;
	}

	// 遍历设备信息集合
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); i++)
	{
		DWORD dwSize;
		PSP_DEVICE_INTERFACE_DATA pInterfaceData;
		PSP_DEVICE_INTERFACE_DETAIL_DATA pDetailData;
		HANDLE hDevice;
		USB_CONFIGURATION_DESCRIPTOR configDesc;

		// 获取设备接口信息
		pInterfaceData = (PSP_DEVICE_INTERFACE_DATA)malloc(sizeof(SP_DEVICE_INTERFACE_DATA));
		pInterfaceData->cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		if (SetupDiEnumDeviceInterfaces(hDevInfo, &devInfoData, &GUID_DEVINTERFACE_USB_DEVICE, 0, pInterfaceData))
		{
			// 获取设备描述符
			DWORD dataType = 0;
			BYTE buffer[1024];
			DWORD bufferSize = sizeof(buffer);

			BOOL result = SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_DEVICEDESC, &dataType, buffer, bufferSize, &bufferSize);
			if (!result) {
				printf("无法获取设备描述符\n");
				continue;
			}
			printf("设备描述符：%s\n", buffer);

			// 获取设备接口详细信息
			SetupDiGetDeviceInterfaceDetail(hDevInfo, pInterfaceData, NULL, 0, &dwSize, NULL);
			pDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwSize);
			pDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			if (SetupDiGetDeviceInterfaceDetail(hDevInfo, pInterfaceData, pDetailData, dwSize, NULL, NULL))
			{
				INFO("DevicePath: %s", pDetailData->DevicePath);
				// 打开设备句柄
				hDevice = CreateFile(pDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
				if (hDevice != INVALID_HANDLE_VALUE)
				{
					// 获取配置描述符
					if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), &configDesc, sizeof(configDesc), &dwSize, NULL))
					{
						printf("Configuration Descriptor:\n");
						printf("bLength: %d\n", configDesc.bLength);
						printf("bDescriptorType: %d\n", configDesc.bDescriptorType);
						printf("wTotalLength: %d\n", configDesc.wTotalLength);
						printf("bNumInterfaces: %d\n", configDesc.bNumInterfaces);
						printf("bConfigurationValue: %d\n", configDesc.bConfigurationValue);
						printf("iConfiguration: %d\n", configDesc.iConfiguration);
						printf("bmAttributes: %d\n", configDesc.bmAttributes);
						printf("MaxPower: %d\n", configDesc.MaxPower);
						printf("\n");
					}

					//CloseHandle(hDevice);
				}

				// 获取设备描述符
				ULONG nBytesEx = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) +
					(sizeof(USB_PIPE_INFO) * 30);
				PUSB_NODE_CONNECTION_INFORMATION_EX connectionInfoEx = (PUSB_NODE_CONNECTION_INFORMATION_EX)malloc(nBytesEx);
				//connectionInfoEx->ConnectionIndex = 0;

				BOOL result = DeviceIoControl(hDevice,
					IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
					connectionInfoEx,
					nBytesEx,
					connectionInfoEx,
					nBytesEx,
					&nBytesEx,
					NULL);
				if (!result) {
					DWORD dwError = GetLastError();
					ERROR("DeviceIoControl failed, dwError %lu", dwError);
					CloseHandle(hDevice);
					continue;
				}
				else {
					INFO("speed %d", connectionInfoEx->Speed);
					ERROR("vid:pid %04x:%04x", connectionInfoEx->DeviceDescriptor.idVendor,
						connectionInfoEx->DeviceDescriptor.idProduct);
				}
			}

			free(pDetailData);
		}

		free(pInterfaceData);
	}

	// 清理资源
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

int test3()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA devInfoData;
	DWORD i;

	// 初始化设备信息集合
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("Failed to get device information, error: %d\n", GetLastError());
		return 1;
	}

	// 遍历设备信息集合
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); i++)
	{
		DWORD dwSize;
		PSP_DEVICE_INTERFACE_DATA pInterfaceData;
		PSP_DEVICE_INTERFACE_DETAIL_DATA pDetailData;
		HANDLE hDevice;
		USB_DEVICE_DESCRIPTOR deviceDesc;
		USB_CONFIGURATION_DESCRIPTOR configDesc;
		USB_STRING_DESCRIPTOR stringDesc;
		UCHAR buffer[1024];

		// 获取设备接口信息
		pInterfaceData = (PSP_DEVICE_INTERFACE_DATA)malloc(sizeof(SP_DEVICE_INTERFACE_DATA));
		pInterfaceData->cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		if (SetupDiEnumDeviceInterfaces(hDevInfo, &devInfoData, &GUID_DEVINTERFACE_USB_DEVICE, 0, pInterfaceData))
		{
			// 获取设备接口详细信息
			SetupDiGetDeviceInterfaceDetail(hDevInfo, pInterfaceData, NULL, 0, &dwSize, NULL);
			pDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwSize);
			pDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			if (SetupDiGetDeviceInterfaceDetail(hDevInfo, pInterfaceData, pDetailData, dwSize, NULL, NULL))
			{
				INFO("pDetailData->DevicePath: %s", pDetailData->DevicePath);
				// 打开设备句柄
				hDevice = CreateFile(pDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
				if (hDevice != INVALID_HANDLE_VALUE)
				{
					// 获取设备描述符
					if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), &deviceDesc, sizeof(deviceDesc), &dwSize, NULL))
					{
						printf("Device Descriptor:\n");
						printf("bLength: %d\n", deviceDesc.bLength);
						printf("bDescriptorType: %d\n", deviceDesc.bDescriptorType);
						printf("bcdUSB: %x\n", deviceDesc.bcdUSB);
						printf("bDeviceClass: %d\n", deviceDesc.bDeviceClass);
						printf("bDeviceSubClass: %d\n", deviceDesc.bDeviceSubClass);
						printf("bDeviceProtocol: %d\n", deviceDesc.bDeviceProtocol);
						printf("bMaxPacketSize0: %d\n", deviceDesc.bMaxPacketSize0);
						printf("idVendor: %04x\n", deviceDesc.idVendor);
						printf("idProduct: %04x\n", deviceDesc.idProduct);
						printf("bcdDevice: %x\n", deviceDesc.bcdDevice);
						printf("iManufacturer: %d\n", deviceDesc.iManufacturer);
						printf("iProduct: %d\n", deviceDesc.iProduct);
						printf("iSerialNumber: %d\n", deviceDesc.iSerialNumber);
						printf("bNumConfigurations: %d\n", deviceDesc.bNumConfigurations);
						printf("\n");
					}

					// 获取配置描述符
					if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), &configDesc, sizeof(configDesc), &dwSize, NULL))
					{
						printf("Configuration Descriptor:\n");
						printf("bLength: %d\n", configDesc.bLength);
						printf("bDescriptorType: %d\n", configDesc.bDescriptorType);
						printf("wTotalLength: %d\n", configDesc.wTotalLength);
						printf("bNumInterfaces: %d\n", configDesc.bNumInterfaces);
						printf("bConfigurationValue: %d\n", configDesc.bConfigurationValue);
						printf("iConfiguration: %d\n", configDesc.iConfiguration);
						printf("bmAttributes: %d\n", configDesc.bmAttributes);
						printf("MaxPower: %d\n", configDesc.MaxPower);
						printf("\n");
					}

					// 获取字符串描述符
					if (deviceDesc.iManufacturer > 0)
					{
						if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), &stringDesc, sizeof(stringDesc), &dwSize, NULL))
						{
							dwSize = (stringDesc.bLength - 2) / 2;
							if (dwSize > 0)
							{
								if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), buffer, sizeof(buffer), &dwSize, NULL))
								{
									printf("Manufacturer: %ls\n", (WCHAR*)buffer);
								}
							}
						}
					}

					if (deviceDesc.iProduct > 0)
					{
						if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), &stringDesc, sizeof(stringDesc), &dwSize, NULL))
						{
							dwSize = (stringDesc.bLength - 2) / 2;
							if (dwSize > 0)
							{
								if (DeviceIoControl(hDevice, IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, &pInterfaceData->InterfaceClassGuid, sizeof(GUID), buffer, sizeof(buffer), &dwSize, NULL))
								{
									printf("Product: %ls\n", (WCHAR*)buffer);
								}
							}
						}
					}

					CloseHandle(hDevice);
				}
			}

			free(pDetailData);
		}

		free(pInterfaceData);
	}

	// 清理资源
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

// 获取字符串描述符
BOOL GetStringDescriptor(HANDLE deviceHandle, UCHAR stringIndex, PUSB_STRING_DESCRIPTOR stringDesc)
{
	// 初始化IOCTL
	USB_DESCRIPTOR_REQUEST descRequest;
	memset(&descRequest, 0, sizeof(descRequest));
	descRequest.ConnectionIndex = 1;  // 控制面索引
	descRequest.SetupPacket.bmRequest = USB_REQUEST_GET_DESCRIPTOR;
	descRequest.SetupPacket.bRequest = USB_REQUEST_GET_DESCRIPTOR;
	descRequest.SetupPacket.wValue = (USB_STRING_DESCRIPTOR_TYPE << 8) | stringIndex;
	descRequest.SetupPacket.wIndex = 0x0409;  // 默认英语(美国)语言ID
	descRequest.SetupPacket.wLength = sizeof(USB_STRING_DESCRIPTOR);

	// 发送IOCTL并读取响应
	DWORD bytesReturned;
	if (!DeviceIoControl(deviceHandle,
		IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
		&descRequest,
		sizeof(descRequest),
		stringDesc,
		sizeof(USB_STRING_DESCRIPTOR),
		&bytesReturned,
		NULL))
	{
		printf("无法获取字符串描述符，错误代码: %d\n", GetLastError());
		return FALSE;
	}
	else
	{
		printf("获取字符串描述符, %ws\n", stringDesc->bString);
	}

	return TRUE;
}

// 定义常量和宏
#define BUFFER_SIZE 1024
// 获取设备描述符和配置描述符
BOOL GetDescriptors(HANDLE deviceHandle)
{
	// 初始化IOCTL
	USB_DESCRIPTOR_REQUEST descRequest;
	memset(&descRequest, 0, sizeof(descRequest));
	descRequest.ConnectionIndex = 1;  // 控制面索引
	descRequest.SetupPacket.bmRequest = USB_REQUEST_GET_DESCRIPTOR;
	descRequest.SetupPacket.bRequest = USB_REQUEST_GET_DESCRIPTOR;
	descRequest.SetupPacket.wValue = (USB_DEVICE_DESCRIPTOR_TYPE << 8) | 0x00;
	descRequest.SetupPacket.wIndex = 0x00;
	descRequest.SetupPacket.wLength = sizeof(USB_DEVICE_DESCRIPTOR);

	// 创建缓冲区
	BYTE buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));

	// 发送IOCTL并读取响应
	DWORD bytesReturned;
	if (!DeviceIoControl(deviceHandle,
		IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
		&descRequest,
		sizeof(descRequest),
		buffer,
		BUFFER_SIZE,
		&bytesReturned,
		NULL))
	{
		printf("无法获取设备描述符，错误代码: %d\n", GetLastError());
		return FALSE;
	}
	else
	{
		printf("获取设备描述符, %s\n", buffer);
	}

	return TRUE;
}

int test4()
{
	GUID guid;
	HDEVINFO hDevInfo;
	SP_DEVICE_INTERFACE_DATA devInterfaceData;
	DWORD dwRequiredSize;
	BOOL bResult;
	DWORD dwLastError;

	// 设置GUID，用于搜索U盘设备
	if (!SetupDiClassGuidsFromName("USB", &guid, 1, &dwRequiredSize))
	{
		ERROR("SetupDiClassGuidsFromName failed. Error: %d", GetLastError());
		return 1;
	}
	INFO("dwRequiredSize %lu", dwRequiredSize);

	// 枚举U盘设备接口
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		ERROR("SetupDiGetClassDevs failed. Error: %d", GetLastError());
		return 1;
	}

	devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	// 遍历设备接口
	for (DWORD dwIndex = 0; ; ++dwIndex)
	{
		bResult = SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_USB_DEVICE, dwIndex, &devInterfaceData);
		dwLastError = GetLastError();
		if (!bResult && dwLastError != ERROR_NO_MORE_ITEMS)
		{
			ERROR("SetupDiEnumDeviceInterfaces failed. Error: %d", GetLastError());
			break;
		}

		if (bResult)
		{
			SP_DEVINFO_DATA devInfoData;
			PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = NULL;
			DWORD dwSize = 0;

			devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

			// 获取设备接口的详细信息
			bResult = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInterfaceData, NULL, 0, &dwSize, NULL);
			if (!bResult && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			{
				ERROR("SetupDiGetDeviceInterfaceDetail failed. Error: %d", GetLastError());
				break;
			}

			pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwSize);
			if (pInterfaceDetailData == NULL)
			{
				ERROR("Memory allocation failed.");
				break;
			}
			pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			// 再次调用SetupDiGetDeviceInterfaceDetail获取详细信息
			bResult = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInterfaceData, pInterfaceDetailData, dwSize, NULL, &devInfoData);
			if (!bResult)
			{
				ERROR("SetupDiGetDeviceInterfaceDetail failed. Error: %d", GetLastError());
				free(pInterfaceDetailData);
				break;
			}

			INFO("pInterfaceDetailData->DevicePath %s", pInterfaceDetailData->DevicePath);

			HANDLE hDevice = CreateFile(pInterfaceDetailData->DevicePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hDevice != INVALID_HANDLE_VALUE)
			{
				STORAGE_DEVICE_NUMBER deviceNumber;
				bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, &deviceNumber, sizeof(deviceNumber), &dwRequiredSize, NULL);
				if (bResult)
				{
					ERROR("U盘设备号： %d", deviceNumber.DeviceNumber);
				}
				else
				{
					ERROR("DeviceIoControl failed. Error: %d", GetLastError());
				}

				CloseHandle(hDevice);
			}
			else
			{
				ERROR("CreateFile failed. Error: %d", GetLastError());
			}

			free(pInterfaceDetailData);
		}
		else
		{
			ERROR("bResult failed. Error: %d", dwLastError);
			break;
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;
}

int __cdecl main()
{
	gHubList.DeviceInfo = INVALID_HANDLE_VALUE;
	InitializeListHead(&gHubList.ListHead);
	gDeviceList.DeviceInfo = INVALID_HANDLE_VALUE;
	InitializeListHead(&gDeviceList.ListHead);

	// Enumerate all USB buses and populate the tree
	//
	//EnumerateHostControllers();

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
		HANDLE hDevice = CreateFile("\\\\?\\USB#ROOT_HUB30#4&15bfe49e&0&0#{f18a0e88-c30c-11d0-8815-00a0c906bed8}",
		//HANDLE hDevice = CreateFile("\\\\?\\USB#VID_465A&PID_1053#5&2c75506a&0&13#{a5dcbf10-6530-11d2-901f-00c04fb951ed}",
		//HANDLE hDevice = CreateFile("\\\\?\\USB#VID_0951&PID_1666#E0D55EA493C4F72068B103FD#{a5dcbf10-6530-11d2-901f-00c04fb951ed}",
		//HANDLE hDevice = CreateFile("\\\\?\\USB#VID_0C45&PID_636D#SN0001#{a5dcbf10-6530-11d2-901f-00c04fb951ed}",
			0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			ERROR("无法打开USB设备句柄，错误码：%d\n", error);
			free(pDetailData);
			continue;
		}

		// 获取连接信息
		USB_NODE_CONNECTION_INFORMATION_EX connectionInfo;
		//connectionInfo.ConnectionIndex = 13; // 设备连接的端口索引号
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
			CloseHandle(hDevice);
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
			DWORD dwError = GetLastError();
			ERROR("**************DeviceIoControl failed, dwError %lu", dwError);
			CloseHandle(hDevice);
		}
		else {
			INFO("**************%lu %lu %lu", device_num.DeviceNumber, device_num.DeviceType, device_num.PartitionNumber);
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
			DWORD dwError = GetLastError();
			ERROR("DeviceIoControl failed, dwError %lu", dwError);
			CloseHandle(hDevice);
		}
		else {
			INFO("speed %d", connectionInfoEx->Speed);
			ERROR("vid:pid %04x:%04x", connectionInfoEx->DeviceDescriptor.idVendor,
				connectionInfoEx->DeviceDescriptor.idProduct);
		}

		PUSB_STRING_DESCRIPTOR stringDesc = (PUSB_STRING_DESCRIPTOR)malloc(sizeof(USB_STRING_DESCRIPTOR));
		GetStringDescriptor(hDevice, 2, stringDesc);
		GetDescriptors(hDevice);

		// 关闭USB设备句柄
		CloseHandle(hDevice);


		free(pDetailData);
	}

	// 销毁设备信息集合句柄
	SetupDiDestroyDeviceInfoList(hDevInfo);

	test();
	test2();
	test3();
	test4();
	return 0;
}
