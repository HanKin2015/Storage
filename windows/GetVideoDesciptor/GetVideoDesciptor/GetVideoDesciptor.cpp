// GetVideoDesciptor.cpp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <cfgmgr32.h>
#include <setupapi.h>
#include <mmreg.h>
#include <assert.h>
#include <devguid.h>
#include <regstr.h>
#include <usbspec.h>
#include <usbioctl.h>
#pragma comment(lib, "Cfgmgr32.lib")
#pragma comment(lib, "setupapi.lib")

#define IOCTL_CUSTOM_GET_DEVICE_DESCRIPTOR CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_USB_CUSTOM_GET_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN, 4001, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define LOGI printf
#define LOGW printf
#define LOGE printf
#define STATIC_KSCATEGORY_CAPTURE \
    0x65E8773DL, 0x8F56, 0x11D0, 0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
DEFINE_GUIDSTRUCT("65E8773D-8F56-11D0-A3B9-00A0C9223196", KSCATEGORY_CAPTURE);
#define KSCATEGORY_CAPTURE DEFINE_GUIDNAMED(KSCATEGORY_CAPTURE)

typedef struct
{
	WCHAR DeviceName[MAX_PATH];
	int length;
	unsigned char data[0];
}CONTROLSTRUCT, *PCONTROLSTRUCT;

/*
�豸�б�ITEM
*/
typedef struct
{
	//���豸��ID Ҳ����Ӧ��DEVONINT
	DWORD id;

	//�豸��PDO�������������Ա�ִ����Ӧ�Ĳ���
	WCHAR DeviceName[MAX_PATH];

	//�豸��ʵ��·�� ����DIRECTSHOW������ͷ�����ִ���һ��
	char DevicePath[MAX_PATH];
}CAMERADEVICEITEM, *PCAMERADEVICEITEM;

/**
* @����  �жϴ˽ڵ��Ƿ�ΪUSBHUB
* @param  srvString ���ڵ�ķ�������
* @return	��
*/
static BOOL IsUsbHubNode(WCHAR *srvString)
{
	BOOL result = FALSE;
	if (srvString == NULL)
	{
		LOGE("srvString == NULL\r\n");
		goto EXIT;
	}

	//LOGI("srvString: %s\n", srvString);
	if (wcscmp(srvString, L"usbhub") == 0 ||
		wcscmp(srvString, L"usbccgp") == 0 ||
		wcscmp(srvString, L"iusb3xhc") == 0 ||
		wcscmp(srvString, L"iusb3hub") == 0 ||
		wcscmp(srvString, L"USBHUB3") == 0)
	{
		LOGI("srvString: %ws\n", srvString);
		result = TRUE;
	}

	//LOGI("service name:%s result:%s\r\n", srvString, result ? "true" : "false");
EXIT:
	return result;
};

/**
* @����  �õ��豸��·��
* @param  str ԭ·��
* @param  dst ת�����·��
* @return  ��
src : \\?\usb#vid_058f&pid_3880&mi_00#7&367824c&0&0000#
{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global
dst :  vid_058f&pid_3880&mi_00#7&27a9895&0&0000#
*/
static void ExtractDevicePath(WCHAR* src, char* dst)
{
	char *  begin = NULL;
	char *  end = NULL;
	int     i = 0;

	assert(src != NULL && dst != NULL);
	LOGI("%d %d\n", strlen(dst), sizeof(dst));

	int Size = WideCharToMultiByte(CP_ACP, NULL, src, (int)wcslen(src), NULL, 0, NULL, NULL);
	char *AnsiName = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size + 1);
	if (AnsiName)
	{
		memset(AnsiName, 0, Size + 1);
		WideCharToMultiByte(CP_ACP, NULL, src, (int)wcslen(src), AnsiName, Size + 1, NULL, NULL);
		AnsiName[Size] = '\0';
	}
	LOGI("AnsiName: %s, Size: %d\n", AnsiName, Size);

	if (AnsiName != NULL)
	{
		for (int idx = 0; idx < Size; idx++)
		{
			AnsiName[idx] = tolower(AnsiName[idx]);
		}
		//CharLowerBuff(LPTSTR(AnsiName), Size + 1);	// ���Ͳ�ƥ��ᵼ�³���������ڴ�

		begin = strstr(AnsiName, "vid");
		end = strstr(AnsiName, "{");
		if (begin != NULL && end != NULL)
		{
			while (*begin != *end)
			{
				dst[i] = *begin;
				i++;
				begin++;
			};

			dst[i] = '\0';
		}

		HeapFree(GetProcessHeap(), 0, AnsiName);
		AnsiName = NULL;
	};

	LOGI("i: %d\n", i);
	LOGI("src: %ws\n", src);
	LOGI("dst: %s\n", dst);
};

