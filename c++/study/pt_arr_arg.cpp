/*
1.指针数组做参数
2.学会指针的指针的用途
*/

#include <iostream>
#include <vector>
using namespace std;

/*
指针数组参数
*/
static inline void fn(int **p)
{
    for (int idx = 0; idx < 5; idx++) {
        int *tmp = new int();
        *tmp = idx;
        p[idx] = tmp;
        //delete tmp;   // 由于作为了返回值，需要在最后使用后再进行释放
    }
    return;
}

/*
指针数组返回值
*/
static inline int **rfn(int n)
{
    static int *p[5];
    for (int idx = 0; idx < 5; idx++) {
        int *tmp = new int();
        *tmp = n;
        p[idx] = tmp;
        //delete tmp;
    }
    return p;
}

/*
使用容器作为返回值
*/
static inline vector<int *> vfn()
{
    vector<int *> v;
    int arr[] = {11, 22, 33, 44, 55};
    for (int idx = 0; idx < 5; idx++) {
        int *tmp = new int();
        *tmp = arr[idx];
        v.push_back(tmp);
        //delete tmp;
    }
    return v;
}

int main()
{
    int *p[5];
    fn(p);
    for (int i = 0; i < 5; i++) {
        cout << *p[i] << endl;
    }
    
    int **q;
    q = rfn(11);
    for (int i = 0; i < 5; i++) {
        cout << *q[i] << endl;
    }
    
    vector<int *> v;
    v = vfn();
    for (int *elem : v) {
        cout << *elem << endl;
    }
    return 0;
}
