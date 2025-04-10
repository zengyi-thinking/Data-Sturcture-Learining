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

BiThrTree pre = NULL; // ȫ�ֱ�����ָ��ǰ�ڵ������ǰ��

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
        (*bt)->ltag = (*bt)->rtag = 0; // ��ʼʱ���Һ��Ӿ�Ϊ������
        crt_tree(&(*bt)->lchild);
        crt_tree(&(*bt)->rchild);
    }
}

// �����������ݹ麯��
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); // �ݹ�������������

        // ����ǰ�ڵ�
        if (!p->lchild)
        { // ����Ϊ�գ�����ǰ������
            p->ltag = 1;
            p->lchild = pre;
        }
        if (pre && !pre->rchild)
        { // ǰ���ڵ���Һ���Ϊ�գ����ú������
            pre->rtag = 1;
            pre->rchild = p;
        }
        pre = p; // ����ǰ���ڵ�

        InThreading(p->rchild); // �ݹ�������������
    }
}

int InOrderThr(BiThrTree *head, BiThrTree T)
{
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType)); // ����ͷ���
    (*head)->ltag = 0;                                // ͷ���� lchild ָ����ڵ�
    (*head)->rtag = 1;                                // ͷ���� rchild ��ʼָ���Լ�
    (*head)->rchild = *head;

    if (!T)
    { // ����
        (*head)->lchild = *head;
        return 1;
    }

    (*head)->lchild = T; // ͷ��������ָ����ڵ�
    pre = *head;         // ��ʼ��ǰ���ڵ�Ϊͷ���

    InThreading(T); // ����������������

    // �������һ���ڵ�ĺ������
    pre->rtag = 1;
    pre->rchild = *head;
    (*head)->rchild = pre; // ͷ�����Һ���ָ�����һ���ڵ�

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