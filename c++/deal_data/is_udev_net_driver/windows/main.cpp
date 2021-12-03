#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <set>
#include <map>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include "USBNetDriverList.h"
using namespace std;

#define INNER_NET_FILE "./udev_net_driver_vpid.txt"
#define Info printf

// 读取文件方案
void readInnerUdevNetDriverVpid(unsigned short v, unsigned short p)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    FILE *fp = NULL;
    unsigned short vid = 0;
    unsigned short pid = 0;
    
    fp = fopen(INNER_NET_FILE, "r");
    if (fp == NULL) {
        Info("fopen file [%s] failed\n", INNER_NET_FILE);
        return;
    }
    
    int index = 0;
    while (fscanf(fp, "0x%hx,0x%hx\n", &vid, &pid) != EOF) {
        //Info("0x%04x, 0x%04x\n", vid, pid);
        //break;
        index++;
        //Info("index: %d\n", index);
        if (v == vid && p == pid) {
            Info("index: %d, [0x%04x:0x%04x]\n", index, vid, pid);
        }
    }
    return;
}

// 内联函数
inline bool IsInUSBNetDriverList(unsigned short vid, unsigned short pid)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
	for (int i = 0; i < USB_NET_DRIVER_NUM; i++)
	{
		if (USBNetDriverList[i][0] == vid && USBNetDriverList[i][1] == pid)
		{
			Info("[usb]device 0x%04x 0x%04x is in usb net driver list!", vid, pid);
			return true;
		}
	}
    return false;
}

int main()
{
    struct timeval timeStart, timeEnd, timeSystemStart; 
    gettimeofday(&timeStart, NULL);
    //usleep(3000000);
    
    //unsigned short vid = 61953, pid = 21360;
    unsigned short vid = 0x0b95, pid = 0x772b;
    //readInnerUdevNetDriverVpid(vid, pid);
    IsInUSBNetDriverList(vid, pid);
    
    gettimeofday(&timeEnd, NULL); 
    double runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;  
    printf("\nrunTime is %lf s\n", runTime);
    return 0;
}