#include <inttypes.h>
#include <stdio.h>

int main()
{
    //uint8_t i;
    int8_t i;
    int16_t maxn = (2 << 8) + 50;
    for (i = 0; i < maxn; i += 10) {
        printf("i: %d, maxn: %d\n", i, maxn);
    }
    return 0;
}
