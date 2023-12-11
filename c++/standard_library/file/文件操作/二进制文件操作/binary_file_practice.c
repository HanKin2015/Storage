/*******************************************************************************
* 文 件 名: binary_file_practice.c
* 文件描述: 练习实战
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// 取消对齐
#pragma pack(1)

//几个时间单位常量
#define DEFAULT_HISTORY_HOUR (4)
#define ONE_MINUTE_SECONDS (60)
#define ONE_HOUR_SECONDS (60*ONE_MINUTE_SECONDS)
#define ONE_DAY_SECONDS	(24*ONE_HOUR_SECONDS)
#define ONE_WEEK_SECONDS (7*ONE_DAY_SECONDS)

#define NET_RECORD_OUT_TMP_PATH "/tmp/net_state_up_tmp.bin"
//过滤网络状态历史记录结构
typedef struct _NetStatusFilter
{
    uint32_t start_time;		//开始时间戳
    uint32_t end_time;			//结束时间戳
}NetStatusFilter;

//网络探测记录VDC用户最大为96个字符
#define NET_USER_NAME_LEN 96

#define FIVE_SECONDS 5*60

//每个网络状态文件日志保存结构
typedef struct _NetStatusLogInfo
{
    uint32_t event_time;    //客户端记录的网络事件时间点
    uint32_t server_ip;     //链接的服务器IP
    uint32_t vm_tag;        //虚拟机唯一标识(过滤检索使用)
    uint16_t delay;         //时延
    uint16_t jitter;        //抖动
    uint8_t  link_proto;    //协议类型，0：srap，1：HEDC，2:3D
    uint8_t  link_type;     //连接类型，0：直连，1：代理
    char user_name[NET_USER_NAME_LEN + 1];//会话接入VDI用户名,长度96+1
} NetStatusLogInfo;

uint8_t g_link_type = 0;
uint8_t g_link_proto = 0; 

static char *uint32_convert_ip(uint32_t decimal_)
{
    uint8_t bytes[4];
    uint32_t decimal = htonl(decimal_);
    bytes[0] = (decimal >> 24) & 255;
    bytes[1] = (decimal >> 16) & 255;
    bytes[2] = (decimal >> 8) & 255;
    bytes[3] = decimal & 255;
    //printf("对应的ip地址为: %d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    static char ip[BUFSIZ] = { 0 };
    snprintf(ip, BUFSIZ, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
    
    struct in_addr network;
    network.s_addr = decimal_;
    //printf("IP : %s\n", inet_ntoa(network));
    return ip;
}

/**
* @brief  过滤出一段时间的数据
* @note   数据是每秒中获取一次，5分钟内所以有300条数据
* @param  data   [in] 网络数据
* @param  count  [in] 数据数量
* @param  filter [in] 过滤器
* @param  latency_list [out] 时延列表
* @param  jitter_list  [out] 抖动列表
* @return 无
*/
static void filter_time_slot_data(const char *data, const uint32_t count,
                                  const NetStatusFilter filter, int *latency_list, int *jitter_list)
{
    NetStatusLogInfo *pstart = (NetStatusLogInfo *)data;
    NetStatusLogInfo *pend = pstart + count - 1;
    time_t timestamp = htonl(pstart->event_time);
    char *tmp = ctime(&timestamp);
    char start_timestr[BUFSIZ] = { 0 };
    strncpy(start_timestr, tmp, strlen(tmp)-1); // 去掉换行符
    timestamp = htonl(pend->event_time);
    tmp = ctime(&timestamp);
    char end_timestr[BUFSIZ] = { 0 };
    strncpy(end_timestr, tmp, strlen(tmp)-1);
    printf("this file record %s to %s time slot net status.\n", start_timestr, end_timestr);
    if (filter.start_time > htonl(pend->event_time) || filter.end_time < htonl(pstart->event_time)) {
        printf("no time begin from %u to %u history log.\n", filter.start_time, filter.end_time);
        if (count < FIVE_SECONDS) {
            pstart = (NetStatusLogInfo *)data;
        } else {
            pstart = (NetStatusLogInfo *)(data + (count - FIVE_SECONDS) * sizeof(NetStatusLogInfo));
        }
    } else {
        //二分查找start_time所在记录位置
        uint32_t low = 0;
        uint32_t high = count - 1;
        uint32_t mid = (low + high) / 2;

        while (low < high && mid >= 1) {
            pstart = (NetStatusLogInfo*)(data + mid * sizeof(NetStatusLogInfo));

            if (htonl(pstart->event_time) == filter.start_time) {
                break;
            } else if (htonl(pstart->event_time) > filter.start_time) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
            mid = (low + high) / 2;

        }
        pstart = (NetStatusLogInfo *)(data + mid * sizeof(NetStatusLogInfo));
    }
    
    //获取开始到结束时间段记录
    for (int i = 0; i < FIVE_SECONDS && i < count; i++) {
        if (htonl(pstart->event_time) > filter.end_time) {
            break;
        }
        //printf("%8s = %d\n", "id", i+1);
        //printf("%8s = %d\n", "latency", ntohs(pstart->delay));
        //printf("%8s = %d\n\n", "jitter", ntohs(pstart->jitter));
        *(latency_list++) = ntohs(pstart->delay);
        *(jitter_list++) = ntohs(pstart->jitter);
        g_link_proto = pstart->link_proto;
        g_link_type = pstart->link_type;
        pstart++;
        actual_count++;
    }
    return;
}

