#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// def.h
#define MAX_VERTEX_NUM 30
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} VertexType;
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;
typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
} ALGraph;
typedef struct
{
    struct
    {
        char name[30];
        ALGraph T;
    } elem[10];
    int length;
    int listsize;
} LISTS;
int CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
int DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
int PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
int InsertVex(ALGraph &G, VertexType v);
int DeleteVex(ALGraph &G, KeyType v);
int InsertArc(ALGraph &G, KeyType v, KeyType w);
int DeleteArc(ALGraph &G, KeyType v, KeyType w);
void DFS(ALGraph G, int v, int *visited);
int DFSTraverse(ALGraph G);
int BFSTraverse(ALGraph G);
void dfs_k(ALGraph G, int v, int k, int depth, int *visited);
int VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int AddList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
int RemoveList(LISTS &Lists, char ListName[]);
int ShortestPathLength(ALGraph G, KeyType u, KeyType v);
void dfs_conn(ALGraph G, int v, int *visited);
int ConnectedComponentsNums(ALGraph G);
int SaveGraph(ALGraph G, char FileName[]);
int LoadGraph(ALGraph &G, char FileName[]);

int main()
{
    LISTS Lists;
    Lists.length = 0;
    int op = 1;
    int i;
    int temp;
    int temp_2;
    int list_num = 1;
    int count = 0;
    char firstname[30];
    while (op)
    {
        char name_temp[30];
        printf("\n\n");
        printf("      Menu for non-Linear Table On Graph Structure \n");
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
        printf("    	  1. CreateGraph   11. file_using\n");
        printf("    	  2. DestroyGraph  12. DFSTraverse\n");
        printf("    	  3. LocateVex     13. BFSTraverse\n");
        printf("    	  4. PutVex        14. VerticesSetLessThanK\n");
        printf("    	  5. FirstAdjVex   15. AddList\n");
        printf("    	  6. NextAdjVex    16. RemoveList\n");
        printf("          7. InsertVex     17. LocateList\n");
        printf("          8. DeleteVex     18. ShortestPathLength\n");
        printf("          9. InsertArc     19. ConnectedComponentsNums\n");
        printf("          10. DeleteArc    20. ShowAllList\n\n");
        printf("          0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1: // 图的创建
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
            VertexType V[30];
            KeyType VR[100][2];
            i = 0;
            int j;
            printf("请输入节点信息\n");
            do
            {
                scanf("%d%s", &V[i].key, V[i].others);
            } while (V[i++].key != -1);
            printf("请输入边\n");
            i = 0;
            do
            {
                scanf("%d%d", &VR[i][0], &VR[i][1]);
            } while (VR[i++][0] != -1);
            if (CreateGraph(Lists.elem[Lists.length - 1].T, V, VR))
            {
                printf("创建成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
                count++;
            }
            else
                printf("创建失败，有重复关键字\n");
            getchar();
            getchar();
            break;
        case 2: // 销毁图
            if (DestroyGraph(Lists.elem[list_num - 1].T) == OK)
                printf("销毁图成功\n");
            getchar();
            getchar();
            break;
        case 3: // 查找顶点
            printf("请输入想要查找的顶点\n");
            scanf("%d", &i);
            if (!LocateVex(Lists.elem[list_num - 1].T, i))
                printf("查找失败\n");
            getchar();
            getchar();
            break;
        case 4: // 顶点赋值
            printf("请输入你想赋值的顶点\n");
            scanf("%d", &i);
            printf("请输入新值\n");
            VertexType value;
            scanf("%d%s", &value.key, value.others);
            if (PutVex(Lists.elem[list_num - 1].T, i, value))
            {
                printf("赋值成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
            }
            getchar();
            getchar();
            break;
        case 5: // 获得第一邻接点
            printf("请输入你想求的节点\n");
            scanf("%d", &i);
            if (FirstAdjVex(Lists.elem[Lists.length - 1].T, i) == -1)
                printf("查找失败");
            getchar();
            getchar();
            break;
        case 6: // 获得下一邻接点
            printf("请输入你想求的节点\n");
            scanf("%d", &i);
            printf("请输入该节点的邻接节点\n");
            scanf("%d", &temp_2);
            if (NextAdjVex(Lists.elem[Lists.length - 1].T, i, temp_2) == -1)
                printf("查找失败");
            getchar();
            getchar();
            break;
        case 7: // 插入顶点
            printf("请输入插入顶点信息\n");
            scanf("%d%s", &value.key, value.others);
            if (InsertVex(Lists.elem[Lists.length - 1].T, value))
            {
                printf("插入成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
            }
            else
                printf("操作失败\n");
            getchar();
            getchar();
            break;
        case 8: // 删除顶点
            printf("请输入你想删除的节点\n");
            scanf("%d", &i);
            if (DeleteVex(Lists.elem[Lists.length - 1].T, i))
            {
                printf("删除成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
            }
            else
                printf("操作失败\n");
            getchar();
            getchar();
            break;
        case 9: // 插入弧
            printf("请输入想插入的弧\n");
            scanf("%d %d", &i, &temp_2);
            if (InsertArc(Lists.elem[Lists.length - 1].T, i, temp_2))
            {
                printf("插入成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
            }
            else
                printf("操作失败\n");
            getchar();
            getchar();
            break;
        case 10: // 删除弧
            printf("请输入想删除的弧\n");
            scanf("%d %d", &i, &temp_2);
            if (DeleteArc(Lists.elem[Lists.length - 1].T, i, temp_2))
            {
                printf("删除成功\n");
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
            }
            else
                printf("操作失败\n");
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
                printf("请输入你想创建的图名称\n");
                scanf("%s", firstname);
                if ((temp = LocateList(Lists, firstname)) > 0)
                {
                    printf("有重复名称,无法创建\n");
                    break;
                }
                AddList(Lists, firstname);
                if (LoadGraph(Lists.elem[Lists.length - 1].T, filename) == OK)
                {
                    printf("读取成功\n");
                    for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                    {
                        ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                        printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                        while (p)
                        {
                            printf(" %d", p->adjvex);
                            p = p->nextarc;
                        }
                        printf("\n");
                    }
                    count++;
                }
                else
                    printf("读取失败\n");
            }
            else if (i == 2)
            {
                printf("请输入需要写入的文件地址,请用.dat作为后缀\n");
                scanf("%s", filename);
                if (SaveGraph(Lists.elem[list_num - 1].T, filename) == OK)
                    printf("写入成功\n");
                else
                    printf("写入失败\n");
            }
            getchar();
            getchar();
            break;
        case 12: // 深度优先搜索遍历
            DFSTraverse(Lists.elem[list_num - 1].T);
            printf("\n");
            getchar();
            getchar();
            break;
        case 13: // 广度优先搜索遍历
            BFSTraverse(Lists.elem[list_num - 1].T);
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
            printf("请输入节点信息\n");
            do
            {
                scanf("%d%s", &V[i].key, V[i].others);
            } while (V[i++].key != -1);
            printf("请输入边\n");
            i = 0;
            do
            {
                scanf("%d%d", &VR[i][0], &VR[i][1]);
            } while (VR[i++][0] != -1);
            if (CreateGraph(Lists.elem[Lists.length - 1].T, V, VR))
            {
                for (j = 0; j < Lists.elem[Lists.length - 1].T.vexnum; j++)
                {
                    ArcNode *p = Lists.elem[Lists.length - 1].T.vertices[j].firstarc;
                    printf("%d %s", Lists.elem[Lists.length - 1].T.vertices[j].data.key, Lists.elem[Lists.length - 1].T.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                    }
                    printf("\n");
                }
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
        case 14: // 距离小于k的顶点集合
            printf("请输入顶点\n");
            scanf("%d", &i);
            printf("请输入距离k\n");
            scanf("%d", &temp_2);
            VerticesSetLessThanK(Lists.elem[Lists.length - 1].T, i, temp_2);
            getchar();
            getchar();
            break;
        case 18: // 顶点间最短路径和长度
            printf("请输入两个顶点的信息\n");
            scanf("%d %d", &i, &temp_2);
            i = ShortestPathLength(Lists.elem[Lists.length - 1].T, i, temp_2);
            if (i != 1000 && i != -2)
                printf("最短路径为:%d", i);
            else if (i == -2)
                printf("无效节点\n");
            else
                printf("两点之间没有通路\n");
            getchar();
            getchar();
            break;
        case 19: // 图的连通分量
            i = ConnectedComponentsNums(Lists.elem[Lists.length - 1].T);
            printf("连通分量个数为:%d", i);
            getchar();
            getchar();
            break;
        case 20: // show all lists
            printf("创建的线性表有：\n");
            for (int temp_2 = 0; temp_2 < Lists.length; temp_2++)
            {
                if (strcmp(Lists.elem[temp_2].name, "0") != 0)
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

// CreateGraph.h
int CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    int i, j, k;
    G.vexnum = 0;
    G.arcnum = 0;
    // 录入顶点
    for (i = 0; V[i].key != -1; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == V[i].key)
                return 0; // 重复关键字
        }
        G.vertices[G.vexnum].data = V[i];
        G.vertices[G.vexnum].firstarc = NULL;
        G.vexnum++;
    }
    // 录入边
    for (i = 0; VR[i][0] != -1; i++)
    {
        int v = -1, w = -1;
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == VR[i][0])
                v = j;
            if (G.vertices[j].data.key == VR[i][1])
                w = j;
        }
        if (v == -1 || w == -1)
            continue;
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = w;
        p->nextarc = G.vertices[v].firstarc;
        G.vertices[v].firstarc = p;
        G.arcnum++;
    }
    return 1;
}

// DestroyGraph.h
int DestroyGraph(ALGraph &G)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            ArcNode *q = p;
            p = p->nextarc;
            free(q);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

// LocateVex.h
int LocateVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
            return i + 1;
    }
    return 0;
}

// PutVex.h
int PutVex(ALGraph &G, KeyType u, VertexType value)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
        {
            G.vertices[i].data = value;
            return 1;
        }
    }
    return 0;
}

