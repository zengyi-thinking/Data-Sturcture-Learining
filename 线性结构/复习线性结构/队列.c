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
    int front;
    int rear;
} Queue;

// ��ʼ������
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// �ж϶����Ƿ�Ϊ��
int IsEmpty(Queue *q)
{
    return q->front == q->rear;
}

// �ж϶����Ƿ���
int IsFull(Queue *q)
{
    return (q->rear + 1) % MAXSIZE == q->front;
}

// ���
int Enqueue(Queue *q, Student s)
{
    if (IsFull(q))
    {
        return 0; // ������
    }
    q->data[q->rear] = s;
    q->rear = (q->rear + 1) % MAXSIZE;
    return 1;
}

// ����
int Dequeue(Queue *q, Student *s)
{
    if (IsEmpty(q))
    {
        return 0; // ���п�
    }
    *s = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 1;
}

// ��ȡ��ͷԪ��
int Peek(Queue *q, Student *s)
{
    if (IsEmpty(q))
    {
        return 0; // ���п�
    }
    *s = q->data[q->front];
    return 1;
}

// ��ӡ����
void PrintQueue(Queue *q)
{
    int i = q->front;
    while (i != q->rear)
    {
        printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n", q->data[i].id, q->data[i].name, q->data[i].age, q->data[i].score);
        i = (i + 1) % MAXSIZE;
    }
}

int main()
{
    Queue q;
    InitQueue(&q);

    int choice, id, age;
    float score;
    char name[50];
    Student student;

    while (1)
    {
        printf("\n1. ����ѧ��\n2. ɾ��ѧ��\n3. �鿴��ͷѧ��\n4. ��ӡѧ���б�\n5. �˳�\n");
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
            if (Enqueue(&q, student))
            {
                printf("ѧ����ӳɹ�\n");
            }
            else
            {
                printf("�����������޷����ѧ��\n");
            }
            break;
        case 2:
            if (Dequeue(&q, &student))
            {
                printf("ɾ����ѧ��: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("����Ϊ�գ��޷�ɾ��ѧ��\n");
            }
            break;
        case 3:
            if (Peek(&q, &student))
            {
                printf("��ͷ��ѧ��: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("����Ϊ�գ��޷��鿴��ͷѧ��\n");
            }
            break;
        case 4:
            PrintQueue(&q);
            break;
        case 5:
            exit(0);
        default:
            printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}