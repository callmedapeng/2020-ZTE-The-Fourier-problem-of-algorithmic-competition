#include <stdio.h>
#include <stdlib.h>
#include "readcvs.h"
#include "differdatasource.h"
#include "graph.h" 
#include "misc.h" 
#include "flexiblearray.h"
/*
***************************************
1.��ģ�����ͼ��2��ʵ�ַ�ʽ���ڽӾ�����ͼ ��  �ڽӱ���ͼ
2.���2�����͵�ͼ������DFS��ȱ�����˼·���ڲ�����������MAXDEEP��ǰ���£�Ѱ�Ҳ��洢���㳤��Ҫ���ȫ����·��MAXDEEP��misc.h�ļ�ͨ���궨�����ã� 
void test_list_dfs()//�����ڽӱ���ͼ�����㳤��Ҫ���ȫ����·
void test_mat_dfs()//�����ڽӾ�����ͼ�����㳤��Ҫ���ȫ����·


3.����ֱ��Ѱ�һ�·�Ĳ��ԣ�������12��14��ʱ�����ڻ������������������ٶȱ�����
Ϊ�˱任˼·������������������·���ķ�ʽ�������2������·����ֹ����ͬ������;û���غϵ㣬��ô��2��·��������ϳ�1����·��
Ϊ�˻����ڽӱ���ͼ�������ڽӱ���ͼ���ٶȱȱ����ڽӾ�����ͼҪ�죩,�ڲ�����������MAXDEEP��ǰ���£�
Ѱ�Ҳ��洢���㳤��Ҫ���ȫ������·����MAXDEEP��misc.h�ļ�ͨ���궨�����ã�
void test_list_dfs_route()//�����ڽӱ���ͼ�г��Ȳ�����MAXDEEP�����㳤��Ҫ���ȫ������·��
***************************************
*/


void MGraphInit(MGraph * g,int ** datasource,int vertextSize)  //��ʼ��һ���ڽӾ�����ͼ
{
    g->vexnum = vertextSize;//�趨�ڵ�����
    g->edges = datasource;//�����ڽӾ���洢�ռ�
 }

void freeMGraph(MGraph *g)//�ͷ��ڽӾ�����ͼ�Ĵ洢�ռ�
{
	int i;
	for(i=0;i<g->vexnum;i++)//�ͷ��ڽӾ�����пռ�
	{
		free(g->edges[i]);
	}
	free(g->edges);//�ͷ��ڽӾ����пռ�
	g->vexnum=0;
	
}


void ALGraphInit(ALGraph * G,int vertextSize)  //��ʼ��һ���ڽӱ���ͼ
{
		int i;
		G->vexnum=vertextSize;//�趨�ڵ�����
		
		G->adjlist=(VNode *)calloc(G->vexnum,sizeof(VNode));//�����ڽӱ�洢�ռ�
		for(i = 0;i<G->vexnum;i++)
		{		
            G->adjlist[i].firstarc= NULL;//�ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
        }
 } 
 

void MatToList(MGraph * g,ALGraph * G)//���ڽӾ���gת�����ڽӱ�G
{	int i,j;
	ArcNode *p;
	ALGraphInit(G,g->vexnum);//��ʼ���ڽӱ�G	
	
	for (i=0;i<g->vexnum;i++)					//����ڽӾ�����ÿ��Ԫ��
		for (j=g->vexnum-1;j>=0;j--)
			if (g->edges[i][j]!=0)		//����һ����
			{	p=(ArcNode *)malloc(sizeof(ArcNode));	//����һ���ڵ�*p
				p->adjvex=j;  
				p->nextarc=G->adjlist[i].firstarc;		//����ͷ�巨����*p
				G->adjlist[i].firstarc=p;
			}
}


void DispMat(MGraph * g)//����ڽӾ���g
{
	int i,j;
	for (i=0;i<g->vexnum;i++)
	{
		for (j=0;j<g->vexnum;j++)
			printf("%3d",g->edges[i][j]);
		printf("\n");
	}
}
void DispList(ALGraph *G)//����ڽӱ�G
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
//�����ڽӾ����ڽӱ��ת�� 
void test_mat2list()
{
	MGraph g={NULL,0};
	ALGraph G={NULL,0};
	
	MGraphInit(&g,unifyAdjMatPort,unifyVertaxSizePort);
	
	
	printf(" ����ͼ���ڽӾ���:\n");
	DispMat(&g);
	
	
	printf(" ͼG���ڽӾ���ת�����ڽӱ�:\n");
	MatToList(&g,&G);
	DispList(&G);
	
	system("pause");
}
 

