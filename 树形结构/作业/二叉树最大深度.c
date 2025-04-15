#include <stdio.h>    // �����׼���������
#include <stdlib.h>   // �����׼�⣬�����ڴ����

typedef int ElementType;   // ����ElementTypeΪint����

// ����������ڵ�ṹ��
typedef struct BiNode {  
    ElementType data;      // �ڵ�����
    struct BiNode *left;   // ָ����������ָ��
    struct BiNode *right;   // ָ����������ָ��
} BiNode, *BiTree;   // BiNodeΪ�ڵ����ͣ�BiTreeΪָ��ڵ��ָ������

// �����������ĺ���
BiTree createBiTree(const int *levelOrder, int size) {  
    if (size == 0 || levelOrder[0] == -1) {   // �����СΪ0����ڵ�Ϊ-1������NULL
        return NULL;  
    }  

    // ������ڵ���ڴ�
    BiTree root = (BiNode *) malloc(sizeof(BiNode));  
    root->data = levelOrder[0];   // ���ø��ڵ������
    root->left = NULL;   // ��ʼ��������ΪNULL
    root->right = NULL;   // ��ʼ��������ΪNULL

    // ����һ���������ڲ�α���
    BiNode *queue[size];  
    int front = 0, rear = 0;  
    queue[rear++] = root;   // �����ڵ����

    int i = 1;   // �ӵڶ���Ԫ�ؿ�ʼ����
    while (i < size) {  
        BiNode *currentNode = queue[front++];   // ȡ������Ԫ��
        for (int j = 0; j < 2 && i < size; j++) {   // ����ǰ�ڵ�������ӽڵ�
            if (levelOrder[i] != -1) {   // �����ǰԪ�ز�Ϊ-1
                BiNode *child = (BiNode *) malloc(sizeof(BiNode));   // �����ӽڵ���ڴ�
                child->data = levelOrder[i];   // �����ӽڵ������
                child->left = NULL;   // ��ʼ���ӽڵ��������ΪNULL
                child->right = NULL;   // ��ʼ���ӽڵ��������ΪNULL
                if (j == 0) {  
                    currentNode->left = child;   // ���õ�ǰ�ڵ�����ӽڵ�
                } else {  
                    currentNode->right = child;   // ���õ�ǰ�ڵ�����ӽڵ�
                }  
                queue[rear++] = child;   // ���ӽڵ����
            }  
            i++;  
        }  
    }  

    return root;   // ���ظ��ڵ�
}  

// ����������������ȵĺ���
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