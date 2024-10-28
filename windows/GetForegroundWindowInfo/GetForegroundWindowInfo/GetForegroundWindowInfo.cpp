// GetForegroundWindowInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <psapi.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Psapi.lib")

void GetProcessName(DWORD processID, LPWSTR processName)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed.\n");
		return;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32)) {
		printf("Process32First failed.\n"); // Show cause of failure
		CloseHandle(hProcessSnap);          // Clean the snapshot object
		return;
	}

	// Now walk the snapshot of processes
	do {
		if (pe32.th32ProcessID == processID) {
			printf("Process name: %ls\n", pe32.szExeFile);
			memcpy_s(processName, MAX_PATH, pe32.szExeFile, MAX_PATH);
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
}

int main()
{
	GetCurrentProcessId();
	while (TRUE)
	{
		HWND hwnd = GetForegroundWindow();
		if (hwnd == NULL) {
			printf("Failed to get foreground window.\n");
			return 1;
		}

		DWORD processId;
		GetWindowThreadProcessId(hwnd, &processId);
		printf("Process ID: %lu\n", processId);

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
		if (hProcess == NULL) {
			printf("Failed to open process.\n");
			continue;
		}

		//char processName[MAX_PATH] = "<unknown>";
		//wchar_t processName[MAX_PATH] = L"<unknown>";
		//if (GetModuleBaseName(hProcess, NULL, processName, sizeof(processName) / sizeof(char))) {
		//	printf("Process Name: %ls\n", processName);
		//}
		//else {
		//	printf("Failed to get process name.\n");
		//}

		// QueryFullProcessImageName 可以获取进程的完整路径，然后你可以从路径中提取进程名称。这个函数需要 Windows Vista 或更高版本（VS2010不行）
		//wchar_t processPath[MAX_PATH];
		//DWORD size = MAX_PATH;
		//if (QueryFullProcessImageNameW(hProcess, 0, processPath, &size))
		//{
		//	// 提取进程名称
		//	wchar_t* processName = wcsrchr(processPath, L'\\');
		//	if (processName != NULL)
		//	{
		//		processName++; // 跳过最后一个反斜杠
		//		wprintf(L"Process Name: %ls\n", processName);
		//	}
		//	else
		//	{
		//		wprintf(L"Failed to extract process name from path.\n");
		//	}
		//}
		//else
		//{
		//	wprintf(L"Failed to get process path.\n");
		//}

		// 又会出现获取不了部分进程名称
		//HMODULE hMod;
		//DWORD cbNeeded;
		//if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		//{
		//	char processName[MAX_PATH];
		//	if (GetModuleBaseNameA(hProcess, hMod, processName, sizeof(processName) / sizeof(char)))
		//	{
		//		printf("Process Name: %s\n", processName);
		//	}
		//	else
		//	{
		//		printf("Failed to get process name.\n");
		//	}
		//}
		//else
		//{
		//	printf("Failed to enumerate process modules.\n");
		//}

		//CloseHandle(hProcess);

		wchar_t processName[MAX_PATH] = L"<unknown>";
		GetProcessName(processId, processName);
		if (wcscmp(processName, L"Everything.exe") == 0)
		{
			printf("hejian %ls\n", processName);
		}
		Sleep(2000);
	}
	return 0;
}

