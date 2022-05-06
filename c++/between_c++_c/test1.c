#include <stdio.h>

#define pri(fmt, ...)	printf("[" __FILE__ "] [%s] %d ",__FUNCTION__,__LINE__ );\
	printf(fmt, ##__VA_ARGS__);


int main()
{
	printf("["__FILE__"] [%s] %d\n", __FUNCTION__, __LINE__);
	
	pri("hello world\n");
	return 0;
}
