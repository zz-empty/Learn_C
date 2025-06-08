#include "bst.h"

// 创建新节点
TreeNode* create_node(int value) {
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node) {
        new_node->data = value;
        new_node->left = new_node->right = NULL;
    }
    return new_node;
}

// 插入节点（递归实现）
TreeNode* insert_node(TreeNode *root, int value) {
    if (!root) {
        return create_node(value); 
    }

    if (value < root->data) {
        root->left = insert_node(root->left, value);
    } else if (value > root->data) {
        root->right = insert_node(root->right, value);
    }

    // 如果值已经存在，直接返回
    return root;
}

// 查找最小值节点（用于删除操作）
TreeNode* find_minNode(TreeNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// 删除节点
TreeNode* delete_node(TreeNode *root, int value) {
    if (!root) return NULL;

    if (value < root->data) {
        return delete_node(root->left, value);
    } else if (value > root->data) {
        return delete_node(root->right, value);
    } else {
        // 只有一个节点，或没有节点
        if (!root->left) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            TreeNode *temp = root->left;
            free(root);
        }

        // 有两个子节点, 用后继节点替代
        TreeNode * temp = find_minNode(root->right);
        // 复制后继节点的值
        root->data = temp->data;
        // 删除后继节点
        root->right = delete_node(root->right, temp->data); 
    }
    return root;
}

// 查找节点（递归实现）
TreeNode* search_node(TreeNode *root, int value) {
    if (!root || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search_node(root->left, value);
    } else {
        return search_node(root->right, value);
    } 
}


// 修改节点值（先删后插）
void update_node(TreeNode **root, int old_value, int new_value) {
    *root = delete_node(*root, old_value);
    *root = insert_node(*root, new_value);
}


// 中序遍历（验证BST性质）
void inorder_traversal(TreeNode *root) {
    if (root) {
        inorder_traversal(root->left);
        printf("%3d", root->data);
        inorder_traversal(root->right);
    }
}

// 释放二叉树内存
void free_tree(TreeNode *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// 打印二叉搜索树
void print_tree(TreeNode *root) {
    inorder_traversal(root);
    printf("\n");
}
