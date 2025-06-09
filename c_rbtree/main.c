#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    RBTree *tree = init_rbtree();
    int keys[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    int n = sizeof(keys) / sizeof(keys[0]);

    // 插入测试
    printf("插入节点: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
        rb_insert(tree, keys[i]);
    }
    printf("\n");

    // 打印树
    printf("root = %d\n", tree->root->key);
    printf("中序遍历: ");
    inorder_traversal(tree, tree->root);
    printf("\n");

    // 验证红黑树
    if (verify_rbtree(tree)) {
        printf("红黑树性质验证通过\n");
    } else {
        printf("红黑树性质验证失败\n");
    }

    // 查找测试
    int search_key = 10;
    RBNode *found = rb_search(tree, search_key);
    if (found != tree->nil) {
        printf("找到节点 %d, 颜色: %s\n", search_key, found->color == RED ? "RED" : "BLACK");
    } else {
        printf("未找到节点 %d\n", search_key);
    }

    // 删除测试
    int delete_key = 18;
    printf("\n删除节点 %d\n", delete_key);
    rb_delete(tree, delete_key);

    printf("root = %d\n", tree->root->key);
    printf("删除后中序遍历: ");
    inorder_traversal(tree, tree->root);
    printf("\n");

    // 再次验证
    if (verify_rbtree(tree)) {
        printf("删除后红黑树性质验证通过\n");
    } else {
        printf("删除后红黑树性质验证失败\n");
    }
    
    // 清理内存
    free_rbtree(tree, tree->root);
    free(tree->nil);
    free(tree);
    
    return 0;
}
