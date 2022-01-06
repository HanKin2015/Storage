
UT_SUITE(add)

UT_SETUP()
{
}

UT_CASE(case1)
{
    UT_EXPECT(0, add(0, 0));
}

UT_CASE(case2)
{
    UT_EXPECT(10, add(0, 10));
    UT_EXPECT(10, add(10, 0));
}

UT_CASE(case3)
{
    UT_EXPECT(-5, add(5, -10));
    UT_EXPECT(-5, add(-10, 5));
}

UT_CASE(case4)
{
    UT_ASSERT(add(2147483647, 1) == -2147483648);
    UT_ASSERT(add(65535, 65535) == 131070);
}

UT_TEARDOWN()
{
}
