
#include <windows.h>
#include <cstdio>
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        char szFileName[MAX_PATH];
        HINSTANCE hInstance = GetModuleHandle(NULL);

        printf("%s[line:%d] hello windows!\n", __FUNCTION__, __LINE__);

        GetModuleFileName(hInstance, szFileName, MAX_PATH);
        MessageBoxW(hwnd, L"窗口弹出成功", L"新消息", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/*

WINUSERAPI int WINAPI MessageBoxA(
 
HWND hWnd,
 
LPCSTR lpText,
 
LPCSTR lpCaption,
 
UINT uType);
 
 
WINUSERAPI int WINAPI MessageBoxW(
 
HWND hWnd,
 
LPCWSTR lpText,
 
LPCWSTR lpCaption,
 
UINT uType);
 
 
#ifdef UNICODE
 
#define MessageBox MessageBoxW//如果启用Unicode库，就用MessageBoxW
 
#else
 
#define MessageBox MessageBoxA//否则，就用MessageBoxA
 
#endif
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    printf("%s[line:%d] hello windows!\n", __FUNCTION__, __LINE__);
    MessageBoxW(NULL, L"苟利国家生死以，岂因祸福避趋之", L"念诗", MB_OK);

    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("MainWindow");
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(0, wc.lpszClassName, TEXT(""), wc.style,
	       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, nullptr, nullptr);
	       
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}