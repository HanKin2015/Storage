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
    HashPrint(ht, "�����ĸ�Ԫ��");
}

// ��֧��˳����ʣ�Ҳ֧�ְ��������ٲ���(���������������ʱ�临�Ӷ�)
void testHashTableFind(HashTable* ht)
{
    __TestHead__;
	HashPrint(ht, "˳�����");
	printf("\n");

    ValueType value = "male";
    int ret = HashTableFind(ht, 1001, &value);	// ����1001
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
