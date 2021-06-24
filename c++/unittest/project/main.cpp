#include "modle.hpp"

int main()
{
	int x = 3, y = 4;
	for (int i = 0; i < ADD_METHOD_CNT; i++) {
		printf("%d + %d = %d\n", x, y, add(x, y, i));
	}
	return 0;
}

