static int s_buf[1024];
static arr_t s_arr;

UT_SUITE(arr)

UT_SETUP()
{
}

// 简单的插入一个元素测试
UT_CASE(case1)
{
    memset(s_buf, 0, sizeof(s_buf));
    s_arr.vals = s_buf;
    s_arr.capacity = 1024;
    s_arr.cnt = 0;

    UT_EXPECT(0, insert(&s_arr, 1));
    UT_EXPECT(1, s_buf[0]);
    UT_EXPECT(1, s_arr.cnt);
}

// 当空间满了插入是否是失败的
UT_CASE(case2)
{
    memset(s_buf, 0, sizeof(s_buf));
    s_arr.vals = s_buf;
    s_arr.cnt = 1;
    s_arr.capacity = 1;
    s_buf[0] = 1;

    UT_EXPECT(-1, insert(&s_arr, 2));
}

// 检查末尾插入是否成功
UT_CASE(case3)
{
    memset(s_buf, 0, sizeof(s_buf));
    s_arr.vals = s_buf;
    s_arr.capacity = 3;
    s_arr.cnt = 2;
    s_buf[0] = 1;
    s_buf[1] = 2;

    UT_EXPECT(0, insert(&s_arr, 3));
    UT_EXPECT(1, s_buf[0]);
    UT_EXPECT(2, s_buf[1]);
    UT_EXPECT(3, s_buf[2]);
    UT_EXPECT(0, s_buf[3]);
    //UT_EXPECT(3, s_arr.cnt);
}

UT_CASE(case4)
{
    memset(s_buf, 0, sizeof(s_buf));
    s_arr.vals = s_buf;
    s_arr.cnt = 3;
    s_arr.capacity = 4;
    s_buf[0] = 1;
    s_buf[1] = 2;
    s_buf[2] = 4;

    UT_EXPECT(0, insert(&s_arr, 3));
    UT_EXPECT(4, s_arr.cnt);
    UT_EXPECT(4, s_arr.capacity);
    UT_EXPECT(1, s_buf[0]);
    UT_EXPECT(2, s_buf[1]);
    UT_EXPECT(3, s_buf[2]);
    UT_EXPECT(4, s_buf[3]);
    UT_EXPECT(0, s_buf[4]);
}

//TODO: add UT_CASE(xxx)

UT_TEARDOWN()
{
}
