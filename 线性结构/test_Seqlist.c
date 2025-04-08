#include "stdio.h"
#include "stdlib.h"

typedef struct Member
{
    char memberName[100];
    int id;
    int studyCount;
} Member;

typedef struct MemberList
{
    Member member;
    struct MemberList *next;
} MemberList;

typedef struct studyGroup
{
    char groupName[100];
    MemberList *memberList;
} studyGroup;

void InitRroup(studyGroup *group)
{
    // 原代码：group = (studyGroup*)malloc(sizeof(studyGroup));
    // 修改原因：group 已经在 main 函数中分配了内存，这里不需要再次分配
    // group = (studyGroup*)malloc(sizeof(studyGroup));

    printf("please input groupName :");
    scanf("%s", group->groupName);

    // 创建头结点
    group->memberList = (MemberList *)malloc(sizeof(MemberList));
    group->memberList->next = NULL;

    MemberList *tail = group->memberList;
    Member members[4];
    for (int i = 0; i < 4; i++)
    {
        printf("please input member %d info:\n", i);
        printf("memberName:");
        scanf("%s", members[i].memberName); // 不需要取地址
        printf("  id:");
        scanf("%d", &members[i].id); // 需要取地址
        printf("  studyCount:");
        scanf("%d", &members[i].studyCount); // 需要取地址
        MemberList *newNode = (MemberList *)malloc(sizeof(MemberList));
        newNode->member = members[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
}

// 原代码：void PrintGroup(studyGroup group)
// 修改原因：传入的是 studyGroup 的副本，修改不会影响原始对象，应传入指针
void PrintGroup(studyGroup *group)
{
    printf("%s\n", group->groupName);
    MemberList *current = group->memberList->next; // 从头结点的下一个节点开始遍历
    for (int i = 1; current != NULL; i++)
    {
        printf("Member %d Info: memberName:%s, id:%d, studyCount:%d\n", i,
               current->member.memberName, current->member.id, current->member.studyCount);
        current = current->next;
    }
}

// 原代码：void find_more_N_member(studyGroup group, int N)
// 修改原因：传入的是 studyGroup 的副本，修改不会影响原始对象，应传入指针
void find_more_N_member(studyGroup *group, int N)
{
    MemberList *current = group->memberList->next; // 从头结点的下一个节点开始遍历
    for (int i = 1; current != NULL; i++)
    {
        if (current->member.studyCount > N)
        {
            printf("The studyCount more than N NumberInfo: memberName:%s, id:%d, studyCount:%d\n",
                   current->member.memberName, current->member.id, current->member.studyCount);
        }
        current = current->next;
    }
}

void change_studeyCount_by_id(studyGroup *group, int id, int studyCount)
{
    MemberList *current = group->memberList->next; // 从头结点的下一个节点开始遍历
    for (int i = 1; current != NULL; i++)
    {
        if (current->member.id == id)
        {
            current->member.studyCount = studyCount;
            printf("studyCount have changed\n");
            return;
        }
        current = current->next;
    }
    printf("Member with id %d not found\n", id);
}

void delete_member_by_id(studyGroup *group, int id)
{
    MemberList *p = group->memberList;
    MemberList *q = group->memberList->next;
    while (q != NULL)
    {
        if (q->member.id == id)
        {
            p->next = q->next;
            free(q);
            printf("delete success\n");
            return;
        }
        p = q;
        q = q->next;
    }
    printf("delete fail\n");
}

void insert_member_to_end(studyGroup *group)
{
    Member member;
    printf("please input member info:\n");
    printf("memberName:");
    scanf("%s", member.memberName); // 不需要取地址
    printf("  id:");
    scanf("%d", &member.id); // 需要取地址
    printf("  studyCount:");
    scanf("%d", &member.studyCount); // 需要取地址
    MemberList *newNode = (MemberList *)malloc(sizeof(MemberList));
    newNode->member = member;
    newNode->next = NULL;
    MemberList *tail = group->memberList;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = newNode;
    printf("insert success\n");
}

int main()
{
    // 原代码：studyGroup group;
    // 修改原因：需要分配内存给 studyGroup 结构体
    studyGroup *group = (studyGroup *)malloc(sizeof(studyGroup));
    if (group == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    InitRroup(group);
    PrintGroup(group);
    find_more_N_member(group, 10);
    change_studeyCount_by_id(group, 1, 20);
    delete_member_by_id(group, 1);
    insert_member_to_end(group);
    PrintGroup(group);

    // 释放内存
    MemberList *current = group->memberList->next;
    while (current != NULL)
    {
        MemberList *temp = current;
        current = current->next;
        free(temp);
    }
    free(group->memberList);
    free(group);

    return 0;
}