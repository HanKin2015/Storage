#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


	int b[10] = {
		[2] = 2,
		[3] = 3,
		[4] = 4,
	};

int main()
{
	int a[10] = {
		[2] = 2,
		[3] = 3,
		[4] = 4,
	};

    // 可以通过gcc init_struct.c -std=c89
    // error: ‘for’ loop initial declarations are only allowed in C99 or C11 mode
	for (int i = 0; i < 10; i++) {
		printf("%d\n", b[i]);
	}
	return 0;
}

#ifdef __cplusplus
}
#endif
