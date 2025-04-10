#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为字符
typedef char elemtype;
// 定义二叉线索树节点结构
typedef struct BiThrNode
{
    int ltag; // 左线索标志，0表示有左孩子，1表示无左孩子但有前驱
    struct BiThrNode *lchild; // 左孩子指针
    elemtype data;
    int rtag; // 右线索标志，0表示有右孩子，1表示无右孩子但有后继
    struct BiThrNode *rchild; // 右孩子指针
} BiThrNodeType, *BiThrTree;

// 创建二叉树
void crt_tree(BiThrTree *bt)
{
    char ch;
    scanf("%c", &ch); // 读取一个字符
    if (ch == '#')
        *bt = NULL; // 如果输入为'#'，表示空节点
    else
    {
        *bt = (BiThrTree)malloc(sizeof(BiThrNodeType)); // 分配内存
        (*bt)->data = ch; // 设置节点数据
        (*bt)->ltag = (*bt)->rtag = 0; // 初始化线索标志
        crt_tree(&(*bt)->lchild); // 递归创建左子树
        crt_tree(&(*bt)->rchild); // 递归创建右子树
    }
}

// 中序遍历二叉树并线索化
void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        InThreading(p->lchild, pre); // 递归线索化左子树
        if (!p->lchild)
        {
            p->ltag = 1; // 设置左线索标志
            p->lchild = *pre; // 指向前驱节点
        }
        else
        {
            p->ltag = 0; // 设置左孩子标志
        }
        if (!(*pre)->rchild)
        {
            (*pre)->rtag = 1; // 设置右线索标志
            (*pre)->rchild = p; // 指向后继节点
        }
        else
        {
            (*pre)->rtag = 0; // 设置右孩子标志
        }
        *pre = p; // 更新前驱节点
        InThreading(p->rchild, pre); // 递归线索化右子树
    }
}

// 构建中序线索二叉树
int InOrderThr(BiThrTree *head, BiThrTree T)
{
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType)); // 创建头节点
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head; // 头节点右孩子指向自己
    BiThrTree pre = *head;
    if (!T)
    {
        (*head)->lchild = *head; // 如果树为空，左孩子指向自己
    }
    else
    {
        (*head)->lchild = T; // 头节点左孩子指向树根
        InThreading(T, &pre);
        pre->rchild = *head; // 最后一个节点右孩子指向头节点
        pre->rtag = 1;
        (*head)->rchild = pre; // 头节点右孩子指向最后一个节点
    }
    return 1;
}

// 获取中序前驱节点
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