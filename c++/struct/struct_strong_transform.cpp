#include <stdio.h>
#include <stdlib.h>

struct resolution {
	int x;
	int y;
};

struct screen {
	void *res;
	int size_x;
	int size_y;
	int pay;
	int value;
};

int main()
{
	struct resolution res = {3, 5};
	struct screen haier = {
		.res    = (void *)(&res),
		.size_x = 1920,
		.size_y = 1080,
		.pay    = 1000,
		.value  = 250,
	};
	
	struct resolution *ptr = (struct resolution *)malloc(sizeof(struct resolution));
	ptr->x = 1;
	ptr->y = 2;
	haier.res = ptr;
	printf("ptr = %p, haier.res = %p, &haier = %p\n", ptr, haier.res, &haier);

	struct resolution *tmp = (struct resolution *)(&haier);
	printf("tmp = %p, &haier = %p\n", tmp, &haier);
	
	printf("res x: %d, y: %d; tmp x: %d y: %d\n", res.x, res.y, tmp->x, tmp->y);
	
	printf("haier.res x: %d, y: %d\n", ((struct resolution *)haier.res)->x, ((struct resolution *)haier.res)->y);
	struct screen *p = (struct screen *)malloc(sizeof(struct screen));
	p = &haier;
	struct resolution *t = (struct resolution *)p;
	printf("x: %d, y: %d\n", t->x, t->y);
	return 0;
}
