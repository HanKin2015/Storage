#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_BUF_LEN 255

/*
 * 获取当前时间
 * @param [out]current_time 当前时间
 * @return 
 */
static char *get_cur_time()
{
        static char cur_time[MAX_BUF_LEN];
        time_t tm = time(NULL);
        strftime(cur_time, MAX_BUF_LEN, "%Y/%m/%d %H:%M:%S", localtime(&tm));
        return cur_time;
}

/*
 * 获取当前日期
 * @param [out]current_date 当前日期
 * @return
 * @remark 格式如20210309/
 */
static char *get_cur_date()
{
        char current_date[MAX_BUF_LEN];
        time_t tm = time(NULL);
        strftime(current_date, MAX_BUF_LEN, "%Y%m%d/", localtime(&tm));
        return current_date;
}

int main()
{
    char tmp[MAX_BUF_LEN];
    int num = 123;
    snprintf(tmp, MAX_BUF_LEN, "%02x", num);
    printf("tmp: %s\n", tmp);

    char *cur_date = get_cur_date();
    char *cur_time = get_cur_time();
    printf("date: %s time: %s\n", cur_date, cur_time);

    char null_str[MAX_BUF_LEN];
    memcpy(tmp, null_str, MAX_BUF_LEN);
    printf("tmp: %s %d %d\n", tmp, strlen(tmp), sizeof(tmp));
    return 0;
}