/**
* @����  �õ��豸·��
* @param  devicePath �豸·��
* @param  inst �豸ʵ��
* @return	��
*/
void GetDevicePath(char* devicePath, DEVINST inst)
{
	BOOL                             ret = FALSE;
	DWORD                            dwIndex = 0;
	PSP_DEVICE_INTERFACE_DETAIL_DATA pInterData = NULL;

	SP_DEVICE_INTERFACE_DATA spDevInterfaceData = { 0 };
	SP_DEVINFO_DATA          spDevInfoData = { 0 };
	HDEVINFO                 hDevInfo = INVALID_HANDLE_VALUE;

	hDevInfo = SetupDiGetClassDevs(&KSCATEGORY_CAPTURE,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (INVALID_HANDLE_VALUE == hDevInfo)
	{
		LOGE("SetupDiGetClassDevs FAILED failed, errCode:%u\r\n", GetLastError());
		return;
	}

	ZeroMemory(&spDevInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
	spDevInterfaceData.cbSize = sizeof(spDevInterfaceData);

	while (!ret && SetupDiEnumDeviceInterfaces(hDevInfo, NULL,
		&KSCATEGORY_CAPTURE, dwIndex, &spDevInterfaceData))
	{
		DWORD dwReqSize = 0;

		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo,
			&spDevInterfaceData,
			NULL,
			0,
			&dwReqSize,
			NULL) && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			LOGE("SetupDiGetDeviceInterfaceDetail failed:%d(0x%08x)\r\n",
				GetLastError(), GetLastError());
			return;
		}
		printf("dwReqSize:%d\n", dwReqSize);
		pInterData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)calloc(1, dwReqSize);
		if (!pInterData)
		{
			LOGE("allocate memeory for pInterData failed\r\n");
			SetupDiDestroyDeviceInfoList(hDevInfo);
			return;
		};
		memset(pInterData, 0, dwReqSize);

		pInterData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		ZeroMemory(&spDevInfoData, sizeof(SP_DEVINFO_DATA));

		spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		if (SetupDiGetDeviceInterfaceDetail(hDevInfo,
			&spDevInterfaceData,
			pInterData,
			dwReqSize,
			NULL,
			&spDevInfoData))
		{
			if (spDevInfoData.DevInst == inst)
			{
				ret = TRUE;
				ExtractDevicePath((WCHAR *)(pInterData->DevicePath), devicePath);
			}
		}

		free(pInterData);

		ZeroMemory(&spDevInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
		spDevInterfaceData.cbSize = sizeof(spDevInterfaceData);
		dwIndex++;
	}

	if (hDevInfo == NULL)
	{
		printf("1231\n");
	}
	printf("aaaa\n");
	if (hDevInfo != INVALID_HANDLE_VALUE)
	{
		//SetupDiDestroyDeviceInfoList(hDevInfo);
		//hDevInfo = INVALID_HANDLE_VALUE;
	}
	return;
};

/**
* @����   ������
* @param  ��
* @return	��
*/
#define MONITOR_DRIVER_NAME          L"\\\\.\\commonUsb"
HANDLE OpenMonitorDriver()
{
	// ���豸
	HANDLE m_MonitorDriver = CreateFile(
		MONITOR_DRIVER_NAME, //DevicePath,
		GENERIC_READ,         // Only read access
		0,                    // FILE_SHARE_READ | FILE_SHARE_WRITE
		NULL,                 // no SECURITY_ATTRIBUTES structure
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL
	);
	if (m_MonitorDriver == INVALID_HANDLE_VALUE)
	{
		LOGE("CreateFile failed :%d(0x%x)\n",
			GetLastError(), GetLastError());
	};

EXIT:
	return m_MonitorDriver;
};

