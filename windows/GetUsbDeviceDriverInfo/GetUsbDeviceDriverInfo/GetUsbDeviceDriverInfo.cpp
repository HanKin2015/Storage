// GetUsbDeviceDriverInfo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <usbspec.h>
#include <usbiodef.h>
#include <initguid.h>
#include <setupapi.h>
#include <Cfgmgr32.h>
#include <iostream>
#pragma comment(lib, "Cfgmgr32.lib")
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "winusb.lib")
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, \
	0xC0, 0x4F, 0xB9, 0x51, 0xED);

/*
=======  GetUsbDeviceDriverInfo:21  ========
�豸����: USB\VID_0C45&PID_636D&REV_0100
Driver version is 000a0000 4a6109f2
Driver file: C:\WINDOWS\INF\usb.inf
Driver section: Composite.Dev
Driver description: USB Composite Device
Driver MfgName: (��׼ USB ������)
Driver ProviderName: Microsoft
Driver HardwareID:
*/
static int GetUsbDeviceDriverInfo()
{
	printf("========  %s:%d  ========\n", __FUNCTION__, __LINE__);
	HDEVINFO deviceInfoSet;
	SP_DEVINFO_DATA deviceInfoData;
	SP_DRVINFO_DATA driverInfoData;
	SP_DRVINFO_DETAIL_DATA driverInfoDetailData;
	DWORD i;

	setlocale(LC_ALL, "chs");	// �ó���֧��UTF-16���ĵ��������һ�л��Ǻ���Ҫ��Ȼ��������룩

	// ��ȡ�豸��Ϣ����
	deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (deviceInfoSet == INVALID_HANDLE_VALUE) {
		return 1;
	}

	// ��ʼ��SP_DEVINFO_DATA
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
		DWORD driverType = SPDIT_COMPATDRIVER;
		driverInfoData.cbSize = sizeof(SP_DRVINFO_DATA);

		DWORD DataT;
		WCHAR buf[MAX_PATH] = { 0 };
		DWORD bufSize = sizeof(buf);

		// ��ȡ�豸����
		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("�豸����: %ws\n", buf);
		}

		// Build a list of driver info items that we will retrieve below 
		if (!SetupDiBuildDriverInfoList(deviceInfoSet,
			&deviceInfoData, SPDIT_COMPATDRIVER))
			return -1; // Exit on error 

					   // ö���豸����������
		if (SetupDiEnumDriverInfo(deviceInfoSet, &deviceInfoData, driverType, 0, &driverInfoData)) {
			driverInfoDetailData.cbSize = sizeof(SP_DRVINFO_DETAIL_DATA);
			printf("Driver version is %08x %08x\n",
				(unsigned)(driverInfoData.DriverVersion >> 32),
				(unsigned)(driverInfoData.DriverVersion & 0xffffffffULL));
			// ��ȡ����������ϸ��Ϣ
			// ��ʵ��ȡ����ע������ݼ����\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}\0067
			if (SetupDiGetDriverInfoDetail(deviceInfoSet, &deviceInfoData, &driverInfoData, &driverInfoDetailData, sizeof(driverInfoDetailData), NULL) || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				// �������������ϸ��Ϣ
				_tprintf(TEXT("Driver file: %s\n"), driverInfoDetailData.InfFileName);
				_tprintf(TEXT("Driver section: %s\n"), driverInfoDetailData.SectionName);
				_tprintf(TEXT("Driver description: %s\n"), driverInfoData.Description);
				_tprintf(TEXT("Driver MfgName: %s\n"), driverInfoData.MfgName);
				_tprintf(TEXT("Driver ProviderName: %s\n"), driverInfoData.ProviderName);
				_tprintf(TEXT("Driver HardwareID: %s\n"), driverInfoDetailData.HardwareID);
			}
		}
		else
		{
			printf("SetupDiEnumDriverInfo FAILED failed, errCode:%u\r\n", GetLastError());
		}
	}

	if (deviceInfoSet) {
		SetupDiDestroyDeviceInfoList(deviceInfoSet);
	}
	return 0;
}

using namespace std;

void printGUID(GUID& guid);
TCHAR* FindVersionFromULONGLONG(ULONGLONG data);

