/**
* 文 件 名: invalid_type_argument.c
* 文件描述: 使用printf进行格式化数据时需要严格按照数据类型匹配
* 作    者: HanKin
* 创建日期: 2023.03.07
* 修改日期：2023.03.07
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

struct NODE {
    double x;
    double y;
};

int main()
{
    double j;
    for (int i = 0, j = 3.5; i < 5; i++) {
        printf("%f %f\n", i, j);
    }

    int k = 100;
    printf("%d %f\n", k, k);

    struct NODE q = {3, 6};
    struct NODE *p = &q;
    p->x = 3;
    p->y = 6;
    printf("%d %d\n", p->x, p->y);

    double m;
    for (int i = 0, m = p->x; i < 5; i++) {
        printf("hello world\n");
    }
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #gcc invalid_type_argument.c
invalid_type_argument.c: In function ‘main’:
invalid_type_argument.c:12:16: warning: format ‘%f’ expects argument of type ‘double’, but argument 2 has type ‘int’ [-Wformat=]
         printf("%f %f\n", i, j);
                ^
invalid_type_argument.c:12:16: warning: format ‘%f’ expects argument of type ‘double’, but argument 3 has type ‘int’ [-Wformat=]
invalid_type_argument.c:16:12: warning: format ‘%f’ expects argument of type ‘double’, but argument 3 has type ‘int’ [-Wformat=]
     printf("%d %f\n", k, k);
            ^
invalid_type_argument.c:22:12: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘double’ [-Wformat=]
     printf("%d %d\n", p->x, p->y);
            ^
invalid_type_argument.c:22:12: warning: format ‘%d’ expects argument of type ‘int’, but argument 3 has type ‘double’ [-Wformat=]
[root@ubuntu0006:/media/vdb] #./a.out
0.000000 0.000000
0.000000 0.000000
0.000000 0.000000
0.000000 0.000000
0.000000 0.000000
100 0.000000
1 831141760
hello world
hello world
hello world
hello world
hello world
*/