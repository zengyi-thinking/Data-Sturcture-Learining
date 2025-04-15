#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为int
typedef int ElementType;

// 定义二叉树节点结构体
typedef struct BiNode {
    ElementType data; // 节点数据
    struct BiNode *left; // 指向左子树的指针
    struct BiNode *right; // 指向右子树的指针
} BiNode, *BiTree;

// 根据层序遍历数组创建二叉树
BiTree createBiTree(const int *levelOrder, int size) {
    // 如果数组为空或第一个元素为-1（表示空树），返回NULL
    if (size == 0 || levelOrder[0] == -1) {
        return NULL;
    }

    // 创建根节点
    BiTree root = (BiNode *) malloc(sizeof(BiNode));
    root->data = levelOrder[0];
    root->left = NULL;
    root->right = NULL;

    // 创建队列用于层序遍历
    BiNode *queue[size];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int i = 1;
    // 遍历层序遍历数组
    while (i < size) {
        BiNode *currentNode = queue[front++]; // 取出队列中的当前节点
        for (int j = 0; j < 2 && i < size; j++) { // 每个节点最多有两个子节点
            if (levelOrder[i] != -1) { // 如果当前元素不为-1，表示有子节点
                BiNode *child = (BiNode *) malloc(sizeof(BiNode)); // 创建子节点
                child->data = levelOrder[i];
                child->left = NULL;
                child->right = NULL;
                if (j == 0) {
                    currentNode->left = child; // 设置左子节点
                } else {
                    currentNode->right = child; // 设置右子节点
                }
                queue[rear++] = child; // 将子节点加入队列
            }
            i++;
        }
    }

    return root; // 返回根节点
}

// 计算二叉树的叶子节点数量
void leafCount(BiTree root, int *count) {
    if(root){
        if((!root->left)&&(!root->right)){
            (*count)++;
        }
            leafCount(root->left,count);
            leafCount(root->right,count);
        }
}


void freeBiTree(BiTree root) {
    if (root == NULL) {
        return;
    }
    freeBiTree(root->left);
    freeBiTree(root->right);
    free(root);
}

int main() {
    int n, nn;
    scanf("%d", &n);
    nn = n;
    int elements[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
        if (elements[i] == -1) {
            nn--;
        }
    }

    BiTree tree = createBiTree(elements, n);

    int count = 0;
    leafCount(tree, &count);
    printf("%d", count);

    freeBiTree(tree);
    return 0;
}
