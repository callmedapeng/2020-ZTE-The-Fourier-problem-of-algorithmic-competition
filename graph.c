#include <stdio.h>
#include <stdlib.h>
#include "readcvs.h"
#include "differdatasource.h"
#include "graph.h" 
#include "misc.h" 
#include "flexiblearray.h"
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


void MGraphInit(MGraph * g,int ** datasource,int vertextSize)  //初始化一个邻接矩阵型图
{
    g->vexnum = vertextSize;//设定节点数量
    g->edges = datasource;//分配邻接矩阵存储空间
 }

void freeMGraph(MGraph *g)//释放邻接矩阵型图的存储空间
{
	int i;
	for(i=0;i<g->vexnum;i++)//释放邻接矩阵的列空间
	{
		free(g->edges[i]);
	}
	free(g->edges);//释放邻接矩阵行空间
	g->vexnum=0;
	
}


void ALGraphInit(ALGraph * G,int vertextSize)  //初始化一个邻接表型图
{
		int i;
		G->vexnum=vertextSize;//设定节点数量
		
		G->adjlist=(VNode *)calloc(G->vexnum,sizeof(VNode));//分配邻接表存储空间
		for(i = 0;i<G->vexnum;i++)
		{		
            G->adjlist[i].firstarc= NULL;//邻接表中所有头节点的指针域置初值
        }
 } 
 

void MatToList(MGraph * g,ALGraph * G)//将邻接矩阵g转换成邻接表G
{	int i,j;
	ArcNode *p;
	ALGraphInit(G,g->vexnum);//初始化邻接表G	
	
	for (i=0;i<g->vexnum;i++)					//检查邻接矩阵中每个元素
		for (j=g->vexnum-1;j>=0;j--)
			if (g->edges[i][j]!=0)		//存在一条边
			{	p=(ArcNode *)malloc(sizeof(ArcNode));	//创建一个节点*p
				p->adjvex=j;  
				p->nextarc=G->adjlist[i].firstarc;		//采用头插法插入*p
				G->adjlist[i].firstarc=p;
			}
}


