#include <stdio.h>  
#include <stdlib.h>  

typedef int ElementType;  

typedef struct BiNode {  
    ElementType data;  
    struct BiNode *left;  
    struct BiNode *right;  
} BiNode, *BiTree;  

// �����������Ĳ����������  
BiTree createBiTree(const int *levelOrder, int size) {  
    if (size == 0 || levelOrder[0] == -1) {  
        return NULL;  
    }  

    BiTree root = (BiNode *)malloc(sizeof(BiNode));  
    root->data = levelOrder[0];  
    root->left = NULL;  
    root->right = NULL;  

    BiNode *queue[size];  
    int front = 0, rear = 0;  
    queue[rear++] = root;  

    int i = 1;  
    while (i < size) {  
        BiNode *currentNode = queue[front++];  
        for (int j = 0; j < 2 && i < size; j++) {  
            if (levelOrder[i] != -1) {  
                BiNode *child = (BiNode *)malloc(sizeof(BiNode));  
                child->data = levelOrder[i];  
                child->left = NULL;  
                child->right = NULL;  
                if (j == 0) {  
                    currentNode->left = child;  
                } else {  
                    currentNode->right = child;  
                }  
                queue[rear++] = child;  
            }  
            i++;  
        }  
    }  

    return root;  
}  

// �ݹ�ʵ���������  
void inorderTraversalRecursive(BiTree root, int** result, int* index) {  
    if (root == NULL) {  
        return;  
    }  
    
    // Traverse the left subtree  
    inorderTraversalRecursive(root->left, result, index);  
    
    // Visit the current node  
    (*result)[*index] = root->data;  
    (*index)++;  
    
    // Traverse the right subtree  
    inorderTraversalRecursive(root->right, result, index);  
}  

// �Ӷ������л������������  
int* inorderTraversal(BiTree root, int* returnSize) {  
    // �ȱ�����������ڵ�����  
    int size = 0;  
    void countNodes(BiTree node) {
        
        if (node) {  
            countNodes(node->left);  
            size++;  
            countNodes(node->right);  
        }  
    }  
    countNodes(root);  
    
    // ����������  
    int* result = (int*)malloc(size * sizeof(int));  
    *returnSize = size; // ���ؽڵ������  
    int index = 0;  
    
    inorderTraversalRecursive(root, &result, &index);  
    return result;  
}  

// �ͷŶ��������ڴ�  
void freeBiTree(BiTree root) {  
    if (root == NULL) {  
        return;  
    }  
    freeBiTree(root->left);  
    freeBiTree(root->right);  
    free(root);  
}  

int main() {  
    int n;  
    scanf("%d", &n);  
    int elements[n];  
    
    // ��������������  
    for (int i = 0; i < n; i++) {  
        scanf("%d", &elements[i]);  
    }  

    BiTree tree = createBiTree(elements, n); // ����������  
    int returnSize;  
    int* result = inorderTraversal(tree, &returnSize); // �������  

    // �������������  
    for (int i = 0; i < returnSize; i++) {  
        printf("%d ", result[i]);  
    }  
    printf("\n");  

    // �ͷ��ڴ�  
    freeBiTree(tree);  
    free(result);  

    return 0;  
}  