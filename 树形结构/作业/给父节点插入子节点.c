#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* firstchild;
    struct Node* nextsibling;
} Node;

// 创建树的子女兄弟链表
void createChildAndSiblingTree(Node** root, char* e, int* degree, int n) {
    if (n == 0) {
        *root = NULL;
        return;
    }

    Node** Q = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        Q[i] = (Node*)malloc(sizeof(Node));
        Q[i]->data = e[i];
        Q[i]->firstchild = Q[i]->nextsibling = NULL;
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        int d = degree[i];
        if (d > 0) {
            k++;
            Q[i]->firstchild = Q[k];
            while (--d > 0) {
                Q[k]->nextsibling = Q[k + 1];
                k++;
            }
        }
    }
    *root = Q[0];
    free(Q);
}

// 查找指定父节点的地址
Node* PreSearchBiT(Node* T, char fa) {
    if (T == NULL) return NULL;
    if (T->data == fa) return T;
    Node* p = PreSearchBiT(T->firstchild, fa);
    if (p != NULL) return p;
    return PreSearchBiT(T->nextsibling, fa);
}

// 插入新节点，fa是双亲节点，ch是孩子节点
int InsertBiT(Node** T, char fa, char ch) {
    Node* parent = PreSearchBiT(*T, fa);
    if (parent == NULL) return 0; // 父节点不存在，插入失败

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->firstchild = newNode->nextsibling = NULL;

    if (parent->firstchild == NULL) {
        parent->firstchild = newNode; // 作为第一个子节点插入
    } else {
        Node* lastChild = parent->firstchild;
        while (lastChild->nextsibling != NULL) {
            lastChild = lastChild->nextsibling; // 找到最后一个兄弟节点
        }
        lastChild->nextsibling = newNode; // 插入到兄弟链末尾
    }
    return 1; // 插入成功
}

// 计算并输出节点的度
void printDegree(Node* root) {
    if (root == NULL) return;

    Node* queue[100]; // 假设节点数不超过100
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];

        // 计算当前节点的度数
        int degree = 0;
        Node* child = current->firstchild;
        while (child != NULL) {
            degree++;
            queue[rear++] = child; // 将子节点加入队列
            child = child->nextsibling;
        }
        printf("%d ", degree);
    }
}

// 层序遍历输出树的结构
void levelOrderTraversal(Node* root) {
    if (root == NULL) return;

    Node* queue[100]; // 假设节点数不超过100
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%c", current->data);

        // 将当前节点的所有子节点按顺序加入队列
        Node* child = current->firstchild;
        while (child != NULL) {
            queue[rear++] = child;
            child = child->nextsibling;
        }
    }
    printf("\n");
}

int main() {
    char e[101]; // 假设最多100个节点
    int degree[100];
    int n = 0;

    // 输入节点数据
    scanf("%s", e);
    n = strlen(e);

    // 输入节点的度
    for (int i = 0; i < n; i++) {
        scanf("%d", &degree[i]);
    }

    Node* root = NULL;
    createChildAndSiblingTree(&root, e, degree, n);

    // 输入要插入的父节点和孩子节点
    char fa, ch;
    scanf(" %c %c", &fa, &ch); // 注意空格，避免读取换行符
    InsertBiT(&root, fa, ch);

    // 输出层序遍历结果
    levelOrderTraversal(root);

    // 输出每个节点的度
    printDegree(root);

    // 释放内存（实际题目可能不需要）
    // 此处省略，实际使用时需补充

    return 0;
}