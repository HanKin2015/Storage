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

// 定义二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 插入节点
void insert(TreeNode*& root, int val) {
    if (root == NULL) {
        root = new TreeNode(val);
        return;
    }
    if (val < root->val) {
        insert(root->left, val);
    } else {
        insert(root->right, val);
    }
}

// 中序遍历
void inorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main()
{
    TreeNode* root = NULL;
    insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 1);
    insert(root, 9);
    inorder(root);
    return 0;
}
