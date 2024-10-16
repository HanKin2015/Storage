// SendInputExample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip> // 包含 std::setw 和 std::setfill

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
	// 发送按键释放事件
	input[0].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input[0], sizeof(INPUT));
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

	// 发送按键释放事件（一定要发送释放按键，否则会有问题）
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

void SendCustomKeyMessage(WPARAM wParam, LPARAM lParam)
{
	// HWND_BROADCAST 可以用于将消息发送到系统中所有的顶级窗口
	PostMessage(HWND_BROADCAST, WM_KEYDOWN, wParam, lParam);
	PostMessage(HWND_BROADCAST, WM_KEYUP, wParam, lParam);
}

void ParseKeyLParam(LPARAM lParam)
{
	int repeatCount = lParam & 0xFFFF; // 位 0-15
	int scanCode = (lParam >> 16) & 0xFF; // 位 16-23
	bool isExtended = (lParam >> 24) & 0x1; // 位 24
	bool isAltPressed = (lParam >> 29) & 0x1; // 位 29
	bool wasDownBefore = (lParam >> 30) & 0x1; // 位 30
	bool isUpNow = (lParam >> 31) & 0x1; // 位 31

	std::cout << "Repeat Count: " << repeatCount << std::endl;
	std::cout << "Scan Code: " << scanCode << std::endl;
	std::cout << "Is Extended: " << isExtended << std::endl;
	std::cout << "Is Alt Pressed: " << isAltPressed << std::endl;
	std::cout << "Was Down Before: " << wasDownBefore << std::endl;
	std::cout << "Is Up Now: " << isUpNow << std::endl;
}

enum RedKey {
	REDKEY_INVALID,
	REDKEY_ESCAPE,
	REDKEY_1,
	REDKEY_2,
	REDKEY_3,
	REDKEY_4,
	REDKEY_5,
	REDKEY_6,
	REDKEY_7,
	REDKEY_8,
	REDKEY_9,
	REDKEY_0,
	REDKEY_MINUS,
	REDKEY_EQUALS,
	REDKEY_BACKSPACE,
	REDKEY_TAB,
	REDKEY_Q,
	REDKEY_W,
	REDKEY_E,
	REDKEY_R,
	REDKEY_T,
	REDKEY_Y,
	REDKEY_U,
	REDKEY_I,
	REDKEY_O,
	REDKEY_P,
	REDKEY_L_BRACKET,
	REDKEY_R_BRACKET,
	REDKEY_ENTER,
	REDKEY_L_CTRL,
	REDKEY_A,
	REDKEY_S,
	REDKEY_D,
	REDKEY_F,
	REDKEY_G,
	REDKEY_H,
	REDKEY_J,
	REDKEY_K,
	REDKEY_L,
	REDKEY_SEMICOLON,
	REDKEY_QUOTE,

	REDKEY_BACK_QUOTE,
	REDKEY_L_SHIFT,
	REDKEY_BACK_SLASH,
	REDKEY_Z,
	REDKEY_X,
	REDKEY_C,
	REDKEY_V,
	REDKEY_B,
	REDKEY_N,
	REDKEY_M,
	REDKEY_COMMA,
	REDKEY_PERIOD,
	REDKEY_SLASH,
	REDKEY_R_SHIFT,
	REDKEY_PAD_MULTIPLY,
	REDKEY_L_ALT,
	REDKEY_SPACE,
	REDKEY_CAPS_LOCK,
	REDKEY_F1,
	REDKEY_F2,
	REDKEY_F3,
	REDKEY_F4,
	REDKEY_F5,
	REDKEY_F6,
	REDKEY_F7,
	REDKEY_F8,
	REDKEY_F9,
	REDKEY_F10,
	REDKEY_NUM_LOCK,
	REDKEY_SCROLL_LOCK,
	REDKEY_PAD_7,
	REDKEY_PAD_8,
	REDKEY_PAD_9,
	REDKEY_PAD_MINUS,
	REDKEY_PAD_4,
	REDKEY_PAD_5,
	REDKEY_PAD_6,
	REDKEY_PAD_PLUS,
	REDKEY_PAD_1,
	REDKEY_PAD_2,
	REDKEY_PAD_3,
	REDKEY_PAD_0,
	REDKEY_PAD_POINT,

	REDKEY_EUROPEAN = 0x56,
	REDKEY_F11,
	REDKEY_F12,

	REDKEY_JAPANESE_HIRAGANA_KATAKANA = 0x70,
	REDKEY_JAPANESE_BACKSLASH = 0x73,
	REDKEY_JAPANESE_HENKAN = 0x79,
	REDKEY_JAPANESE_MUHENKAN = 0x7B,
	REDKEY_JAPANESE_YEN = 0x7D,

	REDKEY_KOREAN_HANGUL_HANJA = 0xf1,
	REDKEY_KOREAN_HANGUL = 0xf2,

