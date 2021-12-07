#include <iostream>
using namespace std;

int main()
{
	int type = 2;
	int x, y;
	
	switch (type) {
	case 1:
		break;
	case 2: 
		x = 1, y = 3;
		cout << x + y << endl;
		break;
	
	case 3:
		break;
	default:
		break;
	}
	return 0;
}
