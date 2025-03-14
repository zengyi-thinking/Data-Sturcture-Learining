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
    group = (studyGroup*)malloc(sizeof(studyGroup));
    printf("please input groupNmae :");
    scanf("%s", group->groupName);
    group->memberList = (MemberList *)malloc(sizeof(MemberList)); // 让头结点的next指向NULL，表示链表为�?
    group->memberList->next = NULL;
    MemberList *tail = group->memberList;
    Member members[4];
    for (int i = 0; i < 4; i++)
    {
        printf("please input member %d info:\n", i);
        printf("memberName:");
        scanf("%s", members[i].memberName);
        printf("  id:");
        scanf("%d", &members[i].id);
        printf("  studyCount:");
        scanf("%d", &members[i].studyCount);
        MemberList *newNode = (MemberList *)malloc(sizeof(MemberList));
        newNode->member = members[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
}

void PrintGroup(studyGroup group)
{
    printf("%s\n", group.groupName);
    for (int i = 1; group.memberList->next != NULL; i++)
    {
        printf("The first %d NumberInfo: memberName:%s,id:%d,studyCount:%d", i,group.memberList->member.memberName, group.memberList->member.id, group.memberList->member.studyCount);
        group.memberList = group.memberList->next;
    }
}

void find_more_N_member(studyGroup group, int N)
{
    for (int i = 1; group.memberList != NULL; i++)
    {
        if (group.memberList->member.studyCount > N)
        {

            printf("The studyCount more than N NumberInfo: memberName:%s,id:%d,studyCount:%d", group.memberList->member.memberName, group.memberList->member.id, group.memberList->member.studyCount);
        }
        group.memberList = group.memberList->next;
    }
}

void change_studeyCount_by_id(studyGroup *group, int id, int studyCount)
{
    for (int i = 1; group->memberList != NULL; i++)
    {
        if (group->memberList->member.id == id)
        {
            group->memberList->member.studyCount = studyCount;
            printf("studyCount have changed");
        }
        group->memberList = group->memberList->next;
    }
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
            printf("delete success");
            return;
        }
        p = q;
        q = q->next;
    }
    printf("delete fail");
}

void insert_member_to_end(studyGroup *group)
{
    Member member;
    printf("please input member info:\n");
    printf("memberName:");
    scanf("%s", member.memberName);
    printf("  id:");
    scanf("%d", &member.id);
    printf("  studyCount:");
    scanf("%d", &member.studyCount);
    MemberList *newNode = (MemberList *)malloc(sizeof(MemberList));
    newNode->member = member;
    newNode->next = NULL;
    MemberList *tail = group->memberList;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = newNode;
    printf("insert success");
}

int main()
{
    studyGroup group;
    InitRroup(&group);
    PrintGroup(group);
    find_more_N_member(group, 10);
    change_studeyCount_by_id(&group, 1, 20);
    delete_member_by_id(&group, 1);
    insert_member_to_end(&group);
    PrintGroup(group);
    

    return 0;
}
