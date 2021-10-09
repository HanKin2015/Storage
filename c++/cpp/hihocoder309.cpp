#include <iostream>
#include <string.h>
#include <typeinfo>
#define maxn 100005
#include <map>
using namespace std;

int main()
{
    int N, A[maxn];
    cin >>N;
    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    bool is_have_son[maxn];
    memset(is_have_son, 0, sizeof(is_have_son));
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        is_have_son[a] = 1;
    }
    return 0;
}
