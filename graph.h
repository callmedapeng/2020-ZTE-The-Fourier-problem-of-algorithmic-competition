#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
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

//���¶���ͼ���ڽӾ�������
typedef struct  				
{  	int ** edges; 		//�ڽӾ���
	int vexnum;   	//������������
} MGraph;						//ͼ���ڽӾ�������


//���¶���ͼ���ڽӱ�����
typedef struct ANode           	//�ߵĽڵ�ṹ����
{	int adjvex;              	//�ñߵ��յ�λ��
   	struct ANode *nextarc; 		//ָ����һ���ߵ�ָ��
} ArcNode;


typedef struct Vnode      		//�ڽӱ�ͷ�ڵ������
{
    ArcNode *firstarc;     		//ָ���һ����
} VNode;

typedef struct 
{	VNode * adjlist;         	//�ڽӱ�
    int vexnum;         //ͼ�ж�����
} ALGraph;                   	//ͼ���ڽӱ�����


void MGraphInit(MGraph * g,int ** datasource,int vertextSize); //��ʼ��һ���ڽӾ�����ͼ
void freeMGraph(MGraph *g);//�ͷ��ڽӾ�����ͼ�Ĵ洢�ռ�
void ALGraphInit(ALGraph * G,int vertextSize) ;//��ʼ��һ���ڽӱ���ͼ
void MatToList(MGraph * g,ALGraph * G);//���ڽӾ���gת�����ڽӱ�G
void DispMat(MGraph * g);//����ڽӾ���g
void DispList(ALGraph *G);//����ڽӱ�G
void test_mat2list();//�����ڽӾ����ڽӱ��ת�� 

typedef struct SequenceStack//·������ջ
{
	int* base;
	int* top;
	int stackSize;
}SequenceStack;



///////////////////�����ڽӱ���ͼ////////////////////////////////////////////////////////////////////////////////////////// 
int FirstNeighbor(ALGraph *G,int v); //v�ĵ�һ���ڽӵ��Ӧ��λ�����
int NextNeighbor(ALGraph *G, int v,int w); //��w������ڽӵ��λ�����
void adjlistDFS(ALGraph * G, int v);//�Ӷ���v�������ڽӱ�ͼ��ȱ��������ڱ�����· 
void adjlistDFSTraverse(ALGraph * G);//�����ڽӱ��ͼ��ȱ��� �����ڱ�����·
void test_list_dfs();////�����ڽӱ���ͼ�г��Ȳ�����MAXDEEP�����㳤��Ҫ���ȫ����·

void adjlistDFSRoute(ALGraph *G, int startVertax);//��start�ڵ����̽����·�������ڱ�������·��
void adjlistDFSTraverseRoute(ALGraph *G);//�����ڽӱ��ͼ��ȱ��������ڱ�������·��
void test_list_dfs_route();//�����ڽӱ���ͼ�г��Ȳ�����MAXDEEP�����㳤��Ҫ���ȫ������·��



////////////////�����ڽӾ�����ͼ/////////////////////////////////////////////////////////////////////////////
int firstAdjacentVertax(MGraph *g,int vertaxID);//Ѱ�ҵ�һ���ڽӵ�
int nextAdjacentVertax(MGraph *g,int vertaxID, int nextVertaxID);//����nextVertaxID������Ѱ����һ���ڽӵ�
void adjmatDFS(MGraph *g,int startVertax);//DFS��start����start�ڵ����̽��û�з��ʹ��Ľڵ㣨·�ڣ���û���߹���·�� 
void adjmatDFSTraverse(MGraph *g);//��ȱ���
void test_mat_dfs();//�����ڽӾ�����ͼ�г��Ȳ�����MAXDEEP�����㳤��Ҫ���ȫ����·


///////////////////////�ڵ���ʼ�¼����غ���////////////////////////////////////////////////
void initialVisitedFlagArray(int vexnum);//��ʼ���ڵ���ʼ�¼��
void freeVisitedFlagArray();//�ͷŽڵ���ʼ�¼��洢�ռ�
void cleanallVisitedFlag(int vexnum);//����ڵ���ʼ�¼��
void printVisitedVertax(int); 
void setVisitedFlag(int,int); 
 
 
////////////////////////����ջ��غ���///////////////////////////////////////////////////////////////// 
void initializeSequenceStack(SequenceStack* stack,int vexnum);//����ջ��ʼ��
void freeSequenceStack(SequenceStack* stack);//�ͷ�����ջ�ռ� 
void pop_stack(SequenceStack*, int*);
void push_stack(SequenceStack*, int);
void print_stack(SequenceStack);
int empty_stack(SequenceStack);
void clear_stack(SequenceStack*);
void test_stack();


































#endif

