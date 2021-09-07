#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER 256

static char* trim(char* str, const char* delim)
{
    char* p1 = str;
    char* p2 = NULL;
    int len;

    if (str == NULL || str[0] == 0)
        return str;
    len = strlen(p1);
    p2 = p1 + len - 1;
    while (strchr(delim, *p1))
        p1++;
    if(p1>p2)
        return NULL;
    if (*p1 == 0)
        return p1;


    while (strchr(delim, *p2))
        p2--;
    if(p2<str)
        return NULL;
    *(p2+1) = 0;
    return p1;
}

/**
 * 对 ini 文件进行读取配置项, 形式类似:
 * [section]
 * key=XXXXX
 *
 * @note visibility用于设置动态链接库中函数的可见性，将变量或函数设置为hidden，则该符号仅在本so中可见，在其他库中则不可见。
 *      https://www.cnblogs.com/bugutian/articles/4746946.html
 *
 * @param
 *  filename[in] 配置文件路径
 *  section[in]
 *  key[in]
 *  value[out] 对应配置项的值，需事先分配好空间
 *  value_size[in] 事先分配好的空间大小, 字节为单位
 *
 * @return
 *  0, fail
 *  other, value's length
 */
__attribute ((visibility("default"))) int config_file_get(const char *filename, 
						const char *section, const char *key, char *value, int value_size)
{
    FILE* file = 0;
    char buff[MAX_BUFFER];
    char* line = 0;
    int length = 0;
    int sec_len = strlen(section);
    int key_len = strlen(key);
    char* pos = 0;
    int findflag = 0; //0: none-find section, 1:find section, but none-find key, 2:find key

    if (value == NULL || value_size < 1) {
        perror("argument");
        return 0;
    }
    memset(value, 0, value_size);

    file = fopen(filename, "rt");
    if (!file) {
        perror("fopen");
        return 0;
    }

    while(!feof(file))
    {
        line = buff;
        if (0 == fgets(line, sizeof(buff), file)) {
            goto __end;
        }
        trim(line, " \r\n\t");

		if (line[0]=='#') {
			continue;
		}
        if (line[0]=='['
                && line[strlen(line)-1]==']'
           )
        {
            if (0 == findflag
                    && strncmp(&line[1], section, sec_len)==0
                    && line[sec_len+1]==']'
               )
            {
                findflag = 1;
            }
            else
            {
                findflag = 0;
            }
            continue;
        }

        if (1 == findflag)
        {
            pos = strchr(line, '=');
            if (pos)
            {
                *pos = 0;
                if (strncmp(trim(line, " \r\n\t"), key, key_len)==0)
                {
                    pos++;
                    findflag = 2;
                }
            }
        }

        if (2 == findflag)
        {
            char* v = trim(pos, " \r\n\t");
            length = strlen(v);
            memset(value, 0, value_size);
            strncpy(value, v, value_size - 1);
            goto __end;
        }
    }


__end:
    if (file)
    {
        fclose(file);
    }
    return length;
}

int main()
{
    const char *ini_file_path = "./conf.ini";
    const char *section = "hoppy";
    const char *key = "football";
    int value_size = MAX_BUFFER;
    char value[value_size];

    int ret = config_file_get(ini_file_path, section, key, value, value_size);
    printf("ret = %d\n", ret);
    
    if (ret) {
        printf("file: %s, section: %s, key: %s, value: %s\n", ini_file_path, section, key, value);
    }
    return 0;
}