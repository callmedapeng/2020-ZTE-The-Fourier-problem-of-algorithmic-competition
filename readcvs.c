#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readcvs.h"
#include "misc.h" 
/*****************************************************************
��ģ������ṩ���ļ���ȡԭʼ���ݵ�һ����ά��̬�������ؽӿ�
����void readcvs()������õ���
1.data  ����ԭʼ��������
2.row ,col ����ԭʼ����������
*******************************************************************
*/

int **data=NULL;//���ڴ洢ԭʼ���ݵĶ�ά����
int row, col;//ԭʼ���������� 
#define linebufferlength  2700   //��������ΪCSV�ļ�������2��

#if (FILESOURCE)
char filename[] = "Example.csv";//�����ļ�·�� 
//char filename[] = "Example_20200508.csv";//�����ļ�·��  
//char filename[] = "Example_20200501.csv";//�����ļ�·��  
//char filename[] = "Example_20200427.csv";//�����ļ�·��  
//char filename[] = "Example_20200424AM.csv";//�����ļ�·��  
//char filename[] = "Example_20200423PM.csv";//�����ļ�·�� 
//char filename[] = "Example_test_unstd77.csv";//�������ݸ�ʽ��7*7ȫ1���Ծ��� 

#else
char filename[] = "Example_test20200507PM.csv";//��׼�ڽӾ����ʽ�����ļ�·�� 
//char filename[] = "Example_test20200429PM.csv";//��׼�ڽӾ����ʽ�����ļ�·��
//char filename[] = "Example_test20200422AM.csv";//��׼�ڽӾ����ʽ�����ļ�·�� 
#endif


void readcvs(void ) //���ļ������ݵ�data��ά���� 
{
    char line[linebufferlength];//�ж�ȡ������
    int i = 0;
    row = get_row(filename);
    col = get_col(filename);
    printf("row = %d\n", row);
	printf("col = %d\n", col);
    
    data = (int **)calloc(row , sizeof(int *));//��̬�����ά���� 
	for (i = 0; i < row; ++i){
		data[i] = (int *)calloc(col,sizeof(int));
	}
	
	
	get_two_dimension(line, data, filename);//���ݴ����ά���� 
	
	
//	print_two_dimension(data, row, col);//��ӡ��ʾ��ά���� 
}

void get_two_dimension(char* line, int** data, char *filename)//���ݴ����ά���� 
{
	FILE* stream = fopen(filename, "r");
	int i = 0;
	while (fgets(line, linebufferlength, stream))//���ж�ȡ
    {
    	int j = 0;
    	char *tok;
        char* tmp = strdup(line);
        for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",\n")){
        	data[i][j] = atoi(tok);//ת�������� 
		}//�ַ�����ֲ��� 
        i++;
        free(tmp);
    }
    fclose(stream);//�ļ��򿪺�Ҫ���йرղ���
}

void print_two_dimension(int * * data, int row, int col)////��ʾԭʼ���� 
{
	int i, j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%d", data[i][j]);
		}
		printf("\n");
	}
}

int get_row(char *filename)//��ȡ�ļ��������� 
{
	char line[linebufferlength];
	int i = 0;
	FILE* stream = fopen(filename, "r");

	if (!stream) 
	{
		printf("file open failed");
		exit(0);
	}
	
	while(fgets(line, linebufferlength, stream)){
		i++;
	}
	fclose(stream);
	return i;
}

int get_col(char *filename)////��ȡ�ļ��������� 
{
	char line[linebufferlength];
	int i = 0;
	FILE* stream = fopen(filename, "r");
	if (!stream) 
	{
		printf("file open failed");
		exit(0);
	}
	
	fgets(line, linebufferlength, stream);
	char* token = strtok(line, ",");
	while(token){
		token = strtok(NULL, ",");
		i++;
	}
	fclose(stream);
	return i;
}
