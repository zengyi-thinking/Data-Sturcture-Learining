#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* firstchild;
    struct Node* nextsibling;
} Node;

// ����������Ů�ֵ�����
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

// ����ָ�����ڵ�ĵ�ַ
Node* PreSearchBiT(Node* T, char fa) {
    if (T == NULL) return NULL;
    if (T->data == fa) return T;
    Node* p = PreSearchBiT(T->firstchild, fa);
    if (p != NULL) return p;
    return PreSearchBiT(T->nextsibling, fa);
}

// �����½ڵ㣬fa��˫�׽ڵ㣬ch�Ǻ��ӽڵ�
int InsertBiT(Node** T, char fa, char ch) {
    Node* parent = PreSearchBiT(*T, fa);
    if (parent == NULL) return 0; // ���ڵ㲻���ڣ�����ʧ��

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->firstchild = newNode->nextsibling = NULL;

    if (parent->firstchild == NULL) {
        parent->firstchild = newNode; // ��Ϊ��һ���ӽڵ����
    } else {
        Node* lastChild = parent->firstchild;
        while (lastChild->nextsibling != NULL) {
            lastChild = lastChild->nextsibling; // �ҵ����һ���ֵܽڵ�
        }
        lastChild->nextsibling = newNode; // ���뵽�ֵ���ĩβ
    }
    return 1; // ����ɹ�
}

// ���㲢����ڵ�Ķ�
void printDegree(Node* root) {
    if (root == NULL) return;

    Node* queue[100]; // ����ڵ���������100
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];

        // ���㵱ǰ�ڵ�Ķ���
        int degree = 0;
        Node* child = current->firstchild;
        while (child != NULL) {
            degree++;
            queue[rear++] = child; // ���ӽڵ�������
            child = child->nextsibling;
        }
        printf("%d ", degree);
    }
}

// �������������Ľṹ
void levelOrderTraversal(Node* root) {
    if (root == NULL) return;

    Node* queue[100]; // ����ڵ���������100
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%c", current->data);

        // ����ǰ�ڵ�������ӽڵ㰴˳��������
        Node* child = current->firstchild;
        while (child != NULL) {
            queue[rear++] = child;
            child = child->nextsibling;
        }
    }
    printf("\n");
}

int main() {
    char e[101]; // �������100���ڵ�
    int degree[100];
    int n = 0;

    // ����ڵ�����
    scanf("%s", e);
    n = strlen(e);

    // ����ڵ�Ķ�
    for (int i = 0; i < n; i++) {
        scanf("%d", &degree[i]);
    }

    Node* root = NULL;
    createChildAndSiblingTree(&root, e, degree, n);

    // ����Ҫ����ĸ��ڵ�ͺ��ӽڵ�
    char fa, ch;
    scanf(" %c %c", &fa, &ch); // ע��ո񣬱����ȡ���з�
    InsertBiT(&root, fa, ch);

    // �������������
    levelOrderTraversal(root);

    // ���ÿ���ڵ�Ķ�
    printDegree(root);

    // �ͷ��ڴ棨ʵ����Ŀ���ܲ���Ҫ��
    // �˴�ʡ�ԣ�ʵ��ʹ��ʱ�貹��

    return 0;
}