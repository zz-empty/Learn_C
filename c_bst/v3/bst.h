#ifndef __BST_H__
#define __BST_H__
#include <stdio.h>
#include <stdlib.h>


// 二叉树节点结构
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

// 创建新节点
TreeNode* create_node(int value);


// 右旋
TreeNode* right_rotate(TreeNode *x);

// 左旋
TreeNode* left_rotate(TreeNode *x);


// 插入节点（带平衡）
TreeNode* insert_node(TreeNode *root, int value);

// 查找最小值节点（用于删除操作）
TreeNode* tree_minimum(TreeNode *node);

// 删除节点
TreeNode* delete_node(TreeNode *root, int value);

// 查找节点（递归实现）
TreeNode* search_node(TreeNode *root, int value);

// 修改节点值（先删后插）
void update_node(TreeNode **root, int old_value, int new_value);

// 中序遍历（验证BST性质）
void inorder_traversal(TreeNode *root);

// 层次遍历(可视化树结构)
void level_order_traversal(TreeNode *root);

// 释放二叉树内存
void free_tree(TreeNode *root);

// 打印二叉搜索树
void print_tree(TreeNode *root);


#endif
