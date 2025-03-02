#include "Data.h"

typedef int E;

struct ListNode
{
    E element;             // 数据域
    struct ListNode *next; // 指针域
};

typedef struct ListNode *Node; // 定义一个指向结构体ListNode的指针类型

void InitList(Node node)
{
    node->next = NULL; // 将头结点的指针域置为空,表示链表为空,头结点的数据域不存放数据，表明头结点地址就是链表地址
}

void Insert(Node node, int index, E element)
{
    // 合法性检查
    if (index < 1)
    {
        return 0;
    }
    while (--index)
    {
        node = node->next; // 找到要插入位置的前一个结点
        if (node == NULL)
        {
            return 0; // 插入位置不合法
        }
    }
    Node newNode = (Node)malloc(sizeof(struct ListNode)); // 为新结点分配内存空间
    if (newNode == NULL)
    {
        return 0; // 分配失败
    }

    newNode->element = element; // 为新结点赋值
    newNode->next = node->next; // 新结点的next指向原来结点的next
    node->next = newNode;       // 原来结点的next指向新结点
    return 1;                   // 插入成功
}

_Bool DeleteList(Node node, int index)
{
    // 合法性检查
    if (index < 1)
    {
        return 0; // 删除位置不合法
    }
    while (--index)
    {
        node = node->next; // 找到要删除位置的前一个结点
        if (node == NULL)
        {
            return 0; // 删除位置不合法
        }
    }
    Node temp = node->next;  // 临时指针指向要删除的结点
    node->next = temp->next; // 原来结点的next指向原来结点的next的next
    free(temp);              // 释放要删除的结点
    return 1;                // 删除成功
}

E *getList(Node node, int index)
{
    // 合法性检查
    if (index < 1)
    {
        return NULL; // 删除位置不合法
    }
    while (--index)
    {
        node = node->next; // 找到要删除位置的前一个结点
        if (node == NULL)
        {
            return NULL; // 删除位置不合法
        }
    }
    return &(node->element); // 返回要查找的结点的数据域的地址
}

int findList(Node node, E element)
{
    node = node->next; // 跳过头结点
    int index = 1;
    while (node != NULL)
    {
        if (node->element == element)
        {
            return index; // 返回元素位置
        }
        node = node->next;
        index++;
    }
}

int sizeList(Node node)
{
    int size = -1; // 头结点不存放数据，所以size从-1开始
    while (node != NULL)
    {
        node = node->next; // 指向下一个结点
        size++;            // 遍历链表，统计链表大小
    }
    return size;
}

int main()
{
    Node head = (Node)malloc(sizeof(struct ListNode)); // 为头结点分配内存空间
    if (head == NULL)
    {
        return 0; // 分配失败
    }
    InitList(head);                            // 初始化链表
    Insert(head, 1, 1);                        // 插入元素
    Insert(head, 2, 2);                        // 插入元素
    Insert(head, 3, 3);                        // 插入元素
    Insert(head, 4, 4);                        // 插入元素
    Insert(head, 5, 5);                        // 插入元素
    printf("size:%d\n", sizeList(head));       // 输出链表大小
    printf("element:%d\n", *getList(head, 3)); // 输出指定位置的元素
    printf("index:%d\n", findList(head, 4));   // 输出元素位置
    DeleteList(head, 3);                       // 删除元素
    printf("size:%d\n", sizeList(head));       // 输出链表大小
    printf("element:%d\n", *getList(head, 3)); // 输出指定位置的元素
    printf("index:%d\n", findList(head, 4));   // 输出元素位置
    return 0;
}