int compare(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

static char *read_binary_file(const char *filename, NetStatusFilter filter)
{
    assert(filename);
    
    FILE *fp = fopen(filename, "rb");
    assert(fp);
    
    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    printf("file[%s] size: %ld bytes\n", filename, file_size);
    
    char *buffer = (char *)malloc(file_size);
    assert(buffer);
    memset(buffer, 0, file_size);
    
    fseek(fp, 0L, SEEK_SET);
    fread(buffer, sizeof(char), file_size, fp);
    
    //计算网络状态日志记录个数
    int iLogNodeSize = sizeof(NetStatusLogInfo);
    printf("结构体对齐有影响: %d\n", iLogNodeSize);
    
    uint32_t count = file_size / iLogNodeSize;
    printf("count: %d\n", count);
    
    //校验数据完整性，数据不完整返回空
    if (count * sizeof(NetStatusLogInfo) != file_size) {
        printf("net status data is invalid, delete read buffter. file size: %lu, unit: %lu, count: %d, %lu\n", 
                file_size, sizeof(NetStatusLogInfo), count, count * sizeof(NetStatusLogInfo));
        count = 0;
        if (buffer) {
            free(buffer);
            buffer = NULL;
        }
    }
    fclose(fp);
    fp = NULL;

    NetStatusLogInfo *iter = NULL;
    for (int i = 0; i < 2; i++) {
        iter = (NetStatusLogInfo *)(buffer + i * iLogNodeSize);
        printf("%12s = %d\n", "id", i+1);
        printf("%12s = %d\n", "event_time", ntohl(iter->event_time));
        printf("%12s = %s\n", "user_name", iter->user_name);
        printf("%12s = %s\n", "server_ip", uint32_convert_ip(iter->server_ip));
        printf("%12s = %d\n", "vm_tag", ntohl(iter->vm_tag));
        printf("%12s = %d\n", "latency", ntohs(iter->delay));
        printf("%12s = %d\n", "jitter", ntohs(iter->jitter));
        printf("%12s = %d\n", "link_proto", iter->link_proto);
        printf("%12s = %d\n\n", "link_type", iter->link_type);
    }
    
    int latency_list[FIVE_SECONDS] = { 0 };
    int jitter_list[FIVE_SECONDS] = { 0 };
    filter_time_slot_data(buffer, count, filter, latency_list, jitter_list);
    qsort(latency_list, FIVE_SECONDS, sizeof(int), &compare);
    qsort(jitter_list, FIVE_SECONDS, sizeof(int), &compare);
    
    printf("latency_list[%d, %d, %d] jitter_list[%d, %d, %d]\n",
            latency_list[0], latency_list[FIVE_SECONDS-1], latency_list[FIVE_SECONDS/2],
            jitter_list[FIVE_SECONDS], jitter_list[FIVE_SECONDS-1], jitter_list[FIVE_SECONDS/2]);
    printf("g_link_proto: %d, g_link_type: %d\n", g_link_proto, g_link_type);
    return buffer;
}

int main(void) 
{
    // 获取当前时间
    time_t timestamp;
    time(&timestamp);
    printf("当前时间戳为：%ld\n", timestamp);

    timestamp = 1700126760;
    
    struct tm *local_tm = localtime(&timestamp);
    char filename[BUFSIZ] = { 0 };
    (void)strftime(filename, BUFSIZ, "%Y-%m-%d", local_tm); 

    // 查询从当前时间到5分钟之前的时延和抖动
    NetStatusFilter filter = {timestamp-FIVE_SECONDS, timestamp};
    read_binary_file(filename, filter);
    
    FILE *fp = fopen("/sys/module/lp/coresize", "r");
    assert(fp);
    int dwc_driver = 0;
    fscanf(fp, "%d", &dwc_driver);
    printf("dwc_driver = %d\n", dwc_driver);
    return 0;
}
/*
当前时间戳为：1700137081
file[2023-11-16] size: 2597505 bytes
结构体对齐有影响: 115
count: 22587
          id = 1
  event_time = 1700100000
   user_name = test
   server_ip = 110.170.25.59
      vm_tag = 3
     latency = 1
      jitter = 1
  link_proto = 0
   link_type = 0

          id = 2
  event_time = 1700100001
   user_name = test
   server_ip = 110.170.25.59
      vm_tag = 3
     latency = 1
      jitter = 0
  link_proto = 0
   link_type = 0

this file record Thu Nov 16 10:00:00 2023 to Thu Nov 16 17:27:20 2023 time slot net status.
latency_list[1, 23, 1] jitter_list[0, 21, 0]
g_link_proto: 1, g_link_type: 1
dwc_driver = 20480
*/