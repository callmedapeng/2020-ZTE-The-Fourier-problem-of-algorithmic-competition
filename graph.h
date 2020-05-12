#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
/*
***************************************
1.本模块给出图的2种实现方式：邻接矩阵型图 和  邻接表型图
2.针对2种类型的图，基于DFS深度遍历的思路，在不超过最大深度MAXDEEP的前提下，寻找并存储满足长度要求的全部环路（MAXDEEP在misc.h文件通过宏定义设置）
void test_list_dfs()//遍历邻接表型图中满足长度要求的全部环路
void test_mat_dfs()//遍历邻接矩阵型图中满足长度要求的全部环路


3.采用直接寻找环路的策略，当搜索12，14环时，由于环长过长，导致搜索速度变慢。
为此变换思路，采用搜索往返单向路径的方式，即如果2条单向路径起止点相同，且中途没有重合点，那么这2条路径可以组合成1条环路。
为此基于邻接表型图（遍历邻接表型图的速度比遍历邻接矩阵型图要快）,在不超过最大深度MAXDEEP的前提下，
寻找并存储满足长度要求的全部单向路径（MAXDEEP在misc.h文件通过宏定义设置）
void test_list_dfs_route()//遍历邻接表型图中长度不超过MAXDEEP且满足长度要求的全部单向路径
***************************************
*/

//以下定义图的邻接矩阵类型
typedef struct  				
{  	int ** edges; 		//邻接矩阵
	int vexnum;   	//顶点数，边数
} MGraph;						//图的邻接矩阵类型


//以下定义图的邻接表类型
typedef struct ANode           	//边的节点结构类型
{	int adjvex;              	//该边的终点位置
   	struct ANode *nextarc; 		//指向下一条边的指针
} ArcNode;


typedef struct Vnode      		//邻接表头节点的类型
{
    ArcNode *firstarc;     		//指向第一条边
} VNode;

typedef struct 
{	VNode * adjlist;         	//邻接表
    int vexnum;         //图中顶点数
} ALGraph;                   	//图的邻接表类型


void MGraphInit(MGraph * g,int ** datasource,int vertextSize); //初始化一个邻接矩阵型图
void freeMGraph(MGraph *g);//释放邻接矩阵型图的存储空间
void ALGraphInit(ALGraph * G,int vertextSize) ;//初始化一个邻接表型图
void MatToList(MGraph * g,ALGraph * G);//将邻接矩阵g转换成邻接表G
void DispMat(MGraph * g);//输出邻接矩阵g
void DispList(ALGraph *G);//输出邻接表G
void test_mat2list();//测试邻接矩阵到邻接表的转换 

typedef struct SequenceStack//路径序列栈
{
	int* base;
	int* top;
	int stackSize;
}SequenceStack;



///////////////////遍历邻接表型图////////////////////////////////////////////////////////////////////////////////////////// 
int FirstNeighbor(ALGraph *G,int v); //v的第一个邻接点对应的位置序号
int NextNeighbor(ALGraph *G, int v,int w); //除w以外的邻接点的位置序号
void adjlistDFS(ALGraph * G, int v);//从顶点v出发的邻接表图深度遍历，用于遍历环路 
void adjlistDFSTraverse(ALGraph * G);//基于邻接表的图深度遍历 ，用于遍历环路
void test_list_dfs();////遍历邻接表型图中长度不超过MAXDEEP且满足长度要求的全部环路

void adjlistDFSRoute(ALGraph *G, int startVertax);//从start节点出发探索新路径，用于遍历单向路径
void adjlistDFSTraverseRoute(ALGraph *G);//基于邻接表的图深度遍历，用于遍历单向路径
void test_list_dfs_route();//遍历邻接表型图中长度不超过MAXDEEP且满足长度要求的全部单向路径



////////////////遍历邻接矩阵型图/////////////////////////////////////////////////////////////////////////////
int firstAdjacentVertax(MGraph *g,int vertaxID);//寻找第一个邻接点
int nextAdjacentVertax(MGraph *g,int vertaxID, int nextVertaxID);//跳过nextVertaxID，继续寻找下一个邻接点
void adjmatDFS(MGraph *g,int startVertax);//DFS（start）从start节点出发探索没有访问过的节点（路口），没有走过的路径 
void adjmatDFSTraverse(MGraph *g);//深度遍历
void test_mat_dfs();//遍历邻接矩阵型图中长度不超过MAXDEEP且满足长度要求的全部环路


///////////////////////节点访问记录表相关函数////////////////////////////////////////////////
void initialVisitedFlagArray(int vexnum);//初始化节点访问记录表
void freeVisitedFlagArray();//释放节点访问记录表存储空间
void cleanallVisitedFlag(int vexnum);//清除节点访问记录表
void printVisitedVertax(int); 
void setVisitedFlag(int,int); 
 
 
////////////////////////序列栈相关函数///////////////////////////////////////////////////////////////// 
void initializeSequenceStack(SequenceStack* stack,int vexnum);//序列栈初始化
void freeSequenceStack(SequenceStack* stack);//释放序列栈空间 
void pop_stack(SequenceStack*, int*);
void push_stack(SequenceStack*, int);
void print_stack(SequenceStack);
int empty_stack(SequenceStack);
void clear_stack(SequenceStack*);
void test_stack();


































#endif

