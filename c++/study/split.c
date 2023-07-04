/**
* 文 件 名: split.c
* 文件描述: split函数实现
* 作    者: HanKin
* 创建日期: 2023.07.03
* 修改日期：2023.07.03
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

static int split1(char *src, const char *separator, char ***dest, int *num)
{
    char *token = NULL;
    
    if (src == NULL || strlen(src) == 0) {
        printf("src is NULL\n");
        return -1;
    }

    if (separator == NULL || strlen(separator) == 0) {
        printf("separator is NULL\n");
        return -1;
    }

    *num = 0;
    token = strtok(src, separator);
    while (token != NULL) {
        *dest = (char **)realloc(*dest, ((*num) + 1)*sizeof(char *));
        if (*dest == NULL) {
            printf("realloc failed\n");
            return -1;
        }
        (*dest)[*num] = (char *)malloc(strlen(token) + 1);
        if ((*dest)[*num] == NULL) {
            printf("malloc failed\n");
            return -1;
        }
        strcpy((*dest)[*num], token);
        (*num)++;
        
        printf("*num %d %s %s\n", *num, token, (*dest)[*num - 1]);
        token = strtok(NULL, separator);  
    }
    return 0;
}

char **split(char *str, const char *delim, int *count)
{
    if (str == NULL || strlen(str) == 0) {
        printf("str is NULL\n");
        return NULL;
    }

    if (delim == NULL || strlen(delim) == 0) {
        printf("delim is NULL\n");
        return NULL;
    }
    
    char **result = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    int i = 0;

    token = strtok_r(str, delim, &saveptr);
    while (token != NULL) {
        result = (char **)realloc(result, (i + 1) * sizeof(char *));
        if (result == NULL) {
            printf("realloc failed\n");
            return NULL;
        }
        result[i] = token;
        i++;
        token = strtok_r(NULL, delim, &saveptr);
    }

    *count = i;
    return result;
}

static int my_split(char *src, const char *separator, char **dest, int *num)
{
    char *token = NULL;
    
    if (src == NULL || strlen(src) == 0) {
        printf("src is NULL\n");
        return -1;
    }

    if (separator == NULL || strlen(separator) == 0) {
        printf("separator is NULL\n");
        return -1;
    }

    *num = 0;
    token = strtok(src, separator);
    while (token != NULL) {
        dest = (char **)realloc(dest, ((*num) + 1)*sizeof(char *));
        if (dest == NULL) {
            printf("realloc failed\n");
            return -1;
        }
        dest[*num] = token; 
        (*num)++;
        
        printf("*num %d %s %s\n", *num, token, dest[*num - 1]);
        token = strtok(NULL, separator);  
    }
    return 0;
}

static char **my_split_(char *src, const char *separator, int *num)
{
    char *token = NULL;
    
    if (src == NULL || strlen(src) == 0) {
        printf("src is NULL\n");
        return NULL;
    }

    if (separator == NULL || strlen(separator) == 0) {
        printf("separator is NULL\n");
        return NULL;
    }

    *num = 0;
    char **dest = NULL;
    token = strtok(src, separator);
    while (token != NULL) {
        dest = (char **)realloc(dest, ((*num) + 1)*sizeof(char *));
        if (dest == NULL) {
            printf("realloc failed\n");
            return NULL;
        }
        dest[*num] = token; 
        (*num)++;
        
        printf("*num %d %s %s\n", *num, token, dest[*num - 1]);
        token = strtok(NULL, separator);  
    }
    return dest;
}

// <Dev ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Ep="82" Aligned="8192" ></Dev>
// ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Param="Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024"
int main()
{
    char str1[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    
    char **dest = NULL;
    int num = 0;
    if (split1(str1, ";", &dest, &num) == 0) {
        printf("num = %d\n", num);
        for (int i = 0; i < num; i++) {
            printf("%s\n", dest[i]);
            free(dest[i]);
        }
    } else {
        printf("memory allocation failure!\n");
    }
    
    int count = 0;
    char str[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    printf("str = %s\n", str);
    char **result = split(str, ";", &count);
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }
    free(result);
    
    // 或许是局部释放了，因此会出现段错误
    char my_str[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    printf("my_str = %s\n", my_str);
    char **my_dest = NULL;
    int cnt = 0;
    if (my_split(my_str, ";", my_dest, &cnt) == 0) {
        printf("%d: cnt = %d\n", __LINE__, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("%s\n", my_dest[i]);
            //free(my_dest[i]);
        }
    } else {
        printf("memory allocation failure!\n");
    }
    free(my_dest);
    
    // 改成返回值就可以了
    char my_str_[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    printf("my_str_ = %s\n", my_str_);
    cnt = 0;
    char **my_dest_ = my_split_(my_str_, ";", &cnt);
    if (my_dest_ != NULL) {
        printf("%d: cnt = %d\n", __LINE__, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("%s\n", my_dest_[i]);
            //free(my_dest_[i]);
        }
    } else {
        printf("memory allocation failure!\n");
    }
    free(my_dest_);
    return 0;
}
