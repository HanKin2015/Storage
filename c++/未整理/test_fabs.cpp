#include <stdio.h>
#include <math.h>

#define GUEST_RES_INTERNAL 16

bool func(int dbc_width, int dbc_height, int recv_width, int recv_height)
{
    if ((fabs(dbc_width - recv_width) < GUEST_RES_INTERNAL && fabs(dbc_height - recv_height) < GUEST_RES_INTERNAL) || dbc_height == 0) {
        printf("no\n");
        return false;       
    }
    printf("yes\n");
    return true;
}

int main ()
{
    int a, b;
    a = 1234;
    b = -344;

    printf("%d 的绝对值是 %lf\n", a, fabs(a));
    printf("%d 的绝对值是 %lf\n", b, fabs(b));

    func(1168, 652, 180, 720);
    return(0);
}
