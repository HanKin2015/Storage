// KeyboardHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

// 全局变量来存储钩子的句柄
HHOOK hKeyboardHook;

// 钩子回调函数
LRESULT CALLBACK KeyboardProc1(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		// 检查 wParam 是否是我们感兴趣的键盘事件
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
			// 获取按键信息
			KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;
			// 打印按键的虚拟键码
			printf("Key Down: %d\n", pKeyboard->vkCode);
		}
	}
	// 将事件传递给下一个钩子程序
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// 模拟按键函数
void SimulateKeyPress(WORD key) {
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

// 键盘钩子回调函数（修改按键值）
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		if (wParam == WM_KEYDOWN) {
			// 检测到按键按下，模拟其他按键
			if (p->vkCode == 'A') {
				// 如果按下的是 'A'，模拟按下 'B'
				SimulateKeyPress('B');
				return 1; // 返回 1 表示吞掉原来的按键消息
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// 安装钩子
void SetHook() {
	// WH_KEYBOARD_LL 表示我们安装一个低级键盘钩子
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (hKeyboardHook == NULL) {
		printf("Keyboard Hook Failed\n");
	}
}

// 卸载钩子
void ReleaseHook() {
	UnhookWindowsHookEx(hKeyboardHook);
}

// 主函数
int main() {
	// 安装钩子
	SetHook();

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 卸载钩子
	ReleaseHook();
	return 0;
}


