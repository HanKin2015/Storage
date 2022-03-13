#include<stdio.h>
#include<malloc.h>

typedef struct {
    int len;
    int array[];
}SoftArray;

void test1()
{
    int len = 10;
    printf("The struct's size is %lu\n",sizeof(SoftArray));
	return;
}

void test2()
{
    int len = 10;
    SoftArray *p=(SoftArray*)malloc(sizeof(SoftArray) + sizeof(int)*len);
    printf("SoftArray size is %lu\n", sizeof(SoftArray));
    free(p);
	return;
}

void test3()
{
    int len = 10, i = 0;
    SoftArray *p = (SoftArray*)malloc(sizeof(SoftArray)+sizeof(int)*len);
    p->len = len;
    for(i = 0;i < p->len; i++) {
        p->array[i] = i+1;
    }
    for(i = 0;i < p->len; i++) {
        printf("%d\n", p->array[i]);
    }
    free(p);
    return;
}

int main()
{
	printf("sizeof(int): %lu\n", sizeof(int));
	test1();
	test2();
	test3();
    return 0;
}