#include "../src/log.h"
#include <iostream>
#include <string.h>

static void test_init_log()
{
    const char *log_file_path = "./test.log";
    init_log(log_file_path);
    LOGI("hello world!");
    return;
}

static void test_printf_log()
{
    std::string str = "test";
    
    LOGI("%s: info", str.c_str());
    LOGW("%s: warning", str.c_str());
    LOGD("%s: debug", str.c_str());
    LOGE("%s: error", str.c_str());
    
    LOGE("pvid = %s:%s", str.c_str(), str.c_str());
    return;
}

#if 1
int main(int argc, char **argv)
{
    test_printf_log();
    test_init_log();
    return 0;
}
#endif