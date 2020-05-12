#ifndef READCVS_H
#define    READCVS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
/*****************************************************************
 readcvs.h 对外提供从文件读取原始数据到一个二维动态数组的相关接口  
 调用void readcvs()函数后得到： 
1.data  保存原始数据内容 
2.row ,col 保存原始数据行列数 
*******************************************************************
 */
extern int **data;//保存原始数据的二维动态数组
extern int row, col;//保存原始数据行列数 
void readcvs(); //读取CVS文件到原始数据二维data数组 


void get_two_dimension(char* line, int ** data, char *filename);//从文件读数据到data二维数组 
void print_two_dimension(int** data, int row, int col);//显示原始数据 
int get_row(char *filename);//获取文件数据函数 
int get_col(char *filename);//获取文件数据列数 


#endif
