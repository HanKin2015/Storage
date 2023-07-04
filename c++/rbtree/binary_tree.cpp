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
#include <algorithm>

using namespace std;

// 定义二叉树节点结构体（链式存储结构）
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 插入节点（创建二叉排序树，更多创建方式见D:\Github\ACM\ACM_Template(HanKin)\二叉树实战.cpp）
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

// 查找节点
bool search(TreeNode* root, int val)
{
    if (root == NULL) {
        return false;
    }
    if (root->val == val) {
        return true;
    } else if (val < root->val) {
        return search(root->left, val);
    } else {
        return search(root->right, val);
    }
}

//统计二叉树的深度
/*
    当左子树的深度大于右子树时，则返回左子树的深度+1，否则返回右子树的深度+1
    当root为叶子结点时，停止递归，返回1，然后逐层向上累加。
*/
int binary_tree_depth(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    int left_depth = binary_tree_depth(root->left);
    int right_depth = binary_tree_depth(root->right);
    return max(left_depth, right_depth) + 1;
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
    
    int val = 7;
    if (search(root, val)) {
        cout << val << " 存在于二叉搜索树中" << endl;
    } else {
        cout << val << " 不存在于二叉搜索树中" << endl;
    }
    
    int depth = binary_tree_depth(root);
    cout << "二叉树深度为：" << depth << endl;
    return 0;
}
