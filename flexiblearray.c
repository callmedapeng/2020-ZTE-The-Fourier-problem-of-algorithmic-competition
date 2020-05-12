#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "flexiblearray.h"
#include "misc.h"
#include "differdatasource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
***************************************************************************
��ģ�����Ҫ�����������FlexibleArray���ֶ�ά��̬���飬 
FlexibleArray�ǿ����趨����������ʱ����׷�������Ķ�ά���飬 ���ڴ洢��Ӧ�ڵ����Ļ�·����·���� 
FlexibleArray��������Ӧ��·����·���ڵ����� 
FlexibleArray��������Ӧ��ͬ�ڵ����Ļ�·������·������ 

**************************************************************************
*/

struct FlexibleArray route3_flexarry = { 0,3,NULL };	//���ڴ洢ȫ����3�ڵ�·�����������4�ڵ㻷·�� 
struct FlexibleArray route4_flexarry = { 0,4,NULL };	//���ڴ洢ȫ����4�ڵ�·�����������6�ڵ㻷·�� 
struct FlexibleArray route5_flexarry = { 0,5,NULL };	//���ڴ洢ȫ����5�ڵ�·�����������8�ڵ㻷·�� 
struct FlexibleArray route6_flexarry = { 0,6,NULL };	//���ڴ洢ȫ����6�ڵ�·�����������10�ڵ㻷·�� 
struct FlexibleArray route7_flexarry = { 0,7,NULL };	//���ڴ洢ȫ����7�ڵ�·�����������12�ڵ㻷·�� 
struct FlexibleArray route8_flexarry = { 0,8,NULL };	//���ڴ洢ȫ����8�ڵ�·�����������14�ڵ㻷·�� 
struct FlexibleArray cycle4combinedbyroute_flexarry = { 0,4,NULL };	//���ڴ洢��·����ϵõ���4�ڵ㻷·
struct FlexibleArray cycle6combinedbyroute_flexarry = { 0,6,NULL };	//���ڴ洢��·����ϵõ���6�ڵ㻷·
struct FlexibleArray cycle8combinedbyroute_flexarry = { 0,8,NULL };	//���ڴ洢��·����ϵõ���8�ڵ㻷·
struct FlexibleArray cycle10combinedbyroute_flexarry = { 0,10,NULL };	//���ڴ洢��·����ϵõ���10�ڵ㻷·
struct FlexibleArray cycle12combinedbyroute_flexarry = { 0,12,NULL };	//���ڴ洢��·����ϵõ���12�ڵ㻷·
struct FlexibleArray cycle14combinedbyroute_flexarry = { 0,14,NULL };	//���ڴ洢��·����ϵõ���14�ڵ㻷·



struct FlexibleArray col4_flexarry={0,4,NULL};			//���ڴ洢�����ظ�·����4�ڵ㻷· 
struct FlexibleArray col4desame_flexarry={0,4,NULL};	//���ڴ洢�޳����ظ�·����4�ڵ㻷· 	


struct FlexibleArray col6_flexarry={0,6,NULL};//���ڴ洢�����ظ�·����6�ڵ㻷· 
struct FlexibleArray col6desame_flexarry={0,6,NULL};//���ڴ洢�޳����ظ�·����6�ڵ㻷· 	


struct FlexibleArray col8_flexarry={0,8,NULL};//���ڴ洢�����ظ�·����8�ڵ㻷· 
struct FlexibleArray col8desame_flexarry={0,8,NULL};//���ڴ洢�޳����ظ�·����8�ڵ㻷·


struct FlexibleArray col10_flexarry={0,10,NULL};//���ڴ洢�����ظ�·����10�ڵ㻷· 
struct FlexibleArray col10desame_flexarry={0,10,NULL};//���ڴ洢�޳����ظ�·����10�ڵ㻷·


struct FlexibleArray col12_flexarry={0,12,NULL};//���ڴ洢�����ظ�·����12�ڵ㻷· 
struct FlexibleArray col12desame_flexarry={0,12,NULL};//���ڴ洢�޳����ظ�·����12�ڵ㻷·


struct FlexibleArray col14_flexarry={0,14,NULL};//���ڴ洢�����ظ�·����14�ڵ㻷· 
struct FlexibleArray col14desame_flexarry={0,14,NULL};//���ڴ洢�޳����ظ�·����14�ڵ㻷·


