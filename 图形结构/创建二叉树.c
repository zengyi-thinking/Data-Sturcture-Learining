#include <stdio.h>  
#include <stdlib.h>  

typedef char ElementType;

typedef struct BiNode {
    ElementType data;
    struct BiNode* left;
    struct BiNode* right;
} BiNode, * BiTree;


// 根据输入字符串创建二叉树  
void crt_tree(BiTree* T ){
    char ch; // 用于存储输入的字符
    scanf("%c", &ch); // 读取一个字符
    if(ch == '#'){
        *T = NULL; // 如果输入字符为'#'，则创建空树
    }else{
        *T =(BiTree)malloc(sizeof(BiNode));
        (*T)->data = ch; // 将输入字符赋值给节点数据
        crt_tree(&(*T)->left); // 递归创建左子树
        crt_tree(&(*T)->right);
      }
}

int main() {
    BiTree T = NULL; // 初始化二叉树
    printf("请输入二叉树的先序遍历序列（'#'表示空节点）：\n");
    crt_tree(&T); // 创建二叉树
    return 0;
}