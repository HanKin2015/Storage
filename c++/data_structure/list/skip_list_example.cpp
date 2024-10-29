/*******************************************************************************
* 文 件 名: skip_list_example.cpp
* 文件描述: 跳表
* 备    注: g++ skip_list_example.cpp --std=c++11
* 作    者: HanKin
* 创建日期: 2024.10.29
* 修改日期：2024.10.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h> // malloc
#include <limits.h> // INT_MIN
#include <time.h>

#define MAX_LEVEL 6 // 定义跳表的最大层数为 6
#define P 0.5       // 定义节点提升到更高层的概率

// forward adv.向前；前进；进展；提前；往后；在（或向）船头；向前地；向将来
typedef struct Node {
    int value;
    struct Node* forward[]; // 指向不同层级的下一个节点的指针数组（相当于是next指针）
} Node;

typedef struct SkipList {
    int level;      // 当前跳表的最大层级（因为所有操作都是从最高层开始）
    Node* header;   // 指向跳表的头节点
} SkipList;

// 创建一个新的节点
Node* createNode(int level, int value)
{
    Node* node = (Node *)malloc(sizeof(Node) + (level + 1) * sizeof(Node *));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    return node;
}

// 创建一个新的跳表
SkipList* createSkipList()
{
    SkipList* list = (SkipList *)malloc(sizeof(SkipList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->level = 0;
    list->header = createNode(MAX_LEVEL, INT_MIN);
    for (int i = 0; i <= MAX_LEVEL; i++) {
        list->header->forward[i] = NULL;
    }
    return list;
}

// 生成一个随机层数（使用概率 P 控制节点提升的层数，确保跳表的概率平衡）
int randomLevel()
{
    int level = 0;
    while ((rand() / (double)RAND_MAX) < P && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// 插入一个新的值
void insert(SkipList* list, int value)
{
    Node* update[MAX_LEVEL + 1];    // 用于记录每一层中最后一个小于待插入值的节点
    Node* current = list->header;

    // 从最高层开始，逐层向下查找插入位置
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    // 如果值不存在，生成一个随机层数 rlevel，并在相应层级插入新节点
    if (current == NULL || current->value != value) {
        int rlevel = randomLevel();
        // 如果 rlevel 大于当前最大层数，更新跳表的最大层数
        if (rlevel > list->level) {
            for (int i = list->level + 1; i <= rlevel; i++) {
                update[i] = list->header;
            }
            list->level = rlevel;
        }

        Node* newNode = createNode(rlevel, value);
        for (int i = 0; i <= rlevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 查找一个值
int search(SkipList* list, int value)
{
    Node* current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    return current != NULL && current->value == value;
}

// 删除一个值
void delete(SkipList* list, int value)
{
    Node* update[MAX_LEVEL + 1];
    Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->value == value) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        free(current);
        current = NULL;

        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }
    }
}

// 打印跳表
void printList(SkipList* list)
{
    printf("Skip List:\n");
    for (int i = 0; i <= list->level; i++) {
        Node* node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->forward[i];
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));  // 初始化随机数生成器

    SkipList* list = createSkipList();

    insert(list, 3);
    insert(list, 6);
    insert(list, 7);
    insert(list, 9);
    insert(list, 12);
    insert(list, 19);
    insert(list, 17);
    insert(list, 26);
    insert(list, 21);
    insert(list, 25);

    printList(list);

    printf("Search for 19: %s\n", search(list, 19) ? "Found" : "Not Found");
    printf("Search for 15: %s\n", search(list, 15) ? "Found" : "Not Found");

    delete(list, 19);
    printf("After deleting 19:\n");
    printList(list);

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Skip List:
Level 0: 3 6 7 9 12 17 19 21 25 26
Level 1: 3 6 7 9 19 21 25 26
Level 2: 3 19 25
Search for 19: Found
Search for 15: Not Found
After deleting 19:
Skip List:
Level 0: 3 6 7 9 12 17 21 25 26
Level 1: 3 6 7 9 21 25 26
Level 2: 3 25
*/

