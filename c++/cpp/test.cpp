#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#define maxn 100000005
using namespace std;

int main()
{
	map<int, int> my_map;
	my_map[3] = 24;
	cout << "my_map size is " << my_map.size() << endl;
	my_map[3] = 25;
	my_map[4] = 2;
	cout << "my_map size is " << my_map.size() << endl;

	set<int> my_set;
	my_set.insert(2);
	my_set.insert(22);

	for (int i : my_set) {
		cout << i << endl;
	}

	pair<int, int> my_pair;
	my_pair = make_pair(4, 6);
	cout << my_pair.first << my_pair.second <<endl;
	system("pause");
	return 0;
}

