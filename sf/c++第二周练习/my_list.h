/*
 *思路：使用hash思路进行存储，使用数组hash分组存储链表指针
 *		数组和链表的结合
 *		查找插入删除时间复杂度O(logn)
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define HashMaxSize 1000    //宏定义哈希表的最大容量
#define LoadFactor 0.8      //宏定义负载因子，用于表示哈希表的负载能力。

typedef int KeyType;         
typedef int DataType;
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
    DataType data;
    Stat stat;
}HashElem;

typedef struct HashTable              //哈希表
{
    HashElem data[HashMaxSize];
    size_t size;                 //当前有效的元素个数
    HashFunc hashfunc;
}HashTable;

//TODO: 以下代码为示范，请根据题目要求修订这些接口
struct node {
	DataType data;
	node *next, *prev;
	node(DataType v = 0, node *n = NULL, node *p = NULL):data(v), next(n), prev(p) {
	};
};

struct iterator {
public:
	explicit iterator(node *p = NULL) {  //构造函数
		current = p;
	}
	iterator(const iterator& other) {
        current = other.current;
    }
    iterator& operator++() {	//迭代器自加
        current = current->next;
        return *this;
    }
    iterator& operator--() {	//迭代器自减
        current = current->prev;
        return *this;
    }
    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }
    iterator operator--(int) {
        iterator temp = *this;
        --(*this);
        return temp;
    }
    node* operator->() {	//迭代器访问成员
        return current;
    }
    DataType& operator*() {	//迭代器访问成员值
        return current->data;
    }
    bool operator==(const iterator & rhs) const  //等于
    { 
		return current == rhs.current; 
	}
		
    bool operator!=(const iterator & rhs) const  //不等于
    { 
		return !( *this == rhs ); 
	}	
    operator node * () {
		return current;
	} 
	void clear() {
		delete this;
	}

public:
	node *current;
};

typedef struct list_t list_t;
struct list_t:node, iterator {
private:
	node *head, *tail;
	int _size;
	void init() {
		_size = 0;
		head = new node();
		tail = new node();
		head->next = tail;
		tail->prev = head;
	}
	
public:
    list_t() {
        init();
    }
    ~list_t() {
        clear();
        delete head;
        delete tail;
    }
    list_t(size_t n_elements, const DataType& c) {
        init();
        for (int i = 0; i != n_elements; i++) {
            push_back(c);
        }
    }
    list_t(const list_t& x) {
        init();
        for (iterator iter = x.begin(); iter != x.end(); iter++) {
            push_back(*iter);
        }
    }
    list_t(iterator b, iterator e) {
        init();
        for (iterator iter = b; iter != e; iter++) {
            push_back(*iter);
        }
    }
    iterator begin() const {
        return iterator(head->next);
    }
    iterator end() const {
        return iterator(tail);
    }
    size_t size() const {
        return _size;
    }
    void push_front(const DataType& c) {
        insert(begin(), c);
    }
    void push_back(const DataType& c) {
        insert(end(), c);
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }
    iterator insert(iterator position, const DataType& val) {
        node* p = position.current;
        _size++;
        return iterator(p->prev = p->prev->next = new node(val, p, p->prev));
    }
    iterator erase(iterator position) {
        node* p = position.current;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        _size--;
        return retVal;
    }
    bool empty() const {
        return _size == 0;
    }
    DataType& front() {
        return *begin();
    }
    DataType& back() {
        return *(--end());
    }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    friend std::ostream& operator << (std::ostream& out, const list_t& x) {
        if (x.empty()) {
            out << "[ ]";
            return out;
        }
        out << "[ ";
        for (iterator iter = x.begin(); iter != (x.end())->prev; iter++) {
            out << *iter << " ";
        }
        out << (x.end())->prev->data;
        out << " ]";
        return out;
    }


	list_t *list_new(const DataType& c)
{
	list_t *lst = new list_t();
	lst->push_front(c);
	return lst;
}

void list_free(list_t *lst)
{
	lst->clear();
}

iterator list_get(const list_t *lst, U32 idx)
{
	iterator it = lst->begin();
	while(idx--) {
		it++;
	}
	return it;
}

iterator list_find(const list_t *lst, int (*fn)(void *data, void *ud), void *ud)
{
	iterator it = lst->begin();
	return it;
}

iterator list_foreach(list_t *lst, int (*fn)(void *data, void *ud), void *ud)
{
	iterator it = lst->begin();
	return it;
}

iterator list_iter_insert_before(iterator it, void *data)
{
	node* p = it.current;
    it->_size++;
    return iterator(p->next = new node(data, p, p->prev))->next = p->prev->next;
}

iterator list_iter_insert_after(iterator it, void *data)
{
	node* p = it.current;
    _size++;
    return iterator(p->prev = p->prev->next = new node(data, p, p->prev));
}

iterator list_iter_next(iterator it)
{
	return it->next;
}

iterator list_iter_forward(iterator it)
{
	return it->prev;
}

void *list_iter_data(iterator it)
{
	return *it;
}

void list_iter_set(iterator it, void *data)
{
	it->value = data;
}

void list_iter_clear(iterator it)
{
	it.clear();
}

};

typedef int U32;

list_t *list_new(const DataType& c);

void list_free(list_t *lst);

iterator list_get(const list_t *lst, U32 idx);

iterator list_find(const list_t *lst, int (*fn)(void *data, void *ud), void *ud);

iterator list_foreach(list_t *lst, int (*fn)(void *data, void *ud), void *ud);

iterator list_iter_insert_before(iterator it, void *data);

iterator list_iter_insert_after(iterator it, void *data);

iterator list_iter_next(iterator it);

iterator list_iter_forward(iterator it);

void *list_iter_data(iterator it);

void list_iter_set(iterator it, void *data);

void list_iter_clear(iterator it);


#endif //LIST_H_



