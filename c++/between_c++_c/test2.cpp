#include <stdio.h>

#define pri1(fmt, ...)	printf("[" __FILE__ "] [%s] %d ",__FUNCTION__,__LINE__ );\
	printf(fmt, ##__VA_ARGS__);


#define pri2(fmt, ...)	printf("["__FILE__"] [%s] %d ",__FUNCTION__,__LINE__ );\
	printf(fmt, ##__VA_ARGS__);

int main()
{
	printf("["__FILE__"] [%s] %d\n", __FUNCTION__, __LINE__);
	
	pri1("hello world\n");
	pri2("hello world\n");
	return 0;
}
