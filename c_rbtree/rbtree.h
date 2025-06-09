#ifndef __RBTREE_H__
#define __RBTREE_H__

// 红黑树节点颜色定义
typedef enum {RED, BLACK} Color;

// 红黑树节点的结构
typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

// 红黑树的结构
typedef struct {
    RBNode *root;
    RBNode *nil;    // 哨兵节点，表示空节点
} RBTree;

// 创建哨兵节点
RBNode* create_nil_node();

// 初始化红黑树
RBTree* init_rbtree();

// 创建新节点
RBNode* create_node(int key);

// 左旋操作
void left_rotate(RBTree *tree, RBNode *x);

// 右旋操作
void right_rotate(RBTree *tree, RBNode *x);

// 插入修复
void insert_fixup(RBTree *tree, RBNode *z);

// 插入节点
void rb_insert(RBTree *tree, int key);

// 查找最小节点
RBNode* tree_minimum(RBTree *tree, RBNode *x);

// 删除修复
void delete_fixup(RBTree *tree, RBNode *x);

// 删除节点
void rb_delete(RBTree *tree, int key);

// 查找节点
RBNode* rb_search(RBTree *tree, int key);

// 打印红黑树（中序遍历）
void inorder_traversal(RBTree *tree, RBNode *node);

// 验证红黑树性质
int verify_rbtree_properties(RBTree *tree, RBNode *node, int black_count, int *path_black_count);

// 验证红黑树
int verify_rbtree(RBTree *tree);

// 释放红黑树节点
void free_rbtree(RBTree *tree, RBNode *node);

#endif
