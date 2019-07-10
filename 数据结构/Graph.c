// 没改完……算了
// 试写出一算法，根据依次输入的顶点数据，边的数目，各顶点的信息和各条边的信息，建立一个无向图的邻接表。打印输出该邻接表。

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef char VerTexType; // 顶点的数据类型
typedef int OtherInfo;   // 边的数据类型

typedef struct ArcNode
{
    OtherInfo info;          //顶点信息
    struct VNode *adjvex;    // 该边指向的顶点
    struct ArcNode *nextarc; // 下一条边
} * ArcNode;                 // 边节点

typedef struct VNode
{
    VerTexType data;          // 顶点储存的数据
    struct ArcNode *firstarc; // 指向第一条依附该顶点的边的指针
} * VNode;                    // 顶点

typedef struct VNodeWithArc
{
    VNode rear, head;
    ArcNode arc;
} * VNodeWithArc; // 顶点和边

typedef enum GraphType {
    UndirectedGraph, // 无向图
    DirectedGraph    // 有向图
} GraphType;

typedef struct Graph
{
    VNode *vertices;    //顶点数组
    int vexnum, arcnum; // 顶点数和边数
    GraphType type;
} * Graph;

typedef struct GraphEnumerator
{
    VNode rear;
    VNode *VNodeStack;
    ArcNode *ArcStack;
    int StackTop;
    int *visited;
    GraphType type;
    int OuterLeft;
} * GraphEnumerator;

Graph CreateGraph(GraphType gt);                          // 创建无向图
VNode *CreateNodeList(int vexnum);                        // 创建顶点数组
VNode CreateVNode(VerTexType data);                       // 创建顶点
ArcNode CreateArcNode(VNode node, OtherInfo info);        // 创建边
void CreateArcs(Graph graph, GraphType gt);               // 交互式获取边的信息并完成边的创建和链接
bool ArcExist(const Graph graph, VNode rear, VNode head); // 判断边是否存，起始的顶点叫尾，指向的顶点叫头
int LocaleVex(Graph graph, VerTexType value);             // 根据值获取顶点索引
VNode GetVNode(Graph graph, int index);                   // 根据索引获取顶点
void LinkArc(VNode vn, ArcNode an);                       // 把边插入图中
void DFSPrint(Graph graph, int index);                    // 深度优先遍历输出
void PrintGraph(Graph graph);                             // 普通遍历，非深度优先也非广度优先遍历
void ClearInput(void);                                    // 清除多余的输入

// 接口函数
VerTexType GetVerticeData(void);      // 获取顶点名称
OtherInfo GetArcInfo(void);           // 获取边的长度
wchar_t *VerTexToString(VNode vn);    // 把顶点名称转换为宽字符串
wchar_t *ArcInfoToString(ArcNode an); // 把边的长度转换为宽字符串

// 函数定义

Graph CreateGraph(GraphType gt)
{
    Graph graph = calloc(1, sizeof(struct Graph));

    wprintf(L"请输入顶点数：");
    scanf("%d", &graph->vexnum);
    wprintf(L"请输入边数：");
    scanf("%d", &graph->arcnum);

    printf("\n");
    wprintf(L"输入顶点储存的数据\n");
    graph->vertices = CreateNodeList(graph->vexnum);

    printf("\n");
    wprintf(L"输入无向边的邻接点\n");
    CreateArcs(graph, gt);

    return graph;
}

VNode *CreateNodeList(int vexnum)
{
    VNode *nl = calloc(vexnum, sizeof(VNode));

    for (int i = 0; i < vexnum; i++)
    {
        wprintf(L"第%d个顶点：", i + 1);
        nl[i] = CreateVNode(GetVerticeData());
    }

    return nl;
}

void CreateArcs(Graph graph, GraphType gt)
{
    int rear, head;
    OtherInfo info;

    for (int i = 0; i < graph->arcnum; i++)
    {

        wprintf(L"第%d条边：\n", i + 1);
        wprintf(L"第一个邻接点：");
        rear = LocaleVex(graph, GetVerticeData());
        if (rear == -1)
        {
            wprintf(L"该顶点不存在！\n：");
            i--;
            continue;
        }
        wprintf(L"第二个邻接点：");

        head = LocaleVex(graph, GetVerticeData());
        if (head == -1)
        {
            wprintf(L"该顶点不存在！\n：");
            i--;
            continue;
        }

        if (ArcExist(graph, GetVNode(graph, rear), GetVNode(graph, head)))
        {
            wprintf(L"这条边已经存在！\n：");
            i--;
            continue;
        }

        wprintf(L"边的长度：");
        info = GetArcInfo();

        LinkArc(GetVNode(graph, rear), CreateArcNode(GetVNode(graph, head), info));
        if (gt == UndirectedGraph) // 无向图
            LinkArc(GetVNode(graph, head), CreateArcNode(GetVNode(graph, rear), info));

        printf("\n");
    }
}

