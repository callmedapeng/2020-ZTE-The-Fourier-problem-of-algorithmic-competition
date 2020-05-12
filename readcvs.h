#ifndef READCVS_H
#define    READCVS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
/*****************************************************************
 readcvs.h �����ṩ���ļ���ȡԭʼ���ݵ�һ����ά��̬�������ؽӿ�  
 ����void readcvs()������õ��� 
1.data  ����ԭʼ�������� 
2.row ,col ����ԭʼ���������� 
*******************************************************************
 */
extern int **data;//����ԭʼ���ݵĶ�ά��̬����
extern int row, col;//����ԭʼ���������� 
void readcvs(); //��ȡCVS�ļ���ԭʼ���ݶ�άdata���� 


void get_two_dimension(char* line, int ** data, char *filename);//���ļ������ݵ�data��ά���� 
void print_two_dimension(int** data, int row, int col);//��ʾԭʼ���� 
int get_row(char *filename);//��ȡ�ļ����ݺ��� 
int get_col(char *filename);//��ȡ�ļ��������� 


#endif
