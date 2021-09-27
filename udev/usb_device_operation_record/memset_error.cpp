#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
	char s1[100];
	memset(s1, 0, sizeof(s1));
	char *s2 = (char *)malloc(100);
	memset(s2, 0, sizeof(char *) * 100);
	//printf("%d %d %d %d\n", sizeof(s2),  sizeof(char *), strlen(s1), strlen(s2));
	//printf("%lud\n", sizeof(s1));
	cout << sizeof(s1) << endl;
	return 0;
}