/**
* @����  ��ȡ�豸������
* @param  ��
* @return	TRUE��ȡ�ɹ���FALSE ��ȡʧ��
*/
BOOL GetDeviceDesc(CAMERADEVICEITEM m_DeviceInfo)
{
	BOOL   result = FALSE;
	DWORD  byte = 0;
	DWORD  InSize = 0;
	DWORD  OutSize = 0;
	DWORD  DeviceSize = 0;
	DWORD  len = 0;
	CONTROLSTRUCT *data = NULL;
	unsigned char *m_DeviceDesc = NULL;

	HANDLE m_driver = OpenMonitorDriver();

	len = sizeof(CONTROLSTRUCT);
	data = (CONTROLSTRUCT*)calloc(1, len);
	if (data == NULL)
	{
		LOGE("calloc1 failed\n");
		result = FALSE;
		goto EXIT;
	};
	memset(data, 0, len);

	memcpy(data->DeviceName,
		m_DeviceInfo.DeviceName, sizeof(data->DeviceName));
	LOGI("data->DeviceName: %ws\n", data->DeviceName);
	OutSize = sizeof(DeviceSize);
	result = DeviceIoControl(
		m_driver,
		IOCTL_USB_CUSTOM_GET_DEVICE,
		data, //in
		len,
		&DeviceSize, //out 
		OutSize,
		&byte,
		0);
	if (!result)
	{
		LOGE("DeviceIoControl1 Fail(0x%x)\r\n", GetLastError());
		result = FALSE;
		goto EXIT;
	};

	m_DeviceDesc = (unsigned char *)calloc(1, DeviceSize);
	if (m_DeviceDesc == NULL)
	{
		LOGE("calloc2 failed\n");
		result = FALSE;
		goto EXIT;
	};
	memset(m_DeviceDesc, 0, DeviceSize);

	OutSize = DeviceSize;
	result = DeviceIoControl(
		m_driver,
		IOCTL_USB_CUSTOM_GET_DEVICE,
		data, //in
		len,
		m_DeviceDesc, //out 
		OutSize,
		&byte,
		0);
	if (!result)
	{
		LOGE("DeviceIoControl2 Fail(0x%x)\r\n", GetLastError());
		result = FALSE;
		goto EXIT;
	};

	LOGI("DeviceSize: %d\n", DeviceSize);
	for (int i = 0; i < DeviceSize; i++)
	{
		LOGI("%02x%c", m_DeviceDesc[i], i == DeviceSize - 1 ? '\n' : ' ');
	}
	result = TRUE;

EXIT:

	if (data != NULL)
	{
		free(data);
		data = NULL;
	}

	if (!result)
	{
		if (m_DeviceDesc != NULL)
		{
			free(m_DeviceDesc);
			m_DeviceDesc = NULL;
		};
		return result;
	}

	return result;
};

/**
* @����  ���������豸�ĸ�������
* @param  subRoot ���ڵ�
* @return	��
*/
static void EnumerateUsbHubSubDevs(DEVINST subRoot)
{
	CONFIGRET    cr;
	WCHAR        srvString[MAX_PATH];
	ULONG        stringSize = sizeof(srvString);
	DEVINST      tmpDevInst;
	ULONG        DeviceStatus;
	ULONG        ProblemNumber;

	CAMERADEVICEITEM device = { 0 };
	memset(device.DeviceName, 0, MAX_PATH);
	memset(device.DevicePath, 0, MAX_PATH);

	cr = CM_Get_Child(&tmpDevInst, subRoot, 0);
	while (cr == CR_SUCCESS)
	{
		stringSize = sizeof(srvString);
		cr = CM_Get_DevNode_Registry_Property(tmpDevInst,
			CM_DRP_SERVICE,
			NULL,
			srvString,
			&stringSize, 0);
		if (cr == CR_SUCCESS && IsUsbHubNode(srvString))
		{
			EnumerateUsbHubSubDevs(tmpDevInst);
		}
		else
		{
			stringSize = sizeof(srvString);
			cr = CM_Get_DevNode_Registry_Property(tmpDevInst,
				CM_DRP_CLASS,
				NULL,
				srvString,
				&stringSize, 0);
			if (cr != CR_SUCCESS)
			{
				LOGW("device class failed skip it cr:0x%x\r\n", cr);
				cr = CM_Get_Sibling(&tmpDevInst, tmpDevInst, 0);
				continue;
			}
			else
			{
				if (wcscmp(srvString, L"Image") != 0 && wcscmp(srvString, L"Camera") != 0)
				{
					LOGW("device class:%ws skip it\r\n", srvString);
					cr = CM_Get_Sibling(&tmpDevInst, tmpDevInst, 0);
					continue;
				}
			};

			cr = CM_Get_DevNode_Status(&DeviceStatus,
				&ProblemNumber, tmpDevInst, 0);
			LOGW("DeviceStatus:0x%x(DeviceStatus & DN_STARTED:0x%x) ProblemNumber:0x%x cr:0x%x\r\n",
				DeviceStatus, DeviceStatus & DN_STARTED, ProblemNumber, cr);
			if (cr != CR_SUCCESS)
			{
				LOGW("skip it\r\n");
				cr = CM_Get_Sibling(&tmpDevInst, tmpDevInst, 0);
				continue;
			}
			else
			{
				if (!(DeviceStatus & DN_STARTED))
				{
					LOGE("DeviceStatus & DN_STARTED failed skip\r\n");
					cr = CM_Get_Sibling(&tmpDevInst, tmpDevInst, 0);
					continue;
				}
			};

			stringSize = sizeof(device.DeviceName);
			cr = CM_Get_DevNode_Registry_Property(subRoot,
				CM_DRP_PHYSICAL_DEVICE_OBJECT_NAME,
				NULL,
				&device.DeviceName,
				&stringSize,
				0);
			if (cr == CR_SUCCESS)
			{
				GetDevicePath(device.DevicePath, tmpDevInst);

				device.id = tmpDevInst;

				LOGE("[new device] DevicePath:%s DeviceName:%ws id:0x%x\r\n",
					device.DevicePath, device.DeviceName, tmpDevInst);
				int vid, pid;
				sscanf_s(device.DevicePath, "%*[a-zA-Z ]_%x&%*[a-zA-Z ]_%x", &vid, &pid);

				LOGI("vid_pid:%04x:%04x\n", vid, pid);
				GetDeviceDesc(device);
			};
		};
		cr = CM_Get_Sibling(&tmpDevInst, tmpDevInst, 0);
	}
}

