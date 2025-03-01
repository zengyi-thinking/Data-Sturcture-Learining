#include "Data.h"

typedef int E;

struct ListNode{
    E element; // 数据域
    struct ListNode *next;// 指针域
};

typedef struct ListNode *LinkedList;//定义一个指向结构体ListNode的指针类型
