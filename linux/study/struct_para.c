#include <stdio.h>

struct son_s {
    int y;
};

typedef struct {
    int z;
} son_t;

static struct node {
    int x;
    
    struct son {
        int y;
    } tq;
    struct son_s b, c;
} a;

void func(struct node *tmp) 
{
    tmp->x = 100;
}

void f1(struct son_s *tmp)
{
    tmp->y = 250;
}

int main()
{
    son_t hejan;

    a.x = 10;
    printf("%d\n", a.x);
    func(&a);
    printf("%d\n", a.x);
    
    a.b.y = 233;
    a.c.y = 1;
    printf("%d\n", a.b.y);
    printf("%d\n", a.c.y);
    f1(&a.b);
    f1(&a.c);
    printf("%d\n", a.b.y);
    printf("%d\n", a.c.y);
    return 0;
}
