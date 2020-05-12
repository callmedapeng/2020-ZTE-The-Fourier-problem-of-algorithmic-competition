#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "readcvs.h"
 #include "misc.h" 
 #include "flexiblearray.h"
 #include "differdatasource.h"
 #include "graph.h" 
 #include  <time.h>

clock_t start=0, finish=0;
double  duration=0.0;
 int main()
 {	
////////////��������������е�ʱ��///////////////
	 start = clock();//��¼����ʼ����ʱ��

////////////////////////����ʼ///////////////////////////////////////////////

	readcvs();//���ļ��������ݵ�data��ά��̬�ڴ�����
 	

 	cutlowdgree();//���������ӶȵĽڵ������� 
 	
 	
 	findvalidnode();//��ʾA,B������Ч�Ľڵ�����Щ 
 	
 	
	UnifyAdjMatFormat();//ͳһ�ڽ�����Ϊ��׼�ڽӾ����ʽ 
	

	test_list_dfs_route();//�����ڽӱ���ͼ�г��Ȳ�����MAXDEEP�����㳤��Ҫ���ȫ������·��
	
	printf("routes finding is  finished\n");


//////////////////////////////��·���������ƴ�ӡ���·����ȥ��/////////////////////////////////////////////////////////////////

	printf("4 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route3_flexarry);//3�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route3_flexarry));//������Ч�����
	FlexibleArrayFree(&route3_flexarry);

	printf("4 vertax cycles before sorting:%d\n", cycle4combinedbyroute_flexarry.rowcount);
	printf("4 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle4combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle4combinedbyroute_flexarry);
	printf("4 vertax cycles are desaming:\n");
	int num4_loop = FlexibleArrayCountUnDuplicate(&cycle4combinedbyroute_flexarry);
	printf("4 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle4combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 


	printf("6 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route4_flexarry);//4�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route4_flexarry));//������Ч�����
	FlexibleArrayFree(&route4_flexarry);

	printf("6 vertax cycles before sorting:%d\n", cycle6combinedbyroute_flexarry.rowcount);
	printf("6 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle6combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle6combinedbyroute_flexarry);
	printf("6 vertax cycles are desaming:\n");
	int num6_loop = FlexibleArrayCountUnDuplicate(&cycle6combinedbyroute_flexarry);
	printf("6 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle6combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 


	printf("8 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route5_flexarry);//5�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route5_flexarry));//������Ч�����
	FlexibleArrayFree(&route5_flexarry);

	printf("8 vertax cycles before sorting:%d\n", cycle8combinedbyroute_flexarry.rowcount);
	printf("8 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle8combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle8combinedbyroute_flexarry);
	printf("8 vertax cycles are desaming:\n");
	int num8_loop = FlexibleArrayCountUnDuplicate(&cycle8combinedbyroute_flexarry);
	printf("8 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle8combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 



	printf("10 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route6_flexarry);//6�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route6_flexarry));//������Ч�����
	FlexibleArrayFree(&route6_flexarry);

	printf("10 vertax cycles before sorting:%d\n", cycle10combinedbyroute_flexarry.rowcount);
	printf("10 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle10combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle10combinedbyroute_flexarry);
	printf("10 vertax cycles are desaming:\n");
	int num10_loop = FlexibleArrayCountUnDuplicate(&cycle10combinedbyroute_flexarry);
	printf("10 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle10combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 


	printf("12 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route7_flexarry);//7�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route7_flexarry));//������Ч�����
	FlexibleArrayFree(&route7_flexarry);

	printf("12 vertax cycles before sorting:%d\n", cycle12combinedbyroute_flexarry.rowcount);
	printf("12 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle12combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle12combinedbyroute_flexarry);
	printf("12 vertax cycles are desaming:\n");
	int num12_loop = FlexibleArrayCountUnDuplicate(&cycle12combinedbyroute_flexarry);
	printf("12 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle12combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 


	printf("14 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route8_flexarry);//8�ڵ�·����������յ�����
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route8_flexarry));//������Ч�����
	FlexibleArrayFree(&route8_flexarry);

	printf("14 vertax cycles before sorting:%d\n", cycle14combinedbyroute_flexarry.rowcount);
	printf("14 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle14combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle14combinedbyroute_flexarry);
	printf("14 vertax cycles are desaming:\n");
	int num14_loop = FlexibleArrayCountUnDuplicate(&cycle14combinedbyroute_flexarry);
	printf("14 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle14combinedbyroute_flexarry);	//�ͷź����ظ���·�Ļ������� 

////////////////��ʾ��ͬ�ڵ����Ļ�·����///////////////////	
	printf("4 vertax cyle number is %d\n",num4_loop);
	printf("6 vertax cyle number is %d\n",num6_loop);
	printf("8 vertax cyle number is %d\n",num8_loop);
	printf("10 vertax cyle number is %d\n",num10_loop);			
	printf("12 vertax cyle number is %d\n",num12_loop);
	printf("14 vertax cyle number is %d\n",num14_loop);	
		
////////////////����𰸵�result.txt�ļ���///////////////////////////////	
	FILE * txtfp = NULL;
	/*�ļ��Ĵ�*/
	txtfp = fopen("result.txt", "w");//fopen���ļ�������ļ������ǵ�ǰ�����ڵġ���w����д�����ʽ�򿪣���r���Զ�����ʽ�򿪣���a��׷��ģʽд��
	fprintf(txtfp, "Result:\n");
	fprintf(txtfp, "%d\n", num4_loop);
	fprintf(txtfp, "%d\n", num6_loop);
	fprintf(txtfp, "%d\n", num8_loop);
	fprintf(txtfp, "%d\n", num10_loop);
	fprintf(txtfp, "%d\n", num12_loop);
	fprintf(txtfp, "%d\n", num14_loop);


////////////////////////////////�������////////////////////////////////////////////////////////
	finish = clock();//��¼�����������ʱ��
	duration = (double)(finish - start) / CLOCKS_PER_SEC;//����������ʱ�䣬��λ����
	printf("Total running time is: %f seconds\n", duration);
	fprintf(txtfp, "Total running time(seconds): %f \n", duration);
	fclose(txtfp);//�ر�result.txt�ļ�	

 	return 0;
} 
  
