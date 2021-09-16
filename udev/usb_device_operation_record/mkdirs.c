#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
 * 创建多级目录
 * @param [in]path  路径
 * @return true创建成功, false创建失败
 */
static bool mkdirs(char *path, int len) 
{
    char str[256];    
    strncpy(str, path, 256);

    printf("path: %s, len: %d\n", path, len);
    
    int i;
    for (i = 0; i < len; i++) {
        if (str[i] == '/') {
            str[i] = '\0';
            printf("str: %s, len: %d i: %d\n", str, strlen(str), i);
            if (strlen(str) && access(str, F_OK)) {
                if (mkdir(str, S_IRWXU)) {
                    printf("[usb record] mkdir folder failed");
                    return false;
                }
            }
            str[i] = '/';
        }
    }
    //可能末尾未加斜线/
    if (length > 0 && access(str, F_OK)) {
        if (mkdir(str, S_IRWXU)) {
            printf("[usb record] mkdir folder failed");
            return false;
        }
    }
    return true;
}

int file_size(char*filename)

{

    FILE*fp = fopen(filename, "r");
    if(!fp) {
        return -1;
    }
    fseek(fp,0L,SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

int main()
{
	char *path = "/media/hankin/a/b";
	if (!mkdirs(path)) {
		printf("mkdirs path failed\n");
	} else {
		printf("mkdirs path success\n");
	}
	system("mkdir -p /media/hankin/b/a");
	return 0;
}
