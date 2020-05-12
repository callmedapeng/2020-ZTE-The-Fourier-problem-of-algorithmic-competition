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
////////////测量程序持续运行的时间///////////////
	 start = clock();//记录程序开始运行时刻

////////////////////////程序开始///////////////////////////////////////////////

	readcvs();//从文件读入数据到data二维动态内存数组
 	

 	cutlowdgree();//剪除低连接度的节点与连接 
 	
 	
 	findvalidnode();//显示A,B部落有效的节点有哪些 
 	
 	
	UnifyAdjMatFormat();//统一邻接数据为标准邻接矩阵格式 
	

	test_list_dfs_route();//遍历邻接表型图中长度不超过MAXDEEP且满足长度要求的全部单向路径
	
	printf("routes finding is  finished\n");


//////////////////////////////对路径进行组合拼接、环路排序、去重/////////////////////////////////////////////////////////////////

	printf("4 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route3_flexarry);//3节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route3_flexarry));//计算有效组合数
	FlexibleArrayFree(&route3_flexarry);

	printf("4 vertax cycles before sorting:%d\n", cycle4combinedbyroute_flexarry.rowcount);
	printf("4 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle4combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle4combinedbyroute_flexarry);
	printf("4 vertax cycles are desaming:\n");
	int num4_loop = FlexibleArrayCountUnDuplicate(&cycle4combinedbyroute_flexarry);
	printf("4 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle4combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 


	printf("6 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route4_flexarry);//4节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route4_flexarry));//计算有效组合数
	FlexibleArrayFree(&route4_flexarry);

	printf("6 vertax cycles before sorting:%d\n", cycle6combinedbyroute_flexarry.rowcount);
	printf("6 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle6combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle6combinedbyroute_flexarry);
	printf("6 vertax cycles are desaming:\n");
	int num6_loop = FlexibleArrayCountUnDuplicate(&cycle6combinedbyroute_flexarry);
	printf("6 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle6combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 


	printf("8 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route5_flexarry);//5节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route5_flexarry));//计算有效组合数
	FlexibleArrayFree(&route5_flexarry);

	printf("8 vertax cycles before sorting:%d\n", cycle8combinedbyroute_flexarry.rowcount);
	printf("8 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle8combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle8combinedbyroute_flexarry);
	printf("8 vertax cycles are desaming:\n");
	int num8_loop = FlexibleArrayCountUnDuplicate(&cycle8combinedbyroute_flexarry);
	printf("8 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle8combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 



	printf("10 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route6_flexarry);//6节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route6_flexarry));//计算有效组合数
	FlexibleArrayFree(&route6_flexarry);

	printf("10 vertax cycles before sorting:%d\n", cycle10combinedbyroute_flexarry.rowcount);
	printf("10 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle10combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle10combinedbyroute_flexarry);
	printf("10 vertax cycles are desaming:\n");
	int num10_loop = FlexibleArrayCountUnDuplicate(&cycle10combinedbyroute_flexarry);
	printf("10 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle10combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 


	printf("12 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route7_flexarry);//7节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route7_flexarry));//计算有效组合数
	FlexibleArrayFree(&route7_flexarry);

	printf("12 vertax cycles before sorting:%d\n", cycle12combinedbyroute_flexarry.rowcount);
	printf("12 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle12combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle12combinedbyroute_flexarry);
	printf("12 vertax cycles are desaming:\n");
	int num12_loop = FlexibleArrayCountUnDuplicate(&cycle12combinedbyroute_flexarry);
	printf("12 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle12combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 


	printf("14 vertax cycles :\n");
	FlexibleArrayStartAndEndHeapSort(&route8_flexarry);//8节点路径按照起点终点排序
	printf("valid combination numbers is:%d\n", FlexibleArrayCountRoute2CycleUseGuard(&route8_flexarry));//计算有效组合数
	FlexibleArrayFree(&route8_flexarry);

	printf("14 vertax cycles before sorting:%d\n", cycle14combinedbyroute_flexarry.rowcount);
	printf("14 vertax cycles are sorting:\n");
	FlexibleArrayHeapSort(&cycle14combinedbyroute_flexarry);
	FlexibleArrayWholeHeapSort(&cycle14combinedbyroute_flexarry);
	printf("14 vertax cycles are desaming:\n");
	int num14_loop = FlexibleArrayCountUnDuplicate(&cycle14combinedbyroute_flexarry);
	printf("14 vertax cycles original are freeing:\n");
	FlexibleArrayFree(&cycle14combinedbyroute_flexarry);	//释放含有重复环路的缓存数组 

////////////////显示不同节点数的环路数量///////////////////	
	printf("4 vertax cyle number is %d\n",num4_loop);
	printf("6 vertax cyle number is %d\n",num6_loop);
	printf("8 vertax cyle number is %d\n",num8_loop);
	printf("10 vertax cyle number is %d\n",num10_loop);			
	printf("12 vertax cyle number is %d\n",num12_loop);
	printf("14 vertax cyle number is %d\n",num14_loop);	
		
////////////////保存答案到result.txt文件中///////////////////////////////	
	FILE * txtfp = NULL;
	/*文件的打开*/
	txtfp = fopen("result.txt", "w");//fopen打开文件，这个文件可以是当前不存在的。“w”以写入的形式打开，“r”以读的形式打开，“a”追加模式写入
	fprintf(txtfp, "Result:\n");
	fprintf(txtfp, "%d\n", num4_loop);
	fprintf(txtfp, "%d\n", num6_loop);
	fprintf(txtfp, "%d\n", num8_loop);
	fprintf(txtfp, "%d\n", num10_loop);
	fprintf(txtfp, "%d\n", num12_loop);
	fprintf(txtfp, "%d\n", num14_loop);


////////////////////////////////程序结束////////////////////////////////////////////////////////
	finish = clock();//记录程序结束运行时刻
	duration = (double)(finish - start) / CLOCKS_PER_SEC;//程序总运行时间，单位：秒
	printf("Total running time is: %f seconds\n", duration);
	fprintf(txtfp, "Total running time(seconds): %f \n", duration);
	fclose(txtfp);//关闭result.txt文件	

 	return 0;
} 
  
