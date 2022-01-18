#include <stdio.h>

#define ATTR_PACKED __attribute__ ((__packed__))

struct exam1 {
	char c;
	int  i;
};

struct __attribute__ ((__packed__)) exam2 {
	char c;
	int  i;
};

struct exam3 {
	char c;
	int  i;
} ATTR_PACKED;

int main()
{
	printf("char: %ld, int: %ld\n", sizeof(char), sizeof(int));
	printf("exam1: %ld, exam2: %ld, exam3: %ld\n", sizeof(struct exam1), sizeof(struct exam2), sizeof(struct exam3));
	return 0;
}

/*
char: 1, int: 4
exam1: 8, exam2: 5, exam3: 5
*/