// FirstAdjVex.h
int FirstAdjVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
        {
            if (G.vertices[i].firstarc)
                return G.vertices[i].firstarc->adjvex;
            else
                return -1;
        }
    }
    return -1;
}

// NextAdjVex.h
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    int i, j;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *p = G.vertices[i].firstarc;
            while (p)
            {
                if (G.vertices[p->adjvex].data.key == w)
                {
                    if (p->nextarc)
                        return p->nextarc->adjvex;
                    else
                        return -1;
                }
                p = p->nextarc;
            }
        }
    }
    return -1;
}

// InsertVex.h
int InsertVex(ALGraph &G, VertexType v)
{
    if (G.vexnum >= MAX_VERTEX_NUM)
        return 0;
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v.key)
            return 0;
    }
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return 1;
}

// DeleteVex.h
int DeleteVex(ALGraph &G, KeyType v)
{
    int i, j, k = -1;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
        return 0;
    // 删除以v为弧尾的弧
    ArcNode *p = G.vertices[k].firstarc;
    while (p)
    {
        ArcNode *q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--;
    }
    // 删除以v为弧头的弧
    for (i = 0; i < G.vexnum; i++)
    {
        if (i == k)
            continue;
        ArcNode *pre = NULL, *cur = G.vertices[i].firstarc;
        while (cur)
        {
            if (cur->adjvex == k)
            {
                if (pre)
                    pre->nextarc = cur->nextarc;
                else
                    G.vertices[i].firstarc = cur->nextarc;
                ArcNode *tmp = cur;
                cur = cur->nextarc;
                free(tmp);
                G.arcnum--;
            }
            else
            {
                if (cur->adjvex > k)
                    cur->adjvex--;
                pre = cur;
                cur = cur->nextarc;
            }
        }
    }
    // 顶点前移
    for (i = k; i < G.vexnum - 1; i++)
    {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;
    return 1;
}

// InsertArc.h
int InsertArc(ALGraph &G, KeyType v, KeyType w)
{
    int i = -1, j = -1, k;
    for (k = 0; k < G.vexnum; k++)
    {
        if (G.vertices[k].data.key == v)
            i = k;
        if (G.vertices[k].data.key == w)
            j = k;
    }
    if (i == -1 || j == -1)
        return 0;
    ArcNode *p = G.vertices[i].firstarc;
    while (p)
    {
        if (p->adjvex == j)
            return 0;
        p = p->nextarc;
    }
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = j;
    p->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = p;
    G.arcnum++;
    return 1;
}

// DeleteArc.h
int DeleteArc(ALGraph &G, KeyType v, KeyType w)
{
    int i = -1, j = -1, k;
    for (k = 0; k < G.vexnum; k++)
    {
        if (G.vertices[k].data.key == v)
            i = k;
        if (G.vertices[k].data.key == w)
            j = k;
    }
    if (i == -1 || j == -1)
        return 0;
    ArcNode *pre = NULL, *cur = G.vertices[i].firstarc;
    while (cur)
    {
        if (cur->adjvex == j)
        {
            if (pre)
                pre->nextarc = cur->nextarc;
            else
                G.vertices[i].firstarc = cur->nextarc;
            free(cur);
            G.arcnum--;
            return 1;
        }
        pre = cur;
        cur = cur->nextarc;
    }
    return 0;
}

// DFSTraverse.h
void DFS(ALGraph G, int v, int *visited)
{
    visited[v] = 1;
    printf("%d %s ", G.vertices[v].data.key, G.vertices[v].data.others);
    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex, visited);
        p = p->nextarc;
    }
}
int DFSTraverse(ALGraph G)
{
    int visited[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    return 1;
}

// BFSTraverse.h
int BFSTraverse(ALGraph G)
{
    int visited[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
            queue[rear++] = i;
            while (front < rear)
            {
                int v = queue[front++];
                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = 1;
                        printf("%d %s ", G.vertices[p->adjvex].data.key, G.vertices[p->adjvex].data.others);
                        queue[rear++] = p->adjvex;
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return 1;
}

// VerticesSetLessThanK.h
void dfs_k(ALGraph G, int v, int k, int depth, int *visited)
{
    if (depth > k)
        return;
    visited[v] = 1;
    printf("%d ", G.vertices[v].data.key);
    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        if (!visited[p->adjvex])
            dfs_k(G, p->adjvex, k, depth + 1, visited);
        p = p->nextarc;
    }
}
int VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    int i, start = -1;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            start = i;
            break;
        }
    }
    if (start == -1)
        return 0;
    int visited[MAX_VERTEX_NUM] = {0};
    dfs_k(G, start, k, 0, visited);
    return 1;
}