void DispMat(MGraph * g)//输出邻接矩阵g
{
	int i,j;
	for (i=0;i<g->vexnum;i++)
	{
		for (j=0;j<g->vexnum;j++)
			printf("%3d",g->edges[i][j]);
		printf("\n");
	}
}
void DispList(ALGraph *G)//输出邻接表G
{
	int i;
	ArcNode *p;
	for (i=0;i<G->vexnum;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%3d: ",i);
		while (p!=NULL)
		{
			printf("%3d",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}
//测试邻接矩阵到邻接表的转换 
void test_mat2list()
{
	MGraph g={NULL,0};
	ALGraph G={NULL,0};
	
	MGraphInit(&g,unifyAdjMatPort,unifyVertaxSizePort);
	
	
	printf(" 无向图的邻接矩阵:\n");
	DispMat(&g);
	
	
	printf(" 图G的邻接矩阵转换成邻接表:\n");
	MatToList(&g,&G);
	DispList(&G);
	
	system("pause");
}
 

static int* visitedFlag=NULL;//节点访问记录表
static int heap;//起始节点
static int innerStep = 0;//路径节点计数
static int isRecall;//回溯标志
static SequenceStack loop_stack;//路径序列栈
static int pop_value; 
 
/////////////////////遍历邻接表型图相关函数////////////////////////////////////////////////////////////////////////////////// 
int FirstNeighbor(ALGraph *G, int v)//寻找第一个邻接点 
{
	if (G->adjlist[v].firstarc== NULL)
		return -1;
	return  G->adjlist[v].firstarc->adjvex;
}
 
int NextNeighbor(ALGraph *G, int v, int w)//跳过节点w，寻找节点v的下一个邻接点 
{
	ArcNode *p = G->adjlist[v].firstarc;
	while (p && p->adjvex!=w){
		p = p->nextarc;
	}
	if (!p || !(p->nextarc))
		return -1;
		
	return p->nextarc->adjvex;
}  
 
void adjlistDFS(ALGraph *G,int startVertax)//DFS（start）从start节点出发探索没有访问过的节点（路口），没有走过的路径 
{
	setVisitedFlag(startVertax, 1);//标记start节点被访问 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//被访问的节点存入路径序列堆栈
	innerStep++;//路径节点数+1
	
	nextVertax = FirstNeighbor(G,startVertax);//寻找节点
	while(1) //keep looping 
	{
		if( nextVertax != -1 )//找到了一个节点
		{
			
			if(visitedFlag[nextVertax]==0)// 是未访问过的新节点 
			{
				
				if(innerStep<MAXDEEP)//没有达到允许搜索的最大深度，继续深入搜素 
				{
					adjlistDFS(G,nextVertax);//从新节点出发继续探索新节点、新路径 
					
					if( isRecall == 1 )
					{
					innerStep--;
					pop_stack(&loop_stack, &pop_value);
					setVisitedFlag(nextVertax, 0);//清除访问标记
					isRecall = 0;
					nextVertax = NextNeighbor(G,startVertax, nextVertax);//新节点可达的新路径被探索完，重新寻找新节点(路口)进行探索 
					continue;
					}					
				}
				else//达到最大允许搜素深度 ,不允许再继续探索新节点 
				{
					nextVertax = NextNeighbor(G,startVertax, nextVertax);//转向老节点继续寻找
					continue; 
				}		
					
			}
			
			else//是已经访问过的节点 
			{
				if(nextVertax == heap)//回到起点，构成有效环路 
				{

					if(innerStep==4||innerStep==6||innerStep==8||innerStep==10||innerStep==12||innerStep==14)//保存满足条件的环路 
					{
//						print_stack(loop_stack);
							
							if(innerStep==4)
								FlexibleArrayAppend(&col4_flexarry,loop_stack.base);							
							else if(innerStep==6)
								FlexibleArrayAppend(&col6_flexarry,loop_stack.base);							
							else if(innerStep==8)
								FlexibleArrayAppend(&col8_flexarry,loop_stack.base);							
							else if(innerStep==10)
								FlexibleArrayAppend(&col10_flexarry,loop_stack.base);
							else if(innerStep==12)
								FlexibleArrayAppend(&col12_flexarry,loop_stack.base);							
							else if(innerStep==14)
								FlexibleArrayAppend(&col14_flexarry,loop_stack.base);								
								
																				
						nextVertax = NextNeighbor(G,startVertax, nextVertax);
						continue;						
					} 
					else
					{
						nextVertax = NextNeighbor(G,startVertax, nextVertax);//重新寻找新节点(路口)进行探索
						continue; 					
					} 
					
				}
				
				else//回到路径中的其他节点，未构成有效环路 
				{
				nextVertax = NextNeighbor(G,startVertax, nextVertax);//重新寻找新节点(路口)进行探索
				continue; 						
					
				}
				
			}
			
		
		}
		else  //没有找到节点 
		{
			isRecall = 1;
			return;//返回上一层被调用点
		} 
	}
}


void adjlistDFSTraverse(ALGraph *G)//深度遍历
{
	initialVisitedFlagArray(G->vexnum);//节点访问记录表初始化 
	initializeSequenceStack(&loop_stack,G->vexnum);//路径节点序列栈初始化 
	for( heap=0; heap <row; heap++ )//遍历每个节点为起点所对应的简单环
	{
//		cleanallVisitedFlag(G->vexnum);//节点访问记录表清零

		if( visitedFlag[heap] == 0 )
		{
			printf("\n-------------------the cycle start and end with %d----------------\n", heap);
			//在搜索某个节点对应的所有环路前，完成一些初始化工作：1.节点访问记录表清空、2.路径序列栈清空、3.内部步数计数器清零、4.重进入标志清零。
			clear_stack(&loop_stack);
			innerStep = 0;
			isRecall = 0;
			adjlistDFS(G,heap);
		}
	}

	freeSequenceStack(&loop_stack);//释放路径节点序列栈空间 
	freeVisitedFlagArray();//释放节点访问记录表空间 

}

void test_list_dfs()//测试邻接表图深度遍历 
{

	MGraph g = { NULL,0 };//创建一张空的邻接矩阵型图 g 
	ALGraph G = { NULL,0 };//创建一张空的邻接表型图 G
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g, unifyAdjMatPort, unifyVertaxSizePort);//初始化创建的邻接矩阵型图g 
														 //	DispMat(&g);

	printf("Converting adjacency matrix graph to adjacency table graph\n");
	MatToList(&g, &G);
	//	DispList(&G);

	printf("Traversing simple cycles in adjacency table graph\n");
	adjlistDFSTraverse(&G);

	freeMGraph(&g);// 释放存储邻接矩阵的空间 

}



void adjlistDFSRoute(ALGraph *G, int startVertax)//DFS（start）从start节点出发探索没有访问过的节点（路口），没有走过的路径 
{
//	printVisitedVertax(startVertax);
	setVisitedFlag(startVertax, 1);//标记start节点被访问 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//被访问的节点存入路径序列堆栈
	innerStep++;//路径节点数+1

	if      (innerStep == 3)
		FlexibleArrayAppend(&route3_flexarry, loop_stack.base);
	else if (innerStep == 4)
		FlexibleArrayAppend(&route4_flexarry, loop_stack.base);
	else if (innerStep == 5)
		FlexibleArrayAppend(&route5_flexarry, loop_stack.base);
	else if (innerStep == 6)
		FlexibleArrayAppend(&route6_flexarry, loop_stack.base);
	else if (innerStep == 7)
		FlexibleArrayAppend(&route7_flexarry, loop_stack.base);
	else if (innerStep == 8)
		FlexibleArrayAppend(&route8_flexarry, loop_stack.base);

	if (innerStep >= MAXDEEP)//达到最大允许搜素深度 ,不允许再继续探索新节点 
	{
		//isRecall =1;
		return;
	}

	//没有达到允许搜索的最大深度，继续深入搜素 
	nextVertax = FirstNeighbor(G, startVertax);//寻找节点
	while (1) //keep looping 
	{
		if (nextVertax != -1)//找到了一个节点
		{

			if (visitedFlag[nextVertax] == 0)// 是未访问过的新节点 
			{

					adjlistDFSRoute(G, nextVertax);//从新节点出发继续探索新节点、新路径 

					//if (isRecall == 1)
					{
						innerStep--;
						pop_stack(&loop_stack, &pop_value);
						setVisitedFlag(nextVertax, 0);//清除访问标记
						//isRecall = 0;
						nextVertax = NextNeighbor(G, startVertax, nextVertax);//新节点可达的新路径被探索完，重新寻找新节点(路口)进行探索 
						continue;
					}
			}

			else//是已经访问过的节点 
			{
					nextVertax = NextNeighbor(G, startVertax, nextVertax);//重新寻找新节点(路口)进行探索
					continue;
			}

		}

		else  //没有找到节点 
		{
			//isRecall = 1;
			return;//返回上一层被调用点
		}

	}
}


void adjlistDFSTraverseRoute(ALGraph *G)//深度遍历
{
	initialVisitedFlagArray(G->vexnum);//节点访问记录表初始化 
	initializeSequenceStack(&loop_stack, G->vexnum);//路径节点序列栈初始化 
	for (heap = 0; heap <row; heap++)//遍历每个节点为起点所对应的简单环
	{
		//		cleanallVisitedFlag(G->vexnum);//节点访问记录表清零

		if (visitedFlag[heap] == 0)
		{
			printf("\n-------------------the route start at %d----------------\n", heap);
			//在搜索某个节点对应的所有环路前，完成一些初始化工作：1.节点访问记录表清空、2.路径序列栈清空、3.内部步数计数器清零、4.重进入标志清零。
			clear_stack(&loop_stack);
			innerStep = 0;
			//isRecall = 0;
			adjlistDFSRoute(G, heap);
		}
	}

	freeSequenceStack(&loop_stack);//释放路径节点序列栈空间 
	freeVisitedFlagArray();//释放节点访问记录表空间 

}



void test_list_dfs_route()//测试遍历邻接表型图中长度不超过MAXDEEP的路径
{
	MGraph g = { NULL,0 };//创建一张空的邻接矩阵型图 g 
	ALGraph G = { NULL,0 };//创建一张空的邻接表型图 G
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g, unifyAdjMatPort, unifyVertaxSizePort);//初始化创建的邻接矩阵型图g 
//	DispMat(&g);

	printf("Converting adjacency matrix graph to adjacency table graph\n");
	MatToList(&g, &G);
//	DispList(&G);

	printf("Traversing routes in adjacency table graph\n");
	adjlistDFSTraverseRoute(&G);

	freeMGraph(&g);// 释放存储邻接矩阵的空间 

}








/////////////////////遍历邻接矩阵型图相关函数//////////////////////////////////////////////////////////////////////////////////
int firstAdjacentVertax(MGraph *g,int vertaxID)//寻找第一个邻接点
{
	int i;
	for( i = 0; i <g->vexnum; i++ )
	{
		if( g->edges[vertaxID][i] == 1 )
			return i;
	}
	return -1;
}
int nextAdjacentVertax(MGraph *g,int vertaxID, int nextVertaxID)//跳过nextVertaxID，继续寻找下一个邻接点
{
	int i;
	for( i = nextVertaxID + 1; i <g->vexnum; i++ )
	{
		if(  g->edges[vertaxID][i] == 1 )
			return i;
	}
	return -1;
}


void adjmatDFS(MGraph *g,int startVertax)//DFS（start）从start节点出发探索没有访问过的节点（路口），没有走过的路径 
{
	setVisitedFlag(startVertax, 1);//标记start节点被访问 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//被访问的节点存入路径序列堆栈
	innerStep++;//路径节点数+1
	
	nextVertax = firstAdjacentVertax(g,startVertax);//寻找节点
	while(1) //keep looping 
	{
		if( nextVertax != -1 )//找到了一个节点
		{
			
			if(visitedFlag[nextVertax]==0)// 是未访问过的新节点 
			{
				
				if(innerStep<MAXDEEP)//没有达到允许搜索的最大深度，继续深入搜素 
				{
					adjmatDFS(g,nextVertax);//从新节点出发继续探索新节点、新路径 
					
					if( isRecall == 1 )
					{
					innerStep--;
					pop_stack(&loop_stack, &pop_value);
					setVisitedFlag(nextVertax, 0);//清除访问标记
					isRecall = 0;
					nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//新节点可达的新路径被探索完，重新寻找新节点(路口)进行探索 
					continue;
					}					
				}
				else//达到最大允许搜素深度 ,不允许再继续探索新节点 
				{
					nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//转向老节点继续寻找
					continue; 
				}		
					
			}
			
			else//是已经访问过的节点 
			{
				if(nextVertax == heap)//回到起点，构成有效环路 
				{

					if(innerStep==4||innerStep==6||innerStep==8||innerStep==10||innerStep==12||innerStep==14)//保存满足条件的环路 
					{
//						print_stack(loop_stack);
							
							if(innerStep==4)
								FlexibleArrayAppend(&col4_flexarry,loop_stack.base);							
							else if(innerStep==6)
								FlexibleArrayAppend(&col6_flexarry,loop_stack.base);							
							else if(innerStep==8)
								FlexibleArrayAppend(&col8_flexarry,loop_stack.base);							
							else if(innerStep==10)
								FlexibleArrayAppend(&col10_flexarry,loop_stack.base);
							else if(innerStep==12)
								FlexibleArrayAppend(&col12_flexarry,loop_stack.base);							
							else if(innerStep==14)
								FlexibleArrayAppend(&col14_flexarry,loop_stack.base);								
								
																				
						nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);
						continue;						
					} 
					else
					{
						nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//重新寻找新节点(路口)进行探索
						continue; 					
					} 
					
				}
				
				else//回到路径中的其他节点，未构成有效环路 
				{
				nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//重新寻找新节点(路口)进行探索
				continue; 						
					
				}
				
			}
			
		
		}
		else  //没有找到节点 
		{
			isRecall = 1;
			return;//返回上一层被调用点
		} 
	}
}


