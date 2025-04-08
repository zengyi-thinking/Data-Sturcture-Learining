#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int id;
    char name[50];
    int age;
    float score;
    struct Student *next;
} Student;

typedef struct
{
    Student *head;
    Student *tail;
} LinkList;

// 初始化链表
void InitList(LinkList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// 打印链表
void PrintList(LinkList *list)
{
    Student *p = list->head;
    while (p != NULL)// 遍历链表基本操作,判断p是否为空,不为空则输出
    {
        printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n", p->id, p->name, p->age, p->score);
        p = p->next;
    }
}

// 增加元素
void AddStudent(LinkList *list, Student s)
{
    Student *newNode = (Student *)malloc(sizeof(Student));//增加都要先申请空间，新增节点
    newNode->id = s.id;
    strcpy(newNode->name, s.name);//字符串赋值
    newNode->age = s.age;
    newNode->score = s.score;
    newNode->next = NULL;
    if (list->tail == NULL)//判断链表是否为空
    {
        list->head = newNode;
        list->tail = newNode;//如果为空，头尾都指向新节点
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// 删除元素
int DeleteStudent(LinkList *list, int id)
{
    Student *p = list->head;//头指针
    Student *prev = NULL;//前一个节点
    while (p != NULL && p->id != id)
    {
        prev = p;
        p = p->next;//遍历链表，找到要删除的节点,如果p不为空且p的id不等于要删除的id，则p指向下一个节点，当p为空时，说明链表遍历结束，没有找到要删除的节点
    }
    if (p == NULL)
    {
        return 0; // 未找到该学生
    }
    if (prev == NULL)//判断是否是头节点
    {
        list->head = p->next;//如果是头节点，头指针指向下一个节点
    }
    else
    {
        prev->next = p->next;//如果不是头节点，前一个节点的next指向下一个节点
    }
    if (p == list->tail)//判断是否是尾节点
    {
        list->tail = prev;//如果是尾节点，尾指针指向前一个节点
    }
    free(p);
    return 1;
}

// 修改元素
int UpdateStudent(LinkList *list, Student s)
{
    Student *p = list->head;
    while (p != NULL)
    {
        if (p->id == s.id)
        {
            strcpy(p->name, s.name);
            p->age = s.age;
            p->score = s.score;
            return 1;
        }
        p = p->next;
    }
    return 0; // 未找到该学生
}

// 查找元素
Student *FindStudent(LinkList *list, int id)
{
    Student *p = list->head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            return p;
        }
        p = p->next;
    }
    return NULL; // 未找到该学生
}

int main()
{
    LinkList list;
    InitList(&list);

    int choice, id, age;
    float score;
    char name[50];
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
            scanf("%s", s.name);
            printf("请输入学生年龄: ");
            scanf("%d", &s.age);
            printf("请输入学生成绩: ");
            scanf("%f", &s.score);
            AddStudent(&list, s);
            break;
        case 2:
            printf("请输入要删除的学生ID: ");
            scanf("%d", &id);
            if (DeleteStudent(&list, id))
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
            if (UpdateStudent(&list, s))
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
            Student *found = FindStudent(&list, id);
            if (found != NULL)
            {
                printf("找到学生: ID: %d, Name: %s, Age: %d, Score: %.2f\n", found->id, found->name, found->age, found->score);
            }
            else
            {
                printf("未找到该学生\n");
            }
            break;
        case 5:
            PrintList(&list);
            break;
        case 6:
            exit(0);
        default:
            printf("无效的选择\n");
        }
    }

    return 0;
}