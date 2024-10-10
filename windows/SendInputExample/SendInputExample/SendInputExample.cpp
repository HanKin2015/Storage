// SendInputExample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>

#pragma comment(lib, "User32.lib")

void SendSingleKey()
{
	// 创建一个INPUT结构体数组
	INPUT input[1] = { 0 };

	// 设置INPUT结构体的类型为键盘输入
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_RETURN; // 设置虚拟键码为CR (carriage return)

	// 发送按键按下事件
	if (SendInput(1, input, sizeof(INPUT)) == 0)
	{
		std::cerr << "SendInput failed: " << GetLastError() << std::endl;
	}
}

void SendKey(WORD vk, bool shift)
{
	INPUT input[2] = { 0 };

	if (shift) {
		// 按下 Shift 键
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		SendInput(1, &input[0], sizeof(INPUT));
	}

	// 发送按键按下事件
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = vk;
	SendInput(1, &input[1], sizeof(INPUT));

	// 发送按键释放事件
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input[1], sizeof(INPUT));

	if (shift) {
		// 释放 Shift 键
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input[0], sizeof(INPUT));
	}
}

void SendString(const std::string& str)
{
	for (char ch : str) {
		SHORT vk = VkKeyScan(ch);
		WORD vkCode = vk & 0xFF; // 低字节是虚拟键码
		bool shift = (vk & 0x0100) != 0; // 高字节的第一个位表示 Shift 键

		if (vkCode != -1) {
			SendKey(vkCode, shift);
		}
		else {
			std::cerr << "Unsupported character: " << ch << std::endl;
		}
	}
}

int main()
{
	printf("z: 0x%04x, Z: 0x%04x\n", VkKeyScan('z'), VkKeyScan('Z'));

	long long cnt = 0;
	while (1)
	{
		// 发送字符串 "Z66741PE0206A114"
		SendString("Z66741PE0206A114");
		SendSingleKey();

		Sleep(1000);
		std::clog << cnt++ << std::endl;
		if (cnt > 60) break;
	}
	return 0;
}

