#include "interface.h"

void printf_array()
{
    int arr[10] = {
        [2] = 2,
        [3] = 3,
        [4] = 4,
    };

	for (int i = 0; i < 10; i++) {
		printf("%d\n", arr[i]);
	}
    return;
}
