#include <iostream>
#include <cstdio>
using namespace std;

struct st_node {
    int x;
    int y;
};

int main()
{
    //st_node a(1, 2);  错误
    st_node a;
    a.x = 5;
    a.y = 8;
    printf("(%d, %d)\n", a.x, a.y);

    st_node b = {
        .x = 2,
        .y = 5
    };
    printf("(%d, %d)\n", b.x, b.y);
    
    st_node c = {1, 3};
    printf("(%d, %d)\n", c.x, c.y);
    return 0;
}
