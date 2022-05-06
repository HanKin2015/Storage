#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct point {
	int *p;
	char *c;
	int n;
};

void func1(struct point &loc)
{
	loc.n = 123;
}

void func2(struct point *loc)
{
	loc->n = 123467;
}

int main()
{
	struct point location;
	char *str = "12345";
	location = {NULL, str};
	if (location.p != NULL) {
		printf("yes\n");	
	} else {
		printf("no\n");
	}
	

	int a = 3;
	int b = (0x03 << 8 | a);
	int c = (0x3 << 8);
	printf("%d\n", c);
	printf("%s[%d] %04x\n", __FUNCTION__, __LINE__, b);

	//clear struct
	if (location.c != NULL) {
                printf("struct is not NULL!\n");
        } else {
                printf("struct is NULL!\n");
        }
	memset(&location, 0, sizeof(location));
	if (location.c != NULL) {
                printf("struct is not NULL!\n");
        } else {
                printf("struct is NULL!\n");
        }

	//time
	time_t t = time(0);
	char *cur_time = (char *)malloc(64);
	strftime(cur_time, sizeof(cur_time)*64, "%Y/%m/%d %H:%M:%S", localtime(&t));
	printf("time: %s\n", cur_time);
	
	//argument
	location.n = 100;
	func1(location);
	printf("n = %d\n", location.n);
	func2(&location);
	printf("n = %d\n", location.n);
	
	//file write
	FILE *fd = fopen("./data.json", "a");
	fseek(fd, -8L, SEEK_END);
	fprintf(fd, "aaaa1232323");
	return 0;
}
