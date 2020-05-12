#ifndef FLEXIBLE_ARRY_H
#define FLEXIBLE_ARRY_H
#include "misc.h"
/*
***************************************************************************
��ģ�����Ҫ�����������FlexibleArray���ֶ�ά��̬���飬
FlexibleArray�ǿ����趨����������ʱ����׷�������Ķ�ά���飬 ���ڴ洢��Ӧ�ڵ����Ļ�·����·����
FlexibleArray��������Ӧ��·����·���ڵ�����
FlexibleArray��������Ӧ��ͬ�ڵ����Ļ�·������·������

**************************************************************************
*/





struct FlexibleArray{
	int rowcount;//��������Ӧ���ٻ�· 
	int coltype;//��������Ӧ��·�ڵ��� 
	int ** data;//���ڴ洢��·�ڵ�����	
};

extern struct FlexibleArray route3_flexarry ;	//���ڴ洢ȫ����3�ڵ�·�����������4�ڵ㻷·�� 
extern struct FlexibleArray route4_flexarry ;	//���ڴ洢ȫ����4�ڵ�·�����������6�ڵ㻷·�� 
extern struct FlexibleArray route5_flexarry ;	//���ڴ洢ȫ����5�ڵ�·�����������8�ڵ㻷·�� 
extern struct FlexibleArray route6_flexarry ;	//���ڴ洢ȫ����6�ڵ�·�����������10�ڵ㻷·�� 
extern struct FlexibleArray route7_flexarry ;	//���ڴ洢ȫ����7�ڵ�·�����������12�ڵ㻷·�� 
extern struct FlexibleArray route8_flexarry ;	//���ڴ洢ȫ����8�ڵ�·�����������14�ڵ㻷·�� 

extern struct FlexibleArray cycle4combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���4�ڵ㻷·
extern struct FlexibleArray cycle6combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���6�ڵ㻷·
extern struct FlexibleArray cycle8combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���8�ڵ㻷·
extern struct FlexibleArray cycle10combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���10�ڵ㻷·
extern struct FlexibleArray cycle12combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���12�ڵ㻷·
extern struct FlexibleArray cycle14combinedbyroute_flexarry ;	//���ڴ洢��·����ϵõ���14�ڵ㻷·



extern struct FlexibleArray col4_flexarry;//���ڴ洢�����ظ�·����4�ڵ㻷· 
extern struct FlexibleArray col4desame_flexarry;//���ڴ洢�޳����ظ�·����4�ڵ㻷· 	

extern struct FlexibleArray col6_flexarry;//���ڴ洢�����ظ�·����6�ڵ㻷· 
extern struct FlexibleArray col6desame_flexarry;//���ڴ洢�޳����ظ�·����6�ڵ㻷· 

extern struct FlexibleArray col8_flexarry;//���ڴ洢�����ظ�·����8�ڵ㻷· 
extern struct FlexibleArray col8desame_flexarry;//���ڴ洢�޳����ظ�·����8�ڵ㻷· 

extern struct FlexibleArray col10_flexarry;//���ڴ洢�����ظ�·����10�ڵ㻷· 
extern struct FlexibleArray col10desame_flexarry;//���ڴ洢�޳����ظ�·����10�ڵ㻷· 


extern struct FlexibleArray col12_flexarry;//���ڴ洢�����ظ�·����12�ڵ㻷· 
extern struct FlexibleArray col12desame_flexarry;//���ڴ洢�޳����ظ�·����12�ڵ㻷· 

extern struct FlexibleArray col14_flexarry;//���ڴ洢�����ظ�·����14�ڵ㻷· 
extern struct FlexibleArray col14desame_flexarry;//���ڴ洢�޳����ظ�·����14�ڵ㻷· 



void FlexibleArrayAppend(struct FlexibleArray * FA,int * source);//���ά������׷��һ������
void FlexibleArrayAppendByTwoRoutes(struct FlexibleArray * FA, int * go, int * back);////ͨ��2����������·����·������׷�ӻ�·
void FlexibleArrayAppendCycleCombinedByRoutes(struct FlexibleArray * FA, int go, int back);//����2������·��ƴ�ϳɵĻ�·���浽��Ӧ�ڵ����Ļ�·����
void FlexibleArrayPrintCycleCombinedByRoutes2Txt(struct FlexibleArray * FA, int go, int back);//����2��·����ϳɵĻ�·��ӡ����Ӧ�ڵ����Ļ�·�ļ�

void FlexibleArrayFree(struct FlexibleArray * FA);//�ͷ�FlexibleArray������Ŀռ�
void FlexibleArrayPrint(struct FlexibleArray * FA);//�������ݴ�ӡ
void FlexibleArrayPrint2Txt(struct FlexibleArray * FA, const char * filename);// ��FlexibleArray��ά�������ݴ�ӡ���ļ�


int compare(int * A,int * B,int len);//�ж�����һά�����С��������ģʽ����A==B����0��A>B��������,A<B���ظ���
int CompareRouteStartAndEnd(int * A, int * B, int len);//������ֹ���ж�������·���Ĵ�С��������ģʽ����A==B����0��A>B��������,A<B���ظ���
int CompareRouteMidWay(int * A, int * B, int len);//�Ƚ�A��B������·����;�Ƿ����غϵ�,���غϵ㷵��1�����򷵻�0


void bubbleSort(int * arr,int len);//һά�������ð���������� 
void HeapSort(int *arr,int length);// ��һά������ж����� 

void FlexibleArraySort(struct FlexibleArray * FA);//��ά�����ÿһ�н���ð����������
void FlexibleArrayWholeSort(struct FlexibleArray * FA);//�Զ�ά�����������ð����������


void FlexibleArrayHeapSort(struct FlexibleArray * FA);//��ά�����ÿһ�н��ж���������
void FlexibleArrayWholeHeapSort(struct FlexibleArray * FA);//�Զ�ά����������ж���������
void FlexibleArrayStartAndEndHeapSort(struct FlexibleArray * FA);//������ֹ��Դ洢�ĵ���·��������ж���������

int FlexibleArrayCountRoute2Cycle(struct FlexibleArray *FA);//����ȫ������·��������ϳɻ�·������������ƴ�ϵõ��Ļ�·������Ӧ�Ļ�·����
int FlexibleArrayCountRoute2CycleUseGuard(struct FlexibleArray *FA);//����ȫ������·��������ϳɻ�·������(ʹ���ڱ�)������ƴ�ϵõ��Ļ�·������Ӧ�Ļ�·����
int CountValidCombination(struct FlexibleArray * FA, int start, int end);  //������ͬ��ֹ���·���п�ƴ�ϳɻ�·��ϣ�����ƴ�ϵõ��Ļ�·������Ӧ��·����





int FlexibleArrayCountUnDuplicate(struct FlexibleArray * FA);//�����ά������ظ�����
void FlexibleArrayRemoveSame(struct FlexibleArray * original,struct FlexibleArray * desame);//����ά��������ͬ���޳���  



#endif
