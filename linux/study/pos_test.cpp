#include <stdio.h>
#include <malloc.h>

void func(const char *str, int str_size)
{
	for (int i = 0; i < str_size; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
	return;
}

static void test_alloc()
{
    int* p = (int*)malloc(sizeof(int));

    if (!p)
        return;
    printf("&p: %p, p: %d\n", p, *p);
    free(p);
}

int main()
{
	const char *str = "abcdefghijklmn";
	str += 5;
	printf("%s\n", str);
	func(str, 3);
	return 0;
}