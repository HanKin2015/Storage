/*
严重性	代码	说明	项目	文件	行	禁止显示状态
错误	C4996	'access': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _access. See online help for details.	StudySTL	D:\Github\Storage\windows\StudySTL\study_fopen.h	71

选择“项目->XXX属性”，打开属性页。之后在左侧的树中选择“配置属性->C/C++->预处理器”
最后，在弹出的预处理器定义的对话框中，输入“_CRT_NONSTDC_NO_DEPRECATE”和“_CRT_SECURE_NO_WARNINGS”，分别表示使用非标准函数和不弹出警告，最后点击“确定”按键
*/

#pragma once

#include "common.h"
#include "study_zip.h"

static int fopen_file(string file_path)
{
	size_t idx = file_path.find_last_of('\\');
	string prefix = file_path.substr(0, idx+1);
	printf("dir path [ %s ] is %sexist!\n", prefix, IsExist(prefix) ? "" : "not ");

	FILE* fp = fopen(file_path.c_str(), "a");
	if (!fp) {
		printf("fopen file [ %s ] failed!\n", file_path.c_str());
		return -1;
	}
	fprintf(fp, "hello world!\n");
	fclose(fp);
	return 0;
}

#define MALLOC_MAX_LENGTH 256
/*
 * 获取当前时间
 * @param [out]current_time 当前时间
 * @return
 */
static void get_current_time(char* current_time)
{
    if (current_time == NULL) {
        printf("[usb record] parameter[in] is NULL");
        return;
    }
    time_t tm = time(NULL);
    strftime(current_time, MALLOC_MAX_LENGTH, "%Y/%m/%d %H:%M:%S", localtime(&tm));
    return;
}

/*
 * 获取当前日期
 * @param [out]current_date 当前日期
 * @return
 * @remark 格式如20210309/
 */
static void get_current_date(char* current_date)
{
    if (current_date == NULL) {
        printf("[usb record] parameter[in] is NULL");
        return;
    }
    time_t tm = time(NULL);
    strftime(current_date, MALLOC_MAX_LENGTH, "%Y%m%d/", localtime(&tm));
    return;
}

/*
 * 创建多级目录
 * @param [in]path  路径
 * @return true创建成功, false创建失败
 */
static bool mkdirs(const char* path)
{
    char str[MALLOC_MAX_LENGTH];
    strncpy(str, path, MALLOC_MAX_LENGTH);

    int length = strlen(str);
    int i;
    for (i = 0; i < length; i++) {
        if (str[i] == '/') {
            str[i] = '\0';
            if (strlen(str) && access(str, F_OK)) {
                if (mkdir(str)) {
                    printf("[usb record] mkdir folder failed");
                    return false;
                }
            }
            str[i] = '/';
        }
    }
    //可能末尾未加斜线/
    if (length > 0 && access(str, F_OK)) {
        if (mkdir(str)) {
            printf("[usb record] mkdir folder failed");
            return false;
        }
    }
    return true;
}

/*
* 测试一个bug，fopen打开一个没有创建的文件失败
* 特殊：中间有一个未创建的文件夹
*/
int test_study_fopen()
{
	fopen_file(R"(.\data\log.txt)");
	fopen_file(R"(.\log\log.txt)");

	char current_time[MALLOC_MAX_LENGTH];
	get_current_time(current_time);
	char current_date[MALLOC_MAX_LENGTH];
	get_current_date(current_date);
	printf("current time: %s, date: %s\n", current_time, current_date);

    string new_dir_path = R"(.\he\hejian\)";
    if (!mkdirs(new_dir_path.c_str())) {
        printf("mkdirs dir path [ %s ] failed!\n", new_dir_path);
        return -1;
    }
	return 0;
}
