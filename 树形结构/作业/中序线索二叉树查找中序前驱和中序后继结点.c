#include <stdio.h>
#include <stdlib.h>

// ����Ԫ������Ϊ�ַ�
typedef char elemtype;
// ��������������ڵ�ṹ
typedef struct BiThrNode
{
    int ltag; // ��������־��0��ʾ�����ӣ�1��ʾ�����ӵ���ǰ��
    struct BiThrNode *lchild; // ����ָ��
    elemtype data;
    int rtag; // ��������־��0��ʾ���Һ��ӣ�1��ʾ���Һ��ӵ��к��
    struct BiThrNode *rchild; // �Һ���ָ��
} BiThrNodeType, *BiThrTree;

// ����������
void crt_tree(BiThrTree *bt)
{
    char ch;
    scanf("%c", &ch); // ��ȡһ���ַ�
    if (ch == '#')
        *bt = NULL; // �������Ϊ'#'����ʾ�սڵ�
    else
    {
        *bt = (BiThrTree)malloc(sizeof(BiThrNodeType)); // �����ڴ�
        (*bt)->data = ch; // ���ýڵ�����
        (*bt)->ltag = (*bt)->rtag = 0; // ��ʼ��������־
        crt_tree(&(*bt)->lchild); // �ݹ鴴��������
        crt_tree(&(*bt)->rchild); // �ݹ鴴��������
    }
}

// ���������������������
void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        InThreading(p->lchild, pre); // �ݹ�������������
        if (!p->lchild)
        {
            p->ltag = 1; // ������������־
            p->lchild = *pre; // ָ��ǰ���ڵ�
        }
        else
        {
            p->ltag = 0; // �������ӱ�־
        }
        if (!(*pre)->rchild)
        {
            (*pre)->rtag = 1; // ������������־
            (*pre)->rchild = p; // ָ���̽ڵ�
        }
        else
        {
            (*pre)->rtag = 0; // �����Һ��ӱ�־
        }
        *pre = p; // ����ǰ���ڵ�
        InThreading(p->rchild, pre); // �ݹ�������������
    }
}

// ������������������
int InOrderThr(BiThrTree *head, BiThrTree T)
{
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType)); // ����ͷ�ڵ�
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head; // ͷ�ڵ��Һ���ָ���Լ�
    BiThrTree pre = *head;
    if (!T)
    {
        (*head)->lchild = *head; // �����Ϊ�գ�����ָ���Լ�
    }
    else
    {
        (*head)->lchild = T; // ͷ�ڵ�����ָ������
        InThreading(T, &pre);
        pre->rchild = *head; // ���һ���ڵ��Һ���ָ��ͷ�ڵ�
        pre->rtag = 1;
        (*head)->rchild = pre; // ͷ�ڵ��Һ���ָ�����һ���ڵ�
    }
    return 1;
}

// ��ȡ����ǰ���ڵ�
BiThrTree InPreNode(BiThrTree p)
{
    if (p->ltag == 1)
    {
        return p->lchild;
    }
    else
    {
        BiThrTree pre = p->lchild;
        while (pre->rtag == 0)
        {
            pre = pre->rchild;
        }
        return pre;
    }
}

BiThrTree InPostNode(BiThrTree p)
{
    if (p->rtag == 1)
    {
        return p->rchild;
    }
    else
    {
        BiThrTree post = p->rchild;
        while (post->ltag == 0)
        {
            post = post->lchild;
        }
        return post;
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

int main()
{
    BiThrTree head, T;
    crt_tree(&T);
    InOrderThr(&head, T);

    elemtype target;
    scanf(" %c", &target);
    BiThrTree targetNode = Search(head, target);

    BiThrTree preNode = InPreNode(targetNode);
    BiThrTree postNode = InPostNode(targetNode);

    if (preNode != head)
    {
        printf("%c ", preNode->data);
    }
    else
    {
        printf("0 ");
    }
    if (postNode != head)
    {
        printf("%c\n", postNode->data);
    }
    else
    {
        printf("0\n");
    }

    return 0;
}