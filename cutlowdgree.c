#include "readcvs.h"
/*
*******************************************************************************
*����void cutlowdgree()��������ԭʼ���ݵĻ������޳����Ӷ�Ϊ1�Ľڵ������ 
**********************************************************************************
*/

int cutlowdgreecalledcount=0;
void cutlowdgree(void);
void cutlowdgree()//��ԭʼ���ݵĻ������޳����Ӷ�Ϊ1�Ľڵ������  
{
	printf("the %d cycle cutlowdgree\n",++cutlowdgreecalledcount);
//	print_two_dimension(data, row, col);
	
	int rowcutcount=0;//�м������� 
	int rowcutflag=0;//�м�����־ 
	int colcutcount=0;//�м������� 
	int colcutflag=0;//�м������� 	
	
	
	//����A��������Ӷȵĳ�Ա���� 
	int i,j;
	int temp=0;	
	for(i=0;i<row;i++)
	{
		rowcutflag=0;//���赱ǰ�в���Ҫ���� 
		temp=0;
		
		for(j=0;j<col;j++)//�жϵ�ǰ���Ƿ���Ҫ���м��� 
		{
		temp+=data[i][j];			
		}	
			
		if (temp==1)//temp==0 or >=2ʱ������Ҫ���� 
		{
			rowcutflag=1;
		}
		
		
		if (rowcutflag)//������ 
		{
		printf("row %d cutting\n",i);
			for(j=0;j<col;j++)
				data[i][j]=0;	
		}
		
		rowcutcount+=rowcutflag;//�м������� +1 
	}

	//����B��������Ӷȵĳ�Ա���� 
	
	for(j=0;j<col;j++)
	{
		colcutflag=0;
		temp=0;
		
		for(i=0;i<row;i++)//�жϵ�ǰ���Ƿ���Ҫ���� 
		{	
		temp+=data[i][j];	 				
		}		
		
		if(temp==1) //temp==0 or >=2ʱ������Ҫ���� 
		{
		colcutflag=1;	
		}
		
		
		if (colcutflag)//������ 
		{
			printf("col %d cutting\n",j);
			for(i=0;i<row;i++)
				data[i][j]=0;	
		}
		
		colcutcount+=colcutflag;
	}

	
	if (rowcutcount||colcutcount)//���д������Ӷȼ�������������е����Ӷȼ��� 
		 cutlowdgree();
	
}
