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
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; // 二叉树结点类型定义

typedef struct BiTNode
{ // 二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}

typedef struct
{ // 线性表的管理表定义
    struct
    {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
    int listsize;
} LISTS;
int z, count_3;
void visit(BiTree T);
BiTree create_Node(TElemType definition);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
status PreOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
struct BiTNode *LocateNode(BiTree T, KeyType e);
status LevelOrderTraverse(BiTree T);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status InOrderTraverse(BiTree T);
struct BiTNode *GetSibling(BiTree T, KeyType e);
status DestroyBiTree(BiTree &T);
status DeleteNode(BiTree &T, KeyType e);
status ClearBiTree(BiTree &T);
status CreateBiTree_pre(BiTree &T, TElemType definition[]);
int BiTreeDepth(BiTree T);
status Assign(BiTree &T, KeyType e, TElemType value);
void AddList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status InvertTree(BiTree &T);
void get_definition(TElemType definition[]);
void MaxPathSum(BiTree &T, int &result);
BiTree LowestCommonAncestor(BiTree &T, int p, int q);
BiTree create_tree(TElemType definition[]);

int main()
{
    LISTS Lists;
    Lists.length = 0;
    TElemType definition[100];
    int op = 1;
    int i;
    int temp, m;
    int result = 0;
    TElemType temp_2;
    int list_num = 1;
    int count = 0;
    char firstname[30];
    while (op)
    {
        char name_temp[30];
        printf("\n\n");
        printf("      Menu for non-Linear Table On non-Sequence Structure \n");
        printf("-------------------------------------------------\n");
        if (count > 1)
        {
            printf("创建的线性表有：\n");
            for (int temp_2 = 0; temp_2 < Lists.length; temp_2++)
            {
                if (strcmp(Lists.elem[temp_2].name, "0") != 0)
                    printf("%s\n", Lists.elem[temp_2].name);
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
        printf("    	  1. CreateBiTree   12. PreOrderTraverse\n");
        printf("    	  2. DestroyBiTree  13. InOrderTraverse\n");
        printf("    	  3. ClearBiTree    14. PostOrderTraverse\n");
        printf("    	  4. BiTreeEmpty    15. AddList\n");
        printf("    	  5. BiTreeDepth    16. RemoveList\n");
        printf("    	  6. Assign         17. LocateList\n");
        printf("          7. LocateNode     18. LevelOrderTraverse\n");
        printf("          8. GetSibling     19. InvertTree\n");
        printf("          9. DeleteNode     20. MaxPathSum\n");
        printf("          10. InsertNode    21. ShowAllList\n");
        printf("    	  11. file_using    22. LowestCommonAncestor\n");
        printf("          0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1: // 二叉树的创建
            if (Lists.length > 0)
            {
                printf("已初始化线性表\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入你想创建的线性表名称\n");
            scanf("%s", firstname);
            if (strcmp(firstname, "0") == 0)
            {
                printf("名字非法\n");
                getchar();
                getchar();
                break;
            }
            AddList(Lists, firstname);
            printf("请问你想如何创建二叉树?\n关键字为0时,表示空子树\n-1表示输入结束\n");
            get_definition(definition);
            // if (i == 1)
            // {
            if (CreateBiTree_pre(Lists.elem[Lists.length - 1].T, definition))
            {
                PreOrderTraverse(Lists.elem[Lists.length - 1].T);
                count++;
                printf("\n创建成功\n");
            }
            else
                printf("创建失败，有重复关键字\n");
            getchar();
            getchar();
            break;
        case 2: // 销毁二叉树
            if (DestroyBiTree(Lists.elem[list_num - 1].T) == OK)
                printf("销毁二叉树成功\n");
            else
                printf("二叉树已空\n");
            getchar();
            getchar();
            break;
        case 3: // 清空二叉树
            if (ClearBiTree(Lists.elem[list_num - 1].T->lchild) == OK && ClearBiTree(Lists.elem[list_num - 1].T->rchild) == OK)
            {
                printf("清空二叉树成功\n");
            }
            else
                printf("二叉树已空\n");
            getchar();
            getchar();
            break;
        case 4: // 二叉树判空
            if (Lists.elem[list_num - 1].T == NULL)
                printf("二叉树为空\n");
            else if (Lists.elem[list_num - 1].T->lchild || Lists.elem[list_num - 1].T->rchild || (Lists.elem[list_num - 1].T->lchild == NULL && Lists.elem[list_num - 1].T->rchild == NULL && Lists.elem[list_num - 1].T))
                printf("二叉树不为空\n");
            else
                printf("二叉树不存在\n");
            getchar();
            getchar();
            break;
        case 5: // 二叉树深度
            if ((i = BiTreeDepth(Lists.elem[list_num - 1].T)) > 0)
                printf("线性表深度为%d\n", i);
            else
                printf("线性表为空\n");
            getchar();
            getchar();
            break;
        case 6: // 节点赋值
            printf("您想更改哪个位置的值？\n");
            scanf("%d", &i);
            printf("您想将其更改为什么值？\n");
            scanf("%d %s", &temp_2.key, &temp_2.others);
            if (Assign(Lists.elem[list_num - 1].T, i, temp_2))
            {
                printf("赋值成功");
                PreOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
                InOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
            }
            else
                printf("赋值失败\n");
            getchar();
            getchar();
            break;
        case 7: // 查找结点
            printf("您想查找哪个元素？\n");
            scanf("%d", &i);
            BiTree p;
            if ((p = LocateNode(Lists.elem[list_num - 1].T, i)) != NULL)
            {
                printf("该节点为%d %s\n", p->data.key, p->data.others);
            }
            else
                printf("不存在该元素\n");
            getchar();
            getchar();
            break;
        case 8: // 获得兄弟结点
            printf("您想查找哪个元素的兄弟？\n");
            scanf("%d", &i);
            if ((p = GetSibling(Lists.elem[list_num - 1].T, i)) != NULL)
                printf("该元素的兄弟结点是%d %s\n", p->data.key, p->data.others);
            else
                printf("该元素无兄弟结点\n");
            getchar();
            getchar();
            break;
        case 9: // 删除结点
            printf("您想删除哪个位置的元素？\n");
            scanf("%d", &i);
            if (DeleteNode(Lists.elem[list_num - 1].T, i) == OK)
            {
                printf("该删除成功\n");
                PreOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
                InOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
            }
            else
                printf("删除操作失败\n");
            getchar();
            getchar();
            break;
        case 10: // 插入元素
            printf("请输入要插入的元素\n");
            scanf("%d %s", &temp_2.key, &temp_2.others);
            printf("请输入要插入的位置\n");
            scanf("%d", &i);
            printf("0:左孩子\n1:右孩子\n-1:根节点\n");
            scanf("%d", &temp);
            if (InsertNode(Lists.elem[list_num - 1].T, i, temp, temp_2) == OK)
            {
                printf("插入成功\n");
                PreOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
                InOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
            }
            else
                printf("插入失败\n");
            getchar();
            getchar();
            break;
        case 11: // 文件读写
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
                if (LoadBiTree(Lists.elem[Lists.length - 1].T, filename) == OK)
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
                if (SaveBiTree(Lists.elem[list_num - 1].T, filename) == OK)
                    printf("写入成功\n");
                else
                    printf("写入失败\n");
            }
            getchar();
            getchar();
            break;
        case 12: // 前序遍历
            PreOrderTraverse(Lists.elem[list_num - 1].T);
            printf("\n");
            getchar();
            getchar();
            break;
        case 13: // 中序遍历
            InOrderTraverse(Lists.elem[list_num - 1].T);
            printf("\n");
            getchar();
            getchar();
            break;
        case 15: // 多线性表管理：增加一个线性表
            printf("请输入新线性表名字\n");
            scanf("%s", firstname);
            if ((temp = LocateList(Lists, firstname)) > 0)
            {
                printf("有重复名称,无法创建\n");
                break;
            }
            AddList(Lists, firstname);
            printf("请问你想如何创建二叉树?\n关键字为0时,表示空子树,-1表示输入结束\n");
            get_definition(definition);
            if (CreateBiTree_pre(Lists.elem[Lists.length - 1].T, definition))
            {
                PreOrderTraverse(Lists.elem[Lists.length - 1].T);
                count++;
                printf("\n创建成功\n");
            }
            else
                printf("创建失败，有重复关键字\n");
            getchar();
            getchar();
            break;
        case 16: // 多线性表管理：移除线性表
            printf("请输入需要移除的线性表名字\n");
            scanf("%s", firstname);
            if (RemoveList(Lists, firstname) == OK)
                printf("移除成功\n");
            else
                printf("移除失败\n");
            getchar();
            getchar();
            break;
        case 17: // 多线性表管理：查找线性表
            printf("请输入需要查找的线性表名字\n");
            scanf("%s", firstname);
            if ((temp = LocateList(Lists, firstname)) == 0)
                printf("查找失败\n");
            else
                printf("查找成功,位置为%d\n", temp);
            getchar();
            getchar();
            break;
        case 14: // 后序遍历
            PostOrderTraverse(Lists.elem[list_num - 1].T);
            printf("\n");
            getchar();
            getchar();
            break;
        case 19: // 二叉树翻转
            if (InvertTree(Lists.elem[list_num - 1].T))
            {
                printf("反转成功,反转后的线性表为：\n");
                PreOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
                InOrderTraverse(Lists.elem[list_num - 1].T);
                printf("\n");
            }
            else
                printf("翻转失败");
            getchar();
            getchar();
            break;
        case 18: // 层序遍历
            LevelOrderTraverse(Lists.elem[list_num - 1].T);
            printf("\n");
            getchar();
            getchar();
            break;
        case 20: // 最大路径和
            result = 0;
            MaxPathSum(Lists.elem[list_num - 1].T, result);
            printf("最大路径和为%d\n", result);
            getchar();
            getchar();
            break;
        case 21: // show all lists
            printf("创建的线性表有：\n");
            for (int temp_2 = 0; temp_2 < Lists.length; temp_2++)
            {
                if (strcmp(Lists.elem[temp_2].name, "0") != 0)
                    printf("%s\n", Lists.elem[temp_2].name);
            }
            getchar();
            getchar();
            break;
        case 22: // 最近公共祖先
            printf("请输入要求的两个节点数据\n");
            scanf("%d %d", &temp, &i);
            BiTree t;
            t = LowestCommonAncestor(Lists.elem[list_num - 1].T, temp, i);
            if (t)
                printf("最近共同祖先是:%d", t->data.key);
            else
                printf("无法找到");
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
BiTree create_Node(TElemType definition)
{
    BiTree Node = (BiTree)malloc(sizeof(struct BiTNode));
    Node->data.key = definition.key;
    strcpy(Node->data.others, definition.others);
    Node->lchild = Node->rchild = NULL;
    return Node;
}
// file_using.h
status SaveBiTree(BiTree T, char FileName[])
{
    int i = 0;
    if (!T)
        return -1;
    FILE *fp = fopen(FileName, "wb");
    BiTree stack[100];
    TElemType definition[100];
    BiTree p = T;
    int top = 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p)
        {
            definition[i].key = p->data.key;
            strcpy(definition[i++].others, p->data.others);
        }
        else
        {
            definition[i].key = 0;
            strcpy(definition[i++].others, "null");
        }
        if (p)
        {
            stack[top++] = p->rchild;
        }
        if (p)
            stack[top++] = p->lchild;
    }
    fwrite(&i, sizeof(int), 1, fp);
    fwrite(&definition, sizeof(TElemType), i, fp);
    fclose(fp);
    return 1;
}
status LoadBiTree(BiTree &T, char FileName[])
// 读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    z = 0;
    FILE *fp = fopen(FileName, "rb");
    fread(&count_3, sizeof(int), 1, fp);
    TElemType definition[count_3];
    fread(&definition, sizeof(TElemType), count_3, fp);
    T = create_tree(definition);
    return 1;
    /********** End 2 **********/
}
BiTree create_tree(TElemType definition[])
{
    if (definition[z].key == 0)
    {
        z++;
        return NULL;
    }
    BiTree root = create_Node(definition[z]);
    if (z == count_3)
        return root;
    z++;
    root->lchild = create_tree(definition);
    root->rchild = create_tree(definition);
    return root;
}
// PreOrderTraverse.h
status PreOrderTraverse(BiTree T)
{
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return 1;
}
// PostOrderTraverse.h
status PostOrderTraverse(BiTree T)
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
    return 1;
}
// LocateNode.h
struct BiTNode *LocateNode(BiTree T, KeyType e)
{
    struct BiTNode *stack[100];
    struct BiTNode *p = T;
    int top = 0;
    if (T)
        stack[top++] = T;
    while (top)
    {
        p = stack[--top];
        if (p->data.key == e)
            return p;
        if (p->rchild != NULL)
            stack[top++] = p->rchild;
        if (p->lchild != NULL)
            stack[top++] = p->lchild;
    }
    return NULL;
}
// LevelOrderTraverse.h
status LevelOrderTraverse(BiTree T)
{
    BiTree queue[100];
    int front = 0, rear = 0;
    if (T)
        queue[rear++] = T;
    BiTree p = T;
    while (front != rear)
    {
        if (p->lchild)
            queue[rear++] = p->lchild;
        if (p->rchild)
            queue[rear++] = p->rchild;
        visit(p);
        p = queue[++front];
    }
    return 1;
}
// InsertNode.h
int list_treaverse(BiTree T, TElemType value)
{
    struct BiTNode *stack[100];
    BiTree p = T;
    int top = 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p->data.key == value.key)
            return 1;
        if (p->rchild)
            stack[top++] = p->rchild;
        if (p->lchild)
            stack[top++] = p->lchild;
    }
    return 0;
}
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
{
    if (list_treaverse(T, c))
        return 0;
    BiTree p;
    p = (BiTree)malloc(sizeof(struct BiTNode));
    p->data = c;
    if (LR == -1)
    {
        p->rchild = T;
        p->lchild = NULL;
        T = p;
        return 1;
    }
    struct BiTNode *stack[100];
    BiTree q = T;
    int top = 0;
    if (T)
        stack[top++] = q;
    while (top)
    {
        q = stack[--top];
        if (q->data.key == e)
        {
            if (LR == 0)
            {
                BiTree temp = q->lchild;
                q->lchild = p;
                p->rchild = temp;
                p->lchild = NULL;
            }
            else if (LR == 1)
            {
                BiTree temp = q->rchild;
                q->rchild = p;
                p->rchild = temp;
                p->lchild = NULL;
            }
            return 1;
        }
        if (q->rchild)
            stack[top++] = q->rchild;
        if (q->lchild)
            stack[top++] = q->lchild;
    }
    return 0;
}
// InOrderTraverse.h
status InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
    return 1;
}
// GetSibling.h
struct BiTNode *GetSibling(BiTree T, KeyType e)
{
    struct BiTNode *stack[100];
    BiTree p = T;
    int top = 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p->rchild != NULL && p->lchild != NULL && p->lchild->data.key == e)
            return p->rchild;
        if (p->lchild != NULL && p->rchild != NULL && p->rchild->data.key == e)
            return p->lchild;
        if (p->rchild)
            stack[top++] = p->rchild;
        if (p->lchild)
            stack[top++] = p->lchild;
    }
    return NULL;
}
// DestroyBiTree.h
status DestroyBiTree(BiTree &T)
{
    if (T)
    {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return 1;
}
// DeleteNode.h
void delete_right_node(BiTree &q, BiTree &p, KeyType e)
{
    BiTree temp = p;
    if (p->lchild == NULL && p->rchild == NULL)
    {
        q->rchild = NULL;
        free(p);
    }
    else if (p->lchild == NULL && p->rchild != NULL)
    {
        q->rchild = p->rchild;
        free(p);
    }
    else if (p->rchild == NULL && p->lchild != NULL)
    {
        q->rchild = p->lchild;
        free(p);
    }
    else if (p->lchild != NULL && p->rchild != NULL)
    {
        q->rchild = p->lchild;
        BiTree temp2 = p->rchild;
        BiTree t = p->lchild;
        free(p);
        while (t->rchild)
            t = t->rchild;
        t->rchild = temp2;
    }
}
void delete_left_node(BiTree &q, BiTree &p, KeyType e)
{
    BiTree temp = p;
    if (p->lchild == NULL && p->rchild == NULL)
    {
        q->lchild = NULL;
        free(p);
    }
    else if (p->lchild == NULL && p->rchild != NULL)
    {
        q->lchild = p->rchild;
        free(p);
    }
    else if (p->rchild == NULL && p->lchild != NULL)
    {
        q->lchild = p->lchild;
        free(p);
    }
    else if (p->lchild != NULL && p->rchild != NULL)
    {
        q->lchild = p->lchild;
        BiTree temp2 = p->rchild;
        BiTree t = p->lchild;
        free(p);
        while (t->rchild)
            t = t->rchild;
        t->rchild = temp2;
    }
}
status DeleteNode(BiTree &T, KeyType e)
{
    struct BiTNode *stack[100];
    BiTree p = T;
    if (p->data.key == e)
    {
        if (p->lchild == NULL && p->rchild == NULL)
            free(p);
        else if (p->lchild == NULL && p->rchild != NULL)
        {
            T = p->rchild;
            free(p);
        }
        else if (p->rchild == NULL && p->lchild != NULL)
        {
            T = p->lchild;
            free(p);
        }
        else if (p->lchild != NULL && p->rchild != NULL)
        {
            T = T->lchild;
            BiTree temp = p->rchild;
            struct BiTNode *temP_2 = p->lchild;
            free(p);
            while (temP_2->rchild)
                temP_2 = temP_2->rchild;
            temP_2->rchild = temp;
        }
        return 1;
    }
    int top = 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p->lchild != NULL && p->lchild->data.key == e)
        {
            delete_left_node(p, p->lchild, e);
            return 1;
        }
        if (p->rchild != NULL && p->rchild->data.key == e)
        {
            delete_right_node(p, p->rchild, e);
            return 1;
        }
        if (p->rchild)
            stack[top++] = p->rchild;
        if (p->lchild)
            stack[top++] = p->lchild;
    }
    return 0;
}
// ClearBiTree.h
status ClearBiTree(BiTree &T)
{
    if (T && (T->lchild || T->rchild))
    {
        ClearBiTree(T->lchild);
        ClearBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return 1;
}
// CreateBiTree_pre.h
int count_1 = 0;
BiTree create_tree_pre(TElemType definition[])
{
    if (definition[count_1].key == 0)
    {
        count_1++;
        return NULL;
    }
    BiTree root = create_Node(definition[count_1]);
    if (definition[count_1].key == -1)
        return root;
    count_1++;
    root->lchild = create_tree_pre(definition);
    root->rchild = create_tree_pre(definition);
    return root;
}
status CreateBiTree_pre(BiTree &T, TElemType definition[])
{
    count_1 = 0;
    int temp[200000] = {0};
    for (int i = 0; definition[i].key != -1; i++)
    {
        temp[definition[i].key]++;
        if (temp[definition[i].key] > 1 && definition[i].key != 0)
        {
            return 0;
        }
    }
    T = create_tree_pre(definition);
    return 1;
}
// BiTreeDepth.h
int BiTreeDepth(BiTree T)
{
    int leftdepth = 0, rightdepth = 0;
    if (T && T->lchild == NULL && T->rchild == NULL)
        return 1;
    else if (!T)
        return 0;
    else if (T->lchild || T->rchild)
    {
        if (T->lchild)
            leftdepth = BiTreeDepth(T->lchild);
        if (T->rchild)
            rightdepth = BiTreeDepth(T->rchild);
    }
    int result = 1 + (leftdepth > rightdepth ? leftdepth : rightdepth);
    return result;
}
// Assign.h
int list_treaverse(BiTree T, KeyType e, TElemType value)
{
    struct BiTNode *stack[100];
    BiTree p = T;
    int top = 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p->data.key == value.key && p->data.key != e)
            return 1;
        if (p->rchild)
            stack[top++] = p->rchild;
        if (p->lchild)
            stack[top++] = p->lchild;
    }
    return 0;
}
status Assign(BiTree &T, KeyType e, TElemType value)
{
    struct BiTNode *stack[100];
    BiTree p = T;
    int top = 0;
    if (list_treaverse(T, e, value))
        return 0;
    if (T)
        stack[top++] = p;
    while (top)
    {
        p = stack[--top];
        if (p->data.key == e)
        {
            p->data.key = value.key;
            strcpy(p->data.others, value.others);
            return 1;
        }
        if (p->rchild)
            stack[top++] = p->rchild;
        if (p->lchild)
            stack[top++] = p->lchild;
    }
    return 0;
}
// AddList.h
void AddList(LISTS &Lists, char ListName[])
{
    Lists.elem[Lists.length++].T = (BiTree)malloc(sizeof(struct BiTNode));
    Lists.elem[Lists.length - 1].T->lchild = NULL;
    Lists.elem[Lists.length - 1].T->rchild = NULL;
    strcpy(Lists.elem[Lists.length - 1].name, ListName);
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
            DestroyBiTree(Lists.elem[i].T);
            strcpy(Lists.elem[i].name, "0");
            return 1;
        }
    }
    return 0;
}
// reverseTree.h
status InvertTree(BiTree &T)
{
    if (T)
    {
        BiTree p = T->lchild;
        T->lchild = T->rchild;
        T->rchild = p;
        InvertTree(T->lchild);
        InvertTree(T->rchild);
    }
    return 1;
}
// get_definition.h
void get_definition(TElemType definition[])
{
    int i = 0;
    do
    {
        scanf("%d%s", &definition[i].key, definition[i].others);
    } while (definition[i++].key != -1);
    return;
}
// MaxPathSum.h
void travers(BiTree &p, int &result, int &temp_result)
{
    temp_result = temp_result + p->data.key;
    if (p->lchild == NULL && p->rchild == NULL)
    {
        result = temp_result > result ? temp_result : result;
    }
    if (p->lchild)
    {
        travers(p->lchild, result, temp_result);
        temp_result = temp_result - p->lchild->data.key;
    }
    if (p->rchild)
    {
        travers(p->rchild, result, temp_result);
        temp_result = temp_result - p->rchild->data.key;
    }
    return;
}
void MaxPathSum(BiTree &T, int &result)
{
    BiTree p = T;
    int temp_result = 0;
    travers(p, result, temp_result);
    return;
}
// LowestCommonAncestor.h
BiTree LowestCommonAncestor(BiTree &T, int p, int q)
{
    if (T == NULL)
        return NULL;
    if (T->data.key == p || T->data.key == q)
        return T;
    BiTree l = LowestCommonAncestor(T->lchild, p, q);
    BiTree r = LowestCommonAncestor(T->rchild, p, q);
    if (l && r)
        return T;
    else if (l && !r)
        return l;
    else if (!l && r)
        return r;
    else
        return NULL;
}