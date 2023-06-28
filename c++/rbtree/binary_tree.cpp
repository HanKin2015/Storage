/**
* 文 件 名: binary_tree.cpp
* 文件描述: 二叉树
* 作    者: HanKin
* 创建日期: 2023.06.26
* 修改日期：2023.06.26
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>

using namespace std;

// 定义二叉树节点结构体（链式存储结构）
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 插入节点
void insert(TreeNode*& root, int val)
{
    if (root == NULL) {
        root = new TreeNode(val);
        return;
    }
    if (val < root->val) {
        insert(root->left, val);
    } else {
        insert(root->right, val);
    }
    return;
}

// 前序遍历
void preorder(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
    return;
}

// 中序遍历
void inorder(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
    return;
}

// 后序遍历
void postorder(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
    return;
}

// 顺序存储结构
// 创建二叉树始终需要满足
void sequential_storage_create_binary_tree(int *root, int *nodes, int len)
{
    root[1] = nodes[1];
    for(int i = 2; i < len; i++) {
        int deepth = 1;
        while(root[deepth] != 0) { //结点为空，退出循环，进行存储
            if(nodes[i] < root[deepth]) {
                deepth = 2 * deepth;
            } else {
                deepth = 2 * deepth + 1;
            }
        }
        root[deepth] = nodes[i];
    }
    return;
}

int main()
{
    TreeNode* root = NULL;
    insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 1);
    insert(root, 9);
    /*
          5
        3   7
      1       9
    *
    * 5 3 1 7 9
    * 1 3 5 7 9
    * 1 3 9 7 5
    */
    preorder(root); cout << endl;
    inorder(root);  cout << endl;
    postorder(root);cout << endl;
    return 0;
}