/**
* @����  ���������豸�ĸ�������
* @param  subRoot ���ڵ�
* @return	��
*/
static void EnumerateUsbHubNode(DEVINST subRoot)
{
	CONFIGRET cr;
	WCHAR     srvString[512];
	ULONG     size = sizeof(srvString);
	DEVINST   tempDevInst;

	cr = CM_Get_DevNode_Registry_Property(subRoot,
		CM_DRP_SERVICE,
		NULL,
		srvString,
		&size,
		0);
	if (cr == CR_SUCCESS && IsUsbHubNode(srvString))
	{
		LOGI("start EnumerateUsbHubSubDevs\n");
		EnumerateUsbHubSubDevs(subRoot);
		goto EXIT;
	}

	cr = CM_Get_Child(&tempDevInst, subRoot, 0);
	if (cr != CR_SUCCESS)
	{
		goto EXIT;
	}

	do
	{	
		EnumerateUsbHubNode(tempDevInst);

		cr = CM_Get_Sibling(&tempDevInst, tempDevInst, 0);
		if (cr != CR_SUCCESS)
		{

			goto EXIT;
		}
	} while (TRUE);

EXIT:
	return;
}

// �Զ�����������ͨ�Ż�ȡ�豸��������Ϣ
static int CustomDriverCommunication()
{
	// ������ͷ�豸
	//HANDLE hCamera = CreateFile(L"\\\\.\\commonUsb", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	HANDLE hCamera = OpenMonitorDriver();
	if (hCamera == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open camera device." << std::endl;
		return -1;
	}

	// ���Ϳ������ȡ�豸������
	UCHAR descBuffer[MAX_PATH] = { 0 };	// ����д��UCHAR��������WCHAR��CHAR������
	DWORD bytesReturned = 0;
	DWORD  len = 0;
	CONTROLSTRUCT *data = NULL;

	len = sizeof(CONTROLSTRUCT);
	data = (CONTROLSTRUCT*)calloc(1, len);
	memset(data, 0, len);
	CHAR *tmp = "\\Device\\USBPDO-14";
	//memcpy(data->DeviceName, tmp, strlen(tmp));
	mbstowcs_s(NULL, data->DeviceName, MAX_PATH, tmp, _TRUNCATE);

	DWORD  DeviceSize = 0;
	BOOL result = DeviceIoControl(hCamera,
								  IOCTL_USB_CUSTOM_GET_DEVICE,
								  data,	// in
								  len,
								  &DeviceSize,
								  sizeof(DeviceSize),
								  &bytesReturned,
		                          NULL);
	LOGI("result: %d, DeviceSize: %lu, bytesReturned: %lu\n", result, DeviceSize, bytesReturned);

	if (DeviceIoControl(hCamera,
						IOCTL_USB_CUSTOM_GET_DEVICE,
						data,	// in
						len,
						descBuffer,
		                DeviceSize,
						&bytesReturned,
						NULL)) {
		LOGI("bytesReturned %lu\n", bytesReturned);
		for (int i = 0; i < DeviceSize; i++)
		{
			LOGI("%02x%c", descBuffer[i], i == DeviceSize - 1 ? '\n' : ' ');
		}
	}
	else {
		LOGE("DeviceIoControl1 Fail(0x%X)\r\n", GetLastError());
		std::cout << "Failed to get device descriptor." << std::endl;
	}

	// �ر��豸���
	CloseHandle(hCamera);
	return 0;
}

