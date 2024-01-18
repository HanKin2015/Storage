
/********************************************************************
 *	@file:		ע�������Ĺ���ʵ��
 *	@author:	xb
 *	@date:		2022/11/17
 *	@brief:		ע�������Ĺ���ʵ��
*********************************************************************/

#include "registryhelper.h"
#if _MSC_VER < 1400		// VS2005����VS�汾
#include "sflog_vc6_helper.h"
#else
#include "sflog_helper.h"
#endif

/*
*	@brief ��������Ϊ���͵�ע���
*	@param [in]hRootKey	root��ֵ��HKEY_LOCAL_MACHINE��HKEY_CURRENT_USER
*	@param [in] lpAppName	ע���·��
*	@param [in] lpKeyName	����
*	@param [in] lpszValue	Ҫд���ֵ
*	@return �ɹ�����true��ʧ�ܷ���false
*/
BOOL RegConfigSetUint(const HKEY hRootKey,
	const char * lpAppName,
	const char * lpKeyName,
	UINT32 nValue)
{
	if (NULL == hRootKey || NULL == lpAppName || NULL == lpKeyName)
	{
		LOG_ERROR("Param error.");
		return false;
	}

	HKEY  hKey = NULL;
	DWORD dwDisp = 0;
	if (RegCreateKeyExA(hRootKey, lpAppName,
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_WRITE | KEY_WOW64_32KEY, NULL, &hKey, &dwDisp) != ERROR_SUCCESS)
	{
		LOG_ERROR("RegCreateKeyExA failed, PathName(%s)", lpAppName);
		return false;
	}

	if (RegSetValueExA(hKey, 
		lpKeyName, 
		0, 
		REG_DWORD,  
		(LPBYTE)&nValue, 
		sizeof(DWORD)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		LOG_ERROR("RegSetValueExA failed, KeyName(%s)", lpKeyName);
		return false;
	}
	
	RegFlushKey(hKey);

	RegCloseKey(hKey);
	return true;
}

/*
*	@brief �õ�����Ϊ���ε�ע���
*	@param [in]hRootKey	root��ֵ��HKEY_LOCAL_MACHINE��HKEY_CURRENT_USER
*	@param [in] lpAppName	ע���·��
*	@param [in] lpKeyName	����
*	@param [in] nDefault	Ĭ��ֵ
*	@return ���ض�ȡ����ֵ
*/
UINT32 RegConfigGetUint(const HKEY hRootKey,
	const char* lpAppName,
	const char* lpKeyName,
	UINT32 nDefault)
{
	DWORD dwValue = nDefault;
	if (NULL == hRootKey || NULL == lpAppName || NULL == lpKeyName)
	{
		LOG_ERROR("Param error.");
		return dwValue;
	}

	HKEY hkey = NULL;
	LONG lRes = ::RegOpenKeyExA(hRootKey, lpAppName, 0,
		KEY_READ | KEY_WOW64_32KEY, &hkey);
	if (lRes == ERROR_SUCCESS)
	{
		DWORD dwType = REG_NONE;
		DWORD nBytes = sizeof(DWORD);
		lRes = ::RegQueryValueExA(hkey, lpKeyName, NULL, &dwType,
			reinterpret_cast<LPBYTE>(&dwValue), &nBytes);
		if (lRes != ERROR_SUCCESS || dwType != REG_DWORD)
		{
			dwValue = nDefault;
			LOG_ERROR("RegQueryValueExA failed, PathName(%s) KeyName(%s) err(%ld)", 
				lpAppName, lpKeyName, lRes);
		}
		::RegCloseKey(hkey);
	}
	else
	{
		LOG_ERROR("RegOpenKeyExA failed, PathName(%s) err(%ld)", lpAppName, lRes);
	}
	
	return dwValue;
}

/*
*	@brief ��ȡ����Ϊ�ַ�����ע���
*	@param  [in]hRootKey		root��ֵ��HKEY_LOCAL_MACHINE��HKEY_CURRENT_USER
*	@param [in] lpAppName		ע���·��
*	@param [in] lpKeyName		����
*	@param [in] lpDefault		Ĭ��ֵ
*	@param [in&out] lpszValue	��ȡ�ַ���ֵ�Ļ�����
*	@param [in] nSize			��������С
*	@return ����д��lpszValue���ַ�������
*/
UINT32 __cdecl RegConfigGetString(const HKEY hRootKey,
	const char * lpAppName,
	const char * lpKeyName,
	const char * lpDefault,
	char * lpszValue,
	UINT32 nSize)
{
	if (NULL == hRootKey  || NULL == lpAppName || 
		NULL == lpKeyName || NULL == lpszValue || 0 == nSize)
	{
		LOG_ERROR("Param error.");
		return 0;
	}

	if (NULL == lpDefault)
	{
		lpDefault = "";
	}
	DWORD dwType = REG_NONE;
	ULONG nBytes = (nSize) * sizeof(char);
	bool bRet = false;
	HKEY hkey = NULL;
	LONG lRes = ::RegOpenKeyExA(hRootKey, lpAppName,
		0, KEY_READ | KEY_WOW64_32KEY, &hkey);
	if (lRes != ERROR_SUCCESS)
	{
		LOG_ERROR("RegOpenKeyExA failed, PathName(%s) err(%ld)", lpAppName, lRes);
		goto _fin;
	}

	lRes = ::RegQueryValueExA(hkey, lpKeyName, NULL, &dwType,
		reinterpret_cast<LPBYTE>(lpszValue), &nBytes);

	if (lRes != ERROR_SUCCESS)
	{
		LOG_ERROR("RegQueryValueExA failed, PathName(%s) KeyName(%s) err(%ld)",
			lpAppName, lpKeyName, lRes);
		goto _fin;
	}

	if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		LOG_ERROR("The type queried is not REG_SZ and REG_EXPAND_SZ");
		goto _fin;
	}

	if (nBytes == 0)
	{
		LOG_ERROR("The size queried is 0");
		goto _fin;
	}

	bRet = true;
_fin:

	if (!bRet)
	{
		(void)StringCchCopyA(lpszValue, nSize, lpDefault);
	}

	if (hkey)
	{
		::RegCloseKey(hkey);
		hkey = NULL;
	}
	return lstrlenA(lpszValue);
}