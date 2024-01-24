/*
========  GetSerialDevices:225  ========
USB\VID_067B&PID_2303&REV_0300
USB\VID_067B&PID_2303
Device #0: 000000A2BC3AA250
*/
static int GetSerialDevices()
{
	printf("========  %s:%d  ========\n", __FUNCTION__, __LINE__);

	HDEVINFO deviceInfoSet;
	SP_DEVINFO_DATA deviceInfoData;
	DWORD i;

	// 获取设备信息集合，这里指定GUID_DEVINTERFACE_COMPORT，GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR表示我们只关心串口设备
	deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (deviceInfoSet == INVALID_HANDLE_VALUE) {
		std::cerr << "SetupDiGetClassDevs failed." << std::endl;
		return 1;
	}

	// 初始化SP_DEVINFO_DATA
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
		DWORD DataT;
		wchar_t buffer[4096] = { 0 };
		DWORD buffersize = 0;

		// 首先获取设备描述的长度
		while (!SetupDiGetDeviceRegistryProperty(
			deviceInfoSet,
			&deviceInfoData,
			SPDRP_HARDWAREID,
			&DataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			
		}
		wchar_t* p = buffer;
		for (; *p != TEXT('\0') && p + buffersize / sizeof(char) <= buffer + ARRAYSIZE(buffer); p += lstrlen(p) + 1)
		{
			_tprintf(TEXT("%s\n"), p);
		}

		std::cout << "Device #" << i << ": " << buffer << std::endl;
	}

	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_NO_MORE_ITEMS) {
		std::cerr << "SetupDiEnumDeviceInfo failed." << std::endl;
		return 1;
	}

	// 清理
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
	return 0;
}