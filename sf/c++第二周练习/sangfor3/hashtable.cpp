#include "KeyValueList.h"

size_t HashFuncDefault(KeyType key)
{
    return key%HashMaxSize;
}
////////////////////////////////////////////////////////////////////////////////////
void HashTableInit(HashTable* ht)
{
    assert(NULL != ht);    
       
    ht->size = 0;
    ht->hashfunc = HashFuncDefault;
    for (size_t i = 0; i < HashMaxSize; i++)
    {
        ht->data[i].key = 0;
        ht->data[i].stat = Empty;
        ht->data[i].value = 0;
    }
}

// ��ϣ��Ĳ��� ,����ɹ�����1������ʧ�ܷ���0
int HashTableInsert(HashTable* ht, KeyType key, ValueType value)
{
    assert(NULL != ht);
    if (ht->size >= HashMaxSize*LoadFactor)   // ����ϣ���size�����˸���
        return 0;
    // 1.�ȸ��ݹ�ϣ������keyת�������key�ڹ�ϣ���е��±�
    size_t cur = ht->hashfunc(key);
    // 2.�жϵ�ǰ�±��Ƿ�ռ��
    while (1)
    {
        if (ht->data[cur].key == key)     // ���ڱ�֤�������ظ������ִ����ϣ��
            return 0;
        if (ht->data[cur].stat != Valid)
        {
            ht->data[cur].key = key;
            ht->data[cur].value = value;
            ht->data[cur].stat = Valid;
            ht->size++;
            return 1;
        }
        cur++;
    }
}

// ��ϣ��Ĳ��� �ҵ�����1��û�ҵ�����0
int HashTableFind(HashTable* ht, KeyType key, ValueType* value)
{
    assert(NULL != ht);
    // ͨ����ϣ�����ҵ�key����Ӧ���±�
    size_t offset=ht->hashfunc(key);
    // ����ǰ�±�����Ӧ��ֵ������key���ҵ�ǰ��״̬����Ϊvalid�ŷ���
    if (ht->data[offset].key == key&&ht->data[offset].stat==Valid)
    {
        *value = ht->data[offset].value;
        return 1;
    }
    // ����ǰ�±�����Ӧ��ֵ����key������������в��ң�ֱ���ҵ�stat����empty
    else
    {
        while (ht->data[offset].stat != Empty)
        {
            if (ht->data[offset].key != key)
            {
                offset++;
                // �ж��Ƿ��±��ѳ������ֵ
                if (offset >= HashMaxSize)
                    offset = 0;
            }
            else
            {
                if (ht->data[offset].stat == Valid)
                {
                    *value = ht->data[offset].value;
                    return 1;
                }
                else
                    offset++;
            }
        }
            return 0;
    }
}

// ɾ���ڵ�
int HashTableFindCur(HashTable* ht, KeyType key, size_t* cur)
{
    assert(NULL != ht);
    for (size_t i = 0; i < HashMaxSize; i++)
    {
        if (ht->data[i].key == key && ht->data[i].stat == Valid)
        {
            *cur = i;
            return 1;
        }
    }
    return 0;
}
void HashRemove(HashTable* ht, KeyType key)
{
    assert(NULL != ht);

    size_t cur = 0;                      //�õ�Ҫɾ��Ԫ�ص��±�
    int ret=HashTableFindCur(ht,key,&cur);//ͨ��find�����õ�key�Ƿ�����ڹ�ϣ����
    if (ret == 0)
        return;
    else
    {
        ht->data[cur].stat = Invalid;
        ht->size--;
    }
}

int HashEmpty(HashTable* ht)
{
    assert(NULL != ht);
    return ht->size > 0 ? 1 : 0;
}

//���ϣ��Ĵ�С
size_t HashSize(HashTable* ht)
{
    assert(NULL != ht);
    return ht->size;
}

void HashPrint(HashTable* ht,const char* msg)         //��ӡ��ϣ��
{
	assert(NULL != ht);
	assert(0 != ht->size);

    printf("%s\n", msg);
    for (size_t i = 0; i < HashMaxSize; i++)
    {
        if (ht->data[i].stat != Empty) 
		{
            printf("[%d]  key=%d  value=%s  stat=%d\n", i, ht->data[i].key, ht->data[i].value, ht->data[i].stat);
		}
    }
}