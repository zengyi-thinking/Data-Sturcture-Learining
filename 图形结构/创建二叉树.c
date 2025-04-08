#include <stdio.h>  
#include <stdlib.h>  

typedef char ElementType;

typedef struct BiNode {
    ElementType data;
    struct BiNode* left;
    struct BiNode* right;
} BiNode, * BiTree;


// ���������ַ�������������  
void crt_tree(BiTree* T ){
    char ch; // ���ڴ洢������ַ�
    scanf("%c", &ch); // ��ȡһ���ַ�
    if(ch == '#'){
        *T = NULL; // ��������ַ�Ϊ'#'���򴴽�����
    }else{
        *T =(BiTree)malloc(sizeof(BiNode));
        (*T)->data = ch; // �������ַ���ֵ���ڵ�����
        crt_tree(&(*T)->left); // �ݹ鴴��������
        crt_tree(&(*T)->right);
      }
}

int main() {
    BiTree T = NULL; // ��ʼ��������
    printf("�����������������������У�'#'��ʾ�սڵ㣩��\n");
    crt_tree(&T); // ����������
    return 0;
}