#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define TElemType char

// 孩子链表结点结构
typedef struct CTNode
{
    int child; // 孩子结点在数组中的索引
    struct CTNode *next;
} ChildPtr;

// 孩子链表表示法的结点结构
typedef struct
{
    TElemType data;       // 结点的数据类型
    ChildPtr *firstchild; // 孩子链表的头指针
} CTBox;

// 孩子链表表示法的树结构
typedef struct
{
    CTBox nodes[MAX_SIZE]; // 存储结点的数组
    int n, r;              // 结点数量和树根的位置
} CTree;

// 孩子兄弟表示法的结点结构
typedef struct CSNode
{
    TElemType data;             // 结点的数据类型
    struct CSNode *firstchild;  // 第一个孩子结点
    struct CSNode *nextsibling; // 下一个兄弟结点
} CSNode;

// 初始化孩子链表表示法的树
CTree initTree(CTree tree, int n, char values[], int children[][MAX_SIZE], int childrenCounts[])
{
    tree.n = n;
    tree.r = 0; // 默认树根结点位于数组nodes[0]处

    for (int i = 0; i < n; i++)
    {
        tree.nodes[i].data = values[i]; // 设置节点数据
        tree.nodes[i].firstchild = NULL;

        if (childrenCounts[i] > 0)
        {
            ChildPtr *p = NULL;
            for (int j = 0; j < childrenCounts[i]; j++)
            {
                // 创建新孩子节点
                ChildPtr *newEle = (ChildPtr *)malloc(sizeof(ChildPtr));
                newEle->child = children[i][j]; // 设置孩子索引
                newEle->next = NULL;

                // 链接孩子节点
                if (tree.nodes[i].firstchild == NULL)
                {
                    tree.nodes[i].firstchild = newEle;
                }
                else
                {
                    p->next = newEle; // 链接到链表
                }
                p = newEle; // 移动到链表的下一个节点
            }
        }
    }

    return tree;
}

// 将孩子链表表示法的树转换为孩子兄弟表示法的树
CSNode *convertToCS(CTree tree, int index)
{
    if (index < 0 || index >= tree.n)
    {
        return NULL; // 如果索引无效，返回 NULL
    }

    // 创建新的 CSNode 结点
    CSNode *newNode = (CSNode *)malloc(sizeof(CSNode));
    newNode->data = tree.nodes[index].data; // 设置数据
    newNode->firstchild = NULL;             // 初始化孩子指针
    newNode->nextsibling = NULL;            // 初始化兄弟指针

    // 将孩子链表中的孩子转换为孩子兄弟表示法
    if (tree.nodes[index].firstchild != NULL)
    {
        ChildPtr *childPtr = tree.nodes[index].firstchild;
        newNode->firstchild = convertToCS(tree, childPtr->child); // 处理第一个孩子

        // 处理后续兄弟孩子
        CSNode *siblingPtr = newNode->firstchild;
        childPtr = childPtr->next; // 移动到下一个孩子
        while (childPtr != NULL)
        {
            siblingPtr->nextsibling = convertToCS(tree, childPtr->child);
            siblingPtr = siblingPtr->nextsibling;
            childPtr = childPtr->next; // 移动到下一个
        }
    }

    return newNode;
}

// 打印孩子兄弟表示法的树（前序遍历）
void printCS(CSNode *root, int level)
{
    if (root == NULL)
    {
        return; // 如果结点为空，直接返回
    }

    // 打印当前结点的数据
    for (int i = 0; i < level; i++)
    {
        printf("  "); // 根据层级打印缩进
    }
    printf("%c\n", root->data); // 打印结点数据

    // 递归打印孩子结点
    printCS(root->firstchild, level + 1);

    // 递归打印兄弟结点
    printCS(root->nextsibling, level);
}

int main()
{
    CTree tree;
    int n;
    char values[MAX_SIZE];
    int children[MAX_SIZE][MAX_SIZE];
    int childrenCounts[MAX_SIZE];

    // 读取结点数量
    scanf("%d", &n);

    // 读取层序遍历树所得各个结点的值
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &values[i]);
    }

    // 读取每个结点的孩子结点信息
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &childrenCounts[i]);
        for (int j = 0; j < childrenCounts[i]; j++)
        {
            scanf("%d", &children[i][j]);
        }
    }

    // 初始化孩子链表表示法的树
    tree = initTree(tree, n, values, children, childrenCounts);

    // 转换为孩子兄弟表示法的树
    CSNode *csRoot = convertToCS(tree, tree.r);

    // 打印孩子兄弟表示法的树
    printCS(csRoot, 0);

    return 0;
}