#include <stdio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

typedef long long           int64_t;
typedef unsigned long long  uint64_t;

/// 时间转换
static uint64_t file_time_2_utc(const FILETIME* ftime)
{
    LARGE_INTEGER li;

    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

/// 获得CPU的核数
static int get_processor_number()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return (int)info.dwNumberOfProcessors;
}

int get_cpu_usage(int pid)
{
    //cpu数量
    static int processor_count_ = -1;
    //上一次的时间
    static int64_t last_time_ = 0;
    static int64_t last_system_time_ = 0;

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    int64_t system_time;
    int64_t time;
    int64_t system_time_delta;
    int64_t time_delta;

    int cpu = -1;

    if(processor_count_ == -1)
    {
        processor_count_ = get_processor_number();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }
    system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time))
        / processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0))
    {
        last_system_time_ = system_time;
        last_time_ = time;
        return get_cpu_usage(pid);
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;

    if (time_delta == 0)
        return get_cpu_usage(pid);

    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
}

int main()
{
    int cpu;
    int process_id;
    // 参数为进程id
    cin>>process_id;

    while(1)
    {
        cpu = get_cpu_usage(process_id);
        printf("CPU使用率: %d%%\n",cpu);

        Sleep(1000);
    }
    return 0;
}
