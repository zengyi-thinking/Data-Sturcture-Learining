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

// ��ʼ������
void InitList(LinkList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// ��ӡ����
void PrintList(LinkList *list)
{
    Student *p = list->head;
    while (p != NULL)// ���������������,�ж�p�Ƿ�Ϊ��,��Ϊ�������
    {
        printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n", p->id, p->name, p->age, p->score);
        p = p->next;
    }
}

// ����Ԫ��
void AddStudent(LinkList *list, Student s)
{
    Student *newNode = (Student *)malloc(sizeof(Student));//���Ӷ�Ҫ������ռ䣬�����ڵ�
    newNode->id = s.id;
    strcpy(newNode->name, s.name);//�ַ�����ֵ
    newNode->age = s.age;
    newNode->score = s.score;
    newNode->next = NULL;
    if (list->tail == NULL)//�ж������Ƿ�Ϊ��
    {
        list->head = newNode;
        list->tail = newNode;//���Ϊ�գ�ͷβ��ָ���½ڵ�
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// ɾ��Ԫ��
int DeleteStudent(LinkList *list, int id)
{
    Student *p = list->head;//ͷָ��
    Student *prev = NULL;//ǰһ���ڵ�
    while (p != NULL && p->id != id)
    {
        prev = p;
        p = p->next;//���������ҵ�Ҫɾ���Ľڵ�,���p��Ϊ����p��id������Ҫɾ����id����pָ����һ���ڵ㣬��pΪ��ʱ��˵���������������û���ҵ�Ҫɾ���Ľڵ�
    }
    if (p == NULL)
    {
        return 0; // δ�ҵ���ѧ��
    }
    if (prev == NULL)//�ж��Ƿ���ͷ�ڵ�
    {
        list->head = p->next;//�����ͷ�ڵ㣬ͷָ��ָ����һ���ڵ�
    }
    else
    {
        prev->next = p->next;//�������ͷ�ڵ㣬ǰһ���ڵ��nextָ����һ���ڵ�
    }
    if (p == list->tail)//�ж��Ƿ���β�ڵ�
    {
        list->tail = prev;//�����β�ڵ㣬βָ��ָ��ǰһ���ڵ�
    }
    free(p);
    return 1;
}

// �޸�Ԫ��
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
    return 0; // δ�ҵ���ѧ��
}

// ����Ԫ��
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
    return NULL; // δ�ҵ���ѧ��
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
        printf("\n1. ����ѧ��\n2. ɾ��ѧ��\n3. �޸�ѧ��\n4. ����ѧ��\n5. ��ӡѧ���б�\n6. �˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("������ѧ��ID: ");
            scanf("%d", &s.id);
            printf("������ѧ������: ");
            scanf("%s", s.name);
            printf("������ѧ������: ");
            scanf("%d", &s.age);
            printf("������ѧ���ɼ�: ");
            scanf("%f", &s.score);
            AddStudent(&list, s);
            break;
        case 2:
            printf("������Ҫɾ����ѧ��ID: ");
            scanf("%d", &id);
            if (DeleteStudent(&list, id))
            {
                printf("ɾ���ɹ�\n");
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 3:
            printf("������Ҫ�޸ĵ�ѧ��ID: ");
            scanf("%d", &s.id);
            printf("�������µ�ѧ������: ");
            scanf("%s", s.name);
            printf("�������µ�ѧ������: ");
            scanf("%d", &s.age);
            printf("�������µ�ѧ���ɼ�: ");
            scanf("%f", &s.score);
            if (UpdateStudent(&list, s))
            {
                printf("�޸ĳɹ�\n");
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 4:
            printf("������Ҫ���ҵ�ѧ��ID: ");
            scanf("%d", &id);
            Student *found = FindStudent(&list, id);
            if (found != NULL)
            {
                printf("�ҵ�ѧ��: ID: %d, Name: %s, Age: %d, Score: %.2f\n", found->id, found->name, found->age, found->score);
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 5:
            PrintList(&list);
            break;
        case 6:
            exit(0);
        default:
            printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}