// ������
static int OpenCameraDevice()
{
	// 1��������ͷ�豸���豸·��ֻ��ͨ���������ȡ����ʹ�ö�Ӧ�Ĵ��룩
	// Failed to get device descriptor����ֵ��ͨ��EnumerateUsbHubNode������ȡ�����ģ�
	//WCHAR *wDevicePath = L"\\\\?\\usb#vid_0c45&pid_636d&mi_00#6&3171a958&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global";
	
	// Failed to open camera device����ֵ��ͨ��EnumerateUsbHubNode������ȡ�����ģ�
	//WCHAR *wDevicePath = L"\\\\.\\USBPDO-14";
	
	// Device Descriptor is null����ֵ��ͨ��UsbTreeView.exe��ȡ�����ģ�
	WCHAR *wDevicePath = L"\\\\?\\usb#vid_0c45&pid_636d#sn0001#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	HANDLE hCamera = CreateFile(wDevicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCamera == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open camera device." << std::endl;
		return 1;
	}

	// 2�����Ϳ������ȡ�豸���������������㿴IOCTL_CUSTOM_GET_DEVICE_DESCRIPTOR�������Զ����IO��������ô���ܻ��ȡ�豸��������
	WCHAR descBuffer[MAX_PATH] = { 0 };
	DWORD bytesReturned;
	if (DeviceIoControl(hCamera, IOCTL_CUSTOM_GET_DEVICE_DESCRIPTOR, NULL, 0, descBuffer, sizeof(descBuffer), &bytesReturned, NULL)) {
		LOGE("DeviceIoControl1 Success(0x%X)\r\n", GetLastError());
		LOGI("%ws\n", descBuffer);
		std::wcout << "Device Descriptor: " << descBuffer << std::endl;
	}
	else {
		LOGE("DeviceIoControl1 Fail(0x%X)\r\n", GetLastError());
		std::cout << "Failed to get device descriptor." << std::endl;
	}

	// 3���ر��豸���
	CloseHandle(hCamera);
	return 0;
}

// �Զ�����������ͨ�Ż�ȡ�豸��������Ϣ
static int Test()
{
	HANDLE hCamera = OpenMonitorDriver();
	assert(hCamera);
	CAMERADEVICEITEM device = { 0 };
	CHAR *tmp = "\\Device\\USBPDO-14";
	//memcpy(device.DeviceName, tmp, strlen(tmp));
	mbstowcs_s(NULL, device.DeviceName, MAX_PATH, tmp, _TRUNCATE);
	LOGI("device.DeviceName: %ws\n", device.DeviceName);
	GetDeviceDesc(device);
	return 0;
}

