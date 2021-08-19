#include <stdio.h>
#include <arpa/inet.h>

#define NIPQUAD(addr) \
        ((unsigned char *)&addr)[0], \
        ((unsigned char *)&addr)[1], \
        ((unsigned char *)&addr)[2], \
        ((unsigned char *)&addr)[3]
#define NIPQUAD_FMT "%u.%u.%u.%u"

int main()
{
    long ip_addr = 288376330;
    printf("IP1: "NIPQUAD_FMT"\n", NIPQUAD(ip_addr)); 

    in_addr ip;
    ip.s_addr = ip_addr;
    printf("IP2: %s\n", inet_ntoa(ip));
    return 0;
}