void adjmatDFSTraverse(MGraph *g)//深度遍历
{
	initialVisitedFlagArray(g->vexnum);//节点访问记录表初始化 
	initializeSequenceStack(&loop_stack,g->vexnum);//路径节点序列栈初始化 
	for( heap=0; heap <row; heap++ )//遍历每个节点为起点所对应的简单环
	{
//		cleanallVisitedFlag(g->vexnum);//节点访问记录表清零

		if( visitedFlag[heap] == 0 )
		{
			printf("\n-------------------the cycle start and end with %d----------------\n", heap);
			//在搜索某个节点对应的所有环路前，完成一些初始化工作：1.节点访问记录表清空、2.路径序列栈清空、3.内部步数计数器清零、4.重进入标志清零。
			clear_stack(&loop_stack);
			innerStep = 0;
			isRecall = 0;
			adjmatDFS(g,heap);
		}
	}

	freeSequenceStack(&loop_stack);//释放路径节点序列栈空间 
	freeVisitedFlagArray();//释放节点访问记录表空间 

}

void test_mat_dfs()//测试邻接矩阵图深度遍历 
{
	
	MGraph g={NULL,0};
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g,unifyAdjMatPort,unifyVertaxSizePort);
//	DispMat(&g);


	printf("Traversing simple cycles in adjacency matrix graph\n");
	adjmatDFSTraverse(&g);
	
	freeMGraph(&g);
}