// AddList.h
int AddList(LISTS &Lists, char ListName[])
{
    if (Lists.length >= 10)
        return 0;
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].T.vexnum = 0;
    Lists.elem[Lists.length].T.arcnum = 0;
    Lists.length++;
    return 1;
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
int RemoveList(LISTS &Lists, char ListName[])
{
    int i, k = -1;
    for (i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
        return 0;
    for (i = k; i < Lists.length - 1; i++)
    {
        Lists.elem[i] = Lists.elem[i + 1];
    }
    Lists.length--;
    return 1;
}

// ShortestPathLength.h
int ShortestPathLength(ALGraph G, KeyType u, KeyType v)
{
    int start = -1, end = -1;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
            start = i;
        if (G.vertices[i].data.key == v)
            end = i;
    }
    if (start == -1 || end == -1)
        return -2;
    int dist[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++)
        dist[i] = 1000;
    dist[start] = 0;
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    queue[rear++] = start;
    while (front < rear)
    {
        int cur = queue[front++];
        ArcNode *p = G.vertices[cur].firstarc;
        while (p)
        {
            if (dist[p->adjvex] > dist[cur] + 1)
            {
                dist[p->adjvex] = dist[cur] + 1;
                queue[rear++] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
    if (dist[end] == 1000)
        return 1000;
    return dist[end];
}

// ConnectedComponentsNums.h
void dfs_conn(ALGraph G, int v, int *visited)
{
    visited[v] = 1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        if (!visited[p->adjvex])
            dfs_conn(G, p->adjvex, visited);
        p = p->nextarc;
    }
}
int ConnectedComponentsNums(ALGraph G)
{
    int visited[MAX_VERTEX_NUM] = {0};
    int count = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            dfs_conn(G, i, visited);
            count++;
        }
    }
    return count;
}

// SaveGraph.h
int SaveGraph(ALGraph G, char FileName[])
{
    FILE *fp = fopen(FileName, "w");
    if (!fp)
        return 0;
    fprintf(fp, "%d %d\n", G.vexnum, G.arcnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            fprintf(fp, "%d %d\n", G.vertices[i].data.key, G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
    }
    fclose(fp);
    return OK;
}

// LoadGraph.h
int LoadGraph(ALGraph &G, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
        return 0;
    int vexnum, arcnum;
    fscanf(fp, "%d %d", &vexnum, &arcnum);
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 0; i < vexnum; i++)
    {
        fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < arcnum; i++)
    {
        int v, w;
        fscanf(fp, "%d %d", &v, &w);
        int vi = -1, wi = -1;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == v)
                vi = j;
            if (G.vertices[j].data.key == w)
                wi = j;
        }
        if (vi == -1 || wi == -1)
            continue;
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = wi;
        p->nextarc = G.vertices[vi].firstarc;
        G.vertices[vi].firstarc = p;
    }
    fclose(fp);
    return OK;
}