static int GetLocalSoftwareDriverInfo()
{
	GUID guid = { 0 };
	DWORD dwRet = 0;
	ULONG guidIndex = 0;

	setlocale(LC_ALL, "chs");//�ó���֧��UTF-16���ĵ����

	while (true)
	{
		// CM_Enumerate_Classes ������ Windows ����ϵͳ�е�һ�����ù����� API��������ö��ϵͳ�д��ڵ��豸���
		// �������ͨ����������ֱ��ö���ض����豸���� USB �豸����������ö���豸��� GUID��ȫ��Ψһ��ʶ������
		dwRet = CM_Enumerate_Classes(guidIndex++, &guid, 0);
		if (CR_NO_SUCH_VALUE == dwRet)
		{
			cout << "�豸��ö�����" << endl;
			break;
		}
		printGUID(guid);

		HDEVINFO hdevInfo = 0;
		hdevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT);
		if (INVALID_HANDLE_VALUE == hdevInfo)
		{
			cout << "SetupDiGetClassDevs failed" << endl;
			break;
		}

		DWORD deviceIndex = 0;
		SP_DEVINFO_DATA devInfoData = { sizeof(SP_DEVINFO_DATA) };

		for (deviceIndex = 0; SetupDiEnumDeviceInfo(hdevInfo, deviceIndex, &devInfoData); ++deviceIndex)
		{
			_tprintf(L"-------------------------------------------------------------\n�����豸��\n");

			ULONG buffSize = 0;
			if (CR_SUCCESS != CM_Get_Device_ID_Size(&buffSize, devInfoData.DevInst, 0))
			{
				break;
			}

			TCHAR* buff = new TCHAR[buffSize + 1];
			dwRet = CM_Get_Device_ID(devInfoData.DevInst, buff, buffSize, 0);
			if (CR_SUCCESS != dwRet)
			{
				break;
			}
			buff[buffSize] = TEXT('\0');
			_tprintf(TEXT("Device ID:%s\n"), buff);
			delete[]buff;

			DWORD dwPropertyRegDataType, dwSize;
			wchar_t propertyBuffer[4096];

			if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_DEVICEDESC,
				&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
			{
				_tprintf(L"Device Name:%s\n", propertyBuffer);
			}


			if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_HARDWAREID,
				&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
			{
				_tprintf(L"Ӳ��ID:\n");
				wchar_t* p = propertyBuffer;
				for (; *p != TEXT('\0') && p + dwSize / sizeof(char) <= propertyBuffer + ARRAYSIZE(propertyBuffer); p += lstrlen(p) + 1)
				{
					_tprintf(L"%s\n", p);
				}
			}
			else
			{
				continue;
			}

			_tprintf(L"\n����ID:\n");
			if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_COMPATIBLEIDS,
				&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
			{
				wchar_t* p = propertyBuffer;
				for (; *p != TEXT('\0') && p + dwSize / sizeof(char) <= propertyBuffer + ARRAYSIZE(propertyBuffer); p += lstrlen(p) + 1)
				{
					_tprintf(TEXT("%s\n"), p);
				}
			}

			_tprintf(TEXT("\n��Ӧ������\n"));
			//��������
			if (SetupDiBuildDriverInfoList(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER))
			{
				SP_DRVINFO_DATA driverInfoData = { sizeof(SP_DRVINFO_DATA) };
				int i = 0;
				for (; SetupDiEnumDriverInfo(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER, i, &driverInfoData); ++i);

				--i;
				_tprintf(TEXT("�豸���ƣ�%s\n"), driverInfoData.Description);
				_tprintf(TEXT("���������ṩ�̣�%s\n"), driverInfoData.ProviderName);
				_tprintf(TEXT("�豸�����̣�%s\n"), driverInfoData.MfgName);
				_tprintf(TEXT("��������汾��%s\n"), FindVersionFromULONGLONG(driverInfoData.DriverVersion));

				SYSTEMTIME sysTime;
				FileTimeToSystemTime(&driverInfoData.DriverDate, &sysTime);
				_tprintf(TEXT("������������:%d/%d/%d\n"),
					sysTime.wYear, sysTime.wMonth, sysTime.wDay);

				SetupDiDestroyDriverInfoList(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER);
			}
			else
			{
				_tprintf(TEXT("\nû�ҵ���Ӧ��������\n"));
			}
			_tprintf(TEXT("-------------------------------------------------------------\n"));
		}
	}
	return 0;
}

