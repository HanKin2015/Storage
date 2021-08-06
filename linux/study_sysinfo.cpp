#include <iostream>
#include <cstdio>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>
using namespace std;

#if 0
struct sysinfo {  
      long uptime;          /* 启动到现在经过的时间 */  
      unsigned long loads[3];
      /* 1, 5, and 15 minute load averages */  
      unsigned long totalram;  /* 总的可用的内存大小 */  
      unsigned long freeram;   /* 还未被使用的内存大小 */  
      unsigned long sharedram; /* 共享的存储器的大小*/  
      unsigned long bufferram; /* 共享的存储器的大小 */  
      unsigned long totalswap; /* 交换区大小 */  
      unsigned long freeswap;  /* 还可用的交换区大小 */  
      unsigned short procs;    /* 当前进程数目 */  
      unsigned long totalhigh; /* 总的高内存大小 */  
      unsigned long freehigh;  /* 可用的高内存大小 */  
      unsigned int mem_unit;   /* 以字节为单位的内存大小 */  
      char _f[20-2*sizeof(long)-sizeof(int)]; /* libc5的补丁 */
};
#endif

//用户在线状态信息
#pragma pack(push, 1)
typedef struct _SYSTEM_INFO
{
    uint32_t  TotalPhys;    // 物理内存总数，MB
    uint32_t  UsagePhys;    // 使用的物理内存，MB
} SYSTEM_INFO;
#pragma pack(pop)

#define KBYTES (1UL << 10)
#define MBYTES (KBYTES << 10)
#define GBYTES (MBYTES << 10)

static int study_sysinfo()
{
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) < 0) {
        printf("get system info error: %m\n");
        return -1;
    }
    SYSTEM_INFO si;
    //si.TotalPhys = htonl(sys_info.totalram / MBYTES);
    //si.UsagePhys = htonl((sys_info.totalram - sys_info.freeram) / MBYTES);
    si.TotalPhys = sys_info.totalram / MBYTES;
    si.UsagePhys = (sys_info.totalram - sys_info.freeram) / MBYTES;

    printf("TotalPhys = %d MB\n", si.TotalPhys);
    printf("UsagePhys = %d MB\n", si.UsagePhys);
    return 0;
}

int main()
{
    study_sysinfo();
    
    struct sysinfo info;
    int iRetVal = -1;       /*用于获取函数的返回值，默认为-1*/
    iRetVal = sysinfo(&info);
    printf("return val         : %d\n",  iRetVal);          // 打印函数返回值，成功为0，失败为-1  
    printf("uptime             : %ld\n", info.uptime);      // 打印从设备开启到现在的时间，单位为秒    
    printf("1  min load average: %lu\n", info.loads[0]);    
    printf("5  min load average: %lu\n", info.loads[1]);    
    printf("15 min load average: %lu\n", info.loads[2]);    // 平均负载    
    printf("totalram           : %lu kB\n", info.totalram  / KBYTES);    // 总的可用的内存大小  
    printf("freeram            : %lu kB\n", info.freeram   / KBYTES);     // 还未被使用的内存大小
    printf("sharedram          : %lu kB\n", info.sharedram / KBYTES);   // 共享的存储器的大小
    printf("bufferram          : %lu kB\n", info.bufferram / KBYTES);   // 共享的存储器的大小
    printf("totalswap          : %lu kB\n", info.totalswap / KBYTES);   // 交换区大小
    printf("freeswap           : %lu kB\n", info.freeswap  / KBYTES);    // 还可用的交换区大小
    printf("procs              : %u\n",  info.procs);       // 当前进程数目
    printf("totalhigh          : %lu\n", info.totalhigh);   // 总的高内存大小 
    printf("freehigh           : %lu\n", info.freehigh);    // 可用的高内存大小
    printf("mem_unit           : %d\n", info.mem_unit);     // 以字节为单位的内存大小
    return 0;
}