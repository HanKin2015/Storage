/* study_x11.cpp
 *
 * 学习X11编程
 *
 * author: hankin
 * date  : 2021.06.02
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <X11/Xlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <X11/Xutil.h>
//#include "icon.bmp"
#include "hj.bmp"

using namespace std;

static XVisualInfo* get_x_vis_info(Display *dsp, int screen)
{
    XVisualInfo vtemplate;
    int count;

    Visual* visual = DefaultVisualOfScreen(ScreenOfDisplay(dsp, screen));
    vtemplate.screen = screen;
    vtemplate.visualid = XVisualIDFromVisual(visual);
    return XGetVisualInfo(dsp, VisualIDMask | VisualScreenMask, &vtemplate, &count);
}

void set_title(Display *x_display, Window win, string& title, string property)
{
	char *name = const_cast<char *>(title.c_str());
	XChangeProperty(x_display, win,
				   XInternAtom(x_display, property.c_str(), False),
				   XInternAtom(x_display, "UTF8_STRING", False),
				   8, PropModeReplace,(unsigned char *)name, strlen(name));

    XTextProperty text_prop;
    int r;
    if (win) {
        XLockDisplay(x_display);
        r = Xutf8TextListToTextProperty(x_display, &name, 1, XUTF8StringStyle, &text_prop);
        XUnlockDisplay(x_display);
        if (r == 0) {
            XSetWMName(x_display, win, &text_prop);
            XFree(text_prop.value);
        } else {
            printf("XwcTextListToTextProperty Error %d", r);
        }
    }
}

void set_icon(Display *dsp, Window win)
{
    XWMHints* wm_hints;
    char pixmap[4096];
    for (int i = 0; i < 4096; i++) {
        pixmap[i] = _red_icon.pixmap[i];
    }
    Pixmap icon_pixmap = XCreateBitmapFromData(dsp, win, pixmap, _red_icon.width, _red_icon.height);
    if (!icon_pixmap) {
        printf("non\n");
        return;
    }

    wm_hints = XAllocWMHints();
    if (!wm_hints) {
        printf("non\n");
        return;
    }
    wm_hints->flags = IconPixmapHint;
    wm_hints->icon_pixmap = icon_pixmap;
    XSetWMHints(dsp, win, wm_hints);
    XFree(wm_hints);
}


int main(int argc, char *argv[])
{
	// 程序(客户端)和服务器建立连接
	Display *dsp = XOpenDisplay(nullptr);
    if (!dsp) {
		printf("XOpenDisplay failed!\n");
        return -1;
    }
	
    // 判断系统是否支持共享内存机制
    int major, minor, pixmaps;
	if (XShmQueryExtension (dsp) &&
        XShmQueryVersion (dsp, &major, &minor, &pixmaps)) {
        printf("support shard memory, major = %d, minor = %d, pixmaps = %d\n", major, minor, pixmaps);
    } else {
        printf("not support shard memory!\n");
    }
    
    // 查询当前系统有多少屏幕
    printf("here has %d screens.\n", ScreenCount(dsp));
    XVisualInfo **vinfo = new XVisualInfo *[ScreenCount(dsp)];
    memset(vinfo, 0, sizeof(XVisualInfo *) * ScreenCount(dsp));
    for (int i = 0; i < ScreenCount(dsp); ++i) {
        vinfo[i] = get_x_vis_info(dsp, i);
        printf("depth = %d\n",  vinfo[i]->depth);
    }
	
	// 请求创建窗口XCreateWindow可以有额外的属性，XCreateSimpleWindow依赖于父窗口
	int screenNumber = DefaultScreen(dsp);
    unsigned long white = WhitePixel(dsp, screenNumber);
    unsigned long black = BlackPixel(dsp, screenNumber);
    #if 0
    Window win = XCreateSimpleWindow(dsp,
            DefaultRootWindow(dsp),
            50, 50,     // origin
            200, 200,   // size
            0, black,   // border
            white);     // backgd
	#endif
    
    // XCreateWindow示例
    Window root_window = RootWindow(dsp, 0);
    XSetWindowAttributes win_attributes;
    unsigned long mask = CWBorderPixel | CWEventMask;
    win_attributes.border_pixel = 1;
    win_attributes.event_mask = StructureNotifyMask | SubstructureNotifyMask | ExposureMask |
                                KeyPressMask | KeyReleaseMask | ButtonPressMask |
                                ButtonReleaseMask | PointerMotionMask | FocusChangeMask |
                                EnterWindowMask | LeaveWindowMask;

    XLockDisplay(dsp);
    Colormap _colormap = XCreateColormap(dsp, root_window, vinfo[0]->visual,
                               AllocNone);
    win_attributes.colormap = _colormap;
    mask |= CWColormap;
    Window win = XCreateWindow(dsp, root_window, 50, 50,
                           800, 600, 0, vinfo[0]->depth,
                           InputOutput, vinfo[0]->visual, mask,
                           &win_attributes);
    XUnlockDisplay(dsp);
    
    if (!win) {
        printf("create X window failed!\n");
    }
    
    // 这段代码没有啥效果啊
    XClassHint *class_hint;
    class_hint = XAllocClassHint();
    if (!class_hint) {
        printf("allocating class hint failed!\n");
    }
    class_hint->res_name = (char *)"TEST";
    class_hint->res_class = (char *)"He Jian";
    XSetClassHint(dsp, win, class_hint);
    XFree(class_hint);
    
    // 设置名称
    string wm_name = "魔法工具";
    string icon_name = "./test.png";
    set_title(dsp, win, wm_name, "_NET_WM_NAME");
    set_title(dsp, win, icon_name, "_NET_WM_ICON_NAME");
    
    set_icon(dsp, win);
    
	// 想象成从内存拷贝到显存
	XMapWindow(dsp, win);
	
	// 通讯是双向的，告诉server我们对哪些事件感兴趣
	long eventMask = StructureNotifyMask;
    XSelectInput(dsp, win, eventMask);
	
	// 等待server的 map 完成的通知
	XEvent evt;
    do {
        XNextEvent(dsp, &evt);   // calls XFlush()
    } while (evt.type != MapNotify);
	
	// 由于server记不住我们的每次绘图操作的设置，我们将设置保存在“Graphics Context”中
	GC gc = XCreateGC(dsp, win, 0, nullptr);
    XSetForeground(dsp, gc, white);
	
	// 画线
    XDrawLine(dsp, win, gc, 10, 10,190,190);
	
	// 告诉server，我们对鼠标按键感兴趣
	eventMask = ButtonPressMask | ButtonReleaseMask;
    XSelectInput(dsp, win, eventMask); // override prev
	
	// 等待鼠标释放的事件
	do {
        XNextEvent(dsp, &evt);   // calls XFlush()
    } while (evt.type != ButtonRelease);
	
	// 收到鼠标按键后：销毁窗口，断开连接，退出程序
	XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);

    return 0;
}