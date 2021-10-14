/**
* 文 件 名: init_struct.cpp
* 文件描述: 初始化结构体
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2021.10.14
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <iostream>
using namespace std;

// linux结构体可以采用乱序初始化，即用成员变量前加（.）符号；
// 乱序初始化是C99标准新加的，比较直观的一种初始化方式。相比顺序初始化而言，乱序初始化就如其名，成员可以不按照顺序初始化，而且可以只初始化部分成员，扩展性较好。linux内核中采用这种方式初始化struct。

#ifdef __cplusplus
extern "C" {
#endif

struct node {
    int x;
    int y;
	int z;
};

int main()
{
    // 声明
    struct node t1;
    
    // 顺序初始化
    struct node t2 = {1, 2};
    struct node t3 = {1, 2, 3,};
    
    // 乱序初始化
    const struct node t4 = {
        .x = 3,
        .y = 4,
		.z = 5,
    };

	struct node t5 = {
		.y = 4,
		.z = 5,
	};
    
    cout << t1.x << ' ' << t1.y << ' ' << t1.z << endl;
    cout << t2.x << ' ' << t2.y << ' ' << t2.z << endl;
    cout << t3.x << ' ' << t3.y << ' ' << t3.z << endl;
    cout << t4.x << ' ' << t4.y << ' ' << t4.z << endl;
    cout << t5.x << ' ' << t5.y << ' ' << t5.z << endl;
    return 0;
}

#ifdef __cplusplus
}
#endif


