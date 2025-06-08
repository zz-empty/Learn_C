#include <stdio.h>
#include "bst.h"

int main() {
    TreeNode *root = NULL; 
    
    // 测试插入
    root = insert_node(root, 50);
    print_tree(root);
    insert_node(root, 30);
    print_tree(root);

#if 1
    insert_node(root, 20);
    print_tree(root);
    insert_node(root, 40);
    print_tree(root);
    insert_node(root, 70);
    print_tree(root);
    insert_node(root, 60);
    print_tree(root);
    insert_node(root, 80);
    print_tree(root);
#endif

    printf("初始BST中序遍历：");
    print_tree(root);
}
