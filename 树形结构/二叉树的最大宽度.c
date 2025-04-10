#include <stdio.h>
#include <stdlib.h>

// ����Ԫ������
typedef int ElementType;

// ����������ڵ�ṹ
typedef struct BiNode {
    ElementType data;       // �ڵ�����
    struct BiNode *left;    // ���ӽڵ�ָ��
    struct BiNode *right;   // ���ӽڵ�ָ��
} BiNode, *BiTree;

// ������нڵ�ṹ
typedef struct QueueNode {
    BiNode *node;           // �������ڵ�ָ��
    unsigned long long position; 
} QueueNode;

typedef struct Queue {
    int front;
    int rear;
    int size;
    QueueNode q[1000]; 
} Queue;

// ��ʼ������
void InitQueue(Queue* Q) {
    Q->front = Q->rear = 0;
    Q->size = 1000;
}

// �������Ƿ�����
int IsFull(Queue* Q) {
    return (Q->rear + 1) % Q->size == Q->front;
}

// �������Ƿ�Ϊ��
int IsEmpty(Queue* Q) {
    return Q->rear == Q->front;
}

// ��Ӳ���
void EnQueue(Queue* Q, BiNode* b, unsigned long long pos) {
    if (IsFull(Q)) {  
        printf("Queue is full!\n");  
        return;
    } 
    Q->q[Q->rear].node = b;
    Q->q[Q->rear].position = pos;
    Q->rear = (Q->rear + 1) % Q->size;
}

// ���Ӳ���
QueueNode DeQueue(Queue* Q) {
    QueueNode empty = {NULL, 0};
    if (IsEmpty(Q)) {  
        printf("Queue is empty!\n");  
        return empty;
    }  
    QueueNode p = Q->q[Q->front];
    Q->front = (Q->front + 1) % Q->size;
    return p;
}

// ���ݲ���������鴴��������
BiTree createBiTree(const int *levelOrder, int size) {
    if (size == 0 || levelOrder[0] == -1) {
        return NULL;
    }

    BiTree root = (BiNode *)malloc(sizeof(BiNode));
    root->data = levelOrder[0];
    root->left = NULL;
    root->right = NULL;

    BiNode *queue[1000];
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

// ����������Ŀ��
int widthOfBinaryTree(BiTree root) {
    if (root == NULL) return 0;
    
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    InitQueue(Q);
    EnQueue(Q, root, 1);
    
    int max_width = 1;
    
    while (!IsEmpty(Q)) {
        int level_size = (Q->rear - Q->front + Q->size) % Q->size;
        unsigned long long left_pos = Q->q[Q->front].position;
        unsigned long long right_pos = left_pos;
        
        for (int i = 0; i < level_size; i++) {
            QueueNode current = DeQueue(Q);
            right_pos = current.position;
            
            if (current.node->left) {
                EnQueue(Q, current.node->left, current.position * 2);
            }
            if (current.node->right) {
                EnQueue(Q, current.node->right, current.position * 2 + 1);
            }
        }
        
        int current_width = (int)(right_pos - left_pos + 1);
        if (current_width > max_width) {
            max_width = current_width;
        }
    }
    
    free(Q);
    return max_width;
}

// �ͷŶ������ڴ�
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
    
    int *elements = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
    }

    BiTree tree = createBiTree(elements, n);
    printf("%d\n", widthOfBinaryTree(tree));

    freeBiTree(tree);
    free(elements);
    return 0;
}