#include "readcvs.h"
#include "misc.h"
/*
******************************************************************************
����void findvalidnode(void )������ �ҳ�A,B�������Ч��Ա�ڵ㣨���Ӷȴ���2�ĳ�Ա�� ��
1.int * A_validnode=NULL;//����A������Ч��Ա�ڵ�ID�����Ӷȴ���2�ĳ�Ա�� 
2.int * B_validnode=NULL;//����A������Ч��Ա�ڵ�ID�����Ӷȴ���2�ĳ�Ա��
**********************************************************************************
*/
int * A_validnode=NULL;//����A������Ч��Ա�ڵ㣨���Ӷȴ���2�ĳ�Ա�� 
int * B_validnode=NULL;//����A������Ч��Ա�ڵ㣨���Ӷȴ���2�ĳ�Ա�� 

void findvalidnode(void )
{
printf("finding validnode in A and B \n");
	int i,j;
	int temp;
	int Avalidcount=0;// A������Ч��Ա������ 
	int Bvalidcount=0;	// B������Ч��Ա������ 
	
	A_validnode=(int *)malloc((row+1) * sizeof(int));
	B_validnode=(int *)malloc((col+1) * sizeof(int));

	
	
	//�б��� ���ҳ�A����ڵ����Ӵ��ڵ���2�ĳ�Ա 
	
	for(i=0;i<row;i++)
	{
		temp=0;
		for(j=0;j<col;j++)//����A�����Աi�����Ӷ� 
		{
		temp+=data[i][j];			
		}	
			
		if (temp>=2)//���Ӷȴ��ڵ���2�ĳ�ԱΪ��Ч��Ա 
		{
			A_validnode[Avalidcount]=i;
			Avalidcount++;
		}

	}

printf("Avalidcount is %d\n",Avalidcount);
for(i=0;i<Avalidcount;i++)
printf("%d\n",A_validnode[i]);
	

	//�б��� ���ҳ�B����ڵ����Ӵ��ڵ���2�ĳ�Ա 	
	for(j=0;j<col;j++)
	{
		temp=0;
		for(i=0;i<row;i++)//����B�����Աj�����Ӷ� 
		{
		temp+=data[i][j];			
		}	
			
		if (temp>=2)//���Ӷȴ��ڵ���2�ĳ�ԱΪ��Ч��Ա 
		{
			B_validnode[Bvalidcount]=j;
			Bvalidcount++;
		}

	}	
printf("Bvalidcount is %d\n",Bvalidcount);	
for(j=0;j<Bvalidcount;j++)
printf("%d\n",B_validnode[j]);	
}
