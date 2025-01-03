// MonitorRegistry.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>

#define REGISTRY_PATH "SYSTEM\\CurrentControlSet\\Services\\usbhub"
#define START_VALUE_NAME "Start"
#define TARGET_VALUE 3

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Advapi32.lib")

HWND g_hWnd = NULL;

// ����ö�ٻص�����
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title[256];
	GetWindowTextA(hwnd, title, sizeof(title));

	// ��鴰�ڱ����Ƿ���� "Process Monitor"
	if (strstr(title, "Process Monitor") != NULL)
	{
		g_hWnd = hwnd; // �ҵ����ڣ�������
		return FALSE;  // �ҵ���ֹͣö��
	}
	return TRUE; // ����ö��
}

// һ��Ҫ����ԱȨ�����У������͵İ�������Ч
void SendCtrlE()
{
	// ö�����д��ڲ��� Process Monitor
	EnumWindows(EnumWindowsProc, 0);

	if (g_hWnd == NULL) {
		printf("Process Monitor is not running.\n");
		return;
	}

	// �����
	SetForegroundWindow(g_hWnd);
	Sleep(1000); // ȷ��������ʱ�伤��

	if (0)
	{
		// ���� Ctrl + E ����
		keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl
		keybd_event('E', 0, 0, 0);        // ���� E

		// �����ͷ��¼�
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0); // �ͷ� E
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl
	}
	else
	{
		// ���� Ctrl + E ����
		INPUT inputs[4] = { 0 };

		// ���� Ctrl ��
		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = VK_CONTROL;

		// ���� E ��
		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = 'E';

		// �ͷ� E ��
		inputs[2].type = INPUT_KEYBOARD;
		inputs[2].ki.wVk = 'E';
		inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

		// �ͷ� Ctrl ��
		inputs[3].type = INPUT_KEYBOARD;
		inputs[3].ki.wVk = VK_CONTROL;
		inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

		// ��������
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	}

	printf("Sent Ctrl + E to Process Monitor.\n");
	return;
}

void CopyFileWithTimestamp()
{
	const char* sourceFilePath = "procmon.PML";

	// ��ȡ��ǰ����Ŀ¼
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);
	printf("Current working directory: %s\n", currentDir);

	// ��ȡ��ǰʱ��
	time_t rawtime;
	struct tm timeinfo;
	char timestamp[20];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	// ��ʽ��ʱ���Ϊ "YYYYMMDD_HHMMSS"
	strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", &timeinfo);

	// ����Ŀ���ļ���
	char targetFilePath[MAX_PATH] = { 0 };
	snprintf(targetFilePath, sizeof(targetFilePath), "%s_%s", timestamp, sourceFilePath);

	// �ж��ļ��Ƿ����
	if (_access(sourceFilePath, 0) != 0)
	{
		printf("sourceFilePath: %s does not exist.\n", sourceFilePath);
		return;
	}

	// �����ļ�
	if (CopyFileA(sourceFilePath, targetFilePath, FALSE)) {
		printf("%s File copied to: %s\n", sourceFilePath, targetFilePath);
	}
	else {
		printf("%s Failed to copy file to %s. Error: %lu\n", sourceFilePath, targetFilePath, GetLastError());
	}
	return;
}

void ShowMessageBox(const char* message)
{
	CopyFileWithTimestamp();
	SendCtrlE();
	MessageBoxA(NULL, message, "�����ƾ���", MB_OK | MB_ICONWARNING | MB_TOPMOST);
	return;
}

int CheckRegistry()
{
	HKEY hKey;
	LONG result;

	// ��ע�����
	result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, REGISTRY_PATH, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS)
	{
		// ע��������
		ShowMessageBox("ע��������: " REGISTRY_PATH);
		return 0; // ��ʾ������
	}

	DWORD startValue;
	DWORD valueType;
	DWORD valueSize = sizeof(startValue);

	// ��ѯ Start ֵ
	result = RegQueryValueExA(hKey, START_VALUE_NAME, NULL, &valueType, (LPBYTE)&startValue, &valueSize);
	RegCloseKey(hKey);

	if (result != ERROR_SUCCESS || valueType != REG_DWORD)
	{
		// Start ֵ�����ڻ����Ͳ���ȷ
		ShowMessageBox("����Start ֵ�����ڻ����Ͳ���ȷ");
		return 0; // ��ʾ�쳣
	}

	// ��� Start ֵ�Ƿ�Ϊ 3
	if (startValue != TARGET_VALUE)
	{
		ShowMessageBox("����Start ֵ�쳣: ���� 3");
		return 0; // ��ʾ�쳣
	}

	return 1; // ��ʾ����
}

int main()
{
	printf("��ʼ���usbhub����......\n");
	while (1)
	{
		// ���ע���
		if (!CheckRegistry())
		{
			break;
		}
		Sleep(2000); // ÿ 2 ����һ��
	}
	system("pause");
    return 0;
}

