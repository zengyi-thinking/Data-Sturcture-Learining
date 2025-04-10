#include <stdio.h>
#include <stdlib.h>

typedef char elemtype;
typedef struct BiThrNode
{
    int ltag;
    struct BiThrNode *lchild;
    elemtype data;
    int rtag;
    struct BiThrNode *rchild;
} BiThrNodeType, *BiThrTree;

BiThrTree pre = NULL; // 全局变量，指向当前节点的中序前驱

void crt_tree(BiThrTree *bt)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
        *bt = NULL;
    else
    {
        *bt = (BiThrTree)malloc(sizeof(BiThrNodeType));
        (*bt)->data = ch;
        (*bt)->ltag = (*bt)->rtag = 0; // 初始时左右孩子均为非线索
        crt_tree(&(*bt)->lchild);
        crt_tree(&(*bt)->rchild);
    }
}

// 中序线索化递归函数
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); // 递归左子树线索化

        // 处理当前节点
        if (!p->lchild)
        { // 左孩子为空，设置前驱线索
            p->ltag = 1;
            p->lchild = pre;
        }
        if (pre && !pre->rchild)
        { // 前驱节点的右孩子为空，设置后继线索
            pre->rtag = 1;
            pre->rchild = p;
        }
        pre = p; // 更新前驱节点

        InThreading(p->rchild); // 递归右子树线索化
    }
}

int InOrderThr(BiThrTree *head, BiThrTree T)
{
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType)); // 创建头结点
    (*head)->ltag = 0;                                // 头结点的 lchild 指向根节点
    (*head)->rtag = 1;                                // 头结点的 rchild 初始指向自己
    (*head)->rchild = *head;

    if (!T)
    { // 空树
        (*head)->lchild = *head;
        return 1;
    }

    (*head)->lchild = T; // 头结点的左孩子指向根节点
    pre = *head;         // 初始化前驱节点为头结点

    InThreading(T); // 中序线索化二叉树

    // 处理最后一个节点的后继线索
    pre->rtag = 1;
    pre->rchild = *head;
    (*head)->rchild = pre; // 头结点的右孩子指向最后一个节点

    return 1;
}

BiThrTree InPostNode(BiThrTree p)
{
    BiThrTree post = p->rchild;
    if (p->rtag == 1)
        return post;
    while (post->ltag == 0)
        post = post->lchild;
    return post;
}

void ThIoOrder(BiThrTree head)
{
    BiThrTree p = head->lchild;
    if (p == head)
        return;

    while (p->ltag == 0)
        p = p->lchild;
    while (p != head)
    {
        printf("%d%d ", p->ltag, p->rtag);
        p = InPostNode(p);
    }
}

int main()
{
    BiThrTree head, T;
    crt_tree(&T);
    InOrderThr(&head, T);
    ThIoOrder(head);
    return 0;
}