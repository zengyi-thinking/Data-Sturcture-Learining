#include <stdio.h>
#include <stdlib.h>

// ����Ԫ������Ϊint
typedef int ElementType;

// ����������ڵ�ṹ��
typedef struct BiNode {
    ElementType data; // �ڵ�����
    struct BiNode *left; // ָ����������ָ��
    struct BiNode *right; // ָ����������ָ��
} BiNode, *BiTree;

// ���ݲ���������鴴��������
BiTree createBiTree(const int *levelOrder, int size) {
    // �������Ϊ�ջ��һ��Ԫ��Ϊ-1����ʾ������������NULL
    if (size == 0 || levelOrder[0] == -1) {
        return NULL;
    }

    // �������ڵ�
    BiTree root = (BiNode *) malloc(sizeof(BiNode));
    root->data = levelOrder[0];
    root->left = NULL;
    root->right = NULL;

    // �����������ڲ������
    BiNode *queue[size];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int i = 1;
    // ���������������
    while (i < size) {
        BiNode *currentNode = queue[front++]; // ȡ�������еĵ�ǰ�ڵ�
        for (int j = 0; j < 2 && i < size; j++) { // ÿ���ڵ�����������ӽڵ�
            if (levelOrder[i] != -1) { // �����ǰԪ�ز�Ϊ-1����ʾ���ӽڵ�
                BiNode *child = (BiNode *) malloc(sizeof(BiNode)); // �����ӽڵ�
                child->data = levelOrder[i];
                child->left = NULL;
                child->right = NULL;
                if (j == 0) {
                    currentNode->left = child; // �������ӽڵ�
                } else {
                    currentNode->right = child; // �������ӽڵ�
                }
                queue[rear++] = child; // ���ӽڵ�������
            }
            i++;
        }
    }

    return root; // ���ظ��ڵ�
}

// �����������Ҷ�ӽڵ�����
void leafCount(BiTree root, int *count) {
    if(root){
        if((!root->left)&&(!root->right)){
            (*count)++;
        }
            leafCount(root->left,count);
            leafCount(root->right,count);
        }
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

    int count = 0;
    leafCount(tree, &count);
    printf("%d", count);

    freeBiTree(tree);
    return 0;
}
