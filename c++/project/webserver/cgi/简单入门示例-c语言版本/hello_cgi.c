/*******************************************************************************
* 文 件 名: hello_cgi.c
* 文件描述: 学习cgi脚本
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.09.08
* 修改日期：2025.09.08
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_inputs()
{
    int length;
    char *method;
    char *inputstring;

    method = getenv("REQUEST_METHOD");  //将返回结果赋予指针
    if (method == NULL) {
        printf("<p>获取REQUEST_METHOD失败</p>\n");
        return -1;       //找不到环境变量REQUEST_METHOD
    }
    if (!strcmp(method, "POST")) {   // POST方法
        length = atoi(getenv("CONTENT_LENGTH"));    //结果是字符，需要转换
        if (length != 0) {
            inputstring = malloc(sizeof(char)*length + 1) //必须申请缓存，因为stdin是不带缓存的。
            fread(inputstring, sizeof(char), length, stdin); //从标准输入读取一定数据
        }
    } else if(!strcmp(method, "GET")) {
        inputstring = getenv("QUERY_STRING");
        length = strlen(inputstring);
    }
    printf("<p>收到信息: %s</p>\n", inputstring);
    return length;
}

int main()
{
    // 必须首先输出HTTP头部，以空行结束
    printf("Content-Type: text/html\n\n");
    
    // 输出HTML内容
    printf("<html>\n");
    printf("<head><title>CGI Example</title></head>\n");
    printf("<body>\n");
    printf("<h1>Hello from C CGI!</h1>\n");
    
    // 可以处理表单数据，例如获取name参数
    char *name = getenv("QUERY_STRING");
    if (name && *name) {
        printf("<p>Received: %s</p>\n", name);
    }
    
    // 上面是简单示例，此函数操作更详细
    get_inputs();
    
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}