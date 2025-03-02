#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Data.h"

typedef int E;

struct ListNode {
    E element;
    struct ListNode *next;
    struct ListNode *prev;
};

typedef struct ListNode *Node;

void initNode(Node node) {
    node->next = node->prev = NULL;
}

_Bool insertList(Node head, E element, int index) {
    // 插入合法性检验
    if (index < 1)
        return 0;
    // 指针移动到要插入的节点的前面一个位置
    while (index--) {
        head = head->next;
        if (head == NULL)
            return 0;
    }
    // 创建新节点
    Node node = malloc(sizeof(struct ListNode));
    if (node == NULL)
        return 0;

    // 如果后面有节点
    if (head->next == NULL) {
        node->next = NULL;
    } else {
        // 后驱节点
        head->next->prev = node; // 后驱节点的钱指针指向新节点node
        node->next = head->next; //
    }
    // 前驱结点
    head->next = node;
    node->prev = head;
    node->element = element;
    return 1;
}

_Bool deleteList(Node node, int index) {
    // 指针移动到要删除的节点的前面一个位置
    while (index--) {
        node = node->next;
        if (node == NULL)
            return 0;
    }
    // 删除节点
    node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    free(node);
    return 1;
}

int findNode(Node node, E elements) {
    int index = 0;
    while (node->next != NULL) {
        node = node->next;
        index++;
        if (node->element == elements)
            return index;
    }
    return -1;
}

E *getList(Node node, int index) {
    while (index--) {
        node = node->next;
        if (node == NULL)
            return NULL;
    }
    return &node->element;
}

int lengthList(Node node) {
    int length = 0;
    while (node->next != NULL) {
        node = node->next;
        length++;
    }
    return length;
}

void print_Node(Node node) {
    while (node->next != NULL) {
        node = node->next;
        printf("%d ", node->element);
    }
    printf("\n");
}

int main() {
    Node head = (Node)malloc(sizeof(struct ListNode));
    initNode(head);

    // 测试插入
    insertList(head, 10, 1);
    insertList(head, 20, 2);
    insertList(head, 15, 2);
    printf("link content: ");
    print_Node(head);

    // 测试查找
    int index = findNode(head, 15);
    printf("element of 15 index: %d\n", index);

    // 测试删除
    deleteList(head, 2);
    printf("after deleted 15, link content: ");
    print_Node(head);

    free(head);
    return 0;
}