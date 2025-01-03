// GetUsbCommonNumber.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>

#define MAX_FILENAME_LEN 256
#define MAX_TIME_LEN 20
#define MAX_ENTRIES 7
#define MAX_CHANNELID_LEN 3
#pragma comment(lib, "Cfgmgr32.lib")
#pragma comment(lib, "setupapi.lib")

/*
MFC的使用：在静态中使用MFC
字符集需要设置成多字节字符集，否则乱码
C:\Users\Administrator\Desktop>GetUsbCommonNumber.exe
端口（COM和LPT）: 通信端口 (COM1)
端口（COM和LPT）: PL2303TA不支援WINDOWS 11及后续版本，请洽询购买厂商
*/
int GetUsbCommonNumber()
{
	HDEVINFO hDevInfo = SetupDiGetClassDevs(
		&GUID_DEVINTERFACE_COMPORT,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
	);

	if (hDevInfo == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Failed to get device info set\n");
		return 1;
	}

	SP_DEVINFO_DATA devInfoData;
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); i++) {
		char buffer[256] = { 0 };
		if (SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&devInfoData,
			SPDRP_FRIENDLYNAME,
			NULL,
			(PBYTE)buffer,
			sizeof(buffer),
			NULL)) {
			printf("端口（COM和LPT）: %s\n", buffer);
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	return 0;
}

// 获取当前时间（格式：YYYY-MM-DD HH:MM:SS）
char* getCurrentTime()
{
	time_t now = time(NULL);
	static char buf[MAX_TIME_LEN] = { 0 };
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
	printf("timestamp: %lld\n", now);
	return buf;
}

// 读取文件内容并解析为文件名和时间
void readFileContent(const char* filename, char fileNames[MAX_ENTRIES][MAX_FILENAME_LEN],
	char fileTimes[MAX_ENTRIES][MAX_TIME_LEN], char channelIds[MAX_ENTRIES][MAX_CHANNELID_LEN], int* count)
{
	// 判断文件是否存在
	if (_access(filename, 0) != 0) {
		printf("File does not exist.\n");
		return;
	}

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Open file failed.\n");
		return;
	}

	char line[MAX_FILENAME_LEN + MAX_TIME_LEN + MAX_CHANNELID_LEN + 3];
	*count = 0;
	while (fgets(line, sizeof(line), file)) {
		char* name = strtok(line, " ");
		char* time = strtok(NULL, " ");
		char* id = strtok(NULL, "\n");
		//printf("line: %s, %s %s %s\n", line, name, time, id);
		if (name != NULL && time != NULL && id != NULL && *count < MAX_ENTRIES) {
			strcpy(fileNames[*count], name);
			strcpy(fileTimes[*count], time);
			strcpy(channelIds[*count], id);
			(*count)++;
		}
	}

	fclose(file);
	file = NULL;
	return;
}

// 写入文件内容
void writeFileContent(const char* filename, char unique_id[MAX_FILENAME_LEN], time_t now, int channelId)
{
	FILE* file = fopen(filename, "a");
	if (file == NULL) {
		perror("Failed to open file");
		return;
	}
	fprintf(file, "%s %lld %d\n", unique_id, now, channelId);
	fclose(file);
}

// 删除最早写入的文件名
int removeOldestEntry(char fileNames[MAX_ENTRIES][MAX_FILENAME_LEN], char fileTimes[MAX_ENTRIES][MAX_TIME_LEN],
	char channelIds[MAX_ENTRIES][MAX_CHANNELID_LEN], int* count)
{
	if (*count == 0) return -1;

	int oldestIndex = 0;
	for (int i = 1; i < *count; i++) {
		if (strcmp(fileTimes[i], fileTimes[oldestIndex]) < 0) {
			oldestIndex = i;
		}
	}

	int channelId = 0;
	sscanf_s(channelIds[oldestIndex], "%d", &channelId);
	printf("remove filename: %s, filetime: %s, channelIds: %d\n", fileNames[oldestIndex], fileTimes[oldestIndex], channelId);

	// 删除最早的条目
	for (int i = oldestIndex; i < *count - 1; i++) {
		strcpy(fileNames[i], fileNames[i + 1]);
		strcpy(fileTimes[i], fileTimes[i + 1]);
		strcpy(channelIds[i], channelIds[i + 1]);
	}
	(*count)--;
	return channelId;
}

// 遍历目录并获取文件名
void getFileNames(const char* folderPath, char fileNames[MAX_ENTRIES][MAX_FILENAME_LEN], int* count)
{
	char searchPath[MAX_FILENAME_LEN];
	sprintf(searchPath, "%s\\*", folderPath);

	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(searchPath, &findFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		perror("Failed to open directory");
		return;
	}

	do {
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (*count < MAX_ENTRIES) {
				strcpy(fileNames[*count], findFileData.cFileName);
				printf("filename: %s\n", findFileData.cFileName);
				(*count)++;
			}
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
}

int main()
{
	// 指定文件夹路径和输出文件名
	const char* folderPath = "D:\\symbols";
	const char* outputFile = "file_list.txt";

	// 读取文件夹下的所有文件名
	char addFileNames[MAX_ENTRIES][MAX_FILENAME_LEN] = { 0 };
	int addCount = 0;
	getFileNames(folderPath, addFileNames, &addCount);

	// 处理文件名
	for (int i = 0; i < addCount; i++) {
		bool found = false;

		// 读取现有文件内容
		char fileNames[MAX_ENTRIES][MAX_FILENAME_LEN] = { 0 };
		char channelIds[MAX_ENTRIES][MAX_CHANNELID_LEN] = { 0 };
		char fileTimes[MAX_ENTRIES][MAX_TIME_LEN] = { 0 };
		int count = 0;
		readFileContent(outputFile, fileNames, fileTimes, channelIds, &count);
		printf("count: %d\n", count);

		for (int j = 0; j < count; j++) {	// 遍历本地存储信息是否已经存在当前usb设备
											//printf("newFilename: %s, fileName: %s\n", addFileNames[i], fileNames[j]);
			if (strcmp(addFileNames[i], fileNames[j]) == 0) {	// 存在则输出通道id
				found = true;
				printf("This is exists!! file name: %s, write time: %s, channel id: %s\n", fileNames[j], fileTimes[j], channelIds[j]);
				break;
			}
		}
		if (!found)	// 不存在则需要添加通道id
		{
			int channelId = 0;
			if (count + 1 > MAX_ENTRIES)	// 超过7个则需要删除最早的绑定信息，并重新写入文件
			{
				channelId = removeOldestEntry(fileNames, fileTimes, channelIds, &count);
				printf("remove after count: %d\n", count);
				FILE* file = fopen(outputFile, "w");
				if (file == NULL)
				{
					perror("Failed to open file");
					return -1;
				}
				for (int k = 0; k < count; k++)
				{
					fprintf(file, "%s %s %s\n", fileNames[k], fileTimes[k], channelIds[k]);
				}
				fclose(file);
			}
			else
			{
				// 36~42
				channelId = 36 + count;
			}
			// 追加写入通道id+当前时间
			time_t now = time(NULL);
			writeFileContent(outputFile, addFileNames[i], now, channelId);
			printf("File names: %s have been processed and written to %s\n", addFileNames[i], outputFile);
		}
	}
	return 0;
}

