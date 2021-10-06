#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<pair<char, int> > v;			// error: ‘>>’ should be ‘> >’ within a nested template argument list
	pair<char, int> p = make_pair('c', 123);
	v.push_back(p);
	for (pair<char, int> elem : v) {	// g++ study_pair.cpp -std=c++11
		cout << elem.first << ' ' << elem.second << endl;
	}
	return 0;
}
