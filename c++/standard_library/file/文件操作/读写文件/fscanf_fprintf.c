/**
* �� �� ��: fscanf_fprintf.cpp
* �ļ�����: fscanf��fprintf������д�ļ�
* ��    ��: HanKin
* ��������: 2021.06.10
* �޸����ڣ�2022.08.09
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <time.h>
#include <io.h>

void file_write(char* data)
{
	char* dir_path = "./usb/";
	//�ж��ļ����Ƿ����
    if (!access(dir_path, F_OK)) {
        printf("dir exist.");
    } else {
		mkdir(dir_path);
        printf("dir not exist.");
    }
	 
    char* usb_device_operation_header = "./usb/usb_device_operation_";
    char* vmid = "3158";

    char* usb_device_operation_path = (char*)malloc(strlen(usb_device_operation_header) + strlen(vmid) + strlen(".log"));

    sprintf(usb_device_operation_path, "%s%s.log", usb_device_operation_header, vmid);

    //�ж��ļ��Ƿ����
     if (!access(usb_device_operation_path, F_OK)) {
        printf("file exist.");
     } else {
        printf("file not exist.");
     }

    FILE* fd;
    fd = fopen(usb_device_operation_path, "a");
    if (fd == NULL) {
        printf("open usb_device_operation file failed!");
        return;
    }

    //��������: ʱ��/�ص�/����/����/��ע
    time_t t = time(0);
    char* cur_time = (char*)malloc(64);
    strftime(cur_time, sizeof(cur_time), "%Y/%m/%d %X %A �����%j�� %z", localtime(&t));

    char* location = "CS";
    char* count = "6";
    char* weather = "cloud";
    char* remark = "well good";

    fprintf(fd, "%s,%s,%s,%s,%s;\n", cur_time, location, count, weather, remark);

    fclose(fd);
    return;
}

void file_read()
{
    const char* usb_device_operation_path = "./usb_device_operation.txt";

    FILE* fd;
    fd = fopen(usb_device_operation_path, "a");
    if (fd == NULL) {
        printf("open usb_device_operation file failed!");
        return;
    }

    fprintf(fd, "%s\n", data);

    fclose(fd);
    return;
}

int main(int argc, char *argv[])
{
    file_write("hello world");
    file_read();
    return 0;
}
