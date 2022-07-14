/**
* 文 件 名: exec_shell.c
* 文件描述: 执行shell命令
* 作    者: HanKin
* 创建日期: 2022.07.12
* 修改日期：2022.07.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
 * @brief 运行shell命令
 * @note 运行结果输出长度不超过outputLen且只输出第一行，超过会截断
 * @param cmd        [in] shell命令
 * @param output     [out] 运行结果输出
 * @param output_len [in] 运行结果字符串长度
 * @return 无
 */
static void exec_shell_cmd(const char *cmd, char *output, int output_len)
{
    if (cmd == NULL) {
        printf("cmd is null\n");
        return;
    }

    int buffer_len = 0;
    FILE *fp = NULL;
    char buffer[BUFSIZ] = { 0 };

    fp = popen(cmd, "r");
    if (!fp) {
        printf("popen error: %m\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer_len = strlen(buffer);
        if (buffer[buffer_len - 1] == '\n') {
            buffer[buffer_len - 1] = '\0';
        }
        if (*buffer != '\0') {
            printf("buffer: %s\n", buffer);
        }

        if (output) {
            if (output_len < 1) {
                printf("output_len is invalid\n");
                break;
            }
            strncpy(output, buffer, buffer_len > output_len ? output_len : buffer_len);
            output[output_len - 1] = '\0';
            break;
        }
    }

    if (fp) {
        pclose(fp);
        fp = NULL;
    }
    return;
}

int main(int argc, char *argv[])
{
    char current_user[BUFSIZ] = { 0 };
    exec_shell_cmd("echo $USER", current_user, BUFSIZ);
    printf("current user name: %s\n", current_user);
    
    const char *cmd = "chmod 666 /home/hejian/log/log";
    exec_shell_cmd(cmd, NULL, 0);
    return 0;
}