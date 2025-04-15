#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define TElemType char

// ����������ṹ
typedef struct CTNode
{
    int child; // ���ӽ���������е�����
    struct CTNode *next;
} ChildPtr;

// ���������ʾ���Ľ��ṹ
typedef struct
{
    TElemType data;       // ������������
    ChildPtr *firstchild; // ���������ͷָ��
} CTBox;

// ���������ʾ�������ṹ
typedef struct
{
    CTBox nodes[MAX_SIZE]; // �洢��������
    int n, r;              // ���������������λ��
} CTree;

// �����ֵܱ�ʾ���Ľ��ṹ
typedef struct CSNode
{
    TElemType data;             // ������������
    struct CSNode *firstchild;  // ��һ�����ӽ��
    struct CSNode *nextsibling; // ��һ���ֵܽ��
} CSNode;

// ��ʼ�����������ʾ������
CTree initTree(CTree tree, int n, char values[], int children[][MAX_SIZE], int childrenCounts[])
{
    tree.n = n;
    tree.r = 0; // Ĭ���������λ������nodes[0]��

    for (int i = 0; i < n; i++)
    {
        tree.nodes[i].data = values[i]; // ���ýڵ�����
        tree.nodes[i].firstchild = NULL;

        if (childrenCounts[i] > 0)
        {
            ChildPtr *p = NULL;
            for (int j = 0; j < childrenCounts[i]; j++)
            {
                // �����º��ӽڵ�
                ChildPtr *newEle = (ChildPtr *)malloc(sizeof(ChildPtr));
                newEle->child = children[i][j]; // ���ú�������
                newEle->next = NULL;

                // ���Ӻ��ӽڵ�
                if (tree.nodes[i].firstchild == NULL)
                {
                    tree.nodes[i].firstchild = newEle;
                }
                else
                {
                    p->next = newEle; // ���ӵ�����
                }
                p = newEle; // �ƶ����������һ���ڵ�
            }
        }
    }

    return tree;
}

// �����������ʾ������ת��Ϊ�����ֵܱ�ʾ������
CSNode *convertToCS(CTree tree, int index)
{
    if (index < 0 || index >= tree.n)
    {
        return NULL; // ���������Ч������ NULL
    }

    // �����µ� CSNode ���
    CSNode *newNode = (CSNode *)malloc(sizeof(CSNode));
    newNode->data = tree.nodes[index].data; // ��������
    newNode->firstchild = NULL;             // ��ʼ������ָ��
    newNode->nextsibling = NULL;            // ��ʼ���ֵ�ָ��

    // �����������еĺ���ת��Ϊ�����ֵܱ�ʾ��
    if (tree.nodes[index].firstchild != NULL)
    {
        ChildPtr *childPtr = tree.nodes[index].firstchild;
        newNode->firstchild = convertToCS(tree, childPtr->child); // �����һ������

        // ��������ֵܺ���
        CSNode *siblingPtr = newNode->firstchild;
        childPtr = childPtr->next; // �ƶ�����һ������
        while (childPtr != NULL)
        {
            siblingPtr->nextsibling = convertToCS(tree, childPtr->child);
            siblingPtr = siblingPtr->nextsibling;
            childPtr = childPtr->next; // �ƶ�����һ��
        }
    }

    return newNode;
}

// ��ӡ�����ֵܱ�ʾ��������ǰ�������
void printCS(CSNode *root, int level)
{
    if (root == NULL)
    {
        return; // ������Ϊ�գ�ֱ�ӷ���
    }

    // ��ӡ��ǰ��������
    for (int i = 0; i < level; i++)
    {
        printf("  "); // ���ݲ㼶��ӡ����
    }
    printf("%c\n", root->data); // ��ӡ�������

    // �ݹ��ӡ���ӽ��
    printCS(root->firstchild, level + 1);

    // �ݹ��ӡ�ֵܽ��
    printCS(root->nextsibling, level);
}

int main()
{
    CTree tree;
    int n;
    char values[MAX_SIZE];
    int children[MAX_SIZE][MAX_SIZE];
    int childrenCounts[MAX_SIZE];

    // ��ȡ�������
    scanf("%d", &n);

    // ��ȡ������������ø�������ֵ
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &values[i]);
    }

    // ��ȡÿ�����ĺ��ӽ����Ϣ
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &childrenCounts[i]);
        for (int j = 0; j < childrenCounts[i]; j++)
        {
            scanf("%d", &children[i][j]);
        }
    }

    // ��ʼ�����������ʾ������
    tree = initTree(tree, n, values, children, childrenCounts);

    // ת��Ϊ�����ֵܱ�ʾ������
    CSNode *csRoot = convertToCS(tree, tree.r);

    // ��ӡ�����ֵܱ�ʾ������
    printCS(csRoot, 0);

    return 0;
}