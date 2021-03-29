#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#define HashMaxSize 1000    //宏定义哈希表的最大容量
#define LoadFactor 0.8       //宏定义负载因子，用于表示哈希表的负载能力。

typedef int KeyType;         
typedef char* ValueType;	// 任意类型数据
typedef size_t(*HashFunc)(KeyType key);     //重定义哈希函数

typedef enum Stat     //用于表示每个元素的状态
{
    Empty,     //空，当前没有值
    Valid,     //有效，当前的值有效
    Invalid    //非空但无效，表示当前结点被删除
}Stat;

typedef struct HashElem      //哈希表的元素结构体
{
    KeyType key;
    ValueType value;
    Stat stat;
}HashElem;

typedef struct HashTable              //哈希表
{
    HashElem data[HashMaxSize];
    size_t size;                 //当前有效的元素个数
    HashFunc hashfunc;
}HashTable;

///////////////////////////哈希表的相关操作///////////////////////////////////////
void HashTableInit(HashTable* ht);

int HashTableInsert(HashTable* ht, KeyType key, ValueType value);

//哈希表的查找，找到返回1，并返回这个结点的value值，未找到返回0
int HashTableFind(HashTable* ht, KeyType key, ValueType* value);

//删除值为key的结点
void HashRemove(HashTable* ht, KeyType key);

///判断哈希表是否为空
int HashEmpty(HashTable* ht);

//求哈希表的大小
size_t HashSize(HashTable* ht);

//销毁哈希表
void HashTableDestroy(HashTable* ht);

//打印哈希表
void HashPrint(HashTable* ht,const char* msg);         

