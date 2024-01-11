// LibusbExample.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ��ȡ HID �����豸��Ϣ�����
	GUID HidGuid;
	HidD_GetHidGuid(&HidGuid);
	HDEVINFO hDevInfo = SetupDiGetClassDevs(
		&HidGuid,					// ֻ���� HID �����豸(��������������ΪNULL�����޸� Flag ����)
		NULL,						// ö��ָ�����͵��豸
		NULL,						// �豸�����Ķ������ھ��
		DIGCF_DEVICEINTERFACE |		// ָ���豸�ӿ�
		DIGCF_PRESENT				// ֻ���ص�ǰϵͳ�д��ڵ��豸
	);
	if (hDevInfo == INVALID_HANDLE_VALUE) {
		printf("�޷���ȡHID�豸��Ϣ���Ͼ��\n");
		return 1;
	}

	// ö��HID�豸�ӿ�
	DWORD index = 0;
	SP_DEVICE_INTERFACE_DATA interfaceData = { 0 };
	interfaceData.cbSize = sizeof(interfaceData);

	while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &HidGuid, index++, &interfaceData)) {
		// ��ȡHID�豸�ӿ���ϸ��Ϣ
		DWORD requiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, NULL, 0, &requiredSize, NULL);

		PSP_DEVICE_INTERFACE_DETAIL_DATA pDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
		pDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, pDetailData, requiredSize, NULL, NULL)) {
			printf("�޷���ȡHID�豸�ӿ���ϸ��Ϣ\n");
			free(pDetailData);
			continue;
		}

		printf("pDetailData->DevicePath %ws\n", pDetailData->DevicePath);

		// ��HID�豸���
		HANDLE hDevice = CreateFile(
			pDetailData->DevicePath,				// �豸����
			GENERIC_READ | GENERIC_WRITE,			// ����Ȩ��
			FILE_SHARE_READ | FILE_SHARE_WRITE,		// ����Ȩ��
			NULL,									// ���صľ�����ܱ��̳�
			OPEN_EXISTING,							// �����豸����ʱ��
			FILE_ATTRIBUTE_NORMAL,					// ��������������
			NULL									// ��������չ����
		);
		if (hDevice == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			//ERROR_INSUFFICIENT_BUFFER
			printf("�޷���HID�豸����������룺%d\n", error);
			free(pDetailData);
			continue;
		}

		// ��ȡHID�豸�ַ���������
		WCHAR manufacturerString[1024] = { 0 };
		WCHAR productString[1024] = { 0 };
		WCHAR serialString[1024] = { 0 };

		BOOL result = HidD_GetIndexedString(hDevice, 1, manufacturerString, 1024);
		result = HidD_GetProductString(hDevice, productString, 1024);
		result = HidD_GetManufacturerString(hDevice, serialString, 1024);	// δ�ҵ��в�Ʒ���к��豸
		if (!result) {
			printf("�޷���ȡHID�豸�ַ���������, %d\n", GetLastError());
			CloseHandle(hDevice);
			free(pDetailData);
			continue;
		}
		printf("HID�豸�����ַ���������(%d)��%ws\n", wcslen(manufacturerString), manufacturerString);
		printf("HID�豸��Ʒ�ַ���������(%d)��%ws\n", wcslen(productString), productString);
		printf("HID�豸�����ַ���������(%d)��%ws\n", wcslen(serialString), serialString);

		// ��ȡ�豸�ӿڵ� PID��VID
		HIDD_ATTRIBUTES hidAttributes = { 0 };
		hidAttributes.Size = sizeof(hidAttributes);
		if (!HidD_GetAttributes(
			hDevice,			// �豸���
			&hidAttributes		// [OUT] HIDD_ATTRIBUTES �ṹ��ָ��
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

		// �ر�HID�豸���
		CloseHandle(hDevice);

		free(pDetailData);
	}

	// ����HID�豸��Ϣ���Ͼ��
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

