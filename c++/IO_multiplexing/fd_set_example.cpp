/**
* 文 件 名: fd_set_example.cpp
* 文件描述: fd_set结构体学习
* 作    者: HanKin
* 创建日期: 2023.02.15
* 修改日期：2023.02.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char **argv)
{    
    fd_set fdset;    
    FD_ZERO (&fdset);                          /*清空集合中所有的元素*/    
    FD_SET(STDOUT_FILENO,&fdset);              /*设置stdout，使集合中包含stdout*/  
       
    if(FD_ISSET(STDOUT_FILENO,&fdset)!=0) {    /*测试stdout是否包含在集合中*/        
        printf("stdout has been set\n");    
    } else {        
        printf("stdout has not been set\n");
    }
         
    FD_CLR(STDOUT_FILENO,&fdset);              /*从位向量中清除stdout*/  
       
    if(FD_ISSET(STDOUT_FILENO,&fdset)!=0) {    /*再次测试*/       
        printf("stdout has been set\n");    
    } else {       
        printf("stdout has not been set\n");
    }        
    return 0;
}
/*
[root@ubuntu0006:/media/hankin/vdb] #./a.out
stdout has been set
stdout has not been set
*/