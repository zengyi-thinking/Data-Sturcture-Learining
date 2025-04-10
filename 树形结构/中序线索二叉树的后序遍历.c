#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为字符
typedef char elemtype;
// 定义二叉线索树节点结构
typedef struct BiThrNode {
    int ltag; // 左线索标志，0表示有左孩子，1表示左线索
    struct BiThrNode *lchild; // 左孩子指针
    elemtype data;
    int rtag; // 右线索标志，0表示有右孩子，1表示右线索
    struct BiThrNode *rchild; // 右孩子指针
} BiThrNodeType, *BiThrTree;

// 创建二叉树
void crt_tree(BiThrTree *bt) {
    char ch;
    scanf("%c", &ch);
    if (ch == '#') *bt = NULL;
    else {
        *bt = (BiThrTree)malloc(sizeof(BiThrNodeType));
        (*bt)->data = ch;
        (*bt)->ltag = (*bt)->rtag = 0;
        crt_tree(&(*bt)->lchild);
        crt_tree(&(*bt)->rchild);
    }
}

void InThreading(BiThrTree p, BiThrTree *pre) {
    if (p) {
        InThreading(p->lchild, pre);
        if (!p->lchild) {
            p->ltag = 1;
            p->lchild = *pre;
        } else {
            p->ltag = 0;
        }
        if (!(*pre)->rchild) {
            (*pre)->rtag = 1;
            (*pre)->rchild = p;
        } else {
            (*pre)->rtag = 0;
        }
        *pre = p;
        InThreading(p->rchild, pre);
    }
}

int InOrderThr(BiThrTree *head, BiThrTree T) {
    *head = (BiThrTree)malloc(sizeof(BiThrNodeType));
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head;
    BiThrTree pre = *head;
    if (!T) {
        (*head)->lchild = *head;
    } else {
        (*head)->lchild = T;
        InThreading(T, &pre);
        pre->rchild = *head;
        pre->rtag = 1;
        (*head)->rchild = pre;
    }
    return 1;
}

BiThrTree IPostPreNode(BiThrTree head, BiThrTree p) {
    if (p == head->lchild) return NULL; // 根节点没有后序前驱

    // 情况1：p是其父节点的右孩子
    if (p->rtag == 1 && p->rchild != head) {
        return p->rchild;
    }

    // 情况2：p是其父节点的左孩子
    if (p->ltag == 1 && p->lchild != head) {
        BiThrTree parent = p->lchild;
        if (parent->rtag == 0) {
            // 父节点有右孩子，后序前驱是右子树的最左节点
            BiThrTree q = parent->rchild;
            while (q->ltag == 0) {
                q = q->lchild;
            }
            return q;
        } else {
            return parent;
        }
    }

    // 其他情况（非线索情况）
    BiThrTree parent = p->lchild;
    while (parent != NULL && parent->rchild != p) {
        parent = parent->rchild;
    }
    if (parent == NULL) return NULL;

    if (parent->rtag == 0) {
        BiThrTree q = parent->rchild;
        while (q->ltag == 0) {
            q = q->lchild;
        }
        return q;
    } else {
        return parent;
    }
}

void ThpostIoOrder(BiThrTree head) {
    if (head->lchild == head) return; // 空树

    // 创建栈用于非递归后序遍历
    BiThrTree stack[100];
    int top = -1;
    BiThrTree p = head->lchild;
    BiThrTree last_visited = NULL;

    while (p != head || top != -1) {
        if (p != head) {
            stack[++top] = p;
            p = (p->ltag == 0) ? p->lchild : head;
        } else {
            BiThrTree peek = stack[top];
            if (peek->rtag == 0 && peek->rchild != last_visited) {
                p = peek->rchild;
            } else {
                printf("%c", peek->data);
                last_visited = stack[top--];
            }
        }
    }
    printf("\n");
}

int main() {
    BiThrTree head, T;
    crt_tree(&T);
    InOrderThr(&head, T);
    ThpostIoOrder(head);
    return 0;
}