//////////////////////////节点访问记录相关函数////////////////////////////////////////////////////////////////
void initialVisitedFlagArray(int vexnum)//初始化节点访问记录表
{
	visitedFlag = (int*)calloc(vexnum,sizeof(int));//节点访问记录表分配空间 
	if( !visitedFlag )
	{
		printf("visitedFlag* malloc error");
		exit(0);
	}
}

void freeVisitedFlagArray()//释放节点访问记录表存储空间
{
	free(visitedFlag);
} 


void cleanallVisitedFlag(int vexnum)//清除节点访问记录表
{
	int i;
	for( i = 0; i <vexnum; i++ )
		visitedFlag[i] = 0;
}

void printVisitedVertax(int vertaxID)//打印正在访问的节点
{
	printf("visited: %d \n", vertaxID);
}
void setVisitedFlag(int vertaxID, int value)//设置指定节点访问记录
{
	visitedFlag[vertaxID] = value;
}

//////////////////序列栈相关函数——基于空增栈////////////////////////////////////////////////////////////////////////////////
void initializeSequenceStack(SequenceStack* stack,int vexnum)//序列栈初始化
{
	stack->base = (int*)malloc(sizeof(int) * (vexnum));//最大环长度为vexnum，起点终点是同一点，只把起点存储到序列栈中
	if( !stack->base )
	{
		printf("Sequence stack malloc error!\n");
		exit(0);
	}
	stack->top = stack->base;
	stack->stackSize = vexnum;
}

void freeSequenceStack(SequenceStack* stack)//释放序列栈空间 
{
	if( !stack->base )
	{
		printf("Sequence stack is blank !\n");
		return;
	}
	free(stack->base);
	stack->top = stack->base;
	stack->stackSize = 0;
}


void pop_stack(SequenceStack* stack, int* value)//出栈  空增栈
{
	if( empty_stack(*stack) == 1 )
	{
		printf("stack is empty , can not to pop!\n");
		exit(0);
	}
	*value = *(--(stack->top));
}
void push_stack(SequenceStack* stack, int value)//入栈   空增栈 
{
	*(stack->top) = value;
	(stack->top)++;
}
int empty_stack(SequenceStack stack)//判断栈是否为空，空返回1，非空返回0
{
	return stack.top == stack.base ? 1 : 0;
}
void print_stack(SequenceStack stack)//打印序列栈
{
	printf("loop length:%d\t", innerStep);	
	int temp = *(stack.base);
	while( stack.top != stack.base )
	{
		printf("%d->", *((stack.base)++));
	}
	printf("%d\n", temp);
}
void clear_stack(SequenceStack* stack)//清空序列栈
{
	stack->top = stack->base;
}















