#include <iostream>
#include <ctime>
#include <time.h>

using namespace std;

/*
 * @brief 获取当前时间
 */
static uint64_t get_time_now()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    char *current_time = nullptr;
    current_time = (char*)malloc(1024);
    time_t tm = time(nullptr);
    strftime(current_time, 1024, "%Y/%m/%d %H:%M:%S", localtime(&tm));
    printf("%s\n", current_time);

    return ((uint64_t) ts.tv_sec) * 1000000000 + ts.tv_nsec;
}


int main(int argc, char *argv[])
{
    cout << get_time_now() << endl;
    return 0;
}