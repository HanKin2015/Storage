#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;

/*
函数原型：

template < class InputIterator, class OutputIterator, class UnaryOperator >  
  OutputIterator transform ( InputIterator first1, InputIterator last1,  
                             OutputIterator result, UnaryOperator op ); 

template < class InputIterator1, class InputIterator2,  
           class OutputIterator, class BinaryOperator >  
  OutputIterator transform ( InputIterator1 first1, InputIterator1 last1,  
                             InputIterator2 first2, OutputIterator result,  
                             BinaryOperator binary_op );  

参数说明：

first1, last1 
指出要进行元素变换的第一个迭代器区间 [first1,last1)。 
first2 
指出要进行元素变换的第二个迭代器区间的首个元素的迭代器位置，该区间的元素个数和第一个区间相等。 
result 
指出变换后的结果存放的迭代器区间的首个元素的迭代器位置 
op 
用一元函数对象op作为参数，执行其后返回一个结果值。它可以是一个函数或对象内的类重载operator()。 
binary_op 
用二元函数对象binary_op作为参数，执行其后返回一个结果值。它可以是一个函数或对象内的类重载operator()。
*/
int op_increase (int i) { return ++i; }  
int op_sum (int i, int j) { return i+j; }  
  
void test()
{  
    vector<int> first;  
    vector<int> second;  
    vector<int>::iterator it;  

    // set some values:  
    for (int i=1; i<6; i++) first.push_back (i*10); //  first: 10 20 30 40 50  

    second.resize(first.size());     // allocate space  
    transform (first.begin(), first.end(), second.begin(), op_increase);  
                                                    // second: 11 21 31 41 51  

    transform (first.begin(), first.end(), second.begin(), first.begin(), op_sum);  
                                                    //  first: 21 41 61 81 101  

    cout << "first contains:";  
    for (it=first.begin(); it!=first.end(); ++it)  
    cout << " " << *it;  

    cout << endl; 
    return ; 
}

void TEST()
{
    string str = "THIS IS A STRING";
    for (int i = 0; i < str.size(); i++) {
       str[i] = tolower(str[i]);    // 把大写全部转为小写
    }
    cout << str << endl;

    for (int i = 0; i < str.size(); i++) {
       str[i] = toupper(str[i]);    // 把小写全部转为大写
    }
    cout << str << endl;
    return ;
}

char op(char ch)
{

    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;
    } else {
        return ch;
    }
}

int main()
{
    string first, second;
    cin >> first;
    second.resize(first.size());
    transform(first.begin(), first.end(), second.begin(), op);
    cout << second << endl;

    test();
    TEST();
    return 0;
}