//�����Ҫ�Ŀ�,stdlib.h�����ڴ������string.h�����ַ�����ƴ��
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//����ѧ�������ݽṹ
typedef struct Student{
    int id;
    char name[29];
    int age;
    float score;
}Student;

//������������ݽṹ
typedef struct LinkList{
    Student data;
    struct LinkList *next;//����Ҫ��struct LinkList *next����ΪLinkList��һ���Զ�������ݽṹ����Ҫ��struct������
}LinkList;

//��ʼ������,����ֻ��Ҫ�������ͷ����nextָ��NULL����,��Ϊͷ��㲻�洢����
void InitList(LinkList *head){
    head->next = NULL;
}

//��ӡ������ͷ������һ���ڵ㿪ʼ��ӡ
void PrintList(LinkList *head){
    LinkList *p = head->next;//���幤��ָ�룬��ͷ������һ���ڵ㿪ʼ��ӡ
    while(p != NULL){
        printf("%s,%d,%d,%f\n",p->data.name,p->data.id,p->data.age,p->data.score);//������p->data.name������p->name����Ϊp->data��һ��Student���͵����ݽṹ����Ҫ��data���������е�����
        p = p->next;
    }
}

//�������в������ݣ�������Ҫ���½ڵ��nextָ��ԭ���ĵ�һ���ڵ㣬Ȼ��ͷ����nextָ���½ڵ�,��Ϊͷ�巨��β�巨
int InsertList(LinkList *head,Student s)
{
    LinkList *newNode = (LinkList *)malloc(sizeof(LinkList));//�����½ڵ���ڴ�
    if(newNode == NULL){
        return 0;
    }
    newNode->data = s;//���½ڵ�����ݸ�ֵΪs
    newNode->next = head->next;//���½ڵ��nextָ��ԭ���ĵ�һ���ڵ�
    head->next = newNode;//��ͷ����nextָ���½ڵ�
    return 1;
    
}

//ɾ�������е����ݣ�ͨ��id��ɾ��
int DeleteList(LinkList *head,int id){
    LinkList *p = head->next;//���幤��ָ�룬��ͷ������һ���ڵ㿪ʼ
    LinkList *pre = head;//����ǰ��ָ�룬ָ����ָ���ǰһ���ڵ㣬��ʼ��ʱָ��ͷ���
    if (p == NULL)
        return 0; // �������ָ��Ϊ�գ�˵��û���ҵ�Ҫɾ����id������0
    while(p != NULL){//��������̶���ʽ
        if(p->data.id ==id){
            pre->next = p->next;//��ǰ��ָ���nextָ����ָ���next����������ָ���������ɾ��
            free(p);//�ͷŹ���ָ����ڴ�
            return 1;//ɾ���ɹ�
        }
        //�������ָ���id������Ҫɾ����id����ôǰ��ָ��͹���ָ��ͬʱ����
        pre = p;    p = p->next;  
    }
    return 0;//�������������û���ҵ�Ҫɾ����id������0
}

//�޸������е����ݣ�ͨ��id�ҵ���Ӧ�����ݣ�Ȼ���޸���������
int ModifyList(LinkList *head,int id,Student s){
    LinkList *p = head->next;//���幤��ָ�룬��ͷ������һ���ڵ㿪ʼ
    while(p != NULL){
        if(p->data.id == id){
            p->data = s;//������ָ������ݸ�ֵΪs
            return 1;//�޸ĳɹ�
        }
        p = p->next;
    }
    return 0;//�������������û���ҵ�Ҫ�޸ĵ�id������0
}

int main()
{
    LinkList *head = (LinkList *)malloc(sizeof(LinkList)); // ����ͷ�����ڴ�
    InitList(head);                                        // ��ʼ������

    int choice, id, age;
    float score;
    char name[29];
    Student s;

    while (1)
    {
        printf("\n1. ����ѧ��\n2. ɾ��ѧ��\n3. �޸�ѧ��\n4. ����ѧ��\n5. ��ӡѧ���б�\n6. �˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("������ѧ��ID: ");
            scanf("%d", &s.id);
            printf("������ѧ������: ");
            scanf("%s", s.name);//ע��������s.name,������&s.name,��Ϊname��һ���ַ����飬����Ҫȡ��ַ
            printf("������ѧ������: ");
            scanf("%d", &s.age);
            printf("������ѧ���ɼ�: ");
            scanf("%f", &s.score);
            InsertList(head, s);
            break;
        case 2:
            printf("������Ҫɾ����ѧ��ID: ");
            scanf("%d", &id);
            if (DeleteList(head, id))
            {
                printf("ɾ���ɹ�\n");
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 3:
            printf("������Ҫ�޸ĵ�ѧ��ID: ");
            scanf("%d", &s.id);
            printf("�������µ�ѧ������: ");
            scanf("%s", s.name);
            printf("�������µ�ѧ������: ");
            scanf("%d", &s.age);
            printf("�������µ�ѧ���ɼ�: ");
            scanf("%f", &s.score);
            if (ModifyList(head, s.id, s))
            {
                printf("�޸ĳɹ�\n");
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 4:
            printf("������Ҫ���ҵ�ѧ��ID: ");
            scanf("%d", &id);
            LinkList *found = head->next;
            while (found != NULL && found->data.id != id)
            {
                found = found->next;
            }
            if (found != NULL)
            {
                printf("�ҵ�ѧ��: %s, %d, %d, %f\n", found->data.name, found->data.id, found->data.age, found->data.score);
            }
            else
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 5:
            PrintList(head);
            break;
        case 6:
            exit(0);
        default:
            printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}