/*
�����豸��
Device ID:USB\VID_0C45&PID_636D\SN0001
Device Name:USB Composite Device
Ӳ��ID:
USB\VID_0C45&PID_636D&REV_0100
USB\VID_0C45&PID_636D

����ID:
USB\DevClass_00&SubClass_00&Prot_00
USB\DevClass_00&SubClass_00
USB\DevClass_00
USB\COMPOSITE

��Ӧ������
�豸���ƣ�USB Composite Device
���������ṩ�̣�Microsoft
�豸�����̣�(��׼ USB ��������)
��������汾��10.0.19041.2546
������������:2006/6/21
*/
int main()
{
	GetUsbDeviceDriverInfo();

	printf("========  %s:%d  ========\n", __FUNCTION__, __LINE__);
	DWORD dwRet = 0;

	setlocale(LC_ALL, "chs");//�ó���֧��UTF-16���ĵ����

	// ��ȡ�豸��Ϣ����
	HDEVINFO hdevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (hdevInfo == INVALID_HANDLE_VALUE) {
		cout << "SetupDiGetClassDevs failed" << endl;
		return 1;
	}

	// ��ʼ��SP_DEVINFO_DATA
	DWORD deviceIndex = 0;
	SP_DEVINFO_DATA devInfoData = { sizeof(SP_DEVINFO_DATA) };
	for (deviceIndex = 0; SetupDiEnumDeviceInfo(hdevInfo, deviceIndex, &devInfoData); ++deviceIndex)
	{
		_tprintf(L"-------------------------------------------------------------\n�����豸��\n");

		ULONG buffSize = 0;
		if (CR_SUCCESS != CM_Get_Device_ID_Size(&buffSize, devInfoData.DevInst, 0))
		{
			break;
		}

		TCHAR* buff = new TCHAR[buffSize + 1];
		dwRet = CM_Get_Device_ID(devInfoData.DevInst, buff, buffSize, 0);
		if (CR_SUCCESS != dwRet)
		{
			break;
		}
		buff[buffSize] = TEXT('\0');
		_tprintf(TEXT("Device ID:%s\n"), buff);
		delete[]buff;

		DWORD dwPropertyRegDataType, dwSize;
		wchar_t propertyBuffer[4096];

		if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_DEVICEDESC,
			&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
		{
			_tprintf(L"Device Name:%s\n", propertyBuffer);
		}


		if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_HARDWAREID,
			&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
		{
			_tprintf(L"Ӳ��ID:\n");
			wchar_t* p = propertyBuffer;
			for (; *p != TEXT('\0') && p + dwSize / sizeof(char) <= propertyBuffer + ARRAYSIZE(propertyBuffer); p += lstrlen(p) + 1)
			{
				_tprintf(L"%s\n", p);
			}
		}
		else
		{
			continue;
		}

		_tprintf(L"\n����ID:\n");
		if (SetupDiGetDeviceRegistryProperty(hdevInfo, &devInfoData, SPDRP_COMPATIBLEIDS,
			&dwPropertyRegDataType, (PBYTE)propertyBuffer, sizeof(propertyBuffer), &dwSize))
		{
			wchar_t* p = propertyBuffer;
			for (; *p != TEXT('\0') && p + dwSize / sizeof(char) <= propertyBuffer + ARRAYSIZE(propertyBuffer); p += lstrlen(p) + 1)
			{
				_tprintf(TEXT("%s\n"), p);
			}
		}

		_tprintf(TEXT("\n��Ӧ������\n"));
		//��������
		if (SetupDiBuildDriverInfoList(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER))
		{
			SP_DRVINFO_DATA driverInfoData = { sizeof(SP_DRVINFO_DATA) };
			int i = 0;
			for (; SetupDiEnumDriverInfo(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER, i, &driverInfoData); ++i);

			--i;
			_tprintf(TEXT("�豸���ƣ�%s\n"), driverInfoData.Description);
			_tprintf(TEXT("���������ṩ�̣�%s\n"), driverInfoData.ProviderName);
			_tprintf(TEXT("�豸�����̣�%s\n"), driverInfoData.MfgName);
			_tprintf(TEXT("��������汾��%s\n"), FindVersionFromULONGLONG(driverInfoData.DriverVersion));

			SYSTEMTIME sysTime;
			FileTimeToSystemTime(&driverInfoData.DriverDate, &sysTime);
			_tprintf(TEXT("������������:%d/%d/%d\n"),
				sysTime.wYear, sysTime.wMonth, sysTime.wDay);

			SetupDiDestroyDriverInfoList(hdevInfo, &devInfoData, SPDIT_COMPATDRIVER);
		}
		else
		{
			_tprintf(TEXT("\nû�ҵ���Ӧ��������\n"));
		}
		_tprintf(TEXT("-------------------------------------------------------------\n"));
	}

	system("pause");
	return 0;
}

void printGUID(GUID& guid)
{
	_tprintf(TEXT("GUID:%8X %4X %4X %2X %2X %2X %2X %2X %2X %2X %2X\n"),
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
}

TCHAR* FindVersionFromULONGLONG(ULONGLONG data)
{
	static TCHAR buff[64];
	memset(buff, 0, sizeof(buff));
	ULONG temp = 0;
	TCHAR numbuff[8];

	for (int i = 48; i >= 0; i -= 16)
	{
		temp = (data >> i) & 0xFFFF;
		_ultot_s(temp, numbuff, 10);
		_tcscat_s(buff, numbuff);
		_tcscat_s(buff, TEXT("."));
	}
	buff[_tcslen(buff) - 1] = 0;
	return buff;
}
