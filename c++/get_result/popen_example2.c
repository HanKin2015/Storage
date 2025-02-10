/*******************************************************************************
* 文 件 名: popen_example2.c
* 文件描述: popen函数
* 备    注: popen函数实际应用
* 作    者: HanKin
* 创建日期: 2025.02.10
* 修改日期：2025.02.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int opt = 0;
    scanf("%d", &opt);
    char card_number[BUFSIZ] = { 0 };
    FILE *fp = popen("aplay -l | grep Castor | awk '{print $2}' | tr -d ':'", "r");
    if (fp) {
        if (fgets(card_number, sizeof(card_number), fp) != NULL) {
            size_t len = strlen(card_number);
            if (len > 0 && card_number[len - 1] == '\n') {
                card_number[len - 1] = '\0';
            }
            printf("Castordevbususb card number is %s\n", card_number);
            char alsa_cmd[BUFSIZ] = { 0 };
            if (opt == 1) {
                snprintf(alsa_cmd, BUFSIZ,  "alsamixer -c %s sset 'PCM' 10%%+", card_number);
                popen(alsa_cmd, "r");
            } else if (opt == 2) {
                snprintf(alsa_cmd, BUFSIZ,  "alsamixer -c %s sset 'PCM' 10%%-", card_number);
                popen(alsa_cmd, "r");
            }
        } else {
            printf("popen result is null\n");
        }
        pclose(fp);
        fp = NULL;
    } else {
        printf("popen failed\n");
    }
    return 0;
}
