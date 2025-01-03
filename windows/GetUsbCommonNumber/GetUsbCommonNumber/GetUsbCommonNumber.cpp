// GetUsbCommonNumber.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <shlobj.h>
#pragma comment(lib, "Shell32.lib")

#define MAX_XHCI_BIND_NUM 7
#define CHANNELNO_XHCI_END 35

// 读取XHCI端口绑定文件内容
void ReadXchiBindFile(const char* xhci_bind_filepath, time_t timestamps[MAX_XHCI_BIND_NUM], int unique_ids[MAX_XHCI_BIND_NUM],
	int channel_ids[MAX_XHCI_BIND_NUM], int* count)
{
	// 判断文件是否存在
	if (_access(xhci_bind_filepath, 0) != 0)
	{
		printf("xhci_bind_filepath: %s does not exist.\n", xhci_bind_filepath);
		return;
	}

	FILE* fp = fopen(xhci_bind_filepath, "r");
	if (fp == NULL)
	{
		printf("Open file: %s failed.\n", xhci_bind_filepath);
		return;
	}

	char line[MAX_PATH] = { 0 };
	*count = 0;
	while (fgets(line, sizeof(line), fp))
	{
		//printf("line: %s", line);
		if (*count < MAX_XHCI_BIND_NUM)
		{
			sscanf_s(line, "%lld %d %d\n", &timestamps[*count], &unique_ids[*count], &channel_ids[*count]);
			(*count)++;
		}
	}

	fclose(fp);
	fp = NULL;
	return;
}

// 写入XHCI端口绑定文件内容
void WriteXhciBindFile(const char* xhci_bind_filepath, time_t timestamp, int unique_id, int channel_id)
{
	FILE* fp = fopen(xhci_bind_filepath, "a");
	if (fp == NULL) {
		perror("Failed to open file");
		return;
	}
	fprintf(fp, "%lld %d %d\n", timestamp, unique_id, channel_id);
	fclose(fp);
	fp = NULL;
	return;
}

// 删除最早写入的XHCI端口绑定记录
int RemoveOldestXhciBind(time_t timestamps[MAX_XHCI_BIND_NUM], int unique_ids[MAX_XHCI_BIND_NUM],
	int channel_ids[MAX_XHCI_BIND_NUM], int* count)
{
	int oldest_index = 0;
	for (int i = 1; i < *count; i++)
	{
		if (timestamps[i] < timestamps[oldest_index])
		{
			oldest_index = i;
		}
	}

	int channel_id = channel_ids[oldest_index];

	for (int i = oldest_index; i < *count - 1; i++)
	{
		timestamps[i] = timestamps[i + 1];
		unique_ids[i] = unique_ids[i + 1];
		channel_ids[i] = channel_ids[i + 1];
	}
	(*count)--;
	return channel_id;
}

static int GetXhciBindChannelId(int unique_id)
{
	const char* xhci_bind_filename = "xhci_bind_filepath.txt";
	char xhci_bind_filepath[MAX_PATH] = { 0 };
	BOOL bRet = SHGetSpecialFolderPathA(NULL, xhci_bind_filepath, CSIDL_APPDATA, FALSE);
	if (!bRet)
	{
		printf("get appdata path fail\n");
		return -1;
	}

	(void)strcat_s(xhci_bind_filepath, MAX_PATH, "\\SangforUsb\\");
	if (_access(xhci_bind_filepath, 0) != 0)
	{
		printf("xhci_bind_filepath: %s does not exist.\n", xhci_bind_filepath);
		SHCreateDirectoryExA(NULL, xhci_bind_filepath, NULL);
		//return -1;
	}
	else
	{
		printf("xhci_bind_filepath: %s exists.\n", xhci_bind_filepath);
	}

	(void)strcat_s(xhci_bind_filepath, MAX_PATH, xhci_bind_filename);
	printf("xhci_bind_filepath: %s\n", xhci_bind_filepath);

	// 读取现有文件内容
	time_t timestamps[MAX_XHCI_BIND_NUM];
	int unique_ids[MAX_XHCI_BIND_NUM];
	int channel_ids[MAX_XHCI_BIND_NUM];
	int count = 0;
	ReadXchiBindFile(xhci_bind_filepath, timestamps, unique_ids, channel_ids, &count);
	printf("count: %d\n", count);

	bool found = false;
	for (int i = 0; i < count; i++)	// 遍历本地存储信息是否已经存在当前usb设备
	{
		if (unique_id == unique_ids[i])	// 存在则输出通道id
		{
			found = true;
			printf("This is exists!! %lld %d %d\n", timestamps[i], unique_ids[i], channel_ids[i]);
			return channel_ids[i];
		}
	}
	// 不存在则需要添加通道id
	int channel_id = 0;
	if (count + 1 > MAX_XHCI_BIND_NUM)	// 超过7个则需要删除最早的绑定信息，并重新写入文件
	{
		channel_id = RemoveOldestXhciBind(timestamps, unique_ids, channel_ids, &count);
		printf("remove channel_id: %d after count: %d\n", channel_id, count);
		FILE* fp = fopen(xhci_bind_filepath, "w");
		if (fp == NULL)
		{
			perror("Failed to open file");
			return -1;
		}
		for (int j = 0; j < count; j++)
		{
			fprintf(fp, "%lld %d %d\n", timestamps[j], unique_ids[j], channel_ids[j]);
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		// 36~42
		channel_id = CHANNELNO_XHCI_END + 1 + count;
	}
	// 追加写入通道id+当前时间
	time_t timestamp = time(NULL);
	WriteXhciBindFile(xhci_bind_filepath, timestamp, unique_id, channel_id);
	printf("unique_id: %d have been written to %s\n", unique_id, xhci_bind_filepath);
	return channel_id;
}

int main()
{
	int unique_id = 0;
	scanf_s("%d", &unique_id);
	int channel_id = GetXhciBindChannelId(unique_id);
	printf("channel_id: %d\n", channel_id);
	return 0;
}

