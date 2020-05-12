#include "readcvs.h"
/*
*******************************************************************************
*调用void cutlowdgree()函数，在原始数据的基础上剔除连接度为1的节点的连接 
**********************************************************************************
*/

int cutlowdgreecalledcount=0;
void cutlowdgree(void);
void cutlowdgree()//在原始数据的基础上剔除连接度为1的节点的连接  
{
	printf("the %d cycle cutlowdgree\n",++cutlowdgreecalledcount);
//	print_two_dimension(data, row, col);
	
	int rowcutcount=0;//行剪除计数 
	int rowcutflag=0;//行剪除标志 
	int colcutcount=0;//列剪除计数 
	int colcutflag=0;//列剪除计数 	
	
	
	//减除A部落低连接度的成员连接 
	int i,j;
	int temp=0;	
	for(i=0;i<row;i++)
	{
		rowcutflag=0;//假设当前行不需要剪除 
		temp=0;
		
		for(j=0;j<col;j++)//判断当前行是否需要进行剪除 
		{
		temp+=data[i][j];			
		}	
			
		if (temp==1)//temp==0 or >=2时都不需要剪除 
		{
			rowcutflag=1;
		}
		
		
		if (rowcutflag)//行清零 
		{
		printf("row %d cutting\n",i);
			for(j=0;j<col;j++)
				data[i][j]=0;	
		}
		
		rowcutcount+=rowcutflag;//行剪除计数 +1 
	}

	//减除B部落低连接度的成员连接 
	
	for(j=0;j<col;j++)
	{
		colcutflag=0;
		temp=0;
		
		for(i=0;i<row;i++)//判断当前列是否需要剪除 
		{	
		temp+=data[i][j];	 				
		}		
		
		if(temp==1) //temp==0 or >=2时都不需要剪除 
		{
		colcutflag=1;	
		}
		
		
		if (colcutflag)//列清零 
		{
			printf("col %d cutting\n",j);
			for(i=0;i<row;i++)
				data[i][j]=0;	
		}
		
		colcutcount+=colcutflag;
	}

	
	if (rowcutcount||colcutcount)//行列存在连接度减除，则继续进行低连接度减除 
		 cutlowdgree();
	
}
