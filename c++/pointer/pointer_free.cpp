#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct NODE {
    char *data;
} node;

// 结论是指针上层被释放后不影响下层
// 因此需要逐层释放内存
static char* func()
{
    node *msg = NULL;
    msg = (node *)malloc(sizeof(NODE));
    msg->data = (char *)malloc(64);
    memset(msg->data, 0, 64);
    char tmp[64] = "12345";
    strncpy(msg->data, tmp, 64);
    char *p = msg->data;
    free(msg);
    msg = NULL;
    return p;
}

struct op_import_request
{
    char busid[1024];
} __attribute__((packed));

// 结论是memset能给内部成员进行清空
// 为啥将未终止的字符串 "req.busid" 传递给期望空字符结尾的字符串
static void test()
{
    struct op_import_request req;
    req.busid[55] = 'h';
    printf("before: %c\n", req.busid[55]);
    memset(&req, 0, sizeof(req));
    printf("after: %c\n", req.busid[55]);
    return;
}

int main()
{
    printf("%s\n", func());
    test();
    return 0;
}