void FlexibleArrayAppend(struct FlexibleArray * FA,int * source)//���ά������׷��һ������
{
	FA->rowcount++;
	
	FA->data=(int**)realloc(FA->data,FA->rowcount*sizeof(int *));//�пռ����
	//if( !FA->data )
	//{
	//	printf("FlexibleArray row malloc error!\n");
	//	exit(0);
	//}
	
	FA->data[FA->rowcount-1]=(int *)calloc(FA->coltype,sizeof(int));//�пռ����
	//if( !FA->data[FA->rowcount-1] )
	//{
	//	printf("FlexibleArray col malloc error!\n");
	//	exit(0);
	//}

	
	//if( !source )//�ж�����Դ�Ƿ���Ч
	//{
	//	printf("data source is blank!\n");
	//	exit(0);
	//}

	memcpy(FA->data[FA->rowcount - 1], source, sizeof(int)*FA->coltype);
}

void FlexibleArrayFree(struct FlexibleArray * FA)//�ͷ�FlexibleArray������Ŀռ�
{
	int i;
	if(! FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	for(i=0;i<FA->rowcount;i++)//�ͷ�FlexibleArray���пռ�
	{
		free(FA->data[i]);
	}
	free(FA->data);//�ͷ�FlexibleArray���пռ�
	
	FA->rowcount=0;//FlexibleArray�м�������

}

void FlexibleArrayPrint(struct FlexibleArray * FA)// FlexibleArray��ά�������ݴ�ӡ
{
	int i,j;
	if( !FA->data )
	{
		printf("FlexibleArray is blank!\n");
		return;
	}
	
	printf("total row:%d total col:%d\n",FA->rowcount,FA->coltype);
	for(i=0;i<FA->rowcount;i++)
	{
		for(j=0;j<FA->coltype;j++)
		{
			printf("%d->",FA->data[i][j]);
		}
		
		printf("%d\n",FA->data[i][0]);		
			
	}


}

void FlexibleArrayPrint2Txt(struct FlexibleArray * FA,const char * filename)// ��FlexibleArray��ά�������ݴ�ӡ���ļ�
{
	int i, j;
	if (!FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	//char tempstr[10];
	//itoa(FA->coltype, tempstr, 10);
	//char filename[50] = "col";
	//strcat(filename, tempstr);
	//strcat(filename,"_flexiblearry.txt");

	FILE * fp = NULL;
	/*�ļ��Ĵ�*/
	fp = fopen(filename, "w");//fopen���ļ�������ļ������ǵ�ǰ�����ڵġ���w����д�����ʽ�򿪣���r���Զ�����ʽ�򿪣���a��׷��ģʽд��

	fprintf(fp, "total row:%d total col:%d\n", FA->rowcount, FA->coltype);
	for (i = 0; i<FA->rowcount; i++)
	{
		for (j = 0; j<FA->coltype; j++)
		{
			fprintf(fp,"%d->", FA->data[i][j]);
		}

		fprintf(fp,"\n");

	}

	fclose(fp);

}

void FlexibleArrayPrintCycleCombinedByRoutes2Txt(struct FlexibleArray * FA, int go,int back)// ����2��·����ϳɵĻ�·��ӡ���ļ�
{
	int i, j;
	if (!FA->data)
	{
		printf("FlexibleArray is blank!\n");
		return;
	}

	char tempstr[10];
	itoa(FA->coltype, tempstr, 10);
	char filename[50] = "col";
	strcat(filename, tempstr);
	strcat(filename,"_CycleCombinedByRoutes.txt");

	FILE * fp = NULL;
	/*�ļ��Ĵ�*/
	fp = fopen(filename, "a");//fopen���ļ�������ļ������ǵ�ǰ�����ڵġ���w����д�����ʽ�򿪣���r���Զ�����ʽ�򿪣���a��׷��ģʽд��

		for (j = 0; j<FA->coltype; j++)
		{
			fprintf(fp, "%d->", FA->data[go][j]);
		}

		for (j = FA->coltype-2; j>=0; j--)
		{
			fprintf(fp, "%d->", FA->data[back][j]);
		}

		fprintf(fp, "\n");

	fclose(fp);

}

void FlexibleArrayAppendCycleCombinedByRoutes(struct FlexibleArray * FA, int go, int back)// ����2��·��ƴ�ϳɵĻ�·���浽��Ӧ�ڵ����Ļ�·������
{
	if (FA->coltype == 3)
		FlexibleArrayAppendByTwoRoutes(&cycle4combinedbyroute_flexarry,FA->data[go],FA->data[back]);
	else if (FA->coltype == 4)
		FlexibleArrayAppendByTwoRoutes(&cycle6combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 5)
		FlexibleArrayAppendByTwoRoutes(&cycle8combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 6)
		FlexibleArrayAppendByTwoRoutes(&cycle10combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 7)
		FlexibleArrayAppendByTwoRoutes(&cycle12combinedbyroute_flexarry, FA->data[go], FA->data[back]);
	else if (FA->coltype == 8)
		FlexibleArrayAppendByTwoRoutes(&cycle14combinedbyroute_flexarry, FA->data[go], FA->data[back]);

}

void FlexibleArrayAppendByTwoRoutes(struct FlexibleArray * FA, int * go, int * back)//ͨ��������������·����·������׷�ӻ�·
{
	FA->rowcount++;
	FA->data = (int**)realloc(FA->data, FA->rowcount*sizeof(int *));//�пռ����
	FA->data[FA->rowcount - 1] = (int *)calloc(FA->coltype, sizeof(int));//�пռ����

	memcpy(FA->data[FA->rowcount - 1], go, sizeof(int)*(FA->coltype/2 + 1));
	memcpy(FA->data[FA->rowcount - 1]+(FA->coltype / 2 + 1), back+1, sizeof(int)*(FA->coltype / 2 - 1));

}



int compare(int * A,int * B,int len)//�ж�����һά�����С��������ģʽ����A==B����0��A>B��������,A<B���ظ���
{
	int i;
	int differflag=0;//�ȼ���A,B������� 
	for(i=0;i<len;i++)//�Ӹ�λ����λ�Ƚ�A,B ����)(���ģʽ)
	{
		differflag =A[i]-B[i];
		if(differflag) 
		{
			return differflag;
		}
	}
	
	return differflag;  //A�����B������ȣ�����0  
}


int CompareRouteStartAndEnd(int * A, int * B, int len)//������ֹ���ж�������·���Ĵ�С��������ģʽ����A==B����0��A>B��������,A<B���ظ���
{
	//int i;
	int differflag = 0;//�ȼ���A,B������� 
	//for (i = 0;;)//�Ƚ�A��B·���������յ�(���ģʽ)
	//{
	//	differflag = A[i] - B[i];
	//	if (differflag != 0)  //A·����B·���󣬷��ش���0��A·����B·��С�����ش���0�� 
	//	{
	//		return differflag;
	//	}


	//	if (i == len - 1)
	//		break;
	//	i = len - 1;
	//}


	//�Ƚ�A��B·���������յ�(���ģʽ)
	differflag = A[0] - B[0];
	if (differflag != 0)  //A·����B·���󣬷��ش���0��A·����B·��С�����ش���0�� 
	{
		return differflag;
	}

	differflag = A[len - 1] - B[len - 1];
	if (differflag != 0)  //A·����B·���󣬷��ش���0��A·����B·��С�����ش���0�� 
	{
		return differflag;
	}

	return differflag;  //A·����B·����ȣ�����0  

}

int CompareRouteMidWay(int * A, int * B, int len)//�Ƚ�A��B��·����;�Ƿ����غϵ�,���غϵ㷵��1�����򷵻�0
{
//	int * content = (int *)calloc(unifyVertaxSizePort, sizeof(int));//�����ռ䣬���ڱȽ�2��·����;�Ƿ����غϵ㣬��������Ϊ�ڵ�����������Ԫ��ֵ��ʼ��Ĭ��Ϊ0
	int  content[2700] = {0};//�����ռ䣬���ڱȽ�2��·����;�Ƿ����غϵ㣬��������Ϊ�ڵ�����(1344+1344=2688)������Ԫ��ֵ��ʼ��Ĭ��Ϊ0
	int i,index;
//	int flag = 0;

	for (i = 1;i<(len-1);i++)//�Ƚ�A��B·���������յ�(���ģʽ)
	{
		index = A[i];
		if (content[index] != 0) //˵����Ԫ���Ѿ�����ֵ�ˣ����������ظ�
		{
			return 1;
		}
		else
			content[index] = 1;    //����־��,Ҳ�ɸ��κβ�Ϊ0����


		index = B[i];
		if (content[index] != 0) //˵����Ԫ���Ѿ�����ֵ�ˣ����������ظ�
		{
			return 1;
		}
		else
			content[index] = 1;    //����־��,Ҳ�ɸ��κβ�Ϊ0����

	}
	
	//free(content);

	return 0;

}


int  test_CompareRouteStartAndEnd()
{
	int a[] = {6,2,3,5};
	int b[] = {6,2,3,5};
	printf("Size relation between a and b:%d\n", CompareRouteStartAndEnd(a, b, 4)); 

}

void test_CompareRouteMidWay()
{
	int a[] = {1,2,4,3,5};
	int b[] = {1,7,6,3,5};
	printf("Route a and b exist same point?:%d\n", CompareRouteMidWay(a, b, sizeof(a) / sizeof(a[0])));


}




void bubbleSort(int * arr,int len)//һά�������ð���������� 
{
	int i,j,temp;
	int exchangeflag=1;
    for( i = 0; (i < len - 1 )&& exchangeflag; i++) {
    	exchangeflag=0;
        for( j = 0; j < len - 1 - i; j++) {
            if(arr[j] > arr[j+1]) {        // ����Ԫ�������Ա�
            	exchangeflag=1;
                temp = arr[j+1];        // Ԫ�ؽ���
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void FlexibleArraySort(struct FlexibleArray * FA)//��ά�����ÿһ�н���ð����������
{
	int i;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	
	for(i=0;i<FA->rowcount;i++)
	{
		bubbleSort(FA->data[i],FA->coltype);
	}
	

}

void FlexibleArrayWholeSort(struct FlexibleArray * FA)//�Զ�ά�����������ð����������
{

	int i,j,flag;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	int * temp=NULL;
	int exchangeflag=1;
    for( i = 0; (i < FA->rowcount - 1)&&exchangeflag; i++) {
    	exchangeflag=0;
        for( j = 0; j < FA->rowcount - 1 - i; j++) {
			flag=compare(FA->data[j],FA->data[j+1],FA->coltype); // ���������������Ա�
			if(flag>0) {
				exchangeflag=1;       
                temp = FA->data[j+1];        // ����������
                FA->data[j+1] = FA->data[j];
                FA->data[j] = temp;
            }
        }
    }

}



/* ������********************************** */
static void HeapAdjust(int *arr,int s,int m);

/*  ��һά����arr���ж����� */
void HeapSort(int *arr,int length)
{
	int i;
	for(i=(length-1)/2;i>=0;i--) /*  ��arr������һ������� */
		 HeapAdjust(arr,i,length-1);

	int temp;
	for(i=(length-1);i>=1;i--)
	{ 	
		temp=arr[i]; /* ���Ѷ���¼�͵�ǰδ�����������е����һ����¼���� */
		arr[i]=arr[0];
		arr[0]=temp;
		
		 HeapAdjust(arr,0,i-1); /*  ��arr[0..i-1]���µ���Ϊ����� */
	}
}

/* ��֪arr[s..m]�м�¼�Ĺؼ��ֳ�arr[s]֮�������ѵĶ��壬 */
/* ����������arr[s]�Ĺؼ���,ʹarr[s..m]��Ϊһ���󶥶� */
void HeapAdjust(int *arr,int s,int m)
{ 
	int temp,j;
	temp=arr[s];
	for(j=2*s;j<=m;j*=2) /* �عؼ��ֽϴ�ĺ��ӽ������ɸѡ */
	{
		if(j<m && arr[j]<arr[j+1])
			++j; /* jΪ�ؼ����нϴ�ļ�¼���±� */
		if(temp>=arr[j])
			break; /* rcӦ������λ��s�� */
		arr[s]=arr[j];
		s=j;
	}
	arr[s]=temp; /* ���� */
}

/* **************************************** */

void test_heapsort()//���Զ����� 
{
	int d[6]={9,7,5,2,20,1};
	HeapSort(d,6);

}


void FlexibleArrayHeapSort(struct FlexibleArray * FA)//��ά�����ÿһ�н��ж���������
{
	int i;
	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	

	
	for(i=0;i<FA->rowcount;i++)
	{
		HeapSort(FA->data[i],FA->coltype);
	}
	

}

static void FlexibleArrayWholeHeapAdjust(struct FlexibleArray * FA,int s,int m);

void FlexibleArrayWholeHeapSort(struct FlexibleArray * FA)//�Զ�ά����������ж���������
{

	int i;
	int * temp=NULL;	
	if( !FA->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}	


	for(i=(FA->rowcount-1)/2;i>=0;i--) /*  ��arr������һ������� */
		 FlexibleArrayWholeHeapAdjust(FA,i,FA->rowcount-1);

	for(i=(FA->rowcount-1);i>=1;i--)
	{ 	
		temp=FA->data[i]; /* ���Ѷ���¼�͵�ǰδ�����������е����һ����¼���� */
		FA->data[i]=FA->data[0];
		FA->data[0]=temp;
		
		FlexibleArrayWholeHeapAdjust(FA,0,i-1); /*  ��arr[0..i-1]���µ���Ϊ����� */
	}

}

/* ��֪arr[s..m]�м�¼�Ĺؼ��ֳ�arr[s]֮�������ѵĶ��壬 */
/* ����������arr[s]�Ĺؼ���,ʹarr[s..m]��Ϊһ���󶥶� */
void FlexibleArrayWholeHeapAdjust(struct FlexibleArray * FA,int s,int m)
{ 
	int j;
	int * temp;
	
	temp=FA->data[s];
	for(j=2*s;j<=m;j*=2) /* �عؼ��ֽϴ�ĺ��ӽ������ɸѡ */
	{
		if(j<m && (compare(FA->data[j],FA->data[j+1],FA->coltype)<0) )
			++j; /* jΪ�ؼ����нϴ�ļ�¼���±� */
		if( compare(temp, FA->data[j], FA->coltype)>=0)
			break; /* rcӦ������λ��s�� */
		FA->data[s]=FA->data[j];
		s=j;
	}
	FA->data[s]=temp; /* ���� */
}



int FlexibleArrayCountUnDuplicate(struct FlexibleArray * FA)//�����ά������ظ�����
{

	if (FA->rowcount <= 1)
	return FA->rowcount;
	
	int start = 0;//��׼λ��
	int end = 1; //�α�λ��
	int count=1;//�������ظ����� 
	
	while (end < FA->rowcount)
	{
		if (compare(FA->data[start], FA->data[end], FA->coltype)==0)
		{
			end++;
		}
		else
		{
			count++;
			start=end;
			end++;
		}
	}
	return count;
}

int CountUnDuplicate(int * arr,int length)//����һά������ظ�Ԫ������
{

	if (length <= 1)
		return length;

	int start = 0;//��׼λ��
	int end = 1; //�α�λ��
	int count = 0;//�������ظ����� 

	while (end < length)
	{
		if (arr[start]==arr[end])
		{
			if(end==length-1)
				count++;

			end++;
		}
		else 
		{
			count++;//do something
			start = end;

			if (end == length - 1)
				count++;
			end++;
		}
	}


	return count;
}

int FlexibleArrayCountRoute2Cycle(struct FlexibleArray *FA)//����ȫ��·��������ϳɻ�·������
{

	if (FA->rowcount <= 1)
		return 0;

	int start = 0;//��׼λ��
	int end = 1; //�α�λ��
	int count = 0; //����ȫ��·��������ϳɻ�·������

	while (end < FA->rowcount)
	{
		if ( CompareRouteStartAndEnd(FA->data[start],FA->data[end],FA->coltype)==0 )
		{
			if (end == FA->rowcount - 1)
			{
				count += CountValidCombination(FA, start, FA->rowcount);
				return count;
			}

			end++;
		}

		else
		{
			count += CountValidCombination(FA, start, end);
			start = end;
			//if (end == FA->rowcount - 1)
			//	count += CountValidCombination(FA, start, FA->rowcount);
			end++;
		}
	}


	return count;
}

int FlexibleArrayCountRoute2CycleUseGuard(struct FlexibleArray *FA)//����ȫ������·��������ϳɻ�·������(ʹ���ڱ�)������ƴ�ϵõ��Ļ�·������Ӧ�Ļ�·����
{

	if (FA->rowcount <= 1)
		return 0;

	int * guard =(int *)calloc(FA->coltype,sizeof(int));//��β���洢ȫ0��·������Ϊ�ڱ�
	FlexibleArrayAppend(FA, guard);
	free(guard);

	int start = 0;//��׼λ��
	int end = 1; //�α�λ��
	int count = 0; //����ȫ��·��������ϳɻ�·������

	while (end < FA->rowcount)
	{
		if (CompareRouteStartAndEnd(FA->data[start], FA->data[end], FA->coltype) == 0)
		{
			end++;
		}

		else
		{
			count += CountValidCombination(FA, start, end);
			start = end;
			end++;
		}
	}


	return count;
}


int CountValidCombination(struct FlexibleArray * FA,int start,int end)  //������ͬ��ֹ���·���п�ƴ�ϳɻ�·��ϣ�����ƴ�ϵõ��Ļ�·������Ӧ��·����
{
	//if (!FA)
	//{
	//	printf("the input FlexibleArray is blank");
	//	return 0;
	//}

	int i = 0, j = 0,count=0;
	if (end - start <= 1)
		return 0;
	else
	{
		for ( i = start; i < (end-1); i++)
		{
			for ( j = i+1; j < end; j++)
			{
				if (!CompareRouteMidWay(FA->data[i], FA->data[j], FA->coltype))
				{
					FlexibleArrayAppendCycleCombinedByRoutes(FA, i, j);
					count++;
				}
			}
		}
		return count;
	}

}

void test_CountUnDuplicate() {
	int a[] = {1,2,2,3,4,4,5,5,5};
	printf("UnDuplication members are :%d\n", CountUnDuplicate(a, sizeof(a) / sizeof(a[0])));

}







void FlexibleArrayRemoveSame(struct FlexibleArray * original,struct FlexibleArray * desame)//����ά��������ͬ���޳��� 
{
	if( !original->data )
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}
	FlexibleArrayAppend(desame,original->data[0]);
	int i,j,differflag,differcount;
	for(i=1;i<original->rowcount;i++)
	{
		differcount=0;
		for(j=0;j<desame->rowcount;j++)
		{
			differflag=compare(original->data[i],desame->data[j],original->coltype);
			if(differflag)
			differcount++;
		}
		
		if(differcount==desame->rowcount)
		FlexibleArrayAppend(desame, original->data[i]);

	}

}

static void FlexibleArrayStartAndEndHeapAdjust(struct FlexibleArray * FA, int s, int m);

void FlexibleArrayStartAndEndHeapSort(struct FlexibleArray * FA)//������ֹ��Դ洢�ĵ���·��������ж���������
{

	int i;
	int * temp = NULL;
	if (!FA->data)
	{
		printf("The input FlexibleArray is blank!\n");
		return;
	}


	for (i = (FA->rowcount - 1) / 2; i >= 0; i--) /*  ��arr������һ������� */
		FlexibleArrayStartAndEndHeapAdjust(FA, i, FA->rowcount - 1);

	for (i = (FA->rowcount - 1); i >= 1; i--)
	{
		temp = FA->data[i]; /* ���Ѷ���¼�͵�ǰδ�����������е����һ����¼���� */
		FA->data[i] = FA->data[0];
		FA->data[0] = temp;

		FlexibleArrayStartAndEndHeapAdjust(FA, 0, i - 1); /*  ��arr[0..i-1]���µ���Ϊ����� */
	}

}

/* ��֪arr[s..m]�м�¼�Ĺؼ��ֳ�arr[s]֮�������ѵĶ��壬 */
/* ����������arr[s]�Ĺؼ���,ʹarr[s..m]��Ϊһ���󶥶� */
void FlexibleArrayStartAndEndHeapAdjust(struct FlexibleArray * FA, int s, int m)
{
	int j;
	int * temp;

	temp = FA->data[s];
	for (j = 2 * s; j <= m; j *= 2) /* �عؼ��ֽϴ�ĺ��ӽ������ɸѡ */
	{
		if (j<m && (CompareRouteStartAndEnd(FA->data[j], FA->data[j + 1], FA->coltype)<0))
			++j; /* jΪ�ؼ����нϴ�ļ�¼���±� */
		if (CompareRouteStartAndEnd(temp, FA->data[j], FA->coltype) >= 0)
			break; /* rcӦ������λ��s�� */
		FA->data[s] = FA->data[j];
		s = j;
	}
	FA->data[s] = temp; /* ���� */
}

























