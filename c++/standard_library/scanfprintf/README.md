# 输入挂

## 1、C++IO流的同步和绑定
在C++中，cin和cout的速度其实不并不慢，C++中的流的IO速度相当的快，其速度与初始设定的缓存区大小和硬盘的IO速度有关。

但在C++中，为了兼容C的IO(scanf和printf)，cin和cout被设置为与C的IO同步，这样导致cin和cout的速度不如scanf和printf快。

另外，在默认情况下，标准输入设备(cin)与标准输出设备(cout)绑定在一起，它保证在调用输入之前已经刷新输出缓冲区，这样也会降低读取效率。

所以，我们可以手动取消他们与C语言IO的同步，并去掉cin和cout的绑定，加速读取，使cin的速度与scanf相差无几，甚至某些情况要快于scanf。

注：在取消绑定后，使用scanf和printf可能会出现问题，比如读取失败或者提前输出的问题，请不要再使用他们，不过可以使用getchar和gets等读入函数。

```
// 取消C++ IO与C的同步
std::ios::sync_with_stdio(false);
 
// 取消cin和cout的绑定
std::cin.tie(NULL);/*等价于cin.tie(0);*/
```

## 2、快读挂
在读取大量整数时，无论是cin还是scanf，都比getchar的读取效率要慢上不少，我们可以使用getchar来模拟输入函数，在读取大量整数的时候效率会很高。
```
inline bool scan_d(int &num)  
{
        char in;bool IsN=false;
        in=getchar();
        if(in==EOF) return false;
        while(in!='-'&&(in<'0'||in>'9')) in=getchar();
        if(in=='-'){ IsN=true;num=0;}
        else num=in-'0';
        while(in=getchar(),in>='0'&&in<='9'){
                num*=10,num+=in-'0';
        }
        if(IsN) num=-num;
        return true;
}
```

```
inline bool scan_lf(double &num)  
{
        char in;double Dec=0.1;
        bool IsN=false,IsD=false;
        in=getchar();
        if(in==EOF) return false;
        while(in!='-'&&in!='.'&&(in<'0'||in>'9'))
                in=getchar();
        if(in=='-'){IsN=true;num=0;}
        else if(in=='.'){IsD=true;num=0;}
        else num=in-'0';
        if(!IsD){
                while(in=getchar(),in>='0'&&in<='9'){
                        num*=10;num+=in-'0';}
        }
        if(in!='.'){
                if(IsN) num=-num;
                return true;
        }else{
                while(in=getchar(),in>='0'&&in<='9'){
                        num+=Dec*(in-'0');Dec*=0.1;
                }
        }
        if(IsN) num=-num;
        return true;
}
```

```
#define FI(n) FastIO::read(n)
 
namespace FastIO {
	const int SIZE = 1 << 16;
	char buf[SIZE], obuf[SIZE], str[60];
	int bi = SIZE, bn = SIZE, opt;
	int read(char *s) {
		while (bn) {
			for (; bi < bn && buf[bi] <= ' '; bi++);
			if (bi < bn) break;
			bn = fread(buf, 1, SIZE, stdin);
			bi = 0;
		}
		int sn = 0;
		while (bn) {
			for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];
			if (bi < bn) break;
			bn = fread(buf, 1, SIZE, stdin);
			bi = 0;
		}
		s[sn] = 0;
		return sn;
	}
	bool read(int& x) {
		int n = read(str), bf;
 
		if (!n) return 0;
		int i = 0; if (str[i] == '-') bf = -1, i++; else bf = 1;
		for (x = 0; i < n; i++) x = x * 10 + str[i] - '0';
		if (bf < 0) x = -x;
		return 1;
	}
};
```

## 3、交互式oj(如leetcode)的加速方法
将其放在solution类的上方即可，一般情况用不到。
```
static auto __ = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
    }();
//注意放在solution上面
```

## 4、不固定输入
```
#include <stdio.h>
int main()
{
    int a,b;
    while (scanf("%d %d",&a, &b) != EOF)
        printf("%d\n",a+b);
}

#include<iostream>
using namespace std;
int main()
{
    int a ,b;
    while (cin>>a>>b)
        cout<<a+b<<endl;
    return 0;
}
cin是一个对象，表达式cin >> m >> n在读入发生错误返回0，否则返回cin的地址。

vector<int> nums;
int num;
while(cin >> num) {
	nums.push_back(num);
	// 读到换行符，终止循环
	if(getchar() == '\n') {
		break;
	}
}

// 验证是否读入成功
for(int i = 0; i < nums.size(); i++) {
	cout << nums[i] << " ";
}
cout << endl;
```