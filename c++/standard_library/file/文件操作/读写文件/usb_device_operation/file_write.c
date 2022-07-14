#include <stdio.h>
#include <time.h>
#include <io.h>

void file_write(char* data)
{
	char* dir_path = "./usb/";
	//判断文件夹是否存在
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

    //判断文件是否存在
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

    //保存数据: 时间/地点/人数/天气/备注
    time_t t = time(0);
    char* cur_time = (char*)malloc(64);
    strftime(cur_time, sizeof(cur_time), "%Y/%m/%d %X %A 本年第%j天 %z", localtime(&t));

    char* location = "CS";
    char* count = "6";
    char* weather = "cloud";
    char* remark = "well good";

    fprintf(fd, "%s,%s,%s,%s,%s;\n", cur_time, location, count, weather, remark);

    fclose(fd);
    return;
}

void file_read(char* data)
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

int main()
{
    file_write("1234");
    file_write("12345678");
    return 0;
}
