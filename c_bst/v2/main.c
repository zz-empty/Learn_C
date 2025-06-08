#include <stdio.h>
#include "bst.h"

int main() {
    TreeNode *root = NULL; 
    
    // 测试插入
    root = insert_node(root, 50);
    root = insert_node(root, 30);
    root = insert_node(root, 10);

    printf("插入后层次遍历:\n");
    level_order_traversal(root);

    printf("\n创建不平衡BST:\n");
    // 创建不平衡的二叉搜索树（右偏）
    TreeNode *root2 = NULL;
    root2 = insert_node(root2, 10);
    root2 = insert_node(root2, 20);
    root2 = insert_node(root2, 30);
    printf("插入后层次遍历:\n");
    level_order_traversal(root2);

    printf("\n测试自动平衡插入:\n");
    TreeNode *avl = NULL;
    int values[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        avl = insert_node(avl, values[i]);
        printf("插入 %d 后: ", values[i]);
        inorder_traversal(avl);
        printf("\n");
    }
    printf("最终层次遍历:\n");
    level_order_traversal(avl);

    // 释放内存
    free_tree(root);
    free_tree(root2);
    free_tree(avl);

}
