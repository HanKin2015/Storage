#include <stdio.h>

int main()
{
	const char *str1 = "12345"
		"6789";
	//const char *str2 = "12345
	//	67891";
	const char *str3 = "12345 \
		67891";
	
	printf("%s\n", str1);
	//printf("%s\n", str2);
	printf("%s\n", str3);
	return 0;
}
