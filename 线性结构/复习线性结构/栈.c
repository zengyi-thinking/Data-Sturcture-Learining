#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct
{
    int id;
    char name[50];
    int age;
    float score;
} Student;

typedef struct
{
    Student data[MAXSIZE];
    int top;
} Stack;

// ��ʼ��ջ
void InitStack(Stack *s)
{
    s->top = -1;//��ʼ��ջ��ָ��,ջ��ָ��Ϊ-1����ջΪ��,Ϊ�β���0�أ���Ϊջ��ָ��ָ�����ջ��Ԫ�ص�λ�ã�������ջ��Ԫ�ص���һ��λ��
}

// �ж�ջ�Ƿ�Ϊ��
int IsEmpty(Stack *s)
{
    return s->top == -1;//ջ��ָ��Ϊ-1����ջΪ��
}

// �ж�ջ�Ƿ���
int IsFull(Stack *s)
{
    return s->top == MAXSIZE - 1;//ջ��ָ��ΪMAXSIZE-1����ջ����Ϊ�β���MAXSIZE�أ���Ϊջ��ָ��ָ�����ջ��Ԫ�ص�λ�ã�������ջ��Ԫ�ص���һ��λ��
}

// ��ջ
int Push(Stack *s, Student student)
{
    if (IsFull(s))
    {
        return 0; // ջ��
    }
    s->data[++(s->top)] = student;
    return 1;
}

// ��ջ
int Pop(Stack *s, Student *student)
{
    if (IsEmpty(s))//�ж�ջ�Ƿ�Ϊ�ջ�������
    {
        return 0; // ջ��
    }
    *student = s->data[(s->top)--];
    return 1;
}

// ��ȡջ��Ԫ��
int Peek(Stack *s, Student *student)
{
    if (IsEmpty(s))
    {
        return 0; // ջ��
    }
    *student = s->data[s->top];
    return 1;
}

// ��ӡջ
void PrintStack(Stack *s)
{
    for (int i = s->top; i >= 0; i--)
    {
        printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n", s->data[i].id, s->data[i].name, s->data[i].age, s->data[i].score);
    }
}

int main()
{
    Stack s;
    InitStack(&s);

    int choice, id, age;
    float score;
    char name[50];
    Student student;

    while (1)
    {
        printf("\n1. ����ѧ��\n2. ɾ��ѧ��\n3. �鿴ջ��ѧ��\n4. ��ӡѧ���б�\n5. �˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);
        getchar(); // ���������

        switch (choice)
        {
        case 1:
            printf("������ѧ��ID: ");
            scanf("%d", &student.id);
            getchar(); // ���������
            printf("������ѧ������: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0'; // ȥ�����з�
            printf("������ѧ������: ");
            scanf("%d", &student.age);
            getchar(); // ���������
            printf("������ѧ���ɼ�: ");
            scanf("%f", &student.score);
            getchar(); // ���������
            if (Push(&s, student))
            {
                printf("ѧ����ӳɹ�\n");
            }
            else
            {
                printf("ջ�������޷����ѧ��\n");
            }
            break;
        case 2:
            if (Pop(&s, &student))
            {
                printf("ɾ����ѧ��: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("ջΪ�գ��޷�ɾ��ѧ��\n");
            }
            break;
        case 3:
            if (Peek(&s, &student))
            {
                printf("ջ����ѧ��: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("ջΪ�գ��޷��鿴ջ��ѧ��\n");
            }
            break;
        case 4:
            PrintStack(&s);
            break;
        case 5:
            exit(0);
        default:
            printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}