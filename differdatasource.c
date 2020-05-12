#include <stdio.h>
#include <stdlib.h>
#include "misc.h"
#include "readcvs.h"
#include "differdatasource.h"
/*
**********************************************************
���ļ��ж�����ԭʼ���ݱ�����data��̬�����У��������±����ļ��и�����ԭʼ�����ǷǱ�׼���ڽӾ��󣬱�д���㷨����Ա�׼�ڽӾ�����Ƶģ�
Ϊ����Ҫ���Ǳ�׼���ڽӾ���ת������Ϊ��׼�ڽӾ��� 
1.void  UnifyAdjMatFormat(void);�����жϵ�ǰ��ԭʼ�����Ƿ�Ϊ��׼�ڽӾ������ݣ�
�Ǳ�׼���ݣ���ԭʼ����ֱ�Ӵ��ݸ�ͳһ���ڽӾ���ӿ�unifyAdjMatPort�ͽڵ����ӿ�unifyVertaxSizePort 
���Ǳ�׼���ݣ���ԭʼ����ת�����ٴ��ݸ�ͳһ���ڽӾ���ӿ�unifyAdjMatPort�ͽڵ����ӿ�unifyVertaxSizePort  

2.ͳһ���ڽӾ���ӿ�unifyAdjMatPort

3.ͳһ�Ľڵ����ӿ�unifyVertaxSizePort  

4.void  UnifyAdjMatFormat(void);//���ڽ�����ͳһΪ��׼�ڽ�������ʽ 

**********************************************************
*/

int ** unifyAdjMatPort=NULL; //ͳһ�ڽӾ����ʽ�ӿ� 
int    unifyVertaxSizePort=0;//ͳһ�ڵ����ӿ� 

void  UnifyAdjMatFormat(void) //���ڽ�����ͳһΪ��׼�ڽӾ�����ʽ 
{
	int i ,j;	
	if(FILESOURCE==1)//�������ݸ�ʽ���Ǳ�׼�ڽӾ����ʽ 
	{
		unifyVertaxSizePort=row+col;//�Ǳ�׼�ڽӾ��󣬽ڵ�����������֮�� 
		
	//����ͳһ��ʽ���ڽӾ���	
		unifyAdjMatPort=(int**)calloc(unifyVertaxSizePort,sizeof(int *));//�пռ����
		if( !unifyAdjMatPort )
		{
			printf("unifyAdjMatPort row malloc error!\n");
			exit(0);
		}
		 
		for (i = 0; i < unifyVertaxSizePort; ++i) // �пռ���� 
		{
			unifyAdjMatPort[i] = (int *)calloc(unifyVertaxSizePort , sizeof(int));
		}

//�洢A��B���ڽӹ�ϵ		
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
			{
			unifyAdjMatPort[i][row+j] =data[i][j];				
			}
		
//�洢B��A���ڽӹ�ϵ		
		for(j=0;j<col;j++)
			for(i=0;i<row;i++)
			{
			unifyAdjMatPort[row+j][i] =data[i][j];				
			}		

	 //�ͷŵ�ԭʼ�������ݵĿռ� 
		for(i=0;i<row;i++)//�ͷ��пռ� 
		{
			free(data[i]);
		 } 
		free(data);//�ͷ��пռ� 

		
	} 
	
	else//��׼�ڽӾ����ʽ �����ݸ�ʽ�����ڽӾ���Ҫ����������ͬ�ҵ��ڽڵ��� 
	{
		unifyAdjMatPort=data;
		unifyVertaxSizePort=row;				
	}
	
	
}
