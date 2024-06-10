#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 定义二叉树节点结构
typedef struct BinaryTree {
    int val; // 节点值
    struct BinaryTree *left; // 0左子节点指针
    struct BinaryTree *right; // 右子节点指针
} BinaryTree;

// 创建一个新的二叉树节点
BinaryTree* create_node(int val) {
    BinaryTree* node = (BinaryTree*)malloc(sizeof(BinaryTree));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 递归删除二叉树
void delete_tree(BinaryTree* root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

// 递归实现前序遍历并输出
void print_pre_order(BinaryTree* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    print_pre_order(root->left);
    print_pre_order(root->right);
}

// 递归实现中序遍历并输出
void print_in_order(BinaryTree* root) {
    if (root == NULL) return;
    print_in_order(root->left);
    printf("%d ", root->val);
    print_in_order(root->right);
}

// 递归实现后序遍历并输出
void print_post_order(BinaryTree* root) {
    if (root == NULL) return;
    print_post_order(root->left);
    print_post_order(root->right);
    printf("%d ", root->val);
}

// 按层次遍历输出
void print_level_order(BinaryTree* root) {
    if (root == NULL) return;
    BinaryTree* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        BinaryTree* current = queue[front++];
        printf("%d ", current->val);
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
    printf("\n");
}

// 前序遍历（非递归）
void get_pre_order(BinaryTree* root, BinaryTree* result[], int* size) {
    if (root == NULL) return;
    BinaryTree* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        BinaryTree* current = stack[top--];
        result[(*size)++] = current;

        if (current->right != NULL) stack[++top] = current->right;
        if (current->left != NULL) stack[++top] = current->left;
    }
}

// 中序遍历（非递归）
void get_in_order(BinaryTree* root, BinaryTree* result[], int* size) {
    if (root == NULL) return;
    BinaryTree* stack[100];
    int top = -1;
    BinaryTree* current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        result[(*size)++] = current;
        current = current->right;
    }
}

// 后序遍历（非递归）
void get_post_order(BinaryTree* root, BinaryTree* result[], int* size) {
    if (root == NULL) return;
    BinaryTree* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 >= 0) {
        BinaryTree* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL) stack1[++top1] = current->left;
        if (current->right != NULL) stack1[++top1] = current->right;
    }

    while (top2 >= 0) {
        result[(*size)++] = stack2[top2--];
    }
}

// 层次遍历
void get_level_order(BinaryTree* root, BinaryTree* result[], int* size) {
    if (root == NULL) return;
    BinaryTree* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        BinaryTree* current = queue[front++];
        result[(*size)++] = current;

        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
}

#endif // BINARY_TREE_H
