//导入必要的库,stdlib.h用于内存操作，string.h用于字符创的拼接
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//定义顺序表最大存储为100
#define MAXSIZE 100


//定义一个学生数据结构
typedef struct Student{
    int id;
    char name[50];
    int age;
}Student;

//定义顺序表的内容，data为数据内容，length为顺序表的长度，两者为顺序表（SeqList）的组成内容
typedef struct SeqList{
    Student data[MAXSIZE];
    int length;
}SeqList;

//初始化顺序表,只用将顺序表的长度标志为0，那么就代表数据表内没有数据，数据初始化完成
void InitSeqList(SeqList *L){
    L->length = 0;
}

//打印顺序表，以顺序表的数组下标作为存储数据的地址，依次打印顺序表中数据的内容
void PrintSeqList(SeqList *L){
    for(int i=0;i<L->length;i++){
        printf("id:%d,name:%s,age:%d\n", L->data[i].id, L->data[i].name, L->data[i].age);//这里注意要将下标的序号给表示出来
    }

}

//插入元素，这里直接将下标的length不断++，然后使其自增即可，代表数据长度不断增长
int AddSeqList(SeqList *L,Student s){
    //如果顺序表已经满了，返回0
    if(L->length>MAXSIZE){
        return 0;
    }
    L->data[L->length++]=s;//通过自增将新增数据纳入来
    return 1;
}

//删除列表内的数据，通过学生的id将数据删除
int DeleteSeqList(SeqList *L,int id){
    int i = 0;
    for (i = 0;i<L->length;i++){
        if(L->data[i].id==id){
            break;//找到对应元素之后便自减
        }
    }
    for (int j = i; j < L->length; j++)
    {
        L->data[j] = L->data[j + 1];
    }
    L->length--; // 这里记得删除完元素之后顺序表的长度要自减
    return 1;
}

//修改顺序表内的数据，通过学生的id找到对应的数据，然后修改数据内容
int ModifySeqList(SeqList *L,int id,Student s){
    for(int i=0;i<L->length;i++){
        if(L->data[i].id==id){
            L->data[i]=s;
            return 1;
        }
    }
    return 0;
}

//查找顺序表内的数据，通过学生的id找到对应的数据，然后打印出来
int FindSeqList(SeqList *L,int id){
    for(int i=0;i<L->length;i++){
        if(L->data[i].id==id){
            printf("id:%d,name:%s,age:%d\n", L->data[i].id, L->data[i].name, L->data[i].age);
            return 1;
        }
    }
    return 0;
}

//主函数，用于测试
int main(){
    SeqList L;
    InitSeqList(&L);
    Student s1 = {1,"张三",18};
    Student s2 = {2,"李四",19};
    Student s3 = {3,"王五",20};
    AddSeqList(&L,s1);
    AddSeqList(&L,s2);
    AddSeqList(&L,s3);
    PrintSeqList(&L);
    DeleteSeqList(&L,2);
    PrintSeqList(&L);
    Student s4 = {3,"赵六",21};
    ModifySeqList(&L,3,s4);
    PrintSeqList(&L);
    FindSeqList(&L,3);
    return 0;
}



