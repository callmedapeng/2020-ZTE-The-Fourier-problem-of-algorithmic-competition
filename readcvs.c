#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readcvs.h"
#include "misc.h" 
/*****************************************************************
本模块对外提供从文件读取原始数据到一个二维动态数组的相关接口
调用void readcvs()函数后得到：
1.data  保存原始数据内容
2.row ,col 保存原始数据行列数
*******************************************************************
*/

int **data=NULL;//用于存储原始数据的二维数组
int row, col;//原始数据行列数 
#define linebufferlength  2700   //长度至少为CSV文件列数的2倍

#if (FILESOURCE)
char filename[] = "Example.csv";//比赛文件路径 
//char filename[] = "Example_20200508.csv";//比赛文件路径  
//char filename[] = "Example_20200501.csv";//比赛文件路径  
//char filename[] = "Example_20200427.csv";//比赛文件路径  
//char filename[] = "Example_20200424AM.csv";//比赛文件路径  
//char filename[] = "Example_20200423PM.csv";//比赛文件路径 
//char filename[] = "Example_test_unstd77.csv";//比赛数据格式的7*7全1测试矩阵 

#else
char filename[] = "Example_test20200507PM.csv";//标准邻接矩阵格式测试文件路径 
//char filename[] = "Example_test20200429PM.csv";//标准邻接矩阵格式测试文件路径
//char filename[] = "Example_test20200422AM.csv";//标准邻接矩阵格式测试文件路径 
#endif


void readcvs(void ) //从文件读数据到data二维数组 
{
    char line[linebufferlength];//行读取缓存区
    int i = 0;
    row = get_row(filename);
    col = get_col(filename);
    printf("row = %d\n", row);
	printf("col = %d\n", col);
    
    data = (int **)calloc(row , sizeof(int *));//动态申请二维数组 
	for (i = 0; i < row; ++i){
		data[i] = (int *)calloc(col,sizeof(int));
	}
	
	
	get_two_dimension(line, data, filename);//数据存入二维数组 
	
	
//	print_two_dimension(data, row, col);//打印显示二维数组 
}

void get_two_dimension(char* line, int** data, char *filename)//数据存入二维数组 
{
	FILE* stream = fopen(filename, "r");
	int i = 0;
	while (fgets(line, linebufferlength, stream))//逐行读取
    {
    	int j = 0;
    	char *tok;
        char* tmp = strdup(line);
        for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",\n")){
        	data[i][j] = atoi(tok);//转换成整数 
		}//字符串拆分操作 
        i++;
        free(tmp);
    }
    fclose(stream);//文件打开后要进行关闭操作
}

void print_two_dimension(int * * data, int row, int col)////显示原始数据 
{
	int i, j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%d", data[i][j]);
		}
		printf("\n");
	}
}

int get_row(char *filename)//获取文件数据行数 
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

int get_col(char *filename)////获取文件数据列数 
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
