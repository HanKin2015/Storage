#include <iostream>
#include "hashtable.h"
#define __TestHead__ printf("\n-----------------------%s--------------------------\n",__FUNCTION__);

void testHashTableInsert(HashTable* ht)
{
    __TestHead__;
    HashTableInit(ht);
    HashTableInsert(ht, 1, 1);
    HashTableInsert(ht, 2, 2);
    HashTableInsert(ht, 1001, 1001);
    HashTableInsert(ht, 1002, 1002);
    HashTableInsert(ht, 10001, 10001);
    HashTableInsert(ht, 1002, 1002);
    HashPrint(ht, "�����ĸ�Ԫ��");
}

void testHashTableFind(HashTable* ht)
{
    __TestHead__;
    HashTableInit(ht);
    HashTableInsert(ht, 1, 1);
    HashTableInsert(ht, 2, 2);
    HashTableInsert(ht, 1001, 1001);
    HashTableInsert(ht, 102, 102);
    HashTableInsert(ht, 10001, 10001);
    HashTableInsert(ht, 1002, 1002);
    ValueType value = 0;
    int ret = HashTableFind(ht, 1002, &value);
    printf("ret: expect=1    actual=%d\nvalue: expect=1002    actual=%d\n", ret,value);
}

void testHashRemove(HashTable* ht)
{
    __TestHead__;
    HashTableInit(ht);
    HashTableInsert(ht, 1, 1);
    HashTableInsert(ht, 2, 2);
    HashTableInsert(ht, 1001, 1001);
    HashTableInsert(ht, 102, 102);
    HashTableInsert(ht, 10001, 10001);
    HashTableInsert(ht, 1002, 1002);
    HashPrint(ht,"������ɺ�");
    HashRemove(ht, 2);
    HashPrint(ht, "ɾ��һ��Ԫ��");
    HashTableInsert(ht, 100001,100001);
    HashPrint(ht, "����һ��Ԫ��");

}

void test()
{
    HashTable ht;
    HashTableInit(&ht);
    testHashTableInsert(&ht);
    testHashTableFind(&ht);
    testHashRemove(&ht);
}

int main()
{
    test();
	system("pause");
    return 0;
}
