#include <iostream>
#include <cstdio>
#include <inttypes.h>
using namespace std;

#define EP2I(ep_address) (((ep_address & 0x80) >> 3) | (ep_address & 0x0f))

int main()
{
    uint64_t interval = 11, mfindex = 6171367;
    uint64_t asap = ((mfindex + interval - 1) &
                     ~(interval-1));
    printf("%lld\n", asap);
    printf("%d\n", EP2I(0x82));
    printf("%d\n", EP2I(0x81));
    return 0;
}
