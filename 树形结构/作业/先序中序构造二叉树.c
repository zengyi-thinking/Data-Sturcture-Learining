#include "stdio.h"
#include "stdlib.h"

typedef int ElementType;

typedef struct BiNode{
    ElementType data;
    struct BiNode* left;
    struct BiNode* right;
}BiNode,*BiTree;

//层次遍历二叉树
void hierarchicalTraversal(BiTree root){
    if(!root){
        return;
    }
    BiTree queue[100]; // 队列数组
    int front = 0, rear = 0; // 队列头尾指针
    queue[rear++] = root; // 入队

    while(front<rear){
        BiNode* current = queue[front++]; // 出队
        if(current){
            printf("%d ", current->data); // 访问节点
            queue[rear++] = current->left; // 出队左子树入队
            queue[rear++] = current->right; // 出队右子树入队
        }else{
            int flag = 0; // 标志变量，用于判断是否为空节点
            for(int i = front; i < rear; i++){
                if(queue[i] != NULL){
                    flag = 1; // 如果队列中有非空节点，设置标志为1
                    break;
                }
            }
            if(flag == 0){
                break; // 如果队列中没有非空节点，退出循环
            }
            printf("-1 "); // 访问空节点
        }
    }
}

//递归构造树
BiTree constructTree(int *preorder,int preorderStart,int preorderEnd,int *inorder,int inorderStart,int inorderEnd,int *inorderIndexMap){//inorderIndexMap是中序遍历的索引映射表
    //递归终止条件
    if(preorderStart > preorderEnd||inorderStart > inorderEnd){
        return NULL;
    }
    //前序遍历的第一个元素是根节点
    ElementType rootValue = preorder[preorderStart];
    BiTree root = (BiTree)malloc(sizeof(BiNode));
    root->data = rootValue;

    //在中序遍历中找到根节点的位置
    int rootIndex = inorderIndexMap[rootValue];
    //计算左子树的长度
    int leftLength = rootIndex - inorderStart;

    //递归构造左子树
    root->left = constructTree(preorder, preorderStart + 1, preorderStart + leftLength, inorder, inorderStart, rootIndex - 1, inorderIndexMap);
    //递归构造右子树
    root->right = constructTree(preorder, preorderStart + leftLength + 1, preorderEnd, inorder, rootIndex + 1, inorderEnd, inorderIndexMap);
    return root;

    
}
//释放树
void freeTree(BiTree root){
    if(root){
        freeTree(root->left); // 递归释放左子树
        freeTree(root->right); // 递归释放右子树
        free(root); // 释放当前节点
    }
}
//主函数
int main(){
    int preorder[] = {1,2,4,7,3,5,6,8};
    int inorder[] = {4,7,2,1,5,3,8,6};
    int preorderLength = sizeof(preorder)/sizeof(preorder[0]);
    int inorderLength = sizeof(inorder)/sizeof(inorder[0]);
    int inorderIndexMap[100];
    for(int i = 0; i < inorderLength; i++){
        inorderIndexMap[inorder[i]] = i;
    }//建立中序遍历的索引映射表
    BiTree root = constructTree(preorder, 0, preorderLength - 1, inorder, 0, inorderLength - 1, inorderIndexMap);
    hierarchicalTraversal(root);
    freeTree(root);
    return 0;

}

