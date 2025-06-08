#ifndef __BST_H__
#define __BST_H__
#include <stdio.h>
#include <stdlib.h>


// 二叉树节点结构
typedef struct TreeNode {
    int data;
    int height; // 节点高度（用于旋转操作）
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode* create_node(int value);

// 计算节点高度
int height(TreeNode *node);

// 更新节点高度
void update_height(TreeNode *node);

// 计算平衡因子 （左子树高 - 右子树高）
int balance_factor(TreeNode *node);

// 右旋
TreeNode* right_rotate(TreeNode *x);

// 左旋
TreeNode* left_rotate(TreeNode *x);

// 平衡因子
TreeNode* balance_node(TreeNode *node);

// 插入节点（带平衡）
TreeNode* insert_node(TreeNode *root, int value);

// 查找最小值节点（用于删除操作）
TreeNode* find_minNode(TreeNode *node);

// 删除节点
TreeNode* deletee_node(TreeNode *root, int value);

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