void LinkArc(VNode vn, ArcNode an)
{
    ArcNode tempan;

    if (vn->firstarc == NULL)
    {
        vn->firstarc = an;
        return;
    }
    else
        tempan = vn->firstarc;

    while (tempan->nextarc != NULL)
        tempan = tempan->nextarc;

    tempan->nextarc = an;
}

VNode CreateVNode(VerTexType data)
{
    VNode vn = calloc(1, sizeof(struct VNode));
    vn->data = data;
    return vn;
}

ArcNode CreateArcNode(VNode adjvex, OtherInfo info)
{
    ArcNode an = calloc(1, sizeof(struct ArcNode));
    an->adjvex = adjvex;
    an->info = info;
    return an;
}

bool ArcExist(const Graph graph, VNode rear, VNode head)
{
    for (ArcNode an = rear->firstarc; an != NULL; an = an->nextarc)
        if (an->adjvex == head)
            return true;

    return false;
}

int LocaleVex(Graph graph, VerTexType value)
{
    for (int i = 0; i < graph->vexnum; i++)
        if (graph->vertices[i]->data == value)
            return i;

    return -1;
}

VNode GetVNode(Graph graph, int index)
{
    if (index < 0)
    {
        wprintf(L"索引超出范围！\n：");
        system("pause");
        exit(0xffff);
    }

    if (graph == NULL)
        return NULL;
    else
        return graph->vertices[index];
}

void DFSPrint(Graph graph, int index) // 从index的节点开始遍历
{
    int needNewLine;             // 单个无边顶点或有边且遍历完后需要换行，已完全遍历过的无需换行
    static bool firstarc = true; // 指示是否需要空格
    static bool firstrun = true; // 初始化
    static int level = 0;        // 指示是否是最外层循环

    static bool *visited; // 指示是否遍历过

    if (firstrun)
    {
        wprintf(L"深度优先搜索遍历图：\n");
        visited = calloc(graph->vexnum, sizeof(bool));
        firstrun = false;
    }

    while (index < graph->vexnum)
    {
        if (visited[index] == false)
        {
            wprintf(L"%s", VerTexToString(GetVNode(graph, index))); // 输出单个无边顶点或第二个邻接点
            needNewLine = true;
        }
        visited[index] = true;

        for (ArcNode an = GetVNode(graph, index)->firstarc; an != NULL; an = an->nextarc) // 如果是单个无边顶点，不会进下面的此循环
        {
            needNewLine = false;
            int location = LocaleVex(graph, an->adjvex->data);

            if (graph->type == UndirectedGraph && visited[location] == false)
            {
                if (!firstarc) //非每行第一个输出则需要输出自己（第一个邻接点）并空格
                    wprintf(L"  %s", VerTexToString(GetVNode(graph, index)));
                wprintf(L"-[%s]-", ArcInfoToString(an)); // 输出边的长度
                level++;
                firstarc = false;
                needNewLine = true;
                DFSPrint(graph, location);
            }
        }

        if (level != 0)
        {
            level--;
            return;
        }
        else
        {
            if (needNewLine)
                printf("\n");
            index++;
            firstarc = true;
        }
    }
}

void PrintGraph(Graph graph)
{
    VNode *nl = graph->vertices;
    bool *visited = calloc(graph->vexnum, sizeof(bool));
    bool needNewLine;

    wprintf(L"普通遍历图：\n");
    for (int i = 0; i < graph->vexnum; i++)
    {
        needNewLine = false;
        if (nl[i]->firstarc == NULL && visited[i] == false)
        {
            wprintf(L"%s", VerTexToString(nl[i]));
            needNewLine = true;
        }

        visited[i] = true;

        for (ArcNode an = nl[i]->firstarc; an != NULL; an = an->nextarc)
        {
            int location = LocaleVex(graph, an->adjvex->data);
            if (graph->type == UndirectedGraph && !visited[location])
            {
                wprintf(L"%s-[%s]-%s  ", VerTexToString(nl[i]), ArcInfoToString(an), VerTexToString(an->adjvex));
                needNewLine = true;
                visited[location] = true;
            }
        }

        if (needNewLine)
            printf("\n");
    }
}

