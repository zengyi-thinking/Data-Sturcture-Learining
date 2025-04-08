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

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// 判断队列是否为空
int IsEmpty(Queue *q)
{
    return q->front == q->rear;
}

// 判断队列是否满
int IsFull(Queue *q)
{
    return (q->rear + 1) % MAXSIZE == q->front;
}

// 入队
int Enqueue(Queue *q, Student s)
{
    if (IsFull(q))
    {
        return 0; // 队列满
    }
    q->data[q->rear] = s;
    q->rear = (q->rear + 1) % MAXSIZE;
    return 1;
}

// 出队
int Dequeue(Queue *q, Student *s)
{
    if (IsEmpty(q))
    {
        return 0; // 队列空
    }
    *s = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 1;
}

// 获取队头元素
int Peek(Queue *q, Student *s)
{
    if (IsEmpty(q))
    {
        return 0; // 队列空
    }
    *s = q->data[q->front];
    return 1;
}

// 打印队列
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
        printf("\n1. 增加学生\n2. 删除学生\n3. 查看队头学生\n4. 打印学生列表\n5. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        getchar(); // 清除缓冲区

        switch (choice)
        {
        case 1:
            printf("请输入学生ID: ");
            scanf("%d", &student.id);
            getchar(); // 清除缓冲区
            printf("请输入学生姓名: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0'; // 去掉换行符
            printf("请输入学生年龄: ");
            scanf("%d", &student.age);
            getchar(); // 清除缓冲区
            printf("请输入学生成绩: ");
            scanf("%f", &student.score);
            getchar(); // 清除缓冲区
            if (Enqueue(&q, student))
            {
                printf("学生添加成功\n");
            }
            else
            {
                printf("队列已满，无法添加学生\n");
            }
            break;
        case 2:
            if (Dequeue(&q, &student))
            {
                printf("删除的学生: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("队列为空，无法删除学生\n");
            }
            break;
        case 3:
            if (Peek(&q, &student))
            {
                printf("队头的学生: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("队列为空，无法查看队头学生\n");
            }
            break;
        case 4:
            PrintQueue(&q);
            break;
        case 5:
            exit(0);
        default:
            printf("无效的选择\n");
        }
    }

    return 0;
}