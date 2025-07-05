#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
typedef struct
{
    struct
    {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
    int listsize;
} LISTS;
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);
void AddList(LISTS &Lists, char ListName[]);
status PriorElem(LinkList L, ElemType e, ElemType &pre);
status NextElem(LinkList L, ElemType e, ElemType &next);
status InitList(LinkList &L);
status ListTraverse(LinkList L);
int ListLength(LinkList L);
status ListInsert(LinkList &L, int i, ElemType e);
status ListEmpty(LinkList L);
status ListDelete(LinkList &L, int i, ElemType &e);
status GetElem(LinkList L, int i, ElemType &e);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
int LocateList(LISTS Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status LocateElem(LinkList L, ElemType e);
int sortList(LinkList L);
void swap(int *a, int *b);
int medianOfThree(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
status reverseList(LinkList &L);
status RemoveNthFromEnd(LinkList &L, int n);

int main()
{
    LISTS Lists;
    Lists.length = 0;
    int op = 1;
    int list_num = 1;
    int count = 0;
    char firstname[30];
    LNode *p, *tail_2;
    while (op)
    {
        char name_temp[30];
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        if (count > 1)
        {
            printf("需要查看有什么表吗？,需要请输入1,不需要输入其他数字\n");
            scanf("%d", &op);
            if (op == 1)
            {
                printf("创建的线性表有：\n");
                for (int temp_2 = 0; temp_2 < Lists.length; temp_2++)
                {
                    printf("%s\n", Lists.elem[temp_2].name);
                }
            }
            bool flag = 1;
            printf("请问你想对哪个线性表进行操作？\n");
            do
            {
                scanf("%s", name_temp);
                if (!(list_num = LocateList(Lists, name_temp)))
                {
                    flag = 0;
                    printf("找不到对应的线性表,请重新输入\n");
                }
                else
                    flag = 1;
            } while (flag != OK);
        }
        printf("    	  1. InitList       11. ListDelete\n");
        printf("    	  2. DestroyList    12. ListTrabverse\n");
        printf("    	  3. ClearList      13. file_using\n");
        printf("    	  4. ListEmpty      14. AddList\n");
        printf("    	  5. ListLength     15. RemoveList\n");
        printf("    	  6. GetElem        16. LocateList\n");
        printf("          7. LocateElem     17. SortList\n");
        printf("          8. PriorElem      18. reverseList\n");
        printf("          9. NextElem       19. RemoveNthFromEnd\n");
        printf("          10. ListInsert    20. ShowAllList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1: // 线性表的创建
            if (Lists.length > 0)
            {
                printf("已初始化线性表\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入你想创建的线性表名称\n");
            scanf("%s", firstname);
            AddList(Lists, firstname);
            printf("请输入元素,以0结束\n");
            int i;
            scanf("%d", &i);
            tail_2 = Lists.elem[Lists.length - 1].L;
            while (i)
            {
                p = (LNode *)malloc(sizeof(LNode));
                p->data = i;
                tail_2->next = p;
                tail_2 = tail_2->next;
                scanf("%d", &i);
            }
            tail_2->next = NULL;
            if (!ListTraverse(Lists.elem[Lists.length - 1].L))
                printf("线性表是空表！\n");
            else
                count++;
            getchar();
            getchar();
            break;
        case 2: // 销毁线性表
            if (DestroyList(Lists.elem[list_num - 1].L) == OK)
                printf("销毁线性表成功\n");
            else
                printf("线性表已空\n");
            getchar();
            getchar();
            break;
        case 3: // 清空线性表
            if (ClearList(Lists.elem[list_num - 1].L) == OK)
                printf("清空线性表成功\n");
            else
                printf("线性表已空\n");
            getchar();
            getchar();
            break;
        case 4: // 线性表判空
            if (ListEmpty(Lists.elem[list_num - 1].L) == OK)
                printf("线性表为空\n");
            else if (ListEmpty(Lists.elem[list_num - 1].L) == 0)
                printf("线性表不为空\n");
            else
                printf("线性表不存在\n");
            getchar();
            getchar();
            break;
        case 5: // 线性表长度
            if (ListLength(Lists.elem[list_num - 1].L) > 0)
                printf("线性表长度为%d\n", ListLength(Lists.elem[list_num - 1].L));
            else
                printf("线性表为空\n");
            getchar();
            getchar();
            break;
        case 6: // 获取元素
            int temp, m;
            printf("您想获取第几个元素？\n");
            scanf("%d", &i);
            if (GetElem(Lists.elem[list_num - 1].L, m, temp) == OK)
                printf("第%d个元素是:%d\n", m, temp);
            else
                printf("i的范围不正确\n");
            getchar();
            getchar();
            break;
        case 7: // 查找元素
            printf("您想查找哪个元素？\n");
            scanf("%d", &i);
            if ((temp = LocateElem(Lists.elem[list_num - 1].L, i)) > 0)
            {
                printf("元素%d在第%d位\n", i, temp);
            }
            else
                printf("不存在该元素\n");
            getchar();
            getchar();
            break;
        case 8: // 获取前驱元素
            int pre;
            printf("您想查找哪个元素的前驱？\n");
            scanf("%d", &i);
            if (PriorElem(Lists.elem[list_num - 1].L, i, pre) == OK)
                printf("该元素的前驱是%d\n", pre);
            else
                printf("不存在该元素\n");
            getchar();
            getchar();
            break;
        case 9: // 获取后继元素
            int next;
            printf("您想查找哪个元素的后驱？\n");
            scanf("%d", &i);
            if (NextElem(Lists.elem[list_num - 1].L, i, next) == OK)
                printf("该元素的后驱是%d\n", next);
            else
                printf("不存在该元素\n");
            getchar();
            getchar();
            break;
        case 10: // 插入元素
            printf("请输入要插入的元素\n");
            scanf("%d", &temp);
            printf("请输入要插入的位置\n");
            scanf("%d", &m);
            if (ListInsert(Lists.elem[list_num - 1].L, m, temp) == OK)
            {
                printf("插入成功\n");
                printf("插入后的线性表为:\n");
                if (!ListTraverse(Lists.elem[list_num - 1].L))
                    printf("线性表是空表！\n");
            }
            else
                printf("插入失败\n");
            getchar();
            getchar();
            break;
        case 11: // 删除元素
            printf("请输入删除的位置\n");
            scanf("%d", &temp);
            if (ListDelete(Lists.elem[list_num - 1].L, temp, m) == OK)
            {
                printf("删除成功\n");
                printf("删除后的线性表为:");
                if (!ListTraverse(Lists.elem[list_num - 1].L))
                    printf("空表！\n");
            }
            else
                printf("删除失败\n");
            getchar();
            getchar();
            break;
        case 12: // 遍历线性表
            if (!ListTraverse(Lists.elem[list_num - 1].L))
                printf("线性表是空表！\n");
            getchar();
            getchar();
            break;
        case 13: // 线性表读写文件
            char filename[30];
            printf("请输入指令\n");
            printf("1.文件读取\n");
            printf("2.文件写入\n");
            scanf("%d", &i);
            if (i == 1)
            {

                printf("请输入需要读取的文件地址,请用.dat作为后缀\n");
                scanf("%s", filename);
                printf("请输入你想创建的线性表名称\n");
                scanf("%s", firstname);
                if ((temp = LocateList(Lists, firstname)) > 0)
                {
                    printf("有重复名称,无法创建\n");
                    break;
                }
                AddList(Lists, firstname);
                if (LoadList(Lists.elem[Lists.length - 1].L, filename) == OK)
                {
                    printf("读取成功\n");
                    count++;
                }
                else
                    printf("读取失败\n");
            }
            else if (i == 2)
            {
                printf("请输入需要写入的文件地址,请用.dat作为后缀\n");
                scanf("%s", filename);
                if (SaveList(Lists.elem[list_num - 1].L, filename) == OK)
                    printf("写入成功\n");
                else
                    printf("写入失败\n");
            }
            getchar();
            getchar();
            break;
        case 14: // 多线性表管理：增加一个新线性表
            printf("请输入新线性表名字\n");
            scanf("%s", firstname);
            if ((temp = LocateList(Lists, firstname)) > 0)
            {
                printf("有重复名称,无法创建\n");
                break;
            }
            AddList(Lists, firstname);
            printf("请输入元素,以0结束\n");
            tail_2 = Lists.elem[Lists.length - 1].L;
            scanf("%d", &i);
            while (i)
            {
                p = (LNode *)malloc(sizeof(LNode));
                p->data = i;
                tail_2->next = p;
                tail_2 = tail_2->next;
                scanf("%d", &i);
            }
            tail_2->next = NULL;
            if (!ListTraverse(Lists.elem[Lists.length - 1].L))
                printf("线性表是空表！\n");
            else
                count++;
            getchar();
            getchar();
            break;
        case 15: // 多线性表管理：移除一个线性表
            printf("请输入需要移除的线性表名字\n");
            scanf("%s", firstname);
            if (RemoveList(Lists, firstname) == OK)
                printf("移除成功\n");
            else
                printf("移除失败\n");
            getchar();
            getchar();
            break;
        case 16: // 多线性表管理：查找线性表
            printf("请输入需要查找的线性表名字\n");
            scanf("%s", firstname);
            if ((temp = LocateList(Lists, firstname)) == 0)
                printf("查找失败\n");
            else
                printf("查找成功,位置为%d\n", temp);
            getchar();
            getchar();
            break;
        case 17:
            temp = sortList(Lists.elem[list_num - 1].L);
            if (temp)
            {
                printf("排序成功,排序后的线性表为:");
                temp = ListTraverse(Lists.elem[list_num - 1].L);
            }
            getchar();
            getchar();
            break;
        case 18:
            if ((temp = reverseList(Lists.elem[list_num - 1].L)))
            {
                printf("反转成功,反转后的线性表为：");
                temp = ListTraverse(Lists.elem[list_num - 1].L);
            }
            else if (temp == 0)
                printf("长度为1,无需反转\n");
            getchar();
            getchar();
            break;
        case 19:
            printf("请输入你想删除链表的倒数第几个结点\n");
            scanf("%d", &i);
            temp = RemoveNthFromEnd(Lists.elem[list_num - 1].L, i);
            if (temp)
            {
                printf("删除成功,删除后的线性表为:\n");
                temp = ListTraverse(Lists.elem[list_num - 1].L);
            }
            else
                printf("删除失败\n");
            getchar();
            getchar();
            break;
        case 20:
            printf("创建的线性表有：");
            for (int temp_2 = 0; temp_2 < Lists.length; temp_2++)
            {
                if (!strcmp(Lists.elem[temp_2].name, 0))
                    printf("%s\n", Lists.elem[temp_2].name);
            }
            getchar();
            getchar();
            break;
        case 0:
            break;
        } // end of switch
    } // end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
} // end of main()

// file_using.h
status SaveList(LinkList L, char FileName[])
{
    if (L == NULL)
        return -1;
    FILE *fp = fopen(FileName, "wb");
    LNode *p = L;
    int count = -1;
    while (p)
    {
        p = p->next;
        count++;
    }
    fwrite(&count, sizeof(ElemType), 1, fp);
    p = L->next;
    for (int i = 0; i < count; i++, p = p->next)
        fwrite(&p->data, sizeof(ElemType), 1, fp);
    fclose(fp);
    return 1;
}
status LoadList(LinkList &L, char FileName[])
{
    if (L->next != NULL)
        return -1;
    int count;
    L = (LinkList)malloc(sizeof(LNode));
    LNode *tail = L;
    LinkList p;
    FILE *fp = fopen(FileName, "rb");
    fread(&count, sizeof(ElemType), 1, fp);
    for (int i = 0; i < count; i++, p = p->next)
    {
        p = (LinkList)malloc(sizeof(LNode));
        fread(&p->data, sizeof(ElemType), 1, fp);
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    fclose(fp);
    return 1;
}

// AddList.h
void AddList(LISTS &Lists, char ListName[])
{
    Lists.elem[Lists.length++].L = (LinkList)malloc(sizeof(LNode));
    Lists.elem[Lists.length - 1].L->next = NULL;
    strcpy(Lists.elem[Lists.length - 1].name, ListName);
}

// PriorElem.h
status PriorElem(LinkList L, ElemType e, ElemType &pre)
{
    if (L == NULL)
        return -1;
    L = L->next;
    while (L)
    {
        if (L->next != NULL && L->next->data == e)
        {
            pre = L->data;
            return 1;
        }
        L = L->next;
    }
    return 0;
}

// NextElem.h
status NextElem(LinkList L, ElemType e, ElemType &next)
{
    if (L == NULL)
        return -1;
    L = L->next;
    while (L)
    {
        if (L->next != NULL && L->data == e)
        {
            next = L->next->data;
            return 1;
        }
        L = L->next;
    }
    return 0;
}

// InitList.h
status InitList(LinkList &L)
{
    if (L != NULL)
        return -1;
    else
    {
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
        return 1;
    }
}

// ListTraverse.h
status ListTraverse(LinkList L)
{
    if (L == NULL)
        return -1;
    else if (L->next == NULL)
        return 1;
    LNode *p = L->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    return 1;
}

// ListLength.h
int ListLength(LinkList L)
{
    if (L == NULL)
        return -1;
    else
    {
        LinkList p = L->next;
        int count = 0;
        while (p != NULL)
        {
            p = p->next;
            count++;
        }
        return count;
    }
}

// ListInsert.h
status ListInsert(LinkList &L, int i, ElemType e)
{
    if (L == NULL)
        return -1;
    LNode *p = L;
    int count = 0;
    while (p)
    {
        p = p->next;
        count++;
    }
    if (i <= 0 || i > count)
        return 0;
    LNode *b;
    b = (LNode *)malloc(sizeof(LNode));
    b->data = e;
    p = L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;
    b->next = p->next;
    p->next = b;
    return 1;
}

// ListEmpty.h
status ListEmpty(LinkList L)
{
    if (L == NULL)
        return -1;
    else if (L->next == NULL)
        return 1;
    else
        return 0;
}

// ListDelete.h
status ListDelete(LinkList &L, int i, ElemType &e)
{
    if (L == NULL)
        return -1;
    LNode *p = L;
    LNode *q = L;
    int count = -1;
    while (p)
    {
        p = p->next;
        count++;
    }
    if (i <= 0 || i > count)
        return 0;
    p = L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;
    e = p->next->data;
    q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

// GetElem.h
status GetElem(LinkList L, int i, ElemType &e)
{
    if (L == NULL)
        return -1;
    else
    {
        LinkList p = L->next;
        int count = 0;
        while (p != NULL)
        {
            p = p->next;
            count++;
        }
        if (i < 1 || i > count)
            return 0;
        else
        {
            p = L->next;
            for (int j = 0; j < i - 1; j++)
                p = p->next;
            e = p->data;
            return 1;
        }
    }
}

// DestroyList.h
status DestroyList(LinkList &L)
{
    if (L == NULL)
        return -1;
    else
    {
        LinkList temp_1 = L->next;
        LinkList temp_2;
        while (temp_1 != NULL)
        {
            temp_2 = temp_1;
            temp_1 = temp_1->next;
            free(temp_2);
        }
        free(L);
        L = NULL;
        return 1;
    }
}

// ClearList.h
status ClearList(LinkList &L)
{
    if (L == NULL)
        return -1;
    else
    {
        LinkList temp_1 = L->next;
        LinkList temp_2;
        while (temp_1 != NULL)
        {
            temp_2 = temp_1;
            temp_1 = temp_1->next;
            free(temp_2);
        }
        L->next = NULL;
        return 1;
    }
}

// LocateList.h
int LocateList(LISTS Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return i + 1;
    }
    return 0;
}

// RemoveList.h
status RemoveList(LISTS &Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            LinkList temp_1 = Lists.elem[i].L->next;
            LinkList temp_2;
            while (temp_1 != NULL)
            {
                temp_2 = temp_1;
                temp_1 = temp_1->next;
                free(temp_2);
            }
            free(Lists.elem[i].L);
            Lists.elem[i].L = NULL;
            Lists.elem[i].name[0] = '\0';
            return 1;
        }
    }
    return 0;
}

// LocateElem.h
status LocateElem(LinkList L, ElemType e)
{
    if (L == NULL)
        return -1;
    L = L->next;
    int count = 0;
    while (L)
    {
        count++;
        if (L->data == e)
            return count;
        L = L->next;
    }
    return 0;
}

// sortList.h
int sortList(LinkList L)
{
    if (L == NULL || L->next == NULL)
    {
        printf("线性表为空\n");
        return 0;
    }
    LinkList p = L->next;
    int count = 0;
    while (p != NULL)
    {
        p = p->next;
        count++;
    }
    int temp_array[count];
    p = L->next;
    for (int i = 0; i < count; i++, p = p->next)
    {
        temp_array[i] = p->data;
    }
    quickSort(temp_array, 0, count - 1);
    p = L->next;
    for (int i = 0; i < count; p = p->next, i++)
    {
        p->data = temp_array[i];
    }
    return 1;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int medianOfThree(int arr[], int low, int high)
{
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
    return mid;
}
int partition(int arr[], int low, int high)
{
    int pivotIndex = medianOfThree(arr, low, high);
    swap(&arr[pivotIndex], &arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high)
{
    while (low < high)
    {
        int pi = partition(arr, low, high);
        if (pi - low < high - pi)
        {
            quickSort(arr, low, pi - 1);
            low = pi + 1;
        }
        else
        {
            quickSort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

// reverseList.h
status reverseList(LinkList &L)
{
    if (L == NULL)
        return -1;
    if (L->next->next == NULL)
        return 0;
    LinkList pre = L->next->next, pro = L->next, temp = pro->next;
    pro->next = NULL;
    while (pre->next)
    {
        temp = pre;
        pre = pre->next;
        temp->next = pro;
        pro = temp;
    }
    temp = pre;
    temp->next = pro;
    pro = temp;
    L->next = pre;
    return 1;
}

// RemoveNthFromEnd.h
status RemoveNthFromEnd(LinkList &L, int n)
{
    if (L == NULL)
        return -1;
    LinkList p = L->next;
    int count = 0;
    while (p != NULL)
    {
        p = p->next;
        count++;
    }
    if (n > count || n < 0)
        return 0;
    p = L->next;
    for (int i = 1; i < count - n; i++)
    {
        p = p->next;
    }
    LinkList temp = p->next;
    p->next = temp->next;
    free(temp);
    return 1;
}
