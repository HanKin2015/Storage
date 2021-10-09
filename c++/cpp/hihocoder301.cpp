#include <iostream> 
#include <map>
#include <algorithm>
#define maxn 100000005
using namespace std;

int main()
{
	int N, x1, x2, y1, y2;
	map<pair<int, int>, int> point;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		point[make_pair(x1, y1)] += 1;
		point[make_pair(x2, y2)] += 1;
		point[make_pair(x1, y2)] += 1;
		point[make_pair(x2, y1)] += 1;
	}
	
	x1 = y1 = maxn;
	x2 = y2 = -1;
	map<pair<int, int>, int>::iterator it = point.begin();
	for (; it != point.end(); it++) {
		if (it->second == 1) {
			x1 = min(x1, it->first.first);
			y1 = min(y1, it->first.second);
			x2 = max(x2, it->first.first);
			y2 = max(y2, it->first.second);
		}
	}
	cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
	return 0; 
}

