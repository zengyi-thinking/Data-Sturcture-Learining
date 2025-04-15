#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为字符
typedef char elemtype;
// 定义二叉线索树节点结构
typedef struct BiThrNode
{
    int ltag; // 左线索标志，0表示有左孩子，1表示左线索
    struct BiThrNode *lchild;
    elemtype data; // 节点数据
    int rtag; // 右线索标志，0表示有右孩子，1表示右线索
    struct BiThrNode *rchild; // 右孩子指针
} BiThrNodeType, *BiThrTree;

// 创建二叉树
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
        (*bt)->ltag = (*bt)->rtag = 0;
        crt_tree(&(*bt)->lchild);
        crt_tree(&(*bt)->rchild);
    }
}

void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        InThreading(p->lchild, pre);
        if (!p->lchild)
        {
            p->ltag = 1;
            p->lchild = *pre;
        }
        else
        {
            p->ltag = 0;
        }
        if (!(*pre)->rchild)
        {
            (*pre)->rtag = 1;
            (*pre)->rchild = p;
        }
        else
        {
            (*pre)->rtag = 0;
        }
        *pre = p;
        InThreading(p->rchild, pre);
    }
}

int InOrderThr(BiThrTree *head, BiThrTree T)
{
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType));
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head;
    BiThrTree pre = *head;
    if (!T)
    {
        (*head)->lchild = *head;
    }
    else
    {
        (*head)->lchild = T;
        InThreading(T, &pre);
        pre->rchild = *head;
        pre->rtag = 1;
        (*head)->rchild = pre;
    }
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
        printf("%c %d %d\n", p->data, p->ltag, p->rtag);
        p = InPostNode(p);
    }
}

BiThrTree Search(BiThrTree head, elemtype x)
{
    BiThrTree p = head->lchild;
    while (p->ltag == 0 && p != head)
        p = p->lchild;
    while (p != head && p->data != x)
        p = InPostNode(p);
    if (p == head)
    {
        printf("Not Found the data!\n");
        return NULL;
    }
    else
    {
        return p;
    }
}

void InsertThrRight(BiThrTree s, BiThrTree p)
{
    p->rchild = s->rchild;
    p->rtag = s->rtag;
    p->lchild = s;
    p->ltag = 1; // p的左孩子是前驱线索

    s->rchild = p;
    s->rtag = 0; // s的右孩子是p

    if (p->rtag == 0)
    { // 如果p有右孩子
        BiThrTree temp = p->rchild;
        while (temp->ltag == 0)
            temp = temp->lchild;
        temp->lchild = p; // 更新p的右子树的最左节点的前驱
    }
}

int main()
{
    BiThrTree head, T;
    crt_tree(&T);
    InOrderThr(&head, T);

    elemtype p_value, s_value;
    scanf(" %c", &p_value);
    BiThrTree pNode = (BiThrTree)malloc(sizeof(BiThrNodeType));
    pNode->data = p_value;
    pNode->lchild = pNode->rchild = NULL;
    pNode->ltag = pNode->rtag = 0;

    scanf(" %c", &s_value);
    BiThrTree sNode = Search(head, s_value);

    InsertThrRight(sNode, pNode);
    ThIoOrder(head);

    return 0;
}