static int* visitedFlag=NULL;//�ڵ���ʼ�¼��
static int heap;//��ʼ�ڵ�
static int innerStep = 0;//·���ڵ����
static int isRecall;//���ݱ�־
static SequenceStack loop_stack;//·������ջ
static int pop_value; 
 
/////////////////////�����ڽӱ���ͼ��غ���////////////////////////////////////////////////////////////////////////////////// 
int FirstNeighbor(ALGraph *G, int v)//Ѱ�ҵ�һ���ڽӵ� 
{
	if (G->adjlist[v].firstarc== NULL)
		return -1;
	return  G->adjlist[v].firstarc->adjvex;
}
 
int NextNeighbor(ALGraph *G, int v, int w)//�����ڵ�w��Ѱ�ҽڵ�v����һ���ڽӵ� 
{
	ArcNode *p = G->adjlist[v].firstarc;
	while (p && p->adjvex!=w){
		p = p->nextarc;
	}
	if (!p || !(p->nextarc))
		return -1;
		
	return p->nextarc->adjvex;
}  
 
void adjlistDFS(ALGraph *G,int startVertax)//DFS��start����start�ڵ����̽��û�з��ʹ��Ľڵ㣨·�ڣ���û���߹���·�� 
{
	setVisitedFlag(startVertax, 1);//���start�ڵ㱻���� 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//�����ʵĽڵ����·�����ж�ջ
	innerStep++;//·���ڵ���+1
	
	nextVertax = FirstNeighbor(G,startVertax);//Ѱ�ҽڵ�
	while(1) //keep looping 
	{
		if( nextVertax != -1 )//�ҵ���һ���ڵ�
		{
			
			if(visitedFlag[nextVertax]==0)// ��δ���ʹ����½ڵ� 
			{
				
				if(innerStep<MAXDEEP)//û�дﵽ���������������ȣ������������� 
				{
					adjlistDFS(G,nextVertax);//���½ڵ��������̽���½ڵ㡢��·�� 
					
					if( isRecall == 1 )
					{
					innerStep--;
					pop_stack(&loop_stack, &pop_value);
					setVisitedFlag(nextVertax, 0);//������ʱ��
					isRecall = 0;
					nextVertax = NextNeighbor(G,startVertax, nextVertax);//�½ڵ�ɴ����·����̽���꣬����Ѱ���½ڵ�(·��)����̽�� 
					continue;
					}					
				}
				else//�ﵽ�������������� ,�������ټ���̽���½ڵ� 
				{
					nextVertax = NextNeighbor(G,startVertax, nextVertax);//ת���Ͻڵ����Ѱ��
					continue; 
				}		
					
			}
			
			else//���Ѿ����ʹ��Ľڵ� 
			{
				if(nextVertax == heap)//�ص���㣬������Ч��· 
				{

					if(innerStep==4||innerStep==6||innerStep==8||innerStep==10||innerStep==12||innerStep==14)//�������������Ļ�· 
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
						nextVertax = NextNeighbor(G,startVertax, nextVertax);//����Ѱ���½ڵ�(·��)����̽��
						continue; 					
					} 
					
				}
				
				else//�ص�·���е������ڵ㣬δ������Ч��· 
				{
				nextVertax = NextNeighbor(G,startVertax, nextVertax);//����Ѱ���½ڵ�(·��)����̽��
				continue; 						
					
				}
				
			}
			
		
		}
		else  //û���ҵ��ڵ� 
		{
			isRecall = 1;
			return;//������һ�㱻���õ�
		} 
	}
}


