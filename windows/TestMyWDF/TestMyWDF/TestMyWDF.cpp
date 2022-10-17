// TestMyWDF.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#define MYDEVICE L"\\\\.\\MyWDF_LINK"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hDevice = CreateFile(MYDEVICE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Failed to open device %s, err: %x\n", MYDEVICE, GetLastError());
	}
	else
	{
		wprintf(L"Open device %s successfully\n", MYDEVICE);
		CloseHandle(hDevice);

		wprintf(L"Closed handle\n");
	}

	return 0;
}


