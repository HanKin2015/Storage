#include <stdio.h>
#include "mini_log.h"

int main()
{
    log_init();
    LOGI("hello world");
    LOGE("hello world");
    LOGD("hello world");
    LOGW("hello world");
    log_deinit();
    return 0;
}