	REDKEY_ESCAPE_BASE = 0x100,
	REDKEY_PAD_ENTER = REDKEY_ESCAPE_BASE + 0x1c,
	REDKEY_R_CTRL = REDKEY_ESCAPE_BASE + 0x1d,
	REDKEY_MUTE = REDKEY_ESCAPE_BASE + 0x20,
	REDKEY_FAKE_L_SHIFT = REDKEY_ESCAPE_BASE + 0x2a,
	REDKEY_VOLUME_DOWN = REDKEY_ESCAPE_BASE + 0x2e,
	REDKEY_VOLUME_UP = REDKEY_ESCAPE_BASE + 0x30,
	REDKEY_PAD_DIVIDE = REDKEY_ESCAPE_BASE + 0x35,
	REDKEY_FAKE_R_SHIFT = REDKEY_ESCAPE_BASE + 0x36,
	REDKEY_CTRL_PRINT_SCREEN = REDKEY_ESCAPE_BASE + 0x37,
	REDKEY_R_ALT = REDKEY_ESCAPE_BASE + 0x38,
	REDKEY_CTRL_BREAK = REDKEY_ESCAPE_BASE + 0x46,
	REDKEY_HOME = REDKEY_ESCAPE_BASE + 0x47,
	REDKEY_UP = REDKEY_ESCAPE_BASE + 0x48,
	REDKEY_PAGEUP = REDKEY_ESCAPE_BASE + 0x49,
	REDKEY_LEFT = REDKEY_ESCAPE_BASE + 0x4b,
	REDKEY_RIGHT = REDKEY_ESCAPE_BASE + 0x4d,
	REDKEY_END = REDKEY_ESCAPE_BASE + 0x4f,
	REDKEY_DOWN = REDKEY_ESCAPE_BASE + 0x50,
	REDKEY_PAGEDOWN = REDKEY_ESCAPE_BASE + 0x51,
	REDKEY_INSERT = REDKEY_ESCAPE_BASE + 0x52,
	REDKEY_DELETE = REDKEY_ESCAPE_BASE + 0x53,
	REDKEY_LEFT_CMD = REDKEY_ESCAPE_BASE + 0x5b,
	REDKEY_RIGHT_CMD = REDKEY_ESCAPE_BASE + 0x5c,
	REDKEY_MENU = REDKEY_ESCAPE_BASE + 0x5d,

	REDKEY_PAUSE,

	REDKEY_NUM_KEYS
};

int main()
{
	printf("z: 0x%04x, Z: 0x%04x\n", VkKeyScan('z'), VkKeyScan('Z'));

	long long cnt = 0;
	while (1)
	{
		// 发送字符串 "Z66741PE0206A114"

		// SendInput 函数用于模拟键盘、鼠标和其他输入设备的输入事件。它主要通过发送虚拟键码（wVk）和扫描码（wScan）来模拟按键事件
		// 是一个高层次的输入模拟函数，旨在模拟用户输入，而不是直接操控底层消息参数
		//SendString("Z66741PE0206A114");
		//SendSingleKey();

		// 使用 PostMessage 或 SendMessage 函数来直接发送消息到系统的消息队列中
		// 示例：发送一个自定义的按键消息
		//SHORT vk = VkKeyScan('Z');
		//WORD vkCode = vk & 0xFF;
		//WPARAM wParam = vkCode; // 虚拟键码
		//LPARAM lParam = 0x001C0001; // 自定义 lParam

		//uint32_t scan = HIWORD(lParam) & 0xff;
		//printf("scan: 0x%04x %d\n", scan, scan);

		//ParseKeyLParam(lParam);

		const std::string str = "Z66741PE02a06A114\n";
		for (char ch : str) {
			SHORT vk = VkKeyScan(ch);
			std::cout << ch << " --- vk: " << vk << std::endl;
			WORD vkCode = vk & 0xFF; // 低字节是虚拟键码
			bool shift = (vk & 0x0100) != 0; // 高字节的第一个位表示 Shift 键

			if (vkCode != -1) {
				//WPARAM wParam = vkCode; // 虚拟键码（windows操作系统会有各种各样的的误按，主要是回车键引起）
				WPARAM wParam = 0; // 虚拟键码

				// 位 0-15：重复计数（Repeat count），表示按键被按住的时间内重复发送的次数
				// 位 16-23：扫描码（Scan code），表示物理键盘上的按键位置
				LPARAM lParam = (vk << 16) | 0x0001; // 自定义 lParam
				if (shift)
				{
					// 位 24：扩展键标志（Extended key flag），如果是扩展键（如箭头键、功能键），则为 1。位 25-28：保留，通常为 0
					lParam |= (1 << 24);
				}

				std::cout << "wParam Key Down: 0x"
					<< std::hex << std::setw(4) << std::setfill('0') << wParam
					<< std::endl;

				std::cout << "lParam Key Down: 0x"
					<< std::hex << std::setw(4) << std::setfill('0') << lParam
					<< std::endl;
				uint32_t scan = HIWORD(lParam) & 0xff;
				printf("scan: 0x%04x\n", scan);
				bool extended = ((HIWORD(lParam) & KF_EXTENDED) != 0);
				if (extended && (scan != REDKEY_R_SHIFT)) {
					scan += REDKEY_ESCAPE_BASE;
				}
				// int变量强转成枚举变量其实就是没有变化，无非是可以对应一个枚举变量名而已，没有太大的实质意义
				printf("scan: 0x%04x (RedKey)scan: 0x%04x\n\n", scan, (RedKey)scan);
				SendCustomKeyMessage(wParam, lParam);
			}
			else {
				std::cerr << "Unsupported character: " << ch << std::endl;
			}
		}

		Sleep(1000);
		std::clog << "cnt = " << cnt++ << std::endl;
		if (cnt > 20) break;
	}
	return 0;
}

