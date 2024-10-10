// SendInputExample.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>

#pragma comment(lib, "User32.lib")

void SendSingleKey()
{
	// ����һ��INPUT�ṹ������
	INPUT input[1] = { 0 };

	// ����INPUT�ṹ�������Ϊ��������
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_RETURN; // �����������ΪCR (carriage return)

	// ���Ͱ��������¼�
	if (SendInput(1, input, sizeof(INPUT)) == 0)
	{
		std::cerr << "SendInput failed: " << GetLastError() << std::endl;
	}
}

void SendKey(WORD vk, bool shift)
{
	INPUT input[2] = { 0 };

	if (shift) {
		// ���� Shift ��
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		SendInput(1, &input[0], sizeof(INPUT));
	}

	// ���Ͱ��������¼�
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = vk;
	SendInput(1, &input[1], sizeof(INPUT));

	// ���Ͱ����ͷ��¼�
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input[1], sizeof(INPUT));

	if (shift) {
		// �ͷ� Shift ��
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input[0], sizeof(INPUT));
	}
}

void SendString(const std::string& str)
{
	for (char ch : str) {
		SHORT vk = VkKeyScan(ch);
		WORD vkCode = vk & 0xFF; // ���ֽ����������
		bool shift = (vk & 0x0100) != 0; // ���ֽڵĵ�һ��λ��ʾ Shift ��

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
		// �����ַ��� "Z66741PE0206A114"
		SendString("Z66741PE0206A114");
		SendSingleKey();

		Sleep(1000);
		std::clog << cnt++ << std::endl;
		if (cnt > 60) break;
	}
	return 0;
}

