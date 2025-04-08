//导入必要的库,stdlib.h用于内存操作，string.h用于字符创的拼接
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//定义学生的数据结构
typedef struct Student{
    int id;
    char name[29];
    int age;
    float score;
}Student;

//定义链表的数据结构
typedef struct LinkList{
    Student data;
    struct LinkList *next;//这里要用struct LinkList *next，因为LinkList是一个自定义的数据结构，需要用struct来定义
}LinkList;

//初始化链表,这里只需要将链表的头结点的next指向NULL即可,因为头结点不存储数据
void InitList(LinkList *head){
    head->next = NULL;
}

//打印链表，从头结点的下一个节点开始打印
void PrintList(LinkList *head){
    LinkList *p = head->next;//定义工作指针，从头结点的下一个节点开始打印
    while(p != NULL){
        printf("%s,%d,%d,%f\n",p->data.name,p->data.id,p->data.age,p->data.score);//这里用p->data.name而不是p->name，因为p->data是一个Student类型的数据结构，需要用data来访问其中的数据
        p = p->next;
    }
}

//向链表中插入数据，这里需要将新节点的next指向原来的第一个节点，然后将头结点的next指向新节点,分为头插法和尾插法
int InsertList(LinkList *head,Student s)
{
    LinkList *newNode = (LinkList *)malloc(sizeof(LinkList));//申请新节点的内存
    if(newNode == NULL){
        return 0;
    }
    newNode->data = s;//将新节点的数据赋值为s
    newNode->next = head->next;//将新节点的next指向原来的第一个节点
    head->next = newNode;//将头结点的next指向新节点
    return 1;
    
}

//删除链表中的数据，通过id来删除
int DeleteList(LinkList *head,int id){
    LinkList *p = head->next;//定义工作指针，从头结点的下一个节点开始
    LinkList *pre = head;//定义前驱指针，指向工作指针的前一个节点，初始化时指向头结点
    if (p == NULL)
        return 0; // 如果工作指针为空，说明没有找到要删除的id，返回0
    while(p != NULL){//遍历链表固定格式
        if(p->data.id ==id){
            pre->next = p->next;//将前驱指针的next指向工作指针的next，即将工作指针从链表中删除
            free(p);//释放工作指针的内存
            return 1;//删除成功
        }
        //如果工作指针的id不等于要删除的id，那么前驱指针和工作指针同时后移
        pre = p;    p = p->next;  
    }
    return 0;//如果遍历完链表都没有找到要删除的id，返回0
}

//修改链表中的数据，通过id找到对应的数据，然后修改数据内容
int ModifyList(LinkList *head,int id,Student s){
    LinkList *p = head->next;//定义工作指针，从头结点的下一个节点开始
    while(p != NULL){
        if(p->data.id == id){
            p->data = s;//将工作指针的数据赋值为s
            return 1;//修改成功
        }
        p = p->next;
    }
    return 0;//如果遍历完链表都没有找到要修改的id，返回0
}

int main()
{
    LinkList *head = (LinkList *)malloc(sizeof(LinkList)); // 申请头结点的内存
    InitList(head);                                        // 初始化链表

    int choice, id, age;
    float score;
    char name[29];
    Student s;

    while (1)
    {
        printf("\n1. 增加学生\n2. 删除学生\n3. 修改学生\n4. 查找学生\n5. 打印学生列表\n6. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("请输入学生ID: ");
            scanf("%d", &s.id);
            printf("请输入学生姓名: ");
            scanf("%s", s.name);//注意这里用s.name,而不是&s.name,因为name是一个字符数组，不需要取地址
            printf("请输入学生年龄: ");
            scanf("%d", &s.age);
            printf("请输入学生成绩: ");
            scanf("%f", &s.score);
            InsertList(head, s);
            break;
        case 2:
            printf("请输入要删除的学生ID: ");
            scanf("%d", &id);
            if (DeleteList(head, id))
            {
                printf("删除成功\n");
            }
            else
            {
                printf("未找到该学生\n");
            }
            break;
        case 3:
            printf("请输入要修改的学生ID: ");
            scanf("%d", &s.id);
            printf("请输入新的学生姓名: ");
            scanf("%s", s.name);
            printf("请输入新的学生年龄: ");
            scanf("%d", &s.age);
            printf("请输入新的学生成绩: ");
            scanf("%f", &s.score);
            if (ModifyList(head, s.id, s))
            {
                printf("修改成功\n");
            }
            else
            {
                printf("未找到该学生\n");
            }
            break;
        case 4:
            printf("请输入要查找的学生ID: ");
            scanf("%d", &id);
            LinkList *found = head->next;
            while (found != NULL && found->data.id != id)
            {
                found = found->next;
            }
            if (found != NULL)
            {
                printf("找到学生: %s, %d, %d, %f\n", found->data.name, found->data.id, found->data.age, found->data.score);
            }
            else
            {
                printf("未找到该学生\n");
            }
            break;
        case 5:
            PrintList(head);
            break;
        case 6:
            exit(0);
        default:
            printf("无效的选择\n");
        }
    }

    return 0;
}