// 迭代器
GraphEnumerator CreateGraphEnumerator(Graph graph)
{
    GraphEnumerator enumerator = calloc(1, sizeof(struct GraphEnumerator));

    enumerator->rear = graph->vertices[0];

    enumerator->VNodeStack = calloc(graph->vexnum, sizeof(VNode));
    enumerator->ArcStack = calloc(graph->arcnum, sizeof(ArcNode));
    enumerator->StackTop = -1;

    enumerator->OuterLeft = graph->vexnum;
    enumerator->type = graph->type;
    enumerator->type == UndirectedGraph ? enumerator->visited = calloc(graph->vexnum, sizeof(int)) : NULL;

    return enumerator;
}

/*
0. 把顶点和边统一，使用enum加union,VNode rear不必要。
1. 初始化时把第一个顶点入两个栈
2. 进入DFS函数。退栈，获得的两个结构均为上一次输出的头顶点。
3. 进入循环，边移到下一个。如果不使用union，会发生无法判断是边往下移还是顶点的第一条边。或者这里也使用两条线判断？
4. 如果不为NULL，说明有边。如果是无序图且被访问过，继续循环；否则找到需要的东西，出循环。
5. 如果为NULL，说明边遍历完了。如果栈非空，退栈。
6. 如果栈为空，说明在最外层，顶点往下走，如果到底，返回NULL，否则继续循环，把走过的顶点赋给边。
7. 循环结束。顶点为尾，边为边，头为边指向的顶点。
8. 设置迭代器数据；如果是无向图，设置访问过的标记；两个栈均入边指向的顶点。
*/

VNodeWithArc DFS(GraphEnumerator enumerator)
{
    VNode rear = enumerator->rear;
    ArcNode an = rear->firstarc;
    VNodeWithArc vwa = calloc(1, sizeof(struct VNodeWithArc));

    if (an == NULL) // 栈顶节点没有边
    {
        if (enumerator->StackTop == -1)
        {
            enumerator->OuterLeft--;
            vwa->rear = enumerator->rear += 1;
            return vwa;
        }
        else
        {
            an = enumerator->ArcStack[enumerator->StackTop--];
            rear = enumerator->VNodeStack[enumerator->StackTop--];
            an = an->nextarc;
        }
    }

    // if(enumerator->type == UndirectedGraph && enumerator->visited[enumerator->OuterLeft] == true)

    vwa->rear = rear;
    vwa->arc = an;
    vwa->head = an->adjvex;

    enumerator->VNodeStack[++enumerator->StackTop] = rear;
    enumerator->ArcStack[++enumerator->StackTop] = an;

    return vwa;
}


// 实现接口函数

VerTexType GetVerticeData(void)
{
    VerTexType data;
    scanf("%c", &data);
    ClearInput();

    return data;
}

OtherInfo GetArcInfo(void)
{
    OtherInfo info;
    scanf("%d", &info);
    ClearInput();

    return info;
}

wchar_t *VerTexToString(VNode vn)
{
    const int BUFFERSIZE = 20;
    wchar_t *buffer = calloc(BUFFERSIZE, sizeof(wchar_t));

    // wcscpy(buffer, (wchar_t *)&vn->data);
    // wcscat(buffer, L"\0");

    buffer[0] = vn->data;
    buffer[1] = '\0';

    return buffer;
}

wchar_t *ArcInfoToString(ArcNode an)
{
    const int BUFFERSIZE = 20;
    wchar_t *buffer = calloc(BUFFERSIZE, sizeof(wchar_t));

    // char tempchar = an->info + '0';
    // wcscpy(buffer, (wchar_t *)&tempchar);

    buffer[0] = an->info + '0';
    buffer[1] = '\0';

    return buffer;
}

void ClearInput(void)
{
    while (getchar() != '\n')
        ;
}

int main(void)
{
    setlocale(LC_ALL, "chs");

    Graph graph = CreateGraph(UndirectedGraph);
    // DFSPrint(graph, 0);
    // printf("\n");
    PrintGraph(graph);

    system("pause");
    return 0;
}
