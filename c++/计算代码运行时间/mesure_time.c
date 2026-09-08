/*******************************************************************************
* 文 件 名: mesure_time.c
* 文件描述: 使用宏测量时间更方便
* 备    注: 
* 作    者: HanKin
* 创建日期: 2026.08.24
* 修改日期:2026.08.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

#ifndef BUFSIZ
    #define BUFSIZ 1024
#endif
#define DDR_SIZE_2GB_THRESHOLD_BYTES (1ULL * 1024 * 1024 * 1024 + 512ULL * 1024 * 1024)

#define MEASURE_TIME(func_call, time_cost_key) \
    do { \
        ulong start = get_timer(0); \
        printf("start = %lu\n", start); \
        func_call;\
        char time_cost[BUFSIZ] = { 0 }; \
        (void)snprintf(time_cost, sizeof(time_cost), "%lu", get_timer(start)); \
        printf("end = %lu, time_cost = %s\n", get_timer(0), time_cost); \
        char tmp[BUFSIZ] = { 0 }; \
        (void)snprintf(tmp, sizeof(tmp), "%s=", time_cost_key); \
        (void)Setenv2Bootargs(tmp, time_cost); \
    } while(0)

MEASURE_TIME({
        check_ddr_freq_test();
        check_ddr_result();
        char* env_ddr_freq_test = NULL;
        env_ddr_freq_test = getenv("ddr_freq_test");
        if(env_ddr_freq_test != NULL)
        {
            Setenv2Bootargs("ddr_freq_test=",env_ddr_freq_test);
        }
    }, "ddr_freq_cost");

int main()
{
	通用的统计工具函数:  - 使用宏（更灵活，无需关心参数）  - 函数指针需要关注参数，另外就是如果原函数分成多步执行，无法同时计时  - 直接在代码里插桩（最简单，不用改架构）
	return 0;
}

#ifndef BUFSIZ
    #define BUFSIZ 1024
#endif
#define DDR_SIZE_2GB_THRESHOLD_BYTES (1ULL * 1024 * 1024 * 1024 + 512ULL * 1024 * 1024)

#define MEASURE_TIME(func_call, time_cost_key) \
    do { \
        unsigned long __mt_start = get_timer(0); \
        printf("start = %lu\n", __mt_start); \
        func_call; \
        unsigned long __mt_elapsed = get_timer(__mt_start); \
        char __mt_val[32] = { 0 }; \
        int __mt_n = snprintf(__mt_val, sizeof(__mt_val), "%lu", __mt_elapsed); \
        if (__mt_n > 0 && (size_t)__mt_n < sizeof(__mt_val)) { \
            unsigned long __mt_end = get_timer(0); \
            printf("end = %lu, time_cost = %s\n", __mt_end, __mt_val); \
            char __mt_key[64] = { 0 }; \
            int __mt_k = snprintf(__mt_key, sizeof(__mt_key), "%s=", time_cost_key); \
            if (__mt_k > 0 && (size_t)__mt_k < sizeof(__mt_key)) { \
                (void)Setenv2Bootargs(__mt_key, __mt_val); \
            } else { \
                printf("Warning: time_cost_key truncated: %s\n", time_cost_key); \
            } \
        } else { \
            printf("Warning: failed to format time cost for %s\n", time_cost_key); \
        } \
    } while(0)