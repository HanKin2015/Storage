# windows编程

## 1、项目说明
GetUsbCommonNumber-----xhci端口绑定（串口设备更换usb端口后com号会变）
MonitorRegistry-----监控注册表被哪个安全软件删除修改

## 2、重点在于StudyWindowsCLanguage项目
学习windows版本的C/C++语言。

## 3、MFC和Win32窗口程序有什么不同
MFC（Microsoft Foundation Class）和Win32窗口程序是Windows平台上的两种不同的应用程序开发框架。

MFC是微软提供的面向对象的应用程序框架，它封装了大量的Windows API功能，并提供了一系列的类库，使得开发者可以更加方便地创建Windows应用程序。MFC提供了诸如窗口管理、消息处理、用户界面控件等方面的封装，使得开发者可以更加专注于应用程序的逻辑而不必过多关注底层的API调用。

Win32窗口程序则是直接使用Windows API进行开发的传统方式。开发者需要手动处理诸如窗口过程、消息循环、窗口创建和管理等底层细节。

因此，MFC相对于Win32窗口程序来说，提供了更高层次的抽象和封装，使得开发者可以更快速地开发Windows应用程序，而Win32窗口程序则更加灵活，但需要开发者处理更多的底层细节。

MFC：D:\Github\Storage\windows\MFCApplication
Win32：D:\Github\Storage\windows\Win32Project

## 4、精简化创建MFC项目
在创建的时候，在应用程序类型选择基于对话框即可。
选择rc文件还是即时看见界面当前情况。

## 5、找了很多资料显示只能通过和hub进行io通信
https://blog.csdn.net/code_xxl/article/details/39343085
https://blog.csdn.net/qq_23867503/article/details/85463675
https://www.coder.work/article/7955478#google_vignette

## 6、加载dll文件
见项目：D:\Github\Storage\windows\testdll

## 7、MFC和Win32窗口程序缺少VCRUNTIME140D.dll文件
很奇怪，同事创建的MFC文件就不缺少，我看也应该是vs2015项目啊。
```
D:\Users\Visual Studio 2015\Projects\MFCApplication\Debug>objdump -x MFCApplication.exe | findstr "\.dll"
        DLL Name: mfc140ud.dll
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: COMCTL32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: gdiplus.dll
        DLL Name: VCRUNTIME140D.dll
        DLL Name: ucrtbased.dll

D:\Users\User\Desktop>objdump -x DetecTool.exe | findstr "\.dll"
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: MSIMG32.dll
        DLL Name: ADVAPI32.dll
        DLL Name: SHELL32.dll
        DLL Name: COMCTL32.dll
        DLL Name: SHLWAPI.dll
        DLL Name: UxTheme.dll
        DLL Name: ole32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: oledlg.dll
        DLL Name: gdiplus.dll
        DLL Name: OLEACC.dll
        DLL Name: IMM32.dll
        DLL Name: WINMM.dll
```

然后灵机一动，同时打开这两个项目，然后点击属性查看发现：配置属性=》常规=》项目默认值=》MFC的使用，从在共享DLL中使用MFC改成在静态库中使用MFC即可。（exe文件也可以这样操作，将使用标准Windows库改成在静态库中使用MFC）
重新编译生成后从206KB大小文件到9.88MB，这时候是Debug版本，改成Release版本后变成3.38MB大小。
```
D:\Users\Visual Studio 2015\Projects\MFCApplication\Debug>objdump -x MFCApplication.exe | findstr "\.dll"
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: MSIMG32.dll
        DLL Name: ADVAPI32.dll
        DLL Name: SHELL32.dll
        DLL Name: COMCTL32.dll
        DLL Name: SHLWAPI.dll
        DLL Name: UxTheme.dll
        DLL Name: ole32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: oledlg.dll
        DLL Name: gdiplus.dll
        DLL Name: OLEACC.dll
        DLL Name: IMM32.dll
        DLL Name: WINMM.dll
```

## 8、HeapAlloc分配内存后释放函数
在C/C++中，如果使用HeapAlloc函数分配内存，则需要使用HeapFree函数来释放内存。HeapAlloc和HeapFree是配对使用的，用于在堆上分配和释放内存。

例如，在使用HeapAlloc分配内存后，需要使用HeapFree来释放内存，示例代码如下：
```
LPVOID lpMem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
// 使用分配的内存
// ...
HeapFree(GetProcessHeap(), 0, lpMem);
```
在这个示例中，HeapAlloc用于分配内存，然后在不再需要这块内存时，使用HeapFree来释放内存。

