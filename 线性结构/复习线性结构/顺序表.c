//�����Ҫ�Ŀ�,stdlib.h�����ڴ������string.h�����ַ�����ƴ��
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//����˳������洢Ϊ100
#define MAXSIZE 100


//����һ��ѧ�����ݽṹ
typedef struct Student{
    int id;
    char name[50];
    int age;
}Student;

//����˳�������ݣ�dataΪ�������ݣ�lengthΪ˳���ĳ��ȣ�����Ϊ˳���SeqList�����������
typedef struct SeqList{
    Student data[MAXSIZE];
    int length;
}SeqList;

//��ʼ��˳���,ֻ�ý�˳���ĳ��ȱ�־Ϊ0����ô�ʹ������ݱ���û�����ݣ����ݳ�ʼ�����
void InitSeqList(SeqList *L){
    L->length = 0;
}

//��ӡ˳�����˳���������±���Ϊ�洢���ݵĵ�ַ�����δ�ӡ˳��������ݵ�����
void PrintSeqList(SeqList *L){
    for(int i=0;i<L->length;i++){
        printf("id:%d,name:%s,age:%d\n", L->data[i].id, L->data[i].name, L->data[i].age);//����ע��Ҫ���±����Ÿ���ʾ����
    }

}

//����Ԫ�أ�����ֱ�ӽ��±��length����++��Ȼ��ʹ���������ɣ��������ݳ��Ȳ�������
int AddSeqList(SeqList *L,Student s){
    //���˳����Ѿ����ˣ�����0
    if(L->length>MAXSIZE){
        return 0;
    }
    L->data[L->length++]=s;//ͨ����������������������
    return 1;
}

//ɾ���б��ڵ����ݣ�ͨ��ѧ����id������ɾ��
int DeleteSeqList(SeqList *L,int id){
    int i = 0;
    for (i = 0;i<L->length;i++){
        if(L->data[i].id==id){
            break;//�ҵ���ӦԪ��֮����Լ�
        }
    }
    for (int j = i; j < L->length; j++)
    {
        L->data[j] = L->data[j + 1];
    }
    L->length--; // ����ǵ�ɾ����Ԫ��֮��˳���ĳ���Ҫ�Լ�
    return 1;
}

//�޸�˳����ڵ����ݣ�ͨ��ѧ����id�ҵ���Ӧ�����ݣ�Ȼ���޸���������
int ModifySeqList(SeqList *L,int id,Student s){
    for(int i=0;i<L->length;i++){
        if(L->data[i].id==id){
            L->data[i]=s;
            return 1;
        }
    }
    return 0;
}

//����˳����ڵ����ݣ�ͨ��ѧ����id�ҵ���Ӧ�����ݣ�Ȼ���ӡ����
int FindSeqList(SeqList *L,int id){
    for(int i=0;i<L->length;i++){
        if(L->data[i].id==id){
            printf("id:%d,name:%s,age:%d\n", L->data[i].id, L->data[i].name, L->data[i].age);
            return 1;
        }
    }
    return 0;
}

//�����������ڲ���
int main(){
    SeqList L;
    InitSeqList(&L);
    Student s1 = {1,"����",18};
    Student s2 = {2,"����",19};
    Student s3 = {3,"����",20};
    AddSeqList(&L,s1);
    AddSeqList(&L,s2);
    AddSeqList(&L,s3);
    PrintSeqList(&L);
    DeleteSeqList(&L,2);
    PrintSeqList(&L);
    Student s4 = {3,"����",21};
    ModifySeqList(&L,3,s4);
    PrintSeqList(&L);
    FindSeqList(&L,3);
    return 0;
}



