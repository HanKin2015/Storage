/*
������	����	˵��	��Ŀ	�ļ�	��	��ֹ��ʾ״̬
����	C4996	'access': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _access. See online help for details.	StudySTL	D:\Github\Storage\windows\StudySTL\study_fopen.h	71

ѡ����Ŀ->XXX���ԡ���������ҳ��֮������������ѡ����������->C/C++->Ԥ��������
����ڵ�����Ԥ����������ĶԻ����У����롰_CRT_NONSTDC_NO_DEPRECATE���͡�_CRT_SECURE_NO_WARNINGS�����ֱ��ʾʹ�÷Ǳ�׼�����Ͳ��������棬�������ȷ��������
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
 * ��ȡ��ǰʱ��
 * @param [out]current_time ��ǰʱ��
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
 * ��ȡ��ǰ����
 * @param [out]current_date ��ǰ����
 * @return
 * @remark ��ʽ��20210309/
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
 * �����༶Ŀ¼
 * @param [in]path  ·��
 * @return true�����ɹ�, false����ʧ��
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
    //����ĩβδ��б��/
    if (length > 0 && access(str, F_OK)) {
        if (mkdir(str)) {
            printf("[usb record] mkdir folder failed");
            return false;
        }
    }
    return true;
}

/*
* ����һ��bug��fopen��һ��û�д������ļ�ʧ��
* ���⣺�м���һ��δ�������ļ���
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
