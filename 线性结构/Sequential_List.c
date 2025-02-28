#include "Data.h"

typedef int E;

struct List{
    E *array;
    int capacity;
    int size;
};//定义一个结构体List,其中data为指向E类型的指针，capacity为容量，size为当前元素个数

typedef struct List * ArrayList;//定义一个指向结构体List的指针类型

_Bool InitList(ArrayList list){
    list->array =(E *)malloc(sizeof(E)*10);//为data分配内存空间
    if(list->array == NULL){
        return 0;//分配失败
    }
    list->capacity = 10;
    list->size = 0;
    return 1;
}

_Bool Insert(ArrayList list ,E element,int index){
    //判断插入位置是否合法
    // 如果index小于0或者大于list的当前大小加1，则插入位置不合法
    if(index <0||index>list->size+1){
        return 0; // 返回0表示插入失败
    }
    //判断是否需要扩容
    // 如果当前大小等于容量，则需要扩容
    if(list->size == list->capacity){
        int newCapacity = list->capacity+(list->capacity>>1);//扩容为原来的1.5倍
        E *newArray = realloc(list->array,sizeof(E)*newCapacity);//重新分配内存空间
        if(newArray == NULL){
            return 0; // 如果重新分配内存失败，返回0表示插入失败
        }//扩容失败
        list->array = newArray;
        list->capacity = newCapacity;
    }
    //插入元素
    for (int i = list->size;i>index-1;i--){
        list->array[i] = list->array[i-1];//将元素后移
    }
    list->array[index-1] = element;
    list->size++;
    return 1;
}

_Bool deleteList(ArrayList list,int index){
    //判断删除位置是否合法
    // 如果索引小于0或者大于等于列表的大小，则返回0，表示删除失败
    if(index<0||index>list->size){
        return 0;
    }
    //删除元素
    // 从要删除的索引位置开始，将后面的元素依次前移一位
    for (int i = index-1;i<list->size-1;i++){
        list->array[i] = list->array[i+1];//将元素前移
    }
    // 删除元素后，列表的大小减1
    list->size--;
    // 返回1，表示删除成功
    return 1;
}

// 定义一个函数，用于获取ArrayList（动态数组）的大小
int sizeList(ArrayList list){
    // 返回ArrayList结构体中的size成员，该成员表示当前ArrayList中存储的元素个数
    return list->size;//返回当前元素个数
}

// 定义一个函数，用于从ArrayList中获取指定位置的元素
E * getList(ArrayList list,int index){
    // 检查索引是否在有效范围内，索引必须大于等于0且小于等于ArrayList的大小
    if(index<0||index>list->size){
        // 如果索引无效，返回NULL
        return NULL;
    }
    // 如果索引有效，返回指定位置的元素地址
    // 注意：ArrayList的索引从1开始，而数组索引从0开始，因此需要减1
    return &list->array[index-1];//返回指定位置的元素
}

int findList(ArrayList list,E element){
    for (int i = 0; i < list->size; ++i) {
        if(list->array[i] == element){
            return i+1;
        }
    }
    return -1;//未找到
}

int main() {
    ArrayList list = (ArrayList)malloc(sizeof(struct List));//为list分配内存空间
    if(list == NULL){
        return 0;
    }
    if(!InitList(list)){
        return 0;
    }
    Insert(list,1,1);
    Insert(list,2,2);
    Insert(list,3,3);
    Insert(list,4,4);
    Insert(list,5,5);
    Insert(list,6,6);
    Insert(list,7,7);
    Insert(list,18,8);
    Insert(list,9,9);
    Insert(list,10,10);
    Insert(list,11,11);
    printf("%d\n",sizeList(list));
    printf("%d\n",*getList(list,8));
    printf("%d\n",findList(list,5));
    deleteList(list,5);
    printf("%d\n",sizeList(list));
    printf("%d\n",*getList(list,5));
    printf("%d\n",findList(list,5));
    return 0;
}

