#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int E;

typedef struct
{
   E data[MAXSIZE];
   int top1;//top1代表
   int top2;
} SharedStack;

// 初始化共享栈
void initStack(SharedStack *s)
{
   s->top1 = -1;
   s->top2 = MAXSIZE;
}

// 判断栈是否为空
int isEmpty1(SharedStack *s)
{
   return s->top1 == -1;
}

int isEmpty2(SharedStack *s)
{
   return s->top2 == MAXSIZE;
}

// 判断栈是否满
int isFull(SharedStack *s)
{
   return s->top1 + 1 == s->top2;
}

// 入栈操作
int push1(SharedStack *s, E element)
{
   if (isFull(s))
   {
      printf("栈已满，无法入栈\n");
      return 0;
   }
   s->data[++s->top1] = element;
   return 1;
}

int push2(SharedStack *s, E element)
{
   if (isFull(s))
   {
      printf("栈已满，无法入栈\n");
      return 0;
   }
   s->data[--s->top2] = element;
   return 1;
}

// 出栈操作
int pop1(SharedStack *s, E *element)
{
   if (isEmpty1(s))
   {
      printf("栈1为空，无法出栈\n");
      return 0;
   }
   *element = s->data[s->top1--];
   return 1;
}

int pop2(SharedStack *s, E *element)
{
   if (isEmpty2(s))
   {
      printf("栈2为空，无法出栈\n");
      return 0;
   }
   *element = s->data[s->top2++];
   return 1;
}

int main()
{
   SharedStack stack;
   initStack(&stack);

   push1(&stack, 10);
   push1(&stack, 20);
   push2(&stack, 30);
   push2(&stack, 40);

   E element;
   pop1(&stack, &element);
   printf("从栈1弹出的元素: %d\n", element);
   pop2(&stack, &element);
   printf("从栈2弹出的元素: %d\n", element);

   return 0;
}
