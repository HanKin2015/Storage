/*******************************************************************************
* 文 件 名: linked_list_example.cpp
* 文件描述: 链表
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 定义节点结构
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// 定义单链表
class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    // 插入元素
    void insert(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 删除元素
    void remove(int val) {
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr && current->data != val) {
            prev = current;
            current = current->next;
        }
        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
        }
    }

    // 打印链表
    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node* head;
};

int main() {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.print();
    list.remove(2);
    list.print();
    return 0;
}
