#ifndef DIFFER_DATA_SOURCE_H
#define DIFFER_DATA_SOURCE_H
/*
**********************************************************
从文件中读出的原始数据保存在data动态数组中，中兴捧月比赛文件中给出的原始数据是非标准的邻接矩阵，后续编写的算法是针对标准邻接矩阵设计的，
为此需要将非标准的邻接矩阵转换保存为标准邻接矩阵。 
1.void  UnifyAdjMatFormat(void);函数判断当前的原始数据是否为标准邻接矩阵数据，
是标准数据，则将原始数据直接传递给统一的邻接矩阵接口unifyAdjMatPort和节点数接口unifyVertaxSizePort 
不是标准数据，则将原始数据转换后再传递给统一的邻接矩阵接口unifyAdjMatPort和节点数接口unifyVertaxSizePort  

2.统一的邻接矩阵接口unifyAdjMatPort

3.统一的节点数接口unifyVertaxSizePort  

4.void  UnifyAdjMatFormat(void);//将邻接数据统一为标准邻接数据形式 

**********************************************************
*/

extern int ** unifyAdjMatPort; //统一邻接矩阵格式接口 
extern int    unifyVertaxSizePort;//统一节点数接口 

void  UnifyAdjMatFormat(void);//将邻接数据统一为标准邻接矩阵形式 



#endif
