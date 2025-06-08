#include "bst.h"
#include <complex.h>
#include <stdio.h>
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

// 计算平衡因子（左子树高 - 右子树高）
int balance_factor(TreeNode *node) {
    return node ? (height(node->left) - height(node->right)) : 0;
}

// 右旋
TreeNode* right_rotate(TreeNode *x) {
    TreeNode *y = x->left;
    TreeNode *B = y->right;

    // 执行旋转
    y->right = x;
    x->left = B;

    // 更新高度
    update_height(y);
    update_height(x);

    return y;   // 返回新的根节点
}

// 左旋
TreeNode* left_rotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *B = y->left;

    // 执行旋转
    y->left = x;
    x->right = B;

    // 更新高度
    update_height(y);
    update_height(x);
    
    return y;   // 返回新的根节点
}

// 平衡节点（根据平衡因子选择旋转方式）
TreeNode* balance_node(TreeNode *node) {
    if (!node) return node;

    // 更新当前节点高度
    update_height(node);
    int bf = balance_factor(node);

    // LL 左左失衡：右旋   左裙子型
    if (bf > 1 && balance_factor(node->left) >= 0) {
        return right_rotate(node); 
    }

    // RR 右右失衡：左旋   右裙子型
    if (bf < -1 && balance_factor(node->right) <= 0) {
        return left_rotate(node);
    }

    // LR 左右失衡：先左旋左子树再右旋   左腰子型
    if (bf > 1 && balance_factor(node->left) < 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // RL 
}

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

