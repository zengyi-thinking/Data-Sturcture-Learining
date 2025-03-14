#include "Data.h"

typedef int E;
typedef struct {
    E* array; // 指向动态分配的数组
    int top;// 栈顶指针
    int capacity;// 栈的容量
} Stack ;

typedef Stack * ArrayStack;

_Bool initStack(ArrayStack stack, int capacity) {
    stack->array = malloc(sizeof(E) * capacity);// 动态分配数组
    if (stack->array == NULL) {
        return 0;
    }
    stack->capacity = capacity;// 栈的容量
    stack->top = -1;// 栈顶指针初始化为-1,原因是栈为空时，栈顶指针为-1
    return 1;// 初始化成功
    
}

_Bool pushStack(ArrayStack stack, E element) {
    if (stack->top == stack->capacity - 1) {// 栈满
        // 扩容
        int newCapacity = stack->capacity * 2;
        E* newArray = realloc(stack->array, sizeof(E) * newCapacity);// 重新分配内存
        if (newArray == NULL) {
            return 0;
        } else {
            stack->array = newArray;
            stack->capacity = newCapacity;
        }
    } 
    stack->array[++stack->top] = element;// 栈顶指针先加1，再存入元素
    return 1;
    
}
_Bool popStack(ArrayStack stack, E* element) {
    if (stack->top == -1) {// 栈空
        return 0;
    }
    *element = stack->array[stack->top--];// 栈顶指针先减1，再取出元素,赋值给element,element是指针,所以用*element
    return 1;
}

void printStack(ArrayStack stack) {
    for(int i=0;i<stack->top;i++) {
        printf("%d ", stack->array[i]);//打印栈中元素
    }
    printf("\n");
}

int main() {
    ArrayStack stack = malloc(sizeof(Stack));
    initStack(stack, 10);
    pushStack(stack, 1);
    pushStack(stack, 2);
    pushStack(stack, 3);
    pushStack(stack, 4);
    printStack(stack);


    E element=0;
    popStack(stack, &element);
    printf("%d\n", element);
    return 0;
}