void adjlistDFSTraverse(ALGraph *G)//��ȱ���
{
	initialVisitedFlagArray(G->vexnum);//�ڵ���ʼ�¼���ʼ�� 
	initializeSequenceStack(&loop_stack,G->vexnum);//·���ڵ�����ջ��ʼ�� 
	for( heap=0; heap <row; heap++ )//����ÿ���ڵ�Ϊ�������Ӧ�ļ򵥻�
	{
//		cleanallVisitedFlag(G->vexnum);//�ڵ���ʼ�¼������

		if( visitedFlag[heap] == 0 )
		{
			printf("\n-------------------the cycle start and end with %d----------------\n", heap);
			//������ĳ���ڵ��Ӧ�����л�·ǰ�����һЩ��ʼ��������1.�ڵ���ʼ�¼����ա�2.·������ջ��ա�3.�ڲ��������������㡢4.�ؽ����־���㡣
			clear_stack(&loop_stack);
			innerStep = 0;
			isRecall = 0;
			adjlistDFS(G,heap);
		}
	}

	freeSequenceStack(&loop_stack);//�ͷ�·���ڵ�����ջ�ռ� 
	freeVisitedFlagArray();//�ͷŽڵ���ʼ�¼��ռ� 

}

void test_list_dfs()//�����ڽӱ�ͼ��ȱ��� 
{

	MGraph g = { NULL,0 };//����һ�ſյ��ڽӾ�����ͼ g 
	ALGraph G = { NULL,0 };//����һ�ſյ��ڽӱ���ͼ G
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g, unifyAdjMatPort, unifyVertaxSizePort);//��ʼ���������ڽӾ�����ͼg 
														 //	DispMat(&g);

	printf("Converting adjacency matrix graph to adjacency table graph\n");
	MatToList(&g, &G);
	//	DispList(&G);

	printf("Traversing simple cycles in adjacency table graph\n");
	adjlistDFSTraverse(&G);

	freeMGraph(&g);// �ͷŴ洢�ڽӾ���Ŀռ� 

}



void adjlistDFSRoute(ALGraph *G, int startVertax)//DFS��start����start�ڵ����̽��û�з��ʹ��Ľڵ㣨·�ڣ���û���߹���·�� 
{
//	printVisitedVertax(startVertax);
	setVisitedFlag(startVertax, 1);//���start�ڵ㱻���� 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//�����ʵĽڵ����·�����ж�ջ
	innerStep++;//·���ڵ���+1

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

	if (innerStep >= MAXDEEP)//�ﵽ�������������� ,�������ټ���̽���½ڵ� 
	{
		//isRecall =1;
		return;
	}

	//û�дﵽ���������������ȣ������������� 
	nextVertax = FirstNeighbor(G, startVertax);//Ѱ�ҽڵ�
	while (1) //keep looping 
	{
		if (nextVertax != -1)//�ҵ���һ���ڵ�
		{

			if (visitedFlag[nextVertax] == 0)// ��δ���ʹ����½ڵ� 
			{

					adjlistDFSRoute(G, nextVertax);//���½ڵ��������̽���½ڵ㡢��·�� 

					//if (isRecall == 1)
					{
						innerStep--;
						pop_stack(&loop_stack, &pop_value);
						setVisitedFlag(nextVertax, 0);//������ʱ��
						//isRecall = 0;
						nextVertax = NextNeighbor(G, startVertax, nextVertax);//�½ڵ�ɴ����·����̽���꣬����Ѱ���½ڵ�(·��)����̽�� 
						continue;
					}
			}

			else//���Ѿ����ʹ��Ľڵ� 
			{
					nextVertax = NextNeighbor(G, startVertax, nextVertax);//����Ѱ���½ڵ�(·��)����̽��
					continue;
			}

		}

		else  //û���ҵ��ڵ� 
		{
			//isRecall = 1;
			return;//������һ�㱻���õ�
		}

	}
}


void adjlistDFSTraverseRoute(ALGraph *G)//��ȱ���
{
	initialVisitedFlagArray(G->vexnum);//�ڵ���ʼ�¼���ʼ�� 
	initializeSequenceStack(&loop_stack, G->vexnum);//·���ڵ�����ջ��ʼ�� 
	for (heap = 0; heap <row; heap++)//����ÿ���ڵ�Ϊ�������Ӧ�ļ򵥻�
	{
		//		cleanallVisitedFlag(G->vexnum);//�ڵ���ʼ�¼������

		if (visitedFlag[heap] == 0)
		{
			printf("\n-------------------the route start at %d----------------\n", heap);
			//������ĳ���ڵ��Ӧ�����л�·ǰ�����һЩ��ʼ��������1.�ڵ���ʼ�¼����ա�2.·������ջ��ա�3.�ڲ��������������㡢4.�ؽ����־���㡣
			clear_stack(&loop_stack);
			innerStep = 0;
			//isRecall = 0;
			adjlistDFSRoute(G, heap);
		}
	}

	freeSequenceStack(&loop_stack);//�ͷ�·���ڵ�����ջ�ռ� 
	freeVisitedFlagArray();//�ͷŽڵ���ʼ�¼��ռ� 

}



