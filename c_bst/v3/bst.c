#include "bst.h"
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

// 创建新节点
TreeNode* create_node(int value) {
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node) {
        new_node->data = value;
        new_node->left = new_node->right = NULL;
    }
    return new_node;
}



// 右旋
TreeNode* right_rotate(TreeNode *x) {
    TreeNode *y = x->left;
    TreeNode *B = y->right;

    // 执行旋转
    y->right = x;
    x->parent = y;
    x->left = B;
    if (B) B->parent = x;

    return y;   // 返回新的根节点
}

// 左旋  右节点替换
//    x
//       y
//     B
// y一定存在，B不一定存在
TreeNode* left_rotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *B = y->left;

    // 执行旋转
    y->left = x;
    x->parent = y;
    x->right = B;
    if (B) B->parent = x;

    return y;   // 返回新的根节点
}


// 插入节点（带平衡）
TreeNode* insert_node(TreeNode *root, int value) {
    TreeNode *node = create_node(value);

    TreeNode *y = NULL;
    TreeNode *cur = root;

    // 查找插入位置
    while (cur) {
        y = cur;
        if (value < cur->data) {
            cur = cur->left;
        } else if (value > cur->data) {
            cur = cur->right;
        } else {
            return NULL;    // 重复值不处理
        }
    }


    if (y == NULL) {
        return node;
    }
    // 将新节点挂到y下
    if (value < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->parent = y;

    return root;
}

// 查找最小值节点（用于删除操作）
TreeNode* tree_minimum(TreeNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// 删除节点
TreeNode* delete_node(TreeNode *root, int value) {
    if (!root) return NULL;

    if (value < root->data) {
        root->left = delete_node(root->left, value);
    } else if (value > root->data) {
        root->right = delete_node(root->right, value);
    } else {
        // 找到目标节点
        // 情况1: 只有一个子树，或没有子树
        if (!root->left) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        } 

        // 情况2：有两个子树
        TreeNode *temp = tree_minimum(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }

    return root; 
}

// 查找节点（递归实现）
TreeNode* search_node(TreeNode *root, int value) {
    if (!root || root->data == value) return NULL;

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

#if 1
// 层次遍历(可视化树结构)
void level_order_traversal(TreeNode *root) {
    if (!root) return; 

    #define MAX_SIZE 100
    TreeNode *queue[MAX_SIZE];
    int front = 0;  // 队头
    int rear = 0;   // 队尾的下一个

    queue[rear++] = root;

    // 只要队列中有元素，就进入循环
    while (front < rear) {
        int level_size = rear - front;
        for (int i = 0; i < level_size; ++i) {
            TreeNode *node = queue[front++];    // 取队头 
            printf("%3d", node->data);

            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        printf("\n");
    }
}
#endif


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

}

