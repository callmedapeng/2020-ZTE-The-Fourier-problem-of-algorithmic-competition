#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "flexiblearray.h"
#include "misc.h"
#include "differdatasource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
***************************************************************************
本模块的主要作用是设计了FlexibleArray这种二维动态数组， 
FlexibleArray是可以设定列数，运行时可以追加行数的二维数组， 用于存储相应节点数的环路或单向路径。 
FlexibleArray的列数对应环路或单向路径节点数； 
FlexibleArray的行数对应相同节点数的环路数或单向路径数； 

**************************************************************************
*/

struct FlexibleArray route3_flexarry = { 0,3,NULL };	//用于存储全部的3节点路径（用于组合4节点环路） 
struct FlexibleArray route4_flexarry = { 0,4,NULL };	//用于存储全部的4节点路径（用于组合6节点环路） 
struct FlexibleArray route5_flexarry = { 0,5,NULL };	//用于存储全部的5节点路径（用于组合8节点环路） 
struct FlexibleArray route6_flexarry = { 0,6,NULL };	//用于存储全部的6节点路径（用于组合10节点环路） 
struct FlexibleArray route7_flexarry = { 0,7,NULL };	//用于存储全部的7节点路径（用于组合12节点环路） 
struct FlexibleArray route8_flexarry = { 0,8,NULL };	//用于存储全部的8节点路径（用于组合14节点环路） 
struct FlexibleArray cycle4combinedbyroute_flexarry = { 0,4,NULL };	//用于存储由路径组合得到的4节点环路
struct FlexibleArray cycle6combinedbyroute_flexarry = { 0,6,NULL };	//用于存储由路径组合得到的6节点环路
struct FlexibleArray cycle8combinedbyroute_flexarry = { 0,8,NULL };	//用于存储由路径组合得到的8节点环路
struct FlexibleArray cycle10combinedbyroute_flexarry = { 0,10,NULL };	//用于存储由路径组合得到的10节点环路
struct FlexibleArray cycle12combinedbyroute_flexarry = { 0,12,NULL };	//用于存储由路径组合得到的12节点环路
struct FlexibleArray cycle14combinedbyroute_flexarry = { 0,14,NULL };	//用于存储由路径组合得到的14节点环路



struct FlexibleArray col4_flexarry={0,4,NULL};			//用于存储包含重复路径的4节点环路 
struct FlexibleArray col4desame_flexarry={0,4,NULL};	//用于存储剔除掉重复路径的4节点环路 	


struct FlexibleArray col6_flexarry={0,6,NULL};//用于存储包含重复路径的6节点环路 
struct FlexibleArray col6desame_flexarry={0,6,NULL};//用于存储剔除掉重复路径的6节点环路 	


struct FlexibleArray col8_flexarry={0,8,NULL};//用于存储包含重复路径的8节点环路 
struct FlexibleArray col8desame_flexarry={0,8,NULL};//用于存储剔除掉重复路径的8节点环路


struct FlexibleArray col10_flexarry={0,10,NULL};//用于存储包含重复路径的10节点环路 
struct FlexibleArray col10desame_flexarry={0,10,NULL};//用于存储剔除掉重复路径的10节点环路


struct FlexibleArray col12_flexarry={0,12,NULL};//用于存储包含重复路径的12节点环路 
struct FlexibleArray col12desame_flexarry={0,12,NULL};//用于存储剔除掉重复路径的12节点环路


struct FlexibleArray col14_flexarry={0,14,NULL};//用于存储包含重复路径的14节点环路 
struct FlexibleArray col14desame_flexarry={0,14,NULL};//用于存储剔除掉重复路径的14节点环路


