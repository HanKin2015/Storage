// MonitorRegistry.cpp : 定义控制台应用程序的入口点。
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

// 窗口枚举回调函数
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title[256];
	GetWindowTextA(hwnd, title, sizeof(title));

	// 检查窗口标题是否包含 "Process Monitor"
	if (strstr(title, "Process Monitor") != NULL)
	{
		g_hWnd = hwnd; // 找到窗口，保存句柄
		return FALSE;  // 找到后停止枚举
	}
	return TRUE; // 继续枚举
}

// 一定要管理员权限运行，否则发送的按键不生效
void SendCtrlE()
{
	// 枚举所有窗口查找 Process Monitor
	EnumWindows(EnumWindowsProc, 0);

	if (g_hWnd == NULL) {
		printf("Process Monitor is not running.\n");
		return;
	}

	// 激活窗口
	SetForegroundWindow(g_hWnd);
	Sleep(1000); // 确保窗口有时间激活

	if (0)
	{
		// 发送 Ctrl + E 按键
		keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl
		keybd_event('E', 0, 0, 0);        // 按下 E

		// 发送释放事件
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0); // 释放 E
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 释放 Ctrl
	}
	else
	{
		// 发送 Ctrl + E 按键
		INPUT inputs[4] = { 0 };

		// 按下 Ctrl 键
		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = VK_CONTROL;

		// 按下 E 键
		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = 'E';

		// 释放 E 键
		inputs[2].type = INPUT_KEYBOARD;
		inputs[2].ki.wVk = 'E';
		inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

		// 释放 Ctrl 键
		inputs[3].type = INPUT_KEYBOARD;
		inputs[3].ki.wVk = VK_CONTROL;
		inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

		// 发送输入
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	}

	printf("Sent Ctrl + E to Process Monitor.\n");
	return;
}

void CopyFileWithTimestamp()
{
	const char* sourceFilePath = "procmon.PML";

	// 获取当前工作目录
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);
	printf("Current working directory: %s\n", currentDir);

	// 获取当前时间
	time_t rawtime;
	struct tm timeinfo;
	char timestamp[20];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	// 格式化时间戳为 "YYYYMMDD_HHMMSS"
	strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", &timeinfo);

	// 构建目标文件名
	char targetFilePath[MAX_PATH] = { 0 };
	snprintf(targetFilePath, sizeof(targetFilePath), "%s_%s", timestamp, sourceFilePath);

	// 判断文件是否存在
	if (_access(sourceFilePath, 0) != 0)
	{
		printf("sourceFilePath: %s does not exist.\n", sourceFilePath);
		return;
	}

	// 复制文件
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
	MessageBoxA(NULL, message, "桌面云警告", MB_OK | MB_ICONWARNING | MB_TOPMOST);
	return;
}

int CheckRegistry()
{
	HKEY hKey;
	LONG result;

	// 打开注册表项
	result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, REGISTRY_PATH, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS)
	{
		// 注册表项不存在
		ShowMessageBox("注册表项不存在: " REGISTRY_PATH);
		return 0; // 表示不存在
	}

	DWORD startValue;
	DWORD valueType;
	DWORD valueSize = sizeof(startValue);

	// 查询 Start 值
	result = RegQueryValueExA(hKey, START_VALUE_NAME, NULL, &valueType, (LPBYTE)&startValue, &valueSize);
	RegCloseKey(hKey);

	if (result != ERROR_SUCCESS || valueType != REG_DWORD)
	{
		// Start 值不存在或类型不正确
		ShowMessageBox("服务Start 值不存在或类型不正确");
		return 0; // 表示异常
	}

	// 检查 Start 值是否为 3
	if (startValue != TARGET_VALUE)
	{
		ShowMessageBox("服务Start 值异常: 不是 3");
		return 0; // 表示异常
	}

	return 1; // 表示正常
}

int main()
{
	printf("开始监控usbhub服务......\n");
	while (1)
	{
		// 检查注册表
		if (!CheckRegistry())
		{
			break;
		}
		Sleep(2000); // 每 2 秒检查一次
	}
	system("pause");
    return 0;
}

