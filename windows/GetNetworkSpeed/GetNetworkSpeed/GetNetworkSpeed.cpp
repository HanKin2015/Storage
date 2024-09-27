// GetNetworkSpeed.cpp : 定义控制台应用程序的入口点。
// https://blog.csdn.net/xiaobaiPlayGame/article/details/131037867
// 输入命令 wmic nic where (NetEnabled=true) get Name, Speed
//

#include "stdafx.h"
#include <Windows.h>
#include <iphlpapi.h>
#include <string>
#include <iostream>

#pragma comment(lib, "Iphlpapi.lib")

int getSpeedOnNetwork(const std::string &networkName)
{
	DWORD speed = 0;

	MIB_IFTABLE* pIfTable = (MIB_IFTABLE *)malloc(sizeof(MIB_IFTABLE));
	if (pIfTable == NULL)
	{
		return speed;
	}

	/* 第一次调用 GetIfTable 获取必要信息写入*/
	DWORD dwSize = sizeof(MIB_IFTABLE);
	if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER)
	{
		free(pIfTable);
		pIfTable = (MIB_IFTABLE *)malloc(dwSize);
		if (pIfTable == NULL)
		{
			return 0;
		}
	}


	DWORD dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);
	if (dwRetVal == NO_ERROR)
	{
		/* 若为多网卡则分别获取接口列表*/
		int num = (int)pIfTable->dwNumEntries;
		for (int i = 0; i < num; i++)
		{
			auto pIfRow = (MIB_IFROW *)& pIfTable->table[i];

			std::string desc = reinterpret_cast<char *>(pIfRow->bDescr);
			if (desc == networkName)
			{
				speed = pIfRow->dwSpeed;
			}
			if (pIfRow->dwSpeed != 0)
			{
				std::cout << desc << ": " << pIfRow->dwSpeed / 1000 / 1000 << std::endl;
			}
		}
	}
	if (pIfTable != NULL)
	{
		free(pIfTable);
		pIfTable = NULL;
	}

	return speed;
}

int main(int argc, char *argv[])
{
	auto value = getSpeedOnNetwork("Realtek PCIe GbE Family Controller");
	std::cout << "speed:" << value / 1000 / 1000 << "Mbps" << std::endl;
	return 0;
}