void test_list_dfs_route()//���Ա����ڽӱ���ͼ�г��Ȳ�����MAXDEEP��·��
{
	MGraph g = { NULL,0 };//����һ�ſյ��ڽӾ�����ͼ g 
	ALGraph G = { NULL,0 };//����һ�ſյ��ڽӱ���ͼ G
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g, unifyAdjMatPort, unifyVertaxSizePort);//��ʼ���������ڽӾ�����ͼg 
//	DispMat(&g);

	printf("Converting adjacency matrix graph to adjacency table graph\n");
	MatToList(&g, &G);
//	DispList(&G);

	printf("Traversing routes in adjacency table graph\n");
	adjlistDFSTraverseRoute(&G);

	freeMGraph(&g);// �ͷŴ洢�ڽӾ���Ŀռ� 

}








/////////////////////�����ڽӾ�����ͼ��غ���//////////////////////////////////////////////////////////////////////////////////
int firstAdjacentVertax(MGraph *g,int vertaxID)//Ѱ�ҵ�һ���ڽӵ�
{
	int i;
	for( i = 0; i <g->vexnum; i++ )
	{
		if( g->edges[vertaxID][i] == 1 )
			return i;
	}
	return -1;
}
int nextAdjacentVertax(MGraph *g,int vertaxID, int nextVertaxID)//����nextVertaxID������Ѱ����һ���ڽӵ�
{
	int i;
	for( i = nextVertaxID + 1; i <g->vexnum; i++ )
	{
		if(  g->edges[vertaxID][i] == 1 )
			return i;
	}
	return -1;
}


void adjmatDFS(MGraph *g,int startVertax)//DFS��start����start�ڵ����̽��û�з��ʹ��Ľڵ㣨·�ڣ���û���߹���·�� 
{
	setVisitedFlag(startVertax, 1);//���start�ڵ㱻���� 
	int nextVertax;
	push_stack(&loop_stack, startVertax);//�����ʵĽڵ����·�����ж�ջ
	innerStep++;//·���ڵ���+1
	
	nextVertax = firstAdjacentVertax(g,startVertax);//Ѱ�ҽڵ�
	while(1) //keep looping 
	{
		if( nextVertax != -1 )//�ҵ���һ���ڵ�
		{
			
			if(visitedFlag[nextVertax]==0)// ��δ���ʹ����½ڵ� 
			{
				
				if(innerStep<MAXDEEP)//û�дﵽ���������������ȣ������������� 
				{
					adjmatDFS(g,nextVertax);//���½ڵ��������̽���½ڵ㡢��·�� 
					
					if( isRecall == 1 )
					{
					innerStep--;
					pop_stack(&loop_stack, &pop_value);
					setVisitedFlag(nextVertax, 0);//������ʱ��
					isRecall = 0;
					nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//�½ڵ�ɴ����·����̽���꣬����Ѱ���½ڵ�(·��)����̽�� 
					continue;
					}					
				}
				else//�ﵽ�������������� ,�������ټ���̽���½ڵ� 
				{
					nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//ת���Ͻڵ����Ѱ��
					continue; 
				}		
					
			}
			
			else//���Ѿ����ʹ��Ľڵ� 
			{
				if(nextVertax == heap)//�ص���㣬������Ч��· 
				{

					if(innerStep==4||innerStep==6||innerStep==8||innerStep==10||innerStep==12||innerStep==14)//�������������Ļ�· 
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
						nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//����Ѱ���½ڵ�(·��)����̽��
						continue; 					
					} 
					
				}
				
				else//�ص�·���е������ڵ㣬δ������Ч��· 
				{
				nextVertax = nextAdjacentVertax(g,startVertax, nextVertax);//����Ѱ���½ڵ�(·��)����̽��
				continue; 						
					
				}
				
			}
			
		
		}
		else  //û���ҵ��ڵ� 
		{
			isRecall = 1;
			return;//������һ�㱻���õ�
		} 
	}
}


