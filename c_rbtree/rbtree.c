#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// 创建哨兵节点
RBNode* create_nil_node() {
    RBNode *nil = (RBNode*)malloc(sizeof(RBNode));
    memset(nil, 0, sizeof(RBNode));
    nil->color = BLACK;     // 哨兵节点是黑色
    return nil;
}

// 初始化红黑树
RBTree* init_rbtree() {
    RBTree *rb = (RBTree*)malloc(sizeof(RBTree));
    rb->nil = create_nil_node();
    rb->root = rb->nil;
    return rb;
}

// 创建新节点
RBNode* create_node(int key) {
    RBNode *node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->parent = node->left = node->right = NULL;
    return node;
}

// 左旋操作
//   x
//A     y
//   B    C
void left_rotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;     // 将B从y挂到x

    // 如果B节点存在，修改它的parent
    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    // 修改y的parent
    y->parent = x->parent;

    // 修改x的上一层
    if (x->parent == tree->nil) {
        tree->root = y;     // x是root节点
    } else if (x == x->parent->left) {
        x->parent->left = y;    // x是上一层的左孩子
    } else {
        x->parent->right = y;       // x是上一层的右孩子
    }

    // 旋转
    y->left = x;
    x->parent = y;
}

// 右旋操作
//        x
//    y      A
// C    B
void right_rotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;

    if (y->right != tree->nil) {
        y->right->parent = x;
    } 

    y->parent = x->parent;

    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

// 插入修复
void insert_fixup(RBTree *tree, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            // 父为爷的左孩子
            RBNode *y = z->parent->parent->right;   // 定义叔叔节点
            
            if (RED == y->color) {
                // 叔叔节点是红色，父叔染黑，爷染红，重新插爷
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // 叔叔黑，如果为左腰子型，父左旋
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                // 此时 为左裙子型，父染黑，爷染红，右旋爷爷
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            // 父为爷的右孩子
            RBNode *y = z->parent->parent->left;    // 定义叔叔节点
            
            if (RED == y->color) {
                // 叔叔节点是红色，父叔染黑，爷染红，重新插爷
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // 叔叔黑，如果为右腰子型，父右旋
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                // 此时 为右裙子型，父染黑，爷染红，左旋爷爷
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    // 根节点染黑
    tree->root->color = BLACK;
}

// 插入节点
void rb_insert(RBTree *tree, int key) {
    // 创建节点
    RBNode *z = create_node(key);

    // 查找插入位置
    RBNode *y = tree->nil;      // 插入位置的父结点
    RBNode *x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            return;     // key已经存在，直接退出
        }
    }

    // 修改插入节点的父节点
    z->parent = y;

    // 插入节点
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else if (z->key > y->key) {
        y->right = z;
    }

    // 设置新节点的左右子节点，颜色为红色
    z->left = z->right = tree->nil;
    z->color = RED;

    // 调整树的结构，使其满足红黑树的性质
    insert_fixup(tree, z);
}

// 查找最小节点
RBNode* tree_minimum(RBTree *tree, RBNode *x) {
    while (x->left != tree->nil) {
        x = x->left;
    }
    return x;
}

