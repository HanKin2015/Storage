static char s_buf[1024];

UT_SUITE(arr)

UT_SETUP()
{
	strcpy(s_buf, "abcd");
}

//first if
UT_CASE(case1)
{
	UT_EXPECT(-1, strcat_n(s_buf, 0, "ef"));
	UT_EXPECT(-1, strcat_n(s_buf, 2, "ef"));
}

//second if
UT_CASE(case2)
{
	UT_EXPECT(0, strcat_n(s_buf, 100, "ef"));
	UT_EXPECT(0, strcmp("abcdef", s_buf));
}

//else
UT_CASE(case3)
{
	UT_EXPECT(-1, strcat_n(s_buf, 6, "ef"));
	UT_EXPECT(0, strcmp("abcde", s_buf));
	UT_EXPECT('\0', s_buf[5]);
}

//TODO: UT_CASE(case2)...

UT_TEARDOWN()
{
}
