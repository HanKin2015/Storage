/**
* 文 件 名: CMocka_example.c
* 文件描述: CMocka
* 备    注：g++ CMocka_example.c -lcmocka
* 作    者: HanKin
* 创建日期: 2022.06.06
* 修改日期：2023.06.06
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_add(void **state) {
    int a = 2;
    int b = 1;
    int result = add(a, b);
    assert_int_equal(result, 3);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
/*
[root@ubuntu0006:~/cmake/build] #apt-get install libcmocka-dev
[root@ubuntu0006:~/cmake/build] #gcc k.c -lcmocka
[root@ubuntu0006:~/cmake/build] #./a.out
[==========] Running 1 test(s).
[ RUN      ] test_add
[       OK ] test_add
[==========] 1 test(s) run.
[  PASSED  ] 1 test(s).
*/
