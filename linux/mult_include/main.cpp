#include <iostream>
#include "log.h"
#include "compute.h"

int main()
{
    LOGI("main");
    
    LOGE("4 + 5 = %d", sum(4, 5));
    return 0;
}