## 9、获取驱动程序信息
http://cn.voidcc.com/question/p-bxbodamg-bcg.html#google_vignette
https://blog.csdn.net/haart/article/details/120709158

（1）驱动路径获取方法
可见驱动路径是通过读取注册表

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services\usbccgp项的ImagePath子项来获取的。

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services是固定位置，usbccgp是设备的service属性值，可以通过调用SetupDiGetDeviceRegistryProperty传参SPDRP_SERVICE来获得。

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services下包含一些列的驱动服务子项，每项下面都有ImagePath这一子项，包含了驱动的路径。

（2）inf文件位置
inf文件位置是通过读取HKEY_LOCAL_MACHINE\CurrentControlSet\Control\Class\{4d36e972-e325-11ce-bfc1-08002be10318}\0009下的InfPath子项得到。

HKEY_LOCAL_MACHINE\CurrentControlSet\Control\Class\是固定位置

{4d36e972-e325-11ce-bfc1-08002be10318}\0009是设备的DriverKey，可以通过调用SetupDiGetDeviceRegistryProperty传参SPDRP_DRIVER来获得。

https://blog.csdn.net/dybb8999/article/details/73606096
提供了打印中文的方法。

另外发现usbtreeview软件有显示sys路径，但是也仅仅是通过注册表读取的信息，只显示了主驱动程序。另外usbtreeview并没有开源。
它也无法阻止USB设备加载其他的驱动，因为有多个筛选器驱动程序（如前述的UpperFilters和LowerFilters），它们在主驱动程序的基础上提供额外的功能或处理。

demo见：D:\Github\Storage\windows\GetUsbDeviceDriverInfo

## 10、向窗口发送虚拟按键
https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
https://baike.baidu.com/item/ASCII/309296?fr=ge_ala
demo见：D:\Github\Storage\windows\SendInputExample

项目切换成在静态中使用MFC后出现无法解析的外部符号 __imp__SendInput，原因是在Windows编程中，SendInput 函数是Windows API的一部分，定义在user32.dll中。要解决这个问题，你需要确保在编译时链接到User32.lib库。

### 10-1、VkKeyScan 函数
VkKeyScan 函数用于将字符转换为虚拟键码（virtual-key code）和键盘状态的组合。它返回一个 SHORT 值，其中低字节包含虚拟键码，高字节包含键盘状态（如 Shift 键是否被按下）。

VkKeyScan('Z')：
- Z 是大写字母，因此需要按下 Shift 键。
- 返回值的低字节将是 Z 的虚拟键码（通常是 0x5A），高字节将指示 Shift 键被按下（通常是 0x01）。
- 因此，VkKeyScan('Z') 的返回值通常是 0x015A。

VkKeyScan('z')：
- z 是小写字母，不需要按下 Shift 键。
- 返回值的低字节将是 z 的虚拟键码（通常也是 0x5A），高字节将为零，因为不需要额外的键盘状态。
- 因此，VkKeyScan('z') 的返回值通常是 0x005A。

## 11、GetForegroundWindow函数
GetForegroundWindow 是 Windows API 中的一个函数，用于获取当前前台窗口的句柄。前台窗口是用户当前正在与之交互的窗口。这个函数在用户界面编程中非常有用，因为它可以帮助程序确定用户当前关注的窗口。

可以通过这个函数获取窗口句柄，然后再获取该进程ID和进程名称。

使用 GetModuleBaseName 或 QueryFullProcessImageName 来获取进程名称（部分窗口名称获取不到）
QueryFullProcessImageName 可以获取进程的完整路径，然后你可以从路径中提取进程名称（需要 Windows Vista 或更高版本）
使用 EnumProcessModules 和 GetModuleBaseName 来获取进程名称（部分窗口名称获取不到）


## 12、"char *" 类型的实参与 "LPWSTR" 类型的形参不兼容
```
#include <windows.h>
#include <stdio.h>

void ConvertCharToLPWSTR(const char* charStr, LPWSTR* lpwStr) {
    int len = MultiByteToWideChar(CP_ACP, 0, charStr, -1, NULL, 0);
    *lpwStr = (LPWSTR)malloc(len * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, charStr, -1, *lpwStr, len);
}

std::wstring ConvertCharToWString(const char* charStr) {
    int len = MultiByteToWideChar(CP_ACP, 0, charStr, -1, NULL, 0);
    std::wstring wstr(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, charStr, -1, &wstr[0], len);
    return wstr;
}

int main() {
    const char* charStr = "Hello, World!";

    LPWSTR lpwStr = NULL;
    ConvertCharToLPWSTR(charStr, &lpwStr);
    // 使用 lpwStr
    wprintf(L"Converted string: %ls\n", lpwStr);
    // 记得释放内存
    free(lpwStr);

    std::wstring wstr = ConvertCharToWString(charStr);
    // 使用 wstr
    std::wcout << L"Converted string: " << wstr << std::endl;
    return 0;
}
```

