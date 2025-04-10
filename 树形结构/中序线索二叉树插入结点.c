#include <stdio.h>
#include <stdlib.h>

// ����Ԫ������Ϊ�ַ�
typedef char elemtype;
// ��������������ڵ�ṹ
typedef struct BiThrNode
{
    int ltag; // ��������־��0��ʾ�����ӣ�1��ʾ������
    struct BiThrNode *lchild;
    elemtype data; // �ڵ�����
    int rtag; // ��������־��0��ʾ���Һ��ӣ�1��ʾ������
    struct BiThrNode *rchild; // �Һ���ָ��
} BiThrNodeType, *BiThrTree;

// ����������
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
    p->ltag = 1; // p��������ǰ������

    s->rchild = p;
    s->rtag = 0; // s���Һ�����p

    if (p->rtag == 0)
    { // ���p���Һ���
        BiThrTree temp = p->rchild;
        while (temp->ltag == 0)
            temp = temp->lchild;
        temp->lchild = p; // ����p��������������ڵ��ǰ��
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