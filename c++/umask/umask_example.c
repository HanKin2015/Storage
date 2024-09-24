/**
* 文 件 名: umask_example.c
* 文件描述: 学习umask函数
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
/* 
 * Linux下设置新建文件时的默认权限掩码 
 * 由umask函数设置 
 * sys/types.h,sys/stat.h 
 * mode_t umask(mode_t umask) 
 * 传入四位八进制数，返回系统原先的权限掩码 
 * 0666对应Linux文件权限中的0000 
 * 0444对应0222 
 *  
 */  
int main(void)  
{  
    mode_t new_umask, old_umask;  
    new_umask = 0666;  
    old_umask = umask(new_umask);  
    printf("系统原来的权限掩码是：%o\n", old_umask);  
    printf("系统新的权限掩码是：%o\n", new_umask);  
    system("touch liu1");  
    printf("创建了文件liu1\n");  
    new_umask = 0444;  
    old_umask = umask(new_umask);  
    printf("系统原来的权限掩码是：%o\n", old_umask);  
    printf("系统新的权限掩码是：%o\n", new_umask);  
    system("touch liu2");  
    printf("创建了文件liu2\n");  
    system("ls liu1 liu2 -l");  
    return 0;   
}
/*执行结果 
[root@ubuntu0006:~/cmake] #./a.out
系统原来的权限掩码是：22
系统新的权限掩码是：666
创建了文件liu1
系统原来的权限掩码是：666
系统新的权限掩码是：444
创建了文件liu2
---------- 1 root root 0 9月  23 21:41 liu1
--w--w--w- 1 root root 0 9月  23 21:41 liu2
*/