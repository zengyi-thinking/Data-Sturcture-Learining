#include "Data.h"

int main()
{
    Student student[100];
    strcpy(student[0].name, "John"); // 使用strcpy函数复制字符串
    strcpy(student[0].age, "20");
    strcpy(student[0].id, "A");
    strcpy(student[0].name, "Jane"); // 使用strcpy函数复制字符串

    printf("Name: %s\n", student[0].name);
    printf("Age: %s\n", student[0].age);
    printf("ID: %s\n", student[0].id);
    printf("Name: %s\n", student[1].name);
}