void adjmatDFSTraverse(MGraph *g)//��ȱ���
{
	initialVisitedFlagArray(g->vexnum);//�ڵ���ʼ�¼���ʼ�� 
	initializeSequenceStack(&loop_stack,g->vexnum);//·���ڵ�����ջ��ʼ�� 
	for( heap=0; heap <row; heap++ )//����ÿ���ڵ�Ϊ�������Ӧ�ļ򵥻�
	{
//		cleanallVisitedFlag(g->vexnum);//�ڵ���ʼ�¼������

		if( visitedFlag[heap] == 0 )
		{
			printf("\n-------------------the cycle start and end with %d----------------\n", heap);
			//������ĳ���ڵ��Ӧ�����л�·ǰ�����һЩ��ʼ��������1.�ڵ���ʼ�¼����ա�2.·������ջ��ա�3.�ڲ��������������㡢4.�ؽ����־���㡣
			clear_stack(&loop_stack);
			innerStep = 0;
			isRecall = 0;
			adjmatDFS(g,heap);
		}
	}

	freeSequenceStack(&loop_stack);//�ͷ�·���ڵ�����ջ�ռ� 
	freeVisitedFlagArray();//�ͷŽڵ���ʼ�¼��ռ� 

}

void test_mat_dfs()//�����ڽӾ���ͼ��ȱ��� 
{
	
	MGraph g={NULL,0};
	printf("Initializing adjacency matrix graph\n");
	MGraphInit(&g,unifyAdjMatPort,unifyVertaxSizePort);
//	DispMat(&g);


	printf("Traversing simple cycles in adjacency matrix graph\n");
	adjmatDFSTraverse(&g);
	
	freeMGraph(&g);
}

//////////////////////////�ڵ���ʼ�¼��غ���////////////////////////////////////////////////////////////////
void initialVisitedFlagArray(int vexnum)//��ʼ���ڵ���ʼ�¼��
{
	visitedFlag = (int*)calloc(vexnum,sizeof(int));//�ڵ���ʼ�¼�����ռ� 
	if( !visitedFlag )
	{
		printf("visitedFlag* malloc error");
		exit(0);
	}
}

void freeVisitedFlagArray()//�ͷŽڵ���ʼ�¼��洢�ռ�
{
	free(visitedFlag);
} 


void cleanallVisitedFlag(int vexnum)//����ڵ���ʼ�¼��
{
	int i;
	for( i = 0; i <vexnum; i++ )
		visitedFlag[i] = 0;
}

void printVisitedVertax(int vertaxID)//��ӡ���ڷ��ʵĽڵ�
{
	printf("visited: %d \n", vertaxID);
}
void setVisitedFlag(int vertaxID, int value)//����ָ���ڵ���ʼ�¼
{
	visitedFlag[vertaxID] = value;
}

//////////////////����ջ��غ����������ڿ���ջ////////////////////////////////////////////////////////////////////////////////
void initializeSequenceStack(SequenceStack* stack,int vexnum)//����ջ��ʼ��
{
	stack->base = (int*)malloc(sizeof(int) * (vexnum));//��󻷳���Ϊvexnum������յ���ͬһ�㣬ֻ�����洢������ջ��
	if( !stack->base )
	{
		printf("Sequence stack malloc error!\n");
		exit(0);
	}
	stack->top = stack->base;
	stack->stackSize = vexnum;
}

void freeSequenceStack(SequenceStack* stack)//�ͷ�����ջ�ռ� 
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


void pop_stack(SequenceStack* stack, int* value)//��ջ  ����ջ
{
	if( empty_stack(*stack) == 1 )
	{
		printf("stack is empty , can not to pop!\n");
		exit(0);
	}
	*value = *(--(stack->top));
}
void push_stack(SequenceStack* stack, int value)//��ջ   ����ջ 
{
	*(stack->top) = value;
	(stack->top)++;
}
int empty_stack(SequenceStack stack)//�ж�ջ�Ƿ�Ϊ�գ��շ���1���ǿշ���0
{
	return stack.top == stack.base ? 1 : 0;
}
void print_stack(SequenceStack stack)//��ӡ����ջ
{
	printf("loop length:%d\t", innerStep);	
	int temp = *(stack.base);
	while( stack.top != stack.base )
	{
		printf("%d->", *((stack.base)++));
	}
	printf("%d\n", temp);
}
void clear_stack(SequenceStack* stack)//�������ջ
{
	stack->top = stack->base;
}















