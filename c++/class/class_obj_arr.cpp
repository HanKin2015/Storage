#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

#define MAXN 256
#define RAND 5

class Node
{
public:
    /*
    高级操作初始化
    Node(int a = 2, int b = 3):x(a), y(b) {
    }
    */
    Node() {
        x = 0;
        y = 0;
    }
    ~Node() {
    }

    void set(int n) {
        x = n;
        y = n;
    }
    
    int get() {
        return x + y;
    }

private:
    int x;
    int y;
};

int main()
{
    // 1.一般使用
    Node *p = new Node();
    cout << p->get() << endl;
    p->set(5);
    cout << p->get() << endl;

#if 0
    // 2.类对象数组
    Node *q = new Node[MAXN]; // no appropriate default constructor available(如果构造函数参数全都设了默认值成功)
    cout << q[RAND].get() << endl;
    q[RAND].set(5);
    cout << q[RAND].get() << endl;
#endif

    // 分配足够的raw memory，给一个预备容纳MAXN个Node objects的数组使用
    void *rawMemory = operator new(MAXN * sizeof(Node));

    // 让bestPieces指向此内存，使这块内存被视为一个Node数组
    Node *bestPieces = reinterpret_cast<Node*>(rawMemory);

    // 利用"placement new"构造这块内存中的Node objects。
    for(int i = 0; i < MAXN; i++){
        new (&bestPieces[i]) Node();
    }
    
    // 像数组一样使用
    cout << bestPieces[RAND].get() << endl;
    bestPieces[RAND].set(5);
    cout << bestPieces[RAND].get() << endl;
    
    // 4.常用的指针数组应该是这样用吧，何必自己来进行分配空间
    Node *r[MAXN];
    if (r[RAND] == NULL) {
        printf("r[%d] is NULL\n", RAND);
    }
    memset(r, 0, MAXN * sizeof(Node *));    // 上面内容不会输出，需要这样进行初始化
    Node *tmp = new Node();
    tmp->set(11);
    if (r[RAND] == NULL) {
        r[RAND] = tmp;
    }
    cout << r[RAND]->get() << endl;
    
    // 5.注意地址和指针
    int *num = new int[MAXN];
    cout << (num[RAND] == NULL ? "NULL" : "NOT NULL") << endl;
    cout << (&num[RAND] == NULL ? "NULL" : "NOT NULL") << endl;
    return 0;
}
