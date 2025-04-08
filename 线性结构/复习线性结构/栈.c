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

// 初始化栈
void InitStack(Stack *s)
{
    s->top = -1;//初始化栈顶指针,栈顶指针为-1代表栈为空,为何不是0呢？因为栈顶指针指向的是栈顶元素的位置，而不是栈顶元素的下一个位置
}

// 判断栈是否为空
int IsEmpty(Stack *s)
{
    return s->top == -1;//栈顶指针为-1代表栈为空
}

// 判断栈是否满
int IsFull(Stack *s)
{
    return s->top == MAXSIZE - 1;//栈顶指针为MAXSIZE-1代表栈满，为何不是MAXSIZE呢？因为栈顶指针指向的是栈顶元素的位置，而不是栈顶元素的下一个位置
}

// 入栈
int Push(Stack *s, Student student)
{
    if (IsFull(s))
    {
        return 0; // 栈满
    }
    s->data[++(s->top)] = student;
    return 1;
}

// 出栈
int Pop(Stack *s, Student *student)
{
    if (IsEmpty(s))//判断栈是否为空基本操作
    {
        return 0; // 栈空
    }
    *student = s->data[(s->top)--];
    return 1;
}

// 获取栈顶元素
int Peek(Stack *s, Student *student)
{
    if (IsEmpty(s))
    {
        return 0; // 栈空
    }
    *student = s->data[s->top];
    return 1;
}

// 打印栈
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
        printf("\n1. 增加学生\n2. 删除学生\n3. 查看栈顶学生\n4. 打印学生列表\n5. 退出\n");
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
            if (Push(&s, student))
            {
                printf("学生添加成功\n");
            }
            else
            {
                printf("栈已满，无法添加学生\n");
            }
            break;
        case 2:
            if (Pop(&s, &student))
            {
                printf("删除的学生: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("栈为空，无法删除学生\n");
            }
            break;
        case 3:
            if (Peek(&s, &student))
            {
                printf("栈顶的学生: ID: %d, Name: %s, Age: %d, Score: %.2f\n", student.id, student.name, student.age, student.score);
            }
            else
            {
                printf("栈为空，无法查看栈顶学生\n");
            }
            break;
        case 4:
            PrintStack(&s);
            break;
        case 5:
            exit(0);
        default:
            printf("无效的选择\n");
        }
    }

    return 0;
}