// ����̽��1
static int GetVideoDeviceDescriptor1()
{
	printf("%s:%d\n", __FUNCTION__, __LINE__);
	// ��ֵ��ͨ��UsbTreeView.exe��ȡ�����ģ�
	WCHAR *wDevicePath = L"\\\\?\\usb#vid_0c45&pid_636d#sn0001#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	HANDLE hCamera = CreateFile(wDevicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCamera == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open camera device." << std::endl;
		return 1;
	}

	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	// ��ʼ���豸��Ϣ����GUID_DEVCLASS_IMAGE/GUID_DEVCLASS_MEDIA��������������û�л�ȡ������ͷ�豸��
	hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_MEDIA, 0, 0, DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("SetupDiGetClassDevs failed: %x\n", GetLastError());
		return 1;
	}

	// �������ȷ�Ĳ���
	hDevInfo = SetupDiGetClassDevs(&KSCATEGORY_CAPTURE,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (INVALID_HANDLE_VALUE == hDevInfo)
	{
		LOGE("SetupDiGetClassDevs FAILED\r\n");
		return -1;
	}

	// ö���豸
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	// ����ö���豸��Ϣ�����е��豸��������һ���豸��Ϣ���ϵľ����һ������ֵ��Ϊ������Ȼ�󷵻�ָ������λ�õ��豸��Ϣ
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		// ��ȡ�豸��������Ϣ
		DWORD DataT;
		LPTSTR buffer = NULL;
		DWORD buffersize = 0;

		// ���ڻ�ȡ�豸��ע�������ֵ���������豸��Ϣ���ϵľ�����豸��Ϣ���ݽṹ�����Ա�ʶ�����������ͺ�����������Ȳ���
		while (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, &DataT, (PBYTE)buffer, buffersize, &buffersize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer) LocalFree(buffer);
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize);
			}
			else
			{
				break;
			}
		}

		if (buffer)
		{
			printf("Device Description: %ls\r\n", buffer);
			printf("ClassGuid: %lu %d %d\n", DeviceInfoData.ClassGuid.Data1, DeviceInfoData.ClassGuid.Data2,
				DeviceInfoData.ClassGuid.Data3);
			LocalFree(buffer);
		}
	}

	// �ͷ��豸��Ϣ����
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

