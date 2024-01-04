// CallDllFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <WinBase.h>
#include <libloaderapi.h>
#include <strsafe.h>

DWORD config_get_uint(
	const char* lpAppName,
	const char* lpKeyName,
	DWORD dwDefault
)
{
	DWORD dwValue = dwDefault;
	if (lpAppName != NULL && lpKeyName != NULL)
	{
		HKEY hkey = NULL;
		LONG lRes = ::RegOpenKeyExA(
			HKEY_LOCAL_MACHINE,
			lpAppName,
			0,
			KEY_READ | KEY_WOW64_32KEY,
			&hkey
		);
		if (lRes == ERROR_SUCCESS)
		{
			DWORD dwType = REG_NONE;
			DWORD nBytes = sizeof(DWORD);
			lRes = ::RegQueryValueExA(
				hkey,
				lpKeyName,
				NULL,
				&dwType,
				reinterpret_cast<LPBYTE>(&dwValue),
				&nBytes
			);
			if (lRes != ERROR_SUCCESS || dwType != REG_DWORD)
			{
				dwValue = dwDefault;
			}
			::RegCloseKey(hkey);
			hkey = NULL;
		}
	}
	return dwValue;
}

DWORD __cdecl config_get_string(
	const char* lpAppName,
	const char* lpKeyName,
	const char* lpDefault,
	char* lpszValue,
	DWORD nSize
)
{
	if (NULL == lpAppName || NULL == lpKeyName ||
		NULL == lpszValue || 0 == nSize)
	{
		return 0;
	}

	if (NULL == lpDefault)
	{
		lpDefault = "";
	}

	HKEY hkey = NULL;
	LONG lRes = ::RegOpenKeyExA(
		HKEY_LOCAL_MACHINE,
		lpAppName,
		0,
		KEY_READ | KEY_WOW64_32KEY,
		&hkey
	);
	if (lRes != ERROR_SUCCESS)
	{
		(void)StringCchCopyA(lpszValue, nSize, lpDefault);
		return lstrlenA(lpszValue);
	}

	ULONG nBytes = (nSize) * sizeof(char);
	DWORD dwType = REG_NONE;
	lRes = ::RegQueryValueExA(
		hkey,
		lpKeyName,
		NULL,
		&dwType,
		reinterpret_cast<LPBYTE>(lpszValue), &nBytes);
	::RegCloseKey(hkey);
	if (lRes != ERROR_SUCCESS)
	{
		(void)StringCchCopyA(lpszValue, nSize, lpDefault);
		return lstrlenA(lpszValue);
	}

	if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		(void)StringCchCopyA(lpszValue, nSize, lpDefault);
		return lstrlenA(lpszValue);
	}

	if (lpszValue != NULL && nBytes == 0)
	{
		(void)StringCchCopyA(lpszValue, nSize, lpDefault);
		return lstrlenA(lpszValue);
	}

	if (lpszValue != NULL)
	{
		if (nBytes != 0)
		{
			if ((nBytes % sizeof(char) != 0) ||
				(lpszValue[nBytes / sizeof(char) - 1] != 0))
			{
				(void)StringCchCopyA(lpszValue, nSize, lpDefault);
				return lstrlenA(lpszValue);
			}
		}
		else
		{
			(void)StringCchCopyA(lpszValue, nSize, lpDefault);
			return lstrlenA(lpszValue);
		}
	}
	printf("%s\n%s\n", lpAppName, lpKeyName);
	return lstrlenA(lpszValue);
}

// 查询关机清理分页内存策略相关宏
#define MEMORY_MANAGEMENT_PATH		"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management"
#define CLEAR_PAGEFILE_ATSHUTDOWN	"ClearPageFileAtShutdown"

#define REG_SSL_VDI_KEY_PATHA                  "SOFTWARE\\Test\\SOS\\HANKIN"
#define REG_NAME_LOGPATHA                      "LogPath"
#define PAGENT_DLL_LOGNAMEA                    "calldllfile.dll.log"

int main()
{
	BOOL bRet = FALSE;
	//HMODULE hPagentDll = LoadLibraryA("pagent.dll");
	HMODULE hPagentDll = LoadLibraryA("D:\\Users\\User\\Desktop\\不清楚中文有影响不\\calldllfile.dll");
	if (!hPagentDll)
	{
		printf("LoadLibrary pagent dll失败！错误码：%lu\n", GetLastError());
		return -1;
	}

	typedef ULONG(*FN_InitBaseEnv)();
	FN_InitBaseEnv InitBaseEnv = (FN_InitBaseEnv)GetProcAddress(hPagentDll, "InitBaseEnv");
	if (InitBaseEnv)
	{
		bRet = InitBaseEnv();
		printf("bRet = %d\n", bRet);
	}

	typedef BOOL(*FN_IsClearPageFileAtShutdown)(BOOL& bClearPageFile);
	FN_IsClearPageFileAtShutdown IsClearPageFileAtShutdown = (FN_IsClearPageFileAtShutdown)GetProcAddress(hPagentDll, "IsClearPageFileAtShutdown");
	if (IsClearPageFileAtShutdown)
	{
		char szLogPath[MAX_PATH + 1] = { 0 };
		if (config_get_string(
			REG_SSL_VDI_KEY_PATHA,
			REG_NAME_LOGPATHA,
			NULL,
			(char*)szLogPath,
			MAX_PATH) > 0)
		{
			printf("%s\n", szLogPath);
		}

		BOOL bClearPageFile = TRUE;
		printf("before %d\n", bClearPageFile);
		bRet = IsClearPageFileAtShutdown(bClearPageFile);
		printf("IsClearPageFileAtShutdown bRet %d bClearPageFile %d\n", bRet, bClearPageFile);
		bClearPageFile = (BOOL)config_get_uint(MEMORY_MANAGEMENT_PATH, CLEAR_PAGEFILE_ATSHUTDOWN, 1);
		printf("config_get_uint bClearPageFile %d\n", bClearPageFile);

		bClearPageFile = FALSE;
		printf("before %d\n", bClearPageFile);
		bRet = IsClearPageFileAtShutdown(bClearPageFile);
		printf("IsClearPageFileAtShutdown bRet %d bClearPageFile %d\n", bRet, bClearPageFile);
		bClearPageFile = (BOOL)config_get_uint(MEMORY_MANAGEMENT_PATH, CLEAR_PAGEFILE_ATSHUTDOWN, 1);
		printf("config_get_uint bClearPageFile %d\n", bClearPageFile);
	}

	FreeLibrary(hPagentDll);
	system("pause");
    return 0;
}

