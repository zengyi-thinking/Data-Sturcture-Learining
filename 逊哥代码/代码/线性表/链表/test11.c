#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
	ElemType data;
	struct node *next;
}Node;

//初化链表
Node* initList()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}

//初始化节点（带节点数据域参数）
Node* initListWithElem(ElemType e)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = e;
	node->next = NULL;
	return node;
}

//头插法
int insertHead(Node* L, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
}

//遍历
void listNode(Node* L)
{
	Node *p = L->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//获取尾部结点
Node*  get_tail(Node  *L)
{
	Node *p = L;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//尾插法
Node* insertTail(Node *tail, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	tail->next = p;
	p->next = NULL;
	return p;
}

//尾插法（节点）
Node* insertTailWithNode(Node *tail, Node *node)
{
	tail->next = node;
	node->next = NULL;
	return node;
}

//指定位置插入
int insertNode(Node *L, int pos, ElemType e)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}
	

	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}

//删除节点
int deleteNode(Node *L, int pos)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}

	if(p->next == NULL)
	{
		printf("要删除的位置错误\n");
		return 0;
	}

	Node *q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

//获取链表长度
int listLength(Node *L)
{
	Node *p = L;
	int len = 0;
	while(p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

//释放链表
void freeList(Node *L)
{
	Node *p = L->next;
	Node *q;

	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

//查找倒数第k个节点
int findNodeFS(Node *L, int k)
{
	Node *fast = L->next;
	Node *slow = L->next;

	for (int i = 0; i < k; i++)
	{
		fast = fast->next;
	}

	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}

	printf("倒数第%d个节点值为：%d\n", k, slow->data);
	return 1;
}
//查找两个节点共同后缀的起始位置
Node* findIntersectionNode(Node *headA, Node *headB)
{
	if(headA == NULL || headB == NULL)
	{
		return NULL;
	}

	Node *p = headA;
	int lenA = 0;
	int lenB = 0;
	while(p != NULL)
	{
		p = p->next;
		lenA++;
	}

	p = headB;
	while(p != NULL)
	{
		p = p->next;
		lenB++;
	}

	Node *m;
	Node *n;
	int step;
	if (lenA > lenB)
	{
		step = lenA - lenB;
		m = headA;
		n = headB;
	}
	else
	{
		step = lenB - lenA;
		m = headB;
		n = headA;
	}

	for (int i = 0; i < step; i++)
	{
		m = m->next;
	}

	while(m != n)
	{
		m = m->next;
		n = n->next;
	}
	return m;
}

//删除绝对值相同的节点
void removeNode(Node *L, int n)
{
	Node *p = L;
	int index;//作为数组下标使用
	int *q = (int*)malloc(sizeof(int)*(n+1));

	//遍历数组，初始化值为0
	for (int i = 0; i < n+1; i++)
	{
		*(q + i) = 0;
	}

	while(p->next != NULL)
	{
		//abs获取绝对值
		index = abs(p->next->data);
		if(*(q+index) == 0)
		{
			*(q + index) = 1;
			p = p->next;
		}
		else
		{
			Node *temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		
	}
	free(q);
}

int main(int argc, char const *argv[])
{
	Node *list = initList();
	
	Node *tail = get_tail(list);
	
	tail = insertTail(tail, 21);
	tail = insertTail(tail, -15);
	tail = insertTail(tail, -15);
	tail = insertTail(tail, 7);
	tail = insertTail(tail, 15);
	listNode(list);
	removeNode(list,21);

	listNode(list);
	

	
	return 0;
}