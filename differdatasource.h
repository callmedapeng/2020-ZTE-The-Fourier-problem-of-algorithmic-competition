#ifndef DIFFER_DATA_SOURCE_H
#define DIFFER_DATA_SOURCE_H
/*
**********************************************************
���ļ��ж�����ԭʼ���ݱ�����data��̬�����У��������±����ļ��и�����ԭʼ�����ǷǱ�׼���ڽӾ��󣬺�����д���㷨����Ա�׼�ڽӾ�����Ƶģ�
Ϊ����Ҫ���Ǳ�׼���ڽӾ���ת������Ϊ��׼�ڽӾ��� 
1.void  UnifyAdjMatFormat(void);�����жϵ�ǰ��ԭʼ�����Ƿ�Ϊ��׼�ڽӾ������ݣ�
�Ǳ�׼���ݣ���ԭʼ����ֱ�Ӵ��ݸ�ͳһ���ڽӾ���ӿ�unifyAdjMatPort�ͽڵ����ӿ�unifyVertaxSizePort 
���Ǳ�׼���ݣ���ԭʼ����ת�����ٴ��ݸ�ͳһ���ڽӾ���ӿ�unifyAdjMatPort�ͽڵ����ӿ�unifyVertaxSizePort  

2.ͳһ���ڽӾ���ӿ�unifyAdjMatPort

3.ͳһ�Ľڵ����ӿ�unifyVertaxSizePort  

4.void  UnifyAdjMatFormat(void);//���ڽ�����ͳһΪ��׼�ڽ�������ʽ 

**********************************************************
*/

extern int ** unifyAdjMatPort; //ͳһ�ڽӾ����ʽ�ӿ� 
extern int    unifyVertaxSizePort;//ͳһ�ڵ����ӿ� 

void  UnifyAdjMatFormat(void);//���ڽ�����ͳһΪ��׼�ڽӾ�����ʽ 



#endif
