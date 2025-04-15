#include <stdio.h>
#include <stdlib.h>

// ����Ԫ������Ϊ�ַ�
typedef char elemtype;
// ��������������ڵ�ṹ
typedef struct BiThrNode {
    int ltag; // ��������־��0��ʾ�����ӣ�1��ʾ������
    struct BiThrNode *lchild; // ����ָ��
    elemtype data;
    int rtag; // ��������־��0��ʾ���Һ��ӣ�1��ʾ������
    struct BiThrNode *rchild; // �Һ���ָ��
} BiThrNodeType, *BiThrTree;

// ����������
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
    if (p == head->lchild) return NULL; // ���ڵ�û�к���ǰ��

    // ���1��p���丸�ڵ���Һ���
    if (p->rtag == 1 && p->rchild != head) {
        return p->rchild;
    }

    // ���2��p���丸�ڵ������
    if (p->ltag == 1 && p->lchild != head) {
        BiThrTree parent = p->lchild;
        if (parent->rtag == 0) {
            // ���ڵ����Һ��ӣ�����ǰ����������������ڵ�
            BiThrTree q = parent->rchild;
            while (q->ltag == 0) {
                q = q->lchild;
            }
            return q;
        } else {
            return parent;
        }
    }

    // ��������������������
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
    if (head->lchild == head) return; // ����

    // ����ջ���ڷǵݹ�������
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