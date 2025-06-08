#include "avl.h"
#include <cmath>
#include <stdlib.h>

// 创建新节点
TreeNode* create_node(int value) {
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node) {
        new_node->data = value;
        new_node->height = 1;   // 新节点高度为1
        new_node->left = new_node->right = NULL;
    }
    return new_node;
}

// 计算节点高度
int height(TreeNode *node) {
    return node ? node->height : 0;
}

// 更新节点高度
void update_height(TreeNode *node) {
    if (node) {
        int left_height = height(node->left);
        int right_height = height(node->right);
        node->height = (left_height > right_height ? left_height : right_height) + 1;
    }
}

// 计算平衡因子
int balance_factor(TreeNode *node) {
    
}

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