/*
Ҫ��ȡ����ͷ�豸���豸��������Ϣ������ʹ�����²��裺
1��������ͷ�豸������ʹ��CreateFile���������豸�������豸���ƻ��豸·����Ϊ���������磬�豸���ƿ�����"\\.\Video0"��
2����ȡ�豸�ӿ�GUID������ʹ��SetupDiGetClassDevs��������ȡ�豸�ӿ���Ϣ����������ͷ�豸����GUID��Ϊ���������磬����ͷ�豸����GUID��GUID_DEVINTERFACE_CAMERA��
3��ö���豸�ӿڡ�ʹ��SetupDiEnumDeviceInterfaces������ö���豸�ӿڣ������豸�ӿ���Ϣ���豸�ӿ�GUID��Ϊ������
4����ȡ�豸�ӿ���ϸ��Ϣ��ʹ��SetupDiGetDeviceInterfaceDetail��������ȡ�豸�ӿ���ϸ��Ϣ�������豸�ӿ���Ϣ��һ��SP_DEVICE_INTERFACE_DETAIL_DATA�ṹ����Ϊ������
5�����豸�ӿڡ�ʹ��CreateFile���������豸�ӿڣ������豸�ӿ���ϸ��Ϣ�е��豸·����Ϊ������
6����ȡ�豸��������Ϣ��ʹ��DeviceIoControl����������IO������IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION�������豸�ӿڵľ����һ��USB_DESCRIPTOR_REQUEST�ṹ����Ϊ��������USB_DESCRIPTOR_REQUEST�ṹ���У�����bRequestΪUSB_REQUEST_GET_DESCRIPTOR��wValueΪUSB_DEVICE_DESCRIPTOR_TYPE��wIndexΪ0��wLengthΪ�豸�������ĳ��ȡ�
7�������豸��������Ϣ�������豸�������ĸ�ʽ�������豸��������Ϣ�������豸�Ĺ�Ӧ��ID����ƷID���汾�ŵȡ�
*/
static int GetVideoDeviceDescriptor2()
{
	printf("========  %s:%d  ========\n", __FUNCTION__, __LINE__);
	// ��ֵ��ͨ��UsbTreeView.exe��ȡ�����ģ�
	WCHAR *wDevicePath = L"\\\\?\\usb#vid_0c45&pid_636d#sn0001#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";


	BOOL                             ret = FALSE;
	DWORD                            dwIndex = 0;
	PSP_DEVICE_INTERFACE_DETAIL_DATA pInterData = NULL;
	SP_DEVICE_INTERFACE_DATA         spDevInterfaceData = { 0 };
	SP_DEVINFO_DATA                  spDevInfoData = { 0 };
	HDEVINFO                         hDevInfo = INVALID_HANDLE_VALUE;

	// 1����ȡ�豸�ӿ�GUID
	hDevInfo = SetupDiGetClassDevs(&KSCATEGORY_CAPTURE,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (INVALID_HANDLE_VALUE == hDevInfo)
	{
		LOGE("SetupDiGetClassDevs FAILED\r\n");
		return -1;
	}

	// 2��ö���豸�ӿ�
	ZeroMemory(&spDevInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
	spDevInterfaceData.cbSize = sizeof(spDevInterfaceData);
	while (!ret && SetupDiEnumDeviceInterfaces(hDevInfo, NULL,
		&KSCATEGORY_CAPTURE, dwIndex, &spDevInterfaceData))
	{
		// 3����ȡ�豸�ӿ���ϸ��Ϣ���Ȼ�ȡ�ӿ���Ϣ���ȣ�
		DWORD dwReqSize = 0;
		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo,
			&spDevInterfaceData,
			NULL,
			0,
			&dwReqSize,
			NULL) && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			LOGE("SetupDiGetDeviceInterfaceDetail failed:%d(0x%08x)\r\n",
				GetLastError(), GetLastError());
		}

		// 4����ȡ�豸�ӿ���ϸ��Ϣ
		printf("interface dwReqSize: %lu\n", dwReqSize);
		pInterData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)calloc(1, dwReqSize);
		if (!pInterData)
		{
			LOGE("allocate memeory for pInterData failed\r\n");
			SetupDiDestroyDeviceInfoList(hDevInfo);
			return -1;
		};
		memset(pInterData, 0, dwReqSize);
		pInterData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		ZeroMemory(&spDevInfoData, sizeof(SP_DEVINFO_DATA));
		spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		if (SetupDiGetDeviceInterfaceDetail(hDevInfo,
			&spDevInterfaceData,
			pInterData,
			dwReqSize,
			NULL,
			&spDevInfoData))
		{
			printf("DevInst: %lu\n", spDevInfoData.DevInst);
			printf("DevicePath: %ls\n", pInterData->DevicePath);

			// 5�����豸�ӿ�
			HANDLE hCamera = CreateFile(wDevicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hCamera == INVALID_HANDLE_VALUE) {
				std::cout << "Failed to open camera device." << std::endl;
				return -1;
			}

			// 6��DeviceIoControlͨ�Ż�ȡ�豸��������Ϣ
#if 1
			for (int index = 0; index <= 30; index++)
			{
				// ����USB_NODE_CONNECTION_INFORMATION_EX�ṹ��
				USB_NODE_CONNECTION_INFORMATION_EX connectionInfoEx = { 0 };
				connectionInfoEx.ConnectionIndex = index; // USB�ڵ���������
				ULONG nBytesReturned = 0;
				ULONG nBytesEx = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) +
					(sizeof(USB_PIPE_INFO) * 30);
				// ʹ��DeviceIoControl��������IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION������
				if (DeviceIoControl(hCamera,
					IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
					&connectionInfoEx,
					nBytesEx,
					&connectionInfoEx,
					nBytesEx,
					&nBytesEx,
					NULL)) {
					// ��descriptorBuffer�л�ȡ�豸�������������Ϣ
					// �����豸����������
					printf("get device descriptor success\n");
					printf("%04x:%04x\n", connectionInfoEx.DeviceDescriptor.idVendor,
						connectionInfoEx.DeviceDescriptor.idProduct);
					printf("speed: %d\n", connectionInfoEx.Speed);	// UsbHighSpeed

				}
				else
				{
					// �����ȡ�豸������ʧ�ܵ����
					printf("get device descriptor failed\n");
				}
			}
#endif
#if 0
			// ����USB_NODE_CONNECTION_INFORMATION_EX�ṹ��
			USB_NODE_CONNECTION_INFORMATION_EX connectionInfo = { 0 };
			connectionInfo.ConnectionIndex = 0x0F; // USB�ڵ���������
			// ����USB_DESCRIPTOR_REQUEST�ṹ��
			USB_DESCRIPTOR_REQUEST deviceDescReq;
			deviceDescReq.ConnectionIndex = connectionInfo.ConnectionIndex;
			deviceDescReq.SetupPacket.wValue = 0x0100; // �豸���������ͺ�����
			deviceDescReq.SetupPacket.wIndex = 0x0409; // ����ID
			deviceDescReq.SetupPacket.wLength = 18;    // �豸����������
			ULONG nBytesReturned = 0;
			//PUSB_DEVICE_DESCRIPTOR deviceDesc = (PUSB_DEVICE_DESCRIPTOR)malloc(sizeof(USB_DEVICE_DESCRIPTOR));
			PUSB_DEVICE_DESCRIPTOR deviceDesc = (PUSB_DEVICE_DESCRIPTOR)(&deviceDescReq + 1);
			//memset(deviceDesc, 0, sizeof(USB_DEVICE_DESCRIPTOR));
			BOOL result = DeviceIoControl(hCamera,
				IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
				&deviceDescReq,
				sizeof(USB_DESCRIPTOR_REQUEST),
				deviceDesc,
				sizeof(deviceDesc),
				&nBytesReturned,
				NULL);
			if (result)
			{
				printf("get device descriptor success\n");
				printf("success: nBytesReturned %d bDescriptorType %02x bLength %d\n",
					nBytesReturned, deviceDesc->bDescriptorType, deviceDesc->bLength);
				printf("%04x:%04x\n", connectionInfo.DeviceDescriptor.idVendor,
					connectionInfo.DeviceDescriptor.idProduct);
			}
			else
			{
				printf("get device descriptor failed\n");
			}
#endif
#if 0
			UCHAR stringDescReqBuf[sizeof(USB_DESCRIPTOR_REQUEST) + MAXIMUM_USB_STRING_LENGTH];
			ULONG nBytes = sizeof(stringDescReqBuf);
			PUSB_DESCRIPTOR_REQUEST stringDescReq = (PUSB_DESCRIPTOR_REQUEST)stringDescReqBuf;
			memset(stringDescReq, 0, nBytes);
			stringDescReq->ConnectionIndex = 0x0F;
			stringDescReq->SetupPacket.wValue = (USB_STRING_DESCRIPTOR_TYPE << 8) | 0x01;
			stringDescReq->SetupPacket.wIndex = 0x0409;
			stringDescReq->SetupPacket.wLength = (USHORT)(nBytes - sizeof(USB_DESCRIPTOR_REQUEST));

			PUSB_STRING_DESCRIPTOR stringDesc = (PUSB_STRING_DESCRIPTOR)(stringDescReq + 1);
			ULONG nBytesReturned = 0;
			BOOL success = DeviceIoControl(hCamera,
				IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
				stringDescReq,
				nBytes,
				stringDescReq,
				nBytes,
				&nBytesReturned,
				NULL);
			if (success)
			{
				printf("success\n");
				if (nBytesReturned < 2 || stringDesc->bDescriptorType != USB_STRING_DESCRIPTOR_TYPE ||
					stringDesc->bLength != nBytesReturned - sizeof(USB_DESCRIPTOR_REQUEST) ||
					stringDesc->bLength % 2 != 0)
				{
					printf("failed: nBytesReturned %d bDescriptorType %02x bLength %d\n",
						nBytesReturned, stringDesc->bDescriptorType, stringDesc->bLength);
				}
				else
				{
					for (int i = 0; i < stringDesc->bLength; i++)
					{
						printf("%02x%c", stringDesc[i], i == stringDesc->bLength - 1 ? '\n' : ' ');
					}
				}
			}
			else
			{
				printf("failed\n");
			}
#endif
		}

		free(pInterData);
		pInterData = NULL;

		ZeroMemory(&spDevInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
		spDevInterfaceData.cbSize = sizeof(spDevInterfaceData);
		dwIndex++;
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

#include <usbiodef.h>
#include <initguid.h>
#pragma comment(lib, "winusb.lib")
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, \
	0xC0, 0x4F, 0xB9, 0x51, 0xED);
