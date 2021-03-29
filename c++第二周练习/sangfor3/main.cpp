#include "KeyValueList.h"
#define __TestHead__ printf("\n-----------------------%s--------------------------\n",__FUNCTION__);

/*
zhangsan 23 male false
*/
void testHashTableInsert(HashTable* ht)
{
    __TestHead__;
    HashTableInsert(ht, 1, "zhangsan");
    HashTableInsert(ht, 2, "23");
    HashTableInsert(ht, 1001, "male");
    HashTableInsert(ht, 1002, "false");
    HashPrint(ht, "插入四个元素");
}

// 既支持顺序访问，也支持按键名快速查找(常数级或对数级的时间复杂度)
void testHashTableFind(HashTable* ht)
{
    __TestHead__;
	HashPrint(ht, "顺序访问");
	printf("\n");

    ValueType value = "male";
    int ret = HashTableFind(ht, 1001, &value);	// 键名1001
    printf("ret: expect=1    actual=%d\nvalue: expect=male    actual=%s\n", ret,value);
}

void TEST()
{
    HashTable ht;
    HashTableInit(&ht);
    testHashTableInsert(&ht);
    testHashTableFind(&ht);
}

int main()
{
    TEST();
	system("pause");
    return 0;
}
