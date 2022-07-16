#include <iostream>
#include <cstdio>
#include <stdint.h>

static void test1()
{
    const char *str = "1234:4321";
    char vid[64] = { 0 };
    char pid[64] = { 0 };
    sscanf(str, "%[^:]:%s", vid, pid);
    printf("%s == %s\n", vid, pid);
    return;
}

static void test2()
{
    const char *str = "1234=4321";
    char vid[64] = { 0 };
    char pid[64] = { 0 };
    sscanf(str, "%[^=]=%s", vid, pid);
    printf("%s == %s\n", vid, pid);
    return;
}

static void test3()
{
    const char *str = "134=54321";
    unsigned int vid = 0;
    unsigned int pid = 0;
    sscanf(str, "%04x=%04x", &vid, &pid);
    printf("%04x == %04x\n", vid, pid);
    return;
}

int main()
{
    (void)test1();
    (void)test2();
    (void)test3();
    return 0;
}