static int EnumerateAllUsbDevices()
{
	printf("========  %s:%d  ========\n", __FUNCTION__, __LINE__);
	// ��ȡ����USB�豸���豸��Ϣ
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, 0, 0,
											DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("SetupDiGetClassDevs failed (%d)\n", GetLastError());
		return 1;
	}

	// ö������USB�豸
	SP_DEVINFO_DATA DeviceInfoData;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD DataT;
		WCHAR buf[MAX_PATH] = { 0 };
		DWORD bufSize = sizeof(buf);

		// ��ȡ�豸����
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, &DataT, (PBYTE)buf, bufSize, NULL))
		{
			printf("�豸����: %ws\n", buf);
		}
	}
	return 0;
}

int main()
{
	// 1����ٱ������е��豸
	DEVINST   rootDevInst;
	CONFIGRET cr;
	cr = CM_Locate_DevNode(&rootDevInst, NULL, 0);	// ���ڶ�λָ���豸ʵ�����豸�ڵ�
	if (CR_SUCCESS != cr)
	{
		LOGE("CM_Locate_DevNode FAILED, Error code is %d\n", cr);
		return -1;
	}
	EnumerateUsbHubNode(rootDevInst);

	//OpenCameraDevice();
	CustomDriverCommunication();
	//Test();
	//GetVideoDeviceDescriptor2();
	EnumerateAllUsbDevices();
	return 0;
}