// 删除修复
void delete_fixup(RBTree *tree, RBNode *x) {
    // 当x不是根节点且x的颜色为黑时，进行修复
    while (x != tree->root && x->color == BLACK) {
        // 如果x是父节点的左孩子
        if (x == x->parent->left) {
            // 获取x的兄弟节点
            RBNode *w = x->parent->right;

            // 情况1：兄弟节点是红色
            if (w->color == RED) {
                // 兄弟染黑，父染红，父左旋
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                // 更新兄弟节点
                w = x->parent->right;
            }

            // 情况2：兄弟节点是黑色，且兄弟的两个节点是黑色
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // 将兄弟染红，x改为父结点
                w->color = RED;
                x = x->parent;
            } else {
                // 情况3：兄弟节点是黑色，兄弟的左孩子是红色，右孩子是黑色
                if (w->right->color == BLACK) {
                    // 兄左孩子染黑，兄染红，兄右旋
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    // 更新兄
                    w = x->parent->right;
                }

                // 情况4：兄黑，兄右红
                // 兄染父色，父染黑，兄右染黑，父左旋
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                // x改为root
                x = tree->root;
            }
        } else {
            // 对称情况
            RBNode *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    // 将x染黑
    x->color = BLACK;
}

// 删除节点
void rb_delete(RBTree *tree, int key) {
    // 查找要删除的节点
    RBNode *z = tree->root;
    while (z != tree->nil) {
        if (z->key == key) break;
        if (z->key > key) z = z->left;  // 这里写错了判断，找了半天的错误, 干
        else z = z->right;
    }

    // 没找到
    if (z == tree->nil) return;
    
    // 找到了
    RBNode *y = z;  // y是实际删除的结点
    Color y_original_color = y->color;  // 保存y的颜色
    RBNode *x;      // 确定替换节点x  用nil, 或者子树，或者最小后继

    // z 没有左子树, 用右子树替代
    if (z->left == tree->nil) {
        x = z->right;
        if (z->parent == tree->nil) {   // z是根节点
            tree->root = x;
        } else if (z == z->parent->left) {  
            z->parent->left = x;    // z是父节点的左孩子
        } else {
            z->parent->right = x;   // z是父节点的右孩子
        }
        x->parent = z->parent;  
    }    
    // z 没有右子树, 用左子树替代
    else if (z->right == tree->nil) {
        x = z->left;
        if (z->parent == tree->nil) {   // z是根节点
            tree->root = x;
        } else if (z == z->parent->left) {  
            z->parent->left = x;    // z是父节点的左孩子
        } else {
            z->parent->right = x;   // z是父节点的右孩子
        }
        x->parent = z->parent;  
    }    
    // z 有两个子树, 用后继节点替代
    else {
        y = tree_minimum(tree, z->right); // z的最小后继
        y_original_color = y->color;
        x = y->right;   // 最小后继的右节点

#if 1
        // 将y从原有结构中摘除
        if (z == y->parent) {
            // y是z的直接子节点
            x->parent = y;
        } else {
            // y不是z的直接子节点, 将y取走后，修改原y所在的结构
            if (y->parent == tree->nil) {
                tree->root = x;
            } else if (y == y->parent->left) {
                y->parent->left = x;
            } else {
                y->parent->right = x;
            }
            x->parent = y->parent;

            // 将y挂到z的右子树
            y->right = z->right;
            y->right->parent = y;
        } 
#else 
        // 修复后代码
        if (y != z->right) {  // 正确：检查y是否是z的直接右子节点
                              // 用x替换y的位置
            if (y->parent == tree->nil) {
                tree->root = x;
            } else if (y == y->parent->left) {
                y->parent->left = x;
            } else {
                y->parent->right = x;
            }
            x->parent = y->parent;  // 正确设置x的父指针

            // 将y连接到z的右子树（不覆盖原有子树）
            y->right = z->right;
            y->right->parent = y;
        } else {
            x->parent = y;  // 直接右子节点的特殊情况
        }  
#endif

        // 用y替换z
        if (z->parent == tree->nil) {
            tree->root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->parent = z->parent;

        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    // 如果y是黑色节点，那么删除后需要调整红黑树, 使其黑色路径相同
    if (y_original_color == BLACK) {
        delete_fixup(tree, x);
    }

    free(z);    // 释放z节点
}

// 查找节点
RBNode* rb_search(RBTree *tree, int key) {
    RBNode *x = tree->root;
    while (x != tree->nil) {
        if (key < x->key) {
            x = x->left;
        } else if (key > x->key) {
            x = x->right;
        } else {
            return x;
        }
    }

    return tree->nil;
}

// 打印红黑树（中序遍历）
void inorder_traversal(RBTree *tree, RBNode *node) {
    if (node != tree->nil) {
        inorder_traversal(tree, node->left);
        printf("%d(%s) ", node->key, node->color == RED ? "RED" : "BLACK");
        inorder_traversal(tree, node->right);
    }
}

// 验证红黑树性质
int verify_rbtree_properties(RBTree *tree, RBNode *node, int black_count, int *path_black_count) {
    if (node == tree->nil) {
        if (-1 == *path_black_count) {
            *path_black_count = black_count;
        } else if (black_count != *path_black_count) {
            return 0;
        }
        return 1;
    }

    // 红节点孩子必须为黑
    if (node->color == RED) {
        if (node->left->color == RED || node->right->color == RED) {
            return 0;
        }
    } else {
        black_count++;
    }

    int left_ok = verify_rbtree_properties(tree, node->left, black_count, path_black_count);
    int right_ok = verify_rbtree_properties(tree, node->right, black_count, path_black_count);

    return left_ok && right_ok;
}

// 验证红黑树
int verify_rbtree(RBTree *tree) {
    // 根节点必须为黑
    if (tree->root->color != BLACK) {
        return 0;
    }

    int path_black_count = -1;  // why
    return verify_rbtree_properties(tree, tree->root, 0, &path_black_count);
}

// 释放红黑树节点
void free_rbtree(RBTree *tree, RBNode *node) {
    if (node == tree->nil) return;
    free_rbtree(tree, node->left);
    free_rbtree(tree, node->right);
    free(node);
}
