#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#define HashMaxSize 1000    //�궨���ϣ����������
#define LoadFactor 0.8       //�궨�帺�����ӣ����ڱ�ʾ��ϣ��ĸ���������

typedef int KeyType;         
typedef char* ValueType;	// ������������
typedef size_t(*HashFunc)(KeyType key);     //�ض����ϣ����

typedef enum Stat     //���ڱ�ʾÿ��Ԫ�ص�״̬
{
    Empty,     //�գ���ǰû��ֵ
    Valid,     //��Ч����ǰ��ֵ��Ч
    Invalid    //�ǿյ���Ч����ʾ��ǰ��㱻ɾ��
}Stat;

typedef struct HashElem      //��ϣ���Ԫ�ؽṹ��
{
    KeyType key;
    ValueType value;
    Stat stat;
}HashElem;

typedef struct HashTable              //��ϣ��
{
    HashElem data[HashMaxSize];
    size_t size;                 //��ǰ��Ч��Ԫ�ظ���
    HashFunc hashfunc;
}HashTable;

///////////////////////////��ϣ�����ز���///////////////////////////////////////
void HashTableInit(HashTable* ht);

int HashTableInsert(HashTable* ht, KeyType key, ValueType value);

//��ϣ��Ĳ��ң��ҵ�����1���������������valueֵ��δ�ҵ�����0
int HashTableFind(HashTable* ht, KeyType key, ValueType* value);

//ɾ��ֵΪkey�Ľ��
void HashRemove(HashTable* ht, KeyType key);

///�жϹ�ϣ���Ƿ�Ϊ��
int HashEmpty(HashTable* ht);

//���ϣ��Ĵ�С
size_t HashSize(HashTable* ht);

//���ٹ�ϣ��
void HashTableDestroy(HashTable* ht);

//��ӡ��ϣ��
void HashPrint(HashTable* ht,const char* msg);         

