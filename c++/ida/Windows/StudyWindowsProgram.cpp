// StudyWindowsProgram.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <usbiodef.h>
#include <initguid.h>
#include <iostream>
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "winusb.lib")
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, \
	0xC0, 0x4F, 0xB9, 0x51, 0xED);

static void TestFunction1()
{
	if (getenv("GOPATH"))
	{
		printf("%s\n", getenv("GOPATH"));
	}
	if (getenv("OneDrive"))
	{
		printf("%s\n", getenv("TEMP"));
	}
	return;
}

#define FAILED(hr)      (((HRESULT)(hr)) < 0)
static int SetFormat(int x)
{
	if (x > 10) return 1;
	else if (x == 5) return -1;
	return 0;
}
static void TestFunction2()
{
	HRESULT hr = 0x80040227;
	printf("0x%x\n", GetLastError());
	int ret = SetFormat(5);
	printf("ret %d 0x%x\n", ret, GetLastError());
	if (FAILED(hr))
	{
		printf("ret %d 0x%x\n", ret, GetLastError());
	}
	return;
}

static void TestFunction3()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);

	ULARGE_INTEGER uli;
	uli.LowPart = ft.dwLowDateTime;
	uli.HighPart = ft.dwHighDateTime;

	ULONGLONG timestamp = uli.QuadPart / 10000000ULL - 11644473600ULL;

	std::cout << "��ǰʱ�����" << timestamp << std::endl;
	return;
}

void example()
{
	int x = 1000, y = 100;
	int var = 5;
	if (x > y) {
		var = 66;
	}
	printf("var = %d\n", var);
	return;
}

int main()
{
	example();

	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	// ��ȡ����USB�豸���豸��Ϣ
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("SetupDiGetClassDevs failed (%d)\n", GetLastError());
		return 1;
	}

	// ö������USB�豸
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD DataT;
		char buf[1024];
		DWORD bufSize = sizeof(buf);

		// ��ȡ�豸����
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("�豸����: %s\n", buf);
		}

		// ��ȡ�� Guid
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("�� Guid: %s\n", buf);
		}
	}

	// �ͷ��豸��Ϣ���
	SetupDiDestroyDeviceInfoList(hDevInfo);

	system("pause");
    return 0;
}

