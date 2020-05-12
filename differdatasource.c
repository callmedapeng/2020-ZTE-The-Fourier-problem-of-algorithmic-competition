#include <stdio.h>
#include <stdlib.h>
#include "misc.h"
#include "readcvs.h"
#include "differdatasource.h"
/*
**********************************************************
从文件中读出的原始数据保存在data动态数组中，中兴捧月比赛文件中给出的原始数据是非标准的邻接矩阵，编写的算法是针对标准邻接矩阵设计的，
为此需要将非标准的邻接矩阵转换保存为标准邻接矩阵。 
1.void  UnifyAdjMatFormat(void);函数判断当前的原始数据是否为标准邻接矩阵数据，
是标准数据，则将原始数据直接传递给统一的邻接矩阵接口unifyAdjMatPort和节点数接口unifyVertaxSizePort 
不是标准数据，则将原始数据转换后再传递给统一的邻接矩阵接口unifyAdjMatPort和节点数接口unifyVertaxSizePort  

2.统一的邻接矩阵接口unifyAdjMatPort

3.统一的节点数接口unifyVertaxSizePort  

4.void  UnifyAdjMatFormat(void);//将邻接数据统一为标准邻接数据形式 

**********************************************************
*/

int ** unifyAdjMatPort=NULL; //统一邻接矩阵格式接口 
int    unifyVertaxSizePort=0;//统一节点数接口 

void  UnifyAdjMatFormat(void) //将邻接数据统一为标准邻接矩阵形式 
{
	int i ,j;	
	if(FILESOURCE==1)//比赛数据格式，非标准邻接矩阵格式 
	{
		unifyVertaxSizePort=row+col;//非标准邻接矩阵，节点数等于行列之和 
		
	//创建统一格式的邻接矩阵	
		unifyAdjMatPort=(int**)calloc(unifyVertaxSizePort,sizeof(int *));//行空间分配
		if( !unifyAdjMatPort )
		{
			printf("unifyAdjMatPort row malloc error!\n");
			exit(0);
		}
		 
		for (i = 0; i < unifyVertaxSizePort; ++i) // 列空间分配 
		{
			unifyAdjMatPort[i] = (int *)calloc(unifyVertaxSizePort , sizeof(int));
		}

//存储A到B的邻接关系		
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
			{
			unifyAdjMatPort[i][row+j] =data[i][j];				
			}
		
//存储B到A的邻接关系		
		for(j=0;j<col;j++)
			for(i=0;i<row;i++)
			{
			unifyAdjMatPort[row+j][i] =data[i][j];				
			}		

	 //释放掉原始输入数据的空间 
		for(i=0;i<row;i++)//释放列空间 
		{
			free(data[i]);
		 } 
		free(data);//释放行空间 

		
	} 
	
	else//标准邻接矩阵格式 ，数据格式符合邻接矩阵要求，行列数相同且等于节点数 
	{
		unifyAdjMatPort=data;
		unifyVertaxSizePort=row;				
	}
	
	
}
