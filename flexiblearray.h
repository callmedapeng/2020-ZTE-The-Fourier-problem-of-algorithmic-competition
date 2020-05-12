#ifndef FLEXIBLE_ARRY_H
#define FLEXIBLE_ARRY_H
#include "misc.h"
/*
***************************************************************************
本模块的主要作用是设计了FlexibleArray这种二维动态数组，
FlexibleArray是可以设定列数，运行时可以追加行数的二维数组， 用于存储相应节点数的环路或单向路径。
FlexibleArray的列数对应环路或单向路径节点数；
FlexibleArray的行数对应相同节点数的环路数或单向路径数；

**************************************************************************
*/





struct FlexibleArray{
	int rowcount;//行数，对应多少环路 
	int coltype;//列数，对应环路节点数 
	int ** data;//用于存储环路节点数据	
};

extern struct FlexibleArray route3_flexarry ;	//用于存储全部的3节点路径（用于组合4节点环路） 
extern struct FlexibleArray route4_flexarry ;	//用于存储全部的4节点路径（用于组合6节点环路） 
extern struct FlexibleArray route5_flexarry ;	//用于存储全部的5节点路径（用于组合8节点环路） 
extern struct FlexibleArray route6_flexarry ;	//用于存储全部的6节点路径（用于组合10节点环路） 
extern struct FlexibleArray route7_flexarry ;	//用于存储全部的7节点路径（用于组合12节点环路） 
extern struct FlexibleArray route8_flexarry ;	//用于存储全部的8节点路径（用于组合14节点环路） 

extern struct FlexibleArray cycle4combinedbyroute_flexarry ;	//用于存储由路径组合得到的4节点环路
extern struct FlexibleArray cycle6combinedbyroute_flexarry ;	//用于存储由路径组合得到的6节点环路
extern struct FlexibleArray cycle8combinedbyroute_flexarry ;	//用于存储由路径组合得到的8节点环路
extern struct FlexibleArray cycle10combinedbyroute_flexarry ;	//用于存储由路径组合得到的10节点环路
extern struct FlexibleArray cycle12combinedbyroute_flexarry ;	//用于存储由路径组合得到的12节点环路
extern struct FlexibleArray cycle14combinedbyroute_flexarry ;	//用于存储由路径组合得到的14节点环路



extern struct FlexibleArray col4_flexarry;//用于存储包含重复路径的4节点环路 
extern struct FlexibleArray col4desame_flexarry;//用于存储剔除掉重复路径的4节点环路 	

extern struct FlexibleArray col6_flexarry;//用于存储包含重复路径的6节点环路 
extern struct FlexibleArray col6desame_flexarry;//用于存储剔除掉重复路径的6节点环路 

extern struct FlexibleArray col8_flexarry;//用于存储包含重复路径的8节点环路 
extern struct FlexibleArray col8desame_flexarry;//用于存储剔除掉重复路径的8节点环路 

extern struct FlexibleArray col10_flexarry;//用于存储包含重复路径的10节点环路 
extern struct FlexibleArray col10desame_flexarry;//用于存储剔除掉重复路径的10节点环路 


extern struct FlexibleArray col12_flexarry;//用于存储包含重复路径的12节点环路 
extern struct FlexibleArray col12desame_flexarry;//用于存储剔除掉重复路径的12节点环路 

extern struct FlexibleArray col14_flexarry;//用于存储包含重复路径的14节点环路 
extern struct FlexibleArray col14desame_flexarry;//用于存储剔除掉重复路径的14节点环路 



void FlexibleArrayAppend(struct FlexibleArray * FA,int * source);//向二维数组中追加一行数据
void FlexibleArrayAppendByTwoRoutes(struct FlexibleArray * FA, int * go, int * back);////通过2条往返单向路径向环路数组中追加环路
void FlexibleArrayAppendCycleCombinedByRoutes(struct FlexibleArray * FA, int go, int back);//将由2条单向路径拼合成的环路保存到相应节点数的环路数组
void FlexibleArrayPrintCycleCombinedByRoutes2Txt(struct FlexibleArray * FA, int go, int back);//将由2条路径组合成的环路打印到相应节点数的环路文件

void FlexibleArrayFree(struct FlexibleArray * FA);//释放FlexibleArray型数组的空间
void FlexibleArrayPrint(struct FlexibleArray * FA);//数组数据打印
void FlexibleArrayPrint2Txt(struct FlexibleArray * FA, const char * filename);// 将FlexibleArray二维数组数据打印到文件


int compare(int * A,int * B,int len);//判断两个一维数组大小情况（大端模式），A==B返回0，A>B返回正数,A<B返回负数
int CompareRouteStartAndEnd(int * A, int * B, int len);//根据起止点判断两单向路径的大小情况（大端模式），A==B返回0，A>B返回正数,A<B返回负数
int CompareRouteMidWay(int * A, int * B, int len);//比较A、B两单向路径中途是否有重合点,有重合点返回1，否则返回0


void bubbleSort(int * arr,int len);//一维数组进行冒泡升序排列 
void HeapSort(int *arr,int length);// 对一维数组进行堆排序 

void FlexibleArraySort(struct FlexibleArray * FA);//二维数组对每一行进行冒泡升序排序
void FlexibleArrayWholeSort(struct FlexibleArray * FA);//对二维数组整体进行冒泡升序排序


void FlexibleArrayHeapSort(struct FlexibleArray * FA);//二维数组对每一行进行堆升序排序
void FlexibleArrayWholeHeapSort(struct FlexibleArray * FA);//对二维数组整体进行堆升序排序
void FlexibleArrayStartAndEndHeapSort(struct FlexibleArray * FA);//根据起止点对存储的单向路径整体进行堆升序排序

int FlexibleArrayCountRoute2Cycle(struct FlexibleArray *FA);//计算全部单向路径可以组合成环路的数量，并将拼合得到的环路存入相应的环路数组
int FlexibleArrayCountRoute2CycleUseGuard(struct FlexibleArray *FA);//计算全部单向路径可以组合成环路的数量(使用哨兵)，并将拼合得到的环路存入相应的环路数组
int CountValidCombination(struct FlexibleArray * FA, int start, int end);  //计算相同起止点的路径中可拼合成环路组合，并将拼合得到的环路存入相应环路数组





int FlexibleArrayCountUnDuplicate(struct FlexibleArray * FA);//计算二维数组非重复行数
void FlexibleArrayRemoveSame(struct FlexibleArray * original,struct FlexibleArray * desame);//将二维数组中相同行剔除掉  



#endif
