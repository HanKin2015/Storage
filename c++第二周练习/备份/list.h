#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define HashMaxSize 1000    //宏定义哈希表的最大容量
#define LoadFactor 0.8      //宏定义负载因子，用于表示哈希表的负载能力。

typedef int KeyType; 
typedef size_t(*HashFunc)(KeyType key);     //重定义哈希函数

typedef enum Stat     //用于表示每个元素的状态
{
    Empty,     //空，当前没有值
    Valid,     //有效，当前的值有效
    Invalid    //非空但无效，表示当前结点被删除
}Stat;

template<class T>
struct HashElem      //哈希表的元素结构体
{
    KeyType key;
    T data;
    Stat stat;
};

template<class T>
struct HashTable              //哈希表
{
    HashElem data[HashMaxSize];
    size_t size;                 //当前有效的元素个数
    HashFunc hashfunc;
};

//TODO: 以下代码为示范，请根据题目要求修订这些接口
template<class T>
struct node {
	T data;
	node *next, *prev;
	node(T v = 0, node *n = NULL, node *p = NULL):data(v), next(n), prev(p) {
	};
};

template<class T>
struct iterator {
public:
	explicit iterator(node<T> *p = NULL) {  //构造函数
		current = p;
	}
	iterator(const iterator& other) {
        current = other.current;
    }
    iterator& operator++() {	// 迭代器自加
        current = current->next;
        return *this;
    }
    iterator& operator--() {	// 迭代器自减
        current = current->prev;
        return *this;
    }
    iterator operator++(int) {  // 值自加
        iterator temp = *this;
        ++(*this);
        return temp;
    }
    iterator operator--(int) {  // 值自减
        iterator temp = *this;
        --(*this);
        return temp;
    }
    node<T>* operator->() {	// 迭代器访问成员
        return current;
    }
    T& operator*() {	// 迭代器访问成员值
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
    operator node<T> * () {
		return current;
	} 
	void clear() {
		delete this;
	}

public:
	node<T> *current;
};

typedef int U32;

template<class T>
struct list_t:node<T>, iterator<T> {
private:
	node<T> *head, *tail;
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
    list_t(size_t n_elements, const T& c) {
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
    void push_front(const T& c) {
        insert(begin(), c);
    }
    void push_back(const T& c) {
        insert(end(), c);
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }
    iterator insert(iterator position, const T& val) {
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
    T& front() {
        return *begin();
    }
    T& back() {
        return *(--end());
    }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    friend std::ostream& operator << (std::ostream& out, const list_t<T>& x) {
        if (x.empty()) {
            out << "[ ]";
            return out;
        }
        out << "[ ";
        for (iterator<T> iter = x.begin(); iter != (x.end())->prev; iter++) {
            out << *iter << " ";
        }
        out << (x.end())->prev->data;
        out << " ]";
        return out;
    }

	// 新建一个list_t对象
	static list_t<T> *list_new() {
		return new list_t<T>();
	}

	// 清空list
	void list_free(list_t *lst) {
		lst->clear();
	}

	// 按照索引值创建迭代器
	static iterator list_get(const list_t *lst, U32 idx)
	{
		iterator it = lst->begin();
		while(--idx > 0) {
			it++;
		}
		return it;
	}

	// 回调list_get函数，data列表，ud索引值，返回对应的迭代器
	iterator list_find(const list_t *lst, iterator (*fn)(const list_t<T> *data, U32 ud), U32 ud)
	{
		iterator it = fn(lst, ud);
		return it;
	}

	static iterator list_print(const list_t *lst, U32 ud)
	{
		iterator it = list_get(lst, ud);
		for (; it != lst->end(); it++) {
			std::cout << *it << ' ';
		}
		std::cout << std::endl;
		return it;
	}

	// 回调list_print函数，data列表，ud起始位置
	iterator list_foreach(list_t *lst, iterator<T> (*fn)(const list_t<T> *data, U32 ud), U32 ud)
	{
		iterator it = fn(lst, ud);
		return it;
	}

	// 在it位置前面插入数据
	iterator list_iter_insert_before(iterator it, T data)
	{
		node* p = it.current;
		_size++;
		node *q = new node((T)data, p, p->prev);
		q->prev = p->prev;
		p->prev->next = q;
		q->next = p;
		p->prev = q;
		return it;
	}

	// 在it位置后面插入数据
	iterator list_iter_insert_after(iterator it, T data)
	{
		node* p = it.current;
		_size++;
		node *q = new node((T)data, p, p->prev);
		q->next = p->next;
		p->next->prev = q;
		p->next = q;
		q->prev = p;
		it++;
		return it;
	}

	// 返回it迭代器下一个位置
	iterator list_iter_next(iterator it)
	{
		it++;
		return it;
	}

	// 返回it迭代器上一个位置
	iterator list_iter_forward(iterator it)
	{
		it--;
		return it;
	}

	// 得到it位置的数据
	void *list_iter_data(iterator it)
	{
		return (void *)(*it);
	}

	//将it位置的数据改为data
	void list_iter_set(iterator it, T data)
	{
		it->data = (T)data;
	}

	//清理it
	void list_iter_clear(iterator it)
	{
		it.clear();
	}

};
#endif //LIST_H_