#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>

#define LIST_MAX_SIZE 10000	// 定义列表最大容量LIST_MAX_SIZE * LIST_MAX_SIZE
typedef char* DataType;
typedef int U32;

//TODO: 以下代码为示范，请根据题目要求修订这些接口
struct node {	// 链表中的节点
	DataType data;	// 任意类型
	char *data_type;	
	node *next, *prev;
	node(DataType d = 0, node *n = NULL, node *p = NULL):data(d), next(n), prev(p) {
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
    node* operator->() {	// 迭代器访问成员
        return current;
    }
    DataType& operator*() {	// 迭代器访问成员值
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
    operator node*() {
		return current;
	} 
	void clear() {
		delete this;
	}

public:
	node *current;
};

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
    void push_front(const DataType& c, char *data_type = "string") {
        insert(begin(), c, data_type);
    }
    void push_back(const DataType& c, char *data_type = "string") {
        insert(end(), c, data_type);
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }
    iterator insert(iterator position, const DataType& val, char *data_type) {
        node* p = position.current;
		p->data_type = data_type;
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

	// 回调list_get函数，data列表，ud索引值，返回对应的迭代器
	iterator list_find(const list_t *lst, iterator (*fn)(const list_t *data, U32 ud), U32 ud)
	{
		iterator it = fn(lst, ud);
		return it;
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

	// 列表输出
	static iterator list_print(const list_t *lst, U32 ud)
	{
		iterator it = list_get(lst, ud);
		printf("[ ");
		for (; it != lst->end(); it++) {
			printf("%s ", *it);
		}
		printf(" ]\n");
		return it;
	}

	// 回调list_print函数，data列表，ud起始位置
	iterator list_foreach(list_t *lst, iterator (*fn)(const list_t *data, U32 ud), U32 ud)
	{
		iterator it = fn(lst, ud);
		return it;
	}

	// 在it位置前面插入数据
	iterator list_iter_insert_before(iterator it, DataType data)
	{
		node* p = it.current;
		node *q = new node(data, p, p->prev);
		_size++;
		q->prev = p->prev;
		p->prev->next = q;
		q->next = p;
		p->prev = q;
		return it;
	}

	// 在it位置后面插入数据
	iterator list_iter_insert_after(iterator it, DataType data)
	{
		node* p = it.current;
		node *q = new node(data, p, p->prev);
		_size++;
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
};

// 新建一个list_t对象
list_t *list_new() 
{
	return new list_t();
}

// 清空list
void list_free(list_t *lst) 
{
	lst->clear();
}

// 得到it位置的数据
DataType list_iter_data(iterator it)
{
	return *it;
}

//将it位置的数据改为data
void list_iter_set(iterator it, DataType data)
{
	it->data = data;
}

//清理it
void list_iter_clear(iterator it)
{
	it.clear();
}
#endif //LIST_H_