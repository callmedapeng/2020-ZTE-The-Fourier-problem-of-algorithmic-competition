#include "readcvs.h"
#include "misc.h"
/*
******************************************************************************
调用void findvalidnode(void )函数， 找出A,B部落的有效成员节点（连接度大于2的成员） ：
1.int * A_validnode=NULL;//保存A部落有效成员节点ID（连接度大于2的成员） 
2.int * B_validnode=NULL;//保存A部落有效成员节点ID（连接度大于2的成员）
**********************************************************************************
*/
int * A_validnode=NULL;//保存A部落有效成员节点（连接度大于2的成员） 
int * B_validnode=NULL;//保存A部落有效成员节点（连接度大于2的成员） 

void findvalidnode(void )
{
printf("finding validnode in A and B \n");
	int i,j;
	int temp;
	int Avalidcount=0;// A部落有效成员计数器 
	int Bvalidcount=0;	// B部落有效成员计数器 
	
	A_validnode=(int *)malloc((row+1) * sizeof(int));
	B_validnode=(int *)malloc((col+1) * sizeof(int));

	
	
	//行遍历 ，找出A部落节点连接大于等于2的成员 
	
	for(i=0;i<row;i++)
	{
		temp=0;
		for(j=0;j<col;j++)//计算A部落成员i的连接度 
		{
		temp+=data[i][j];			
		}	
			
		if (temp>=2)//连接度大于等于2的成员为有效成员 
		{
			A_validnode[Avalidcount]=i;
			Avalidcount++;
		}

	}

printf("Avalidcount is %d\n",Avalidcount);
for(i=0;i<Avalidcount;i++)
printf("%d\n",A_validnode[i]);
	

	//列遍历 ，找出B部落节点连接大于等于2的成员 	
	for(j=0;j<col;j++)
	{
		temp=0;
		for(i=0;i<row;i++)//计算B部落成员j的连接度 
		{
		temp+=data[i][j];			
		}	
			
		if (temp>=2)//连接度大于等于2的成员为有效成员 
		{
			B_validnode[Bvalidcount]=j;
			Bvalidcount++;
		}

	}	
printf("Bvalidcount is %d\n",Bvalidcount);	
for(j=0;j<Bvalidcount;j++)
printf("%d\n",B_validnode[j]);	
}