void FlexibleArrayAppend(struct FlexibleArray * FA,int * source)//向二维数组中追加一行数据
{
	FA->rowcount++;
	
	FA->data=(int**)realloc(FA->data,FA->rowcount*sizeof(int *));//行空间分配
	//if( !FA->data )
	//{
	//	printf("FlexibleArray row malloc error!\n");
	//	exit(0);
	//}
	
	FA->data[FA->rowcount-1]=(int *)calloc(FA->coltype,sizeof(int));//列空间分配
	//if( !FA->data[FA->rowcount-1] )
	//{
	//	printf("FlexibleArray col malloc error!\n");
	//	exit(0);
	//}

	
	//if( !source )//判断数据源是否有效
	//{
	//	printf("data source is blank!\n");
	//	exit(0);
	//}

	memcpy(FA->data[FA->rowcount - 1], source, sizeof(int)*FA->coltype);
}

void FlexibleArrayFree(struct FlexibleArray * FA)//释放FlexibleArray型数组的空间
{
	int i;
	if(! FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	for(i=0;i<FA->rowcount;i++)//释放FlexibleArray的列空间
	{
		free(FA->data[i]);
	}
	free(FA->data);//释放FlexibleArray的行空间
	
	FA->rowcount=0;//FlexibleArray行计数清零

}

void FlexibleArrayPrint(struct FlexibleArray * FA)// FlexibleArray二维数组数据打印
{
	int i,j;
	if( !FA->data )
	{
		printf("FlexibleArray is blank!\n");
		return;
	}
	
	printf("total row:%d total col:%d\n",FA->rowcount,FA->coltype);
	for(i=0;i<FA->rowcount;i++)
	{
		for(j=0;j<FA->coltype;j++)
		{
			printf("%d->",FA->data[i][j]);
		}
		
		printf("%d\n",FA->data[i][0]);		
			
	}


}

void FlexibleArrayPrint2Txt(struct FlexibleArray * FA,const char * filename)// 将FlexibleArray二维数组数据打印到文件
{
	int i, j;
	if (!FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	//char tempstr[10];
	//itoa(FA->coltype, tempstr, 10);
	//char filename[50] = "col";
	//strcat(filename, tempstr);
	//strcat(filename,"_flexiblearry.txt");

	FILE * fp = NULL;
	/*文件的打开*/
	fp = fopen(filename, "w");//fopen打开文件，这个文件可以是当前不存在的。“w”以写入的形式打开，“r”以读的形式打开，“a”追加模式写入

	fprintf(fp, "total row:%d total col:%d\n", FA->rowcount, FA->coltype);
	for (i = 0; i<FA->rowcount; i++)
	{
		for (j = 0; j<FA->coltype; j++)
		{
			fprintf(fp,"%d->", FA->data[i][j]);
		}

		fprintf(fp,"\n");

	}

	fclose(fp);

}

void FlexibleArrayPrintCycleCombinedByRoutes2Txt(struct FlexibleArray * FA, int go,int back)// 将由2条路径组合成的环路打印到文件
{
	int i, j;
	if (!FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	char tempstr[10];
	itoa(FA->coltype, tempstr, 10);
	char filename[50] = "col";
	strcat(filename, tempstr);
	strcat(filename,"_CycleCombinedByRoutes.txt");

	FILE * fp = NULL;
	/*文件的打开*/
	fp = fopen(filename, "a");//fopen打开文件，这个文件可以是当前不存在的。“w”以写入的形式打开，“r”以读的形式打开，“a”追加模式写入

		for (j = 0; j<FA->coltype; j++)
		{
			fprintf(fp, "%d->", FA->data[go][j]);
		}

		for (j = FA->coltype-2; j>=0; j--)
		{
			fprintf(fp, "%d->", FA->data[back][j]);
		}

		fprintf(fp, "\n");

	fclose(fp);

}

void FlexibleArrayAppendCycleCombinedByRoutes(struct FlexibleArray * FA, int go, int back)// 将由2条路径拼合成的环路保存到相应节点数的环路数组中
{
	if (FA->coltype == 3)
		FlexibleArrayAppendByTwoRoutes(&cycle4combinedbyroute_flexarry,FA->data[go],FA->data[back]);
	else if (FA->coltype == 4)
		FlexibleArrayAppendByTwoRoutes(&cycle6combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 5)
		FlexibleArrayAppendByTwoRoutes(&cycle8combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 6)
		FlexibleArrayAppendByTwoRoutes(&cycle10combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 7)
		FlexibleArrayAppendByTwoRoutes(&cycle12combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 8)
		FlexibleArrayAppendByTwoRoutes(&cycle14combinedbyroute_flexarry, FA->data[go], FA->data[back]);

}

void FlexibleArrayAppendByTwoRoutes(struct FlexibleArray * FA, int * go, int * back)//通过两条往返单向路径向环路数组中追加环路
{
	FA->rowcount++;
	FA->data = (int**)realloc(FA->data, FA->rowcount*sizeof(int *));//行空间分配
	FA->data[FA->rowcount - 1] = (int *)calloc(FA->coltype, sizeof(int));//列空间分配

	memcpy(FA->data[FA->rowcount - 1], go, sizeof(int)*(FA->coltype/2 + 1));
	memcpy(FA->data[FA->rowcount - 1]+(FA->coltype / 2 + 1), back+1, sizeof(int)*(FA->coltype / 2 - 1));

}



int compare(int * A,int * B,int len)//判断两个一维数组大小情况（大端模式），A==B返回0，A>B返回正数,A<B返回负数
{
	int i;
	int differflag=0;//先假设A,B数组相等 
	for(i=0;i<len;i++)//从高位到低位比较A,B 数组)(大端模式)
	{
		differflag =A[i]-B[i];
		if(differflag) 
		{
			return differflag;
		}
	}
	
	return differflag;  //A数组和B数组相等，返回0  
}


int CompareRouteStartAndEnd(int * A, int * B, int len)//根据起止点判断两单向路径的大小情况（大端模式），A==B返回0，A>B返回正数,A<B返回负数
{
	//int i;
	int differflag = 0;//先假设A,B数组相等 
	//for (i = 0;;)//比较A、B路径的起点和终点(大端模式)
	//{
	//	differflag = A[i] - B[i];
	//	if (differflag != 0)  //A路径比B路径大，返回大于0；A路径比B路径小，返回大于0， 
	//	{
	//		return differflag;
	//	}


	//	if (i == len - 1)
	//		break;
	//	i = len - 1;
	//}


	//比较A、B路径的起点和终点(大端模式)
	differflag = A[0] - B[0];
	if (differflag != 0)  //A路径比B路径大，返回大于0；A路径比B路径小，返回大于0， 
	{
		return differflag;
	}

	differflag = A[len - 1] - B[len - 1];
	if (differflag != 0)  //A路径比B路径大，返回大于0；A路径比B路径小，返回大于0， 
	{
		return differflag;
	}

	return differflag;  //A路径和B路径相等，返回0  

}

int CompareRouteMidWay(int * A, int * B, int len)//比较A、B两路径中途是否有重合点,有重合点返回1，否则返回0
{
//	int * content = (int *)calloc(unifyVertaxSizePort, sizeof(int));//辅助空间，用于比较2条路径中途是否有重合点，长度至少为节点总数，数组元素值初始化默认为0
	int  content[2700] = {0};//辅助空间，用于比较2条路径中途是否有重合点，长度至少为节点总数(1344+1344=2688)，数组元素值初始化默认为0
	int i,index;
//	int flag = 0;

	for (i = 1;i<(len-1);i++)//比较A、B路径的起点和终点(大端模式)
	{
		index = A[i];
		if (content[index] != 0) //说明此元素已经赋过值了，即发生了重复
		{
			return 1;
		}
		else
			content[index] = 1;    //做标志用,也可赋任何不为0的数


		index = B[i];
		if (content[index] != 0) //说明此元素已经赋过值了，即发生了重复
		{
			return 1;
		}
		else
			content[index] = 1;    //做标志用,也可赋任何不为0的数

	}
	
	//free(content);

	return 0;

}


int  test_CompareRouteStartAndEnd()
{
	int a[] = {6,2,3,5};
	int b[] = {6,2,3,5};
	printf("Size relation between a and b:%d\n", CompareRouteStartAndEnd(a, b, 4)); 

}

void test_CompareRouteMidWay()
{
	int a[] = {1,2,4,3,5};
	int b[] = {1,7,6,3,5};
	printf("Route a and b exist same point?:%d\n", CompareRouteMidWay(a, b, sizeof(a) / sizeof(a[0])));


}




void bubbleSort(int * arr,int len)//一维数组进行冒泡升序排列 
{
	int i,j,temp;
	int exchangeflag=1;
    for( i = 0; (i < len - 1 )&& exchangeflag; i++) {
    	exchangeflag=0;
        for( j = 0; j < len - 1 - i; j++) {
            if(arr[j] > arr[j+1]) {        // 相邻元素两两对比
            	exchangeflag=1;
                temp = arr[j+1];        // 元素交换
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void FlexibleArraySort(struct FlexibleArray * FA)//二维数组对每一行进行冒泡升序排序
{
	int i;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	
	for(i=0;i<FA->rowcount;i++)
	{
		bubbleSort(FA->data[i],FA->coltype);
	}
	

}

void FlexibleArrayWholeSort(struct FlexibleArray * FA)//对二维数组整体进行冒泡升序排序
{

	int i,j,flag;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	int * temp=NULL;
	int exchangeflag=1;
    for( i = 0; (i < FA->rowcount - 1)&&exchangeflag; i++) {
    	exchangeflag=0;
        for( j = 0; j < FA->rowcount - 1 - i; j++) {
			flag=compare(FA->data[j],FA->data[j+1],FA->coltype); // 相邻行数组两两对比
			if(flag>0) {
				exchangeflag=1;       
                temp = FA->data[j+1];        // 交换行数组
                FA->data[j+1] = FA->data[j];
                FA->data[j] = temp;
            }
        }
    }

}



/* 堆排序********************************** */
static void HeapAdjust(int *arr,int s,int m);

/*  对一维数组arr进行堆排序 */
void HeapSort(int *arr,int length)
{
	int i;
	for(i=(length-1)/2;i>=0;i--) /*  把arr构建成一个大根堆 */
		 HeapAdjust(arr,i,length-1);

	int temp;
	for(i=(length-1);i>=1;i--)
	{ 	
		temp=arr[i]; /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */
		arr[i]=arr[0];
		arr[0]=temp;
		
		 HeapAdjust(arr,0,i-1); /*  将arr[0..i-1]重新调整为大根堆 */
	}
}

/* 已知arr[s..m]中记录的关键字除arr[s]之外均满足堆的定义， */
/* 本函数调整arr[s]的关键字,使arr[s..m]成为一个大顶堆 */
void HeapAdjust(int *arr,int s,int m)
{ 
	int temp,j;
	temp=arr[s];
	for(j=2*s;j<=m;j*=2) /* 沿关键字较大的孩子结点向下筛选 */
	{
		if(j<m && arr[j]<arr[j+1])
			++j; /* j为关键字中较大的记录的下标 */
		if(temp>=arr[j])
			break; /* rc应插入在位置s上 */
		arr[s]=arr[j];
		s=j;
	}
	arr[s]=temp; /* 插入 */
}

/* **************************************** */

void test_heapsort()//测试堆排序 
{
	int d[6]={9,7,5,2,20,1};
	HeapSort(d,6);

}


void FlexibleArrayHeapSort(struct FlexibleArray * FA)//二维数组对每一行进行堆升序排序
{
	int i;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	
	for(i=0;i<FA->rowcount;i++)
	{
		HeapSort(FA->data[i],FA->coltype);
	}
	

}

static void FlexibleArrayWholeHeapAdjust(struct FlexibleArray * FA,int s,int m);

void FlexibleArrayWholeHeapSort(struct FlexibleArray * FA)//对二维数组整体进行堆升序排序
{

	int i;
	int * temp=NULL;	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	


	for(i=(FA->rowcount-1)/2;i>=0;i--) /*  把arr构建成一个大根堆 */
		 FlexibleArrayWholeHeapAdjust(FA,i,FA->rowcount-1);

	for(i=(FA->rowcount-1);i>=1;i--)
	{ 	
		temp=FA->data[i]; /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */
		FA->data[i]=FA->data[0];
		FA->data[0]=temp;
		
		FlexibleArrayWholeHeapAdjust(FA,0,i-1); /*  将arr[0..i-1]重新调整为大根堆 */
	}

}

/* 已知arr[s..m]中记录的关键字除arr[s]之外均满足堆的定义， */
/* 本函数调整arr[s]的关键字,使arr[s..m]成为一个大顶堆 */
void FlexibleArrayWholeHeapAdjust(struct FlexibleArray * FA,int s,int m)
{ 
	int j;
	int * temp;
	
	temp=FA->data[s];
	for(j=2*s;j<=m;j*=2) /* 沿关键字较大的孩子结点向下筛选 */
	{
		if(j<m && (compare(FA->data[j],FA->data[j+1],FA->coltype)<0) )
			++j; /* j为关键字中较大的记录的下标 */
		if( compare(temp, FA->data[j], FA->coltype)>=0)
			break; /* rc应插入在位置s上 */
		FA->data[s]=FA->data[j];
		s=j;
	}
	FA->data[s]=temp; /* 插入 */
}



int FlexibleArrayCountUnDuplicate(struct FlexibleArray * FA)//计算二维数组非重复行数
{

	if (FA->rowcount <= 1)
	return FA->rowcount;
	
	int start = 0;//基准位置
	int end = 1; //游标位置
	int count=1;//计数非重复行数 
	
	while (end < FA->rowcount)
	{
		if (compare(FA->data[start], FA->data[end], FA->coltype)==0)
		{
			end++;
		}
		else
		{
			count++;
			start=end;
			end++;
		}
	}
	return count;
}

int CountUnDuplicate(int * arr,int length)//计算一维数组非重复元素数量
{

	if (length <= 1)
		return length;

	int start = 0;//基准位置
	int end = 1; //游标位置
	int count = 0;//计数非重复行数 

	while (end < length)
	{
		if (arr[start]==arr[end])
		{
			if(end==length-1)
				count++;

			end++;
		}
		else 
		{
			count++;//do something
			start = end;

			if (end == length - 1)
				count++;
			end++;
		}
	}


	return count;
}

int FlexibleArrayCountRoute2Cycle(struct FlexibleArray *FA)//计算全部路径可以组合成环路的数量
{

	if (FA->rowcount <= 1)
		return 0;

	int start = 0;//基准位置
	int end = 1; //游标位置
	int count = 0; //计数全部路径可以组合成环路的数量

	while (end < FA->rowcount)
	{
		if ( CompareRouteStartAndEnd(FA->data[start],FA->data[end],FA->coltype)==0 )
		{
			if (end == FA->rowcount - 1)
			{
				count += CountValidCombination(FA, start, FA->rowcount);
				return count;
			}

			end++;
		}

		else
		{
			count += CountValidCombination(FA, start, end);
			start = end;
			//if (end == FA->rowcount - 1)
			//	count += CountValidCombination(FA, start, FA->rowcount);
			end++;
		}
	}


	return count;
}

int FlexibleArrayCountRoute2CycleUseGuard(struct FlexibleArray *FA)//计算全部单向路径可以组合成环路的数量(使用哨兵)，并将拼合得到的环路存入相应的环路数组
{

	if (FA->rowcount <= 1)
		return 0;

	int * guard =(int *)calloc(FA->coltype,sizeof(int));//向尾部存储全0的路径，作为哨兵
	FlexibleArrayAppend(FA, guard);
	free(guard);

	int start = 0;//基准位置
	int end = 1; //游标位置
	int count = 0; //计数全部路径可以组合成环路的数量

	while (end < FA->rowcount)
	{
		if (CompareRouteStartAndEnd(FA->data[start], FA->data[end], FA->coltype) == 0)
		{
			end++;
		}

		else
		{
			count += CountValidCombination(FA, start, end);
			start = end;
			end++;
		}
	}


	return count;
}


int CountValidCombination(struct FlexibleArray * FA,int start,int end)  //计算相同起止点的路径中可拼合成环路组合，并将拼合得到的环路存入相应环路数组
{
	//if (!FA)
	//{
	//	printf("the input FlexibleArray is blank");
	//	return 0;
	//}

	int i = 0, j = 0,count=0;
	if (end - start <= 1)
		return 0;
	else
	{
		for ( i = start; i < (end-1); i++)
		{
			for ( j = i+1; j < end; j++)
			{
				if (!CompareRouteMidWay(FA->data[i], FA->data[j], FA->coltype))
				{
					FlexibleArrayAppendCycleCombinedByRoutes(FA, i, j);
					count++;
				}
			}
		}
		return count;
	}

}

void test_CountUnDuplicate() {
	int a[] = {1,2,2,3,4,4,5,5,5};
	printf("UnDuplication members are :%d\n", CountUnDuplicate(a, sizeof(a) / sizeof(a[0])));

}







void FlexibleArrayRemoveSame(struct FlexibleArray * original,struct FlexibleArray * desame)//将二维数组中相同行剔除掉 
{
	if( !original->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}
	FlexibleArrayAppend(desame,original->data[0]);
	int i,j,differflag,differcount;
	for(i=1;i<original->rowcount;i++)
	{
		differcount=0;
		for(j=0;j<desame->rowcount;j++)
		{
			differflag=compare(original->data[i],desame->data[j],original->coltype);
			if(differflag)
			differcount++;
		}
		
		if(differcount==desame->rowcount)
		FlexibleArrayAppend(desame, original->data[i]);

	}

}

static void FlexibleArrayStartAndEndHeapAdjust(struct FlexibleArray * FA, int s, int m);

void FlexibleArrayStartAndEndHeapSort(struct FlexibleArray * FA)//根据起止点对存储的单向路径整体进行堆升序排序
{

	int i;
	int * temp = NULL;
	if (!FA->data)
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}


	for (i = (FA->rowcount - 1) / 2; i >= 0; i--) /*  把arr构建成一个大根堆 */
		FlexibleArrayStartAndEndHeapAdjust(FA, i, FA->rowcount - 1);

	for (i = (FA->rowcount - 1); i >= 1; i--)
	{
		temp = FA->data[i]; /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */
		FA->data[i] = FA->data[0];
		FA->data[0] = temp;

		FlexibleArrayStartAndEndHeapAdjust(FA, 0, i - 1); /*  将arr[0..i-1]重新调整为大根堆 */
	}

}

/* 已知arr[s..m]中记录的关键字除arr[s]之外均满足堆的定义， */
/* 本函数调整arr[s]的关键字,使arr[s..m]成为一个大顶堆 */
void FlexibleArrayStartAndEndHeapAdjust(struct FlexibleArray * FA, int s, int m)
{
	int j;
	int * temp;

	temp = FA->data[s];
	for (j = 2 * s; j <= m; j *= 2) /* 沿关键字较大的孩子结点向下筛选 */
	{
		if (j<m && (CompareRouteStartAndEnd(FA->data[j], FA->data[j + 1], FA->coltype)<0))
			++j; /* j为关键字中较大的记录的下标 */
		if (CompareRouteStartAndEnd(temp, FA->data[j], FA->coltype) >= 0)
			break; /* rc应插入在位置s上 */
		FA->data[s] = FA->data[j];
		s = j;
	}
	FA->data[s] = temp; /* 插入 */
}

























