#include <stdio.h>    // 引入标准输入输出库
#include <stdlib.h>   // 引入标准库，用于内存分配

typedef int ElementType;   // 定义ElementType为int类型

// 定义二叉树节点结构体
typedef struct BiNode {  
    ElementType data;      // 节点数据
    struct BiNode *left;   // 指向左子树的指针
    struct BiNode *right;   // 指向右子树的指针
} BiNode, *BiTree;   // BiNode为节点类型，BiTree为指向节点的指针类型

// 创建二叉树的函数
BiTree createBiTree(const int *levelOrder, int size) {  
    if (size == 0 || levelOrder[0] == -1) {   // 如果大小为0或根节点为-1，返回NULL
        return NULL;  
    }  

    // 分配根节点的内存
    BiTree root = (BiNode *) malloc(sizeof(BiNode));  
    root->data = levelOrder[0];   // 设置根节点的数据
    root->left = NULL;   // 初始化左子树为NULL
    root->right = NULL;   // 初始化右子树为NULL

    // 创建一个队列用于层次遍历
    BiNode *queue[size];  
    int front = 0, rear = 0;  
    queue[rear++] = root;   // 将根节点入队

    int i = 1;   // 从第二个元素开始处理
    while (i < size) {  
        BiNode *currentNode = queue[front++];   // 取出队首元素
        for (int j = 0; j < 2 && i < size; j++) {   // 处理当前节点的左右子节点
            if (levelOrder[i] != -1) {   // 如果当前元素不为-1
                BiNode *child = (BiNode *) malloc(sizeof(BiNode));   // 分配子节点的内存
                child->data = levelOrder[i];   // 设置子节点的数据
                child->left = NULL;   // 初始化子节点的左子树为NULL
                child->right = NULL;   // 初始化子节点的右子树为NULL
                if (j == 0) {  
                    currentNode->left = child;   // 设置当前节点的左子节点
                } else {  
                    currentNode->right = child;   // 设置当前节点的右子节点
                }  
                queue[rear++] = child;   // 将子节点入队
            }  
            i++;  
        }  
    }  

    return root;   // 返回根节点
}  

// 计算二叉树的最大深度的函数
int maxDepth(BiNode *root) {  
    if (root == NULL) {  
        return 0;  // Base case: the depth of a null node is 0  
    }  

    int llevel = maxDepth(root->left);   // Recursively find the depth of the left subtree  
    int rlevel = maxDepth(root->right);  // Recursively find the depth of the right subtree  

    // Return the maximum of left and right depths plus 1 for the current node  
    return (llevel > rlevel ? llevel : rlevel) + 1;  
}  

void freeBiTree(BiTree root) {  
    if (root == NULL) {  
        return;  
    }  
    freeBiTree(root->left);  
    freeBiTree(root->right);  
    free(root);  
}  

int main() {  
    int n, nn;  
    scanf("%d", &n);  
    nn = n;  
    int elements[n];  
    for (int i = 0; i < n; i++) {  
        scanf("%d", &elements[i]);  
        if (elements[i] == -1) {  
            nn--;  
        }  
    }  

    BiTree tree = createBiTree(elements, n);  

    printf("%d", maxDepth(tree));  

    freeBiTree(tree);  
    return 0;  
}  