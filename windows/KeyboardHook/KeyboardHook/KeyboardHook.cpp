// KeyboardHook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

// ȫ�ֱ������洢���ӵľ��
HHOOK hKeyboardHook;

// ���ӻص�����
LRESULT CALLBACK KeyboardProc1(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		// ��� wParam �Ƿ������Ǹ���Ȥ�ļ����¼�
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
			// ��ȡ������Ϣ
			KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;
			// ��ӡ�������������
			printf("Key Down: %d\n", pKeyboard->vkCode);
		}
	}
	// ���¼����ݸ���һ�����ӳ���
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// ģ�ⰴ������
void SimulateKeyPress(WORD key) {
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

// ���̹��ӻص��������޸İ���ֵ��
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		if (wParam == WM_KEYDOWN) {
			// ��⵽�������£�ģ����������
			if (p->vkCode == 'A') {
				// ������µ��� 'A'��ģ�ⰴ�� 'B'
				SimulateKeyPress('B');
				return 1; // ���� 1 ��ʾ�̵�ԭ���İ�����Ϣ
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// ��װ����
void SetHook() {
	// WH_KEYBOARD_LL ��ʾ���ǰ�װһ���ͼ����̹���
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (hKeyboardHook == NULL) {
		printf("Keyboard Hook Failed\n");
	}
}

// ж�ع���
void ReleaseHook() {
	UnhookWindowsHookEx(hKeyboardHook);
}

// ������
int main() {
	// ��װ����
	SetHook();

	// ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ж�ع���
	ReleaseHook();
	return 0;
}


