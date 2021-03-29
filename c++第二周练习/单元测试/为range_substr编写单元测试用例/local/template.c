
UT_SUITE(range_substr)

char *str = NULL;
UT_SETUP()
{
	str = "hello world";
}

UT_CASE(case1)
{
	UT_ASSERT(NULL == range_substr(str, str + 5, "wo"));
}

UT_CASE(case2)
{
	//!pe
	UT_EXPECT(0, strcmp("world", range_substr(str, NULL, "wo")));
	UT_ASSERT(NULL == range_substr(str, NULL, "hj"));
}

UT_CASE(case3)
{
	//!*sub
	UT_EXPECT(0, strcmp(str, range_substr(str, str + 10, "")));
}

UT_CASE(case4)
{
	UT_EXPECT(0, strcmp("world", range_substr(str, str + 11, "wo")));
}

//TODO: UT_CASE(case2)...
