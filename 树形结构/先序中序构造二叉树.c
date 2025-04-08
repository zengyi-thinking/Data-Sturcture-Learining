#include "stdio.h"
#include "stdlib.h"

typedef int ElementType;

typedef struct BiNode{
    ElementType data;
    struct BiNode* left;
    struct BiNode* right;
}BiNode,*BiTree;

//��α���������
void hierarchicalTraversal(BiTree root){
    if(!root){
        return;
    }
    BiTree queue[100]; // ��������
    int front = 0, rear = 0; // ����ͷβָ��
    queue[rear++] = root; // ���

    while(front<rear){
        BiNode* current = queue[front++]; // ����
        if(current){
            printf("%d ", current->data); // ���ʽڵ�
            queue[rear++] = current->left; // �������������
            queue[rear++] = current->right; // �������������
        }else{
            int flag = 0; // ��־�����������ж��Ƿ�Ϊ�սڵ�
            for(int i = front; i < rear; i++){
                if(queue[i] != NULL){
                    flag = 1; // ����������зǿսڵ㣬���ñ�־Ϊ1
                    break;
                }
            }
            if(flag == 0){
                break; // ���������û�зǿսڵ㣬�˳�ѭ��
            }
            printf("-1 "); // ���ʿսڵ�
        }
    }
}

//�ݹ鹹����
BiTree constructTree(int *preorder,int preorderStart,int preorderEnd,int *inorder,int inorderStart,int inorderEnd,int *inorderIndexMap){//inorderIndexMap���������������ӳ���
    //�ݹ���ֹ����
    if(preorderStart > preorderEnd||inorderStart > inorderEnd){
        return NULL;
    }
    //ǰ������ĵ�һ��Ԫ���Ǹ��ڵ�
    ElementType rootValue = preorder[preorderStart];
    BiTree root = (BiTree)malloc(sizeof(BiNode));
    root->data = rootValue;

    //������������ҵ����ڵ��λ��
    int rootIndex = inorderIndexMap[rootValue];
    //�����������ĳ���
    int leftLength = rootIndex - inorderStart;

    //�ݹ鹹��������
    root->left = constructTree(preorder, preorderStart + 1, preorderStart + leftLength, inorder, inorderStart, rootIndex - 1, inorderIndexMap);
    //�ݹ鹹��������
    root->right = constructTree(preorder, preorderStart + leftLength + 1, preorderEnd, inorder, rootIndex + 1, inorderEnd, inorderIndexMap);
    return root;

    
}
//�ͷ���
void freeTree(BiTree root){
    if(root){
        freeTree(root->left); // �ݹ��ͷ�������
        freeTree(root->right); // �ݹ��ͷ�������
        free(root); // �ͷŵ�ǰ�ڵ�
    }
}
//������
int main(){
    int preorder[] = {1,2,4,7,3,5,6,8};
    int inorder[] = {4,7,2,1,5,3,8,6};
    int preorderLength = sizeof(preorder)/sizeof(preorder[0]);
    int inorderLength = sizeof(inorder)/sizeof(inorder[0]);
    int inorderIndexMap[100];
    for(int i = 0; i < inorderLength; i++){
        inorderIndexMap[inorder[i]] = i;
    }//�����������������ӳ���
    BiTree root = constructTree(preorder, 0, preorderLength - 1, inorder, 0, inorderLength - 1, inorderIndexMap);
    hierarchicalTraversal(root);
    freeTree(root);
    return 0;

}

