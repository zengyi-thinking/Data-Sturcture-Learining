#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 定义队列结构用于层次遍历
typedef struct Queue
{
    TreeNode **nodes;
    int front;
    int rear;
    int capacity;
} Queue;

// 创建队列
Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->nodes = (TreeNode **)malloc(sizeof(TreeNode *) * capacity);
    queue->front = queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

// 检查队列是否为空
int isEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}

// 入队
void enqueue(Queue *queue, TreeNode *node)
{
    if (queue->rear == queue->capacity)
    {
        // 这里简单处理，实际应用中可能需要扩容
        return;
    }
    queue->nodes[queue->rear++] = node;
}

// 出队
TreeNode *dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        return NULL;
    }
    return queue->nodes[queue->front++];
}

// 层次遍历二叉树
void levelOrderTraversal(TreeNode *root, int n)
{
    if (root == NULL)
        return;

    Queue *queue = createQueue(n);
    enqueue(queue, root);

    int isFirst = 1;

    while (!isEmpty(queue))
    {
        TreeNode *current = dequeue(queue);

        if (!isFirst)
        {
            printf(" ");
        }
        printf("%d", current->val);
        isFirst = 0;

        if (current->left != NULL)
        {
            enqueue(queue, current->left);
        }
        if (current->right != NULL)
        {
            enqueue(queue, current->right);
        }
    }

    free(queue->nodes);
    free(queue);
}

int main()
{
    int N;
    scanf("%d", &N);

    // 创建节点数组，索引从1开始
    TreeNode **nodes = (TreeNode **)malloc(sizeof(TreeNode *) * (N + 1));
    for (int i = 1; i <= N; i++)
    {
        nodes[i] = (TreeNode *)malloc(sizeof(TreeNode));
        nodes[i]->left = nodes[i]->right = NULL;
    }

    // 读取输入并构建树
    int rootFlag = 1;
    int *isChild = (int *)calloc(N + 1, sizeof(int)); // 标记哪些节点是其他节点的孩子

    for (int i = 1; i <= N; i++)
    {
        int left, right, val;
        scanf("%d %d %d", &left, &right, &val);

        nodes[i]->val = val;
        if (left != 0)
        {
            nodes[i]->left = nodes[left];
            isChild[left] = 1;
        }
        if (right != 0)
        {
            nodes[i]->right = nodes[right];
            isChild[right] = 1;
        }
    }

    // 找出根节点（没有被任何节点指向的节点）
    int rootIndex = 1;
    for (int i = 1; i <= N; i++)
    {
        if (!isChild[i])
        {
            rootIndex = i;
            break;
        }
    }

    // 进行层次遍历
    levelOrderTraversal(nodes[rootIndex], N);
    printf("\n");

    // 释放内存
    for (int i = 1; i <= N; i++)
    {
        free(nodes[i]);
    }
    free(nodes);
    free(isChild);

    return 0;
}