## 13、Windows可视化窗口打印调试日志
项目：Win32WindowsOutputDebugString
- OutputDebugString 是一个 Windows API 函数，用于将调试信息发送到调试器（如 DebugView）。
- 可以创建一个控制台窗口并使用 printf。
```
#include <windows.h>
#include <iostream>

void CreateConsole() {
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    CreateConsole();
    std::cout << "Console window created. Logging started." << std::endl;

    // 你的窗口创建和消息循环代码
    // ...

    return 0;
}
```

OutputDebugString 函数用于将调试信息输出到调试器窗口，但它只接受一个字符串参数，而不像 printf 那样支持格式化字符串和可变参数列表。因此，直接将格式化字符串传递给 OutputDebugString 是不正确的。

要解决这个问题，你需要先使用 sprintf 或类似的函数将格式化字符串转换为一个完整的字符串，然后将该字符串传递给 OutputDebugString。在 Windows 环境下，使用 _stprintf（或 swprintf/sprintf，取决于字符集）来格式化字符串。

## 14、虚拟按键对应转换
项目：KbdKeyCodeToRedKey
Windows按照键盘的布局进行虚拟按键布局，但Linux是按照ASCII表布局，需要进行宏转换。

## 15、wParam参数和lParam参数
在 Windows 编程中，WM_KEYDOWN 和 WM_KEYUP 消息的 wParam 和 lParam 参数分别包含不同的信息：
- wParam：通常包含虚拟键码（Virtual-Key Code），即按下或释放的键的标识符。
- lParam：包含有关按键事件的附加信息，如重复计数、扫描码、扩展键标志等。

lParam 的结构
lParam 是一个 32 位的值，其中包含以下信息：
- 位 0-15：重复计数（Repeat count），表示按键被按住的时间内重复发送的次数。
- 位 16-23：扫描码（Scan code），表示物理键盘上的按键位置。
- 位 24：扩展键标志（Extended key flag），如果是扩展键（如箭头键、功能键），则为 1。
- 位 25-28：保留，通常为 0。
- 位 29：上下文代码（Context code），如果按下 Alt 键，则为 1。
- 位 30：上一次键状态（Previous key state），如果按键之前是按下的，则为 1。
- 位 31：过渡状态（Transition state），如果按键是按下的，则为 0；如果是释放的，则为 1。

判断按键信息
如果你发现某些软件发送的按键消息信息主要在 lParam 中，而不是 wParam，可能是因为这些软件使用了低级别的键盘钩子或其他方式来直接操作键盘消息。通常情况下，wParam 应该始终包含虚拟键码。

## 16、PostMessage和sendMessage函数区别
PostMessage 和 SendMessage 是 Windows API 中用于发送消息的两个函数，它们在消息的发送和处理方式上有一些重要的区别：

SendMessage
- 同步调用：SendMessage 是一个同步函数调用。它将消息发送到指定的窗口过程，并等待该窗口过程处理完消息后返回。这意味着调用线程会被阻塞，直到消息被处理完成。
- 返回值：SendMessage 返回由窗口过程处理消息后返回的结果。这个返回值可以用于获取消息处理的结果。
- 使用场景：适用于需要立即得到消息处理结果的场景，比如需要从窗口过程获取某些信息。

PostMessage
- 异步调用：PostMessage 是一个异步函数调用。它将消息放入指定窗口的消息队列中，然后立即返回，不等待消息被处理。这意味着调用线程不会被阻塞。
- 无返回值：由于 PostMessage 是异步的，它不会返回窗口过程的处理结果。
- 使用场景：适用于不需要立即得到消息处理结果的场景，或者需要避免阻塞调用线程的场景。

选择使用的场景
- SendMessage：当你需要确保消息被立即处理并且需要获取处理结果时使用。例如，发送一个请求并需要立即得到响应。
- PostMessage：当你不需要立即处理消息或者不关心处理结果时使用。例如，发送一个通知或更新请求，而不需要等待处理完成。

示例代码

## 17、_T 
_T是一个宏，作用是让程序支持Unicode编码。因为Windows使用两种字符集ANSI和UNICODE，前者就是通常使用的单字节方式，但这种方式处理像中文这样的双字节字符不方便，容易出现半个汉字的情况。而后者是双字节方式，方便处理双字节字符。
