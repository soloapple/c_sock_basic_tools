/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: time_diff.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��06��09�� 02ʱ09��17��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��06��09��                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

int main()
{
	float time_use=0;
	struct timeval start;
	struct timeval end;

	//struct timezone tz; //������˵��

	gettimeofday(&start,NULL);//gettimeofday(&start,&tz);���һ��
	printf("start.tv_sec:%d\n",start.tv_sec);
	printf("start.tv_usec:%d\n",start.tv_usec);

	sleep(3);

	gettimeofday(&end,NULL);
	printf("end.tv_sec:%d\n",end.tv_sec);
	printf("end.tv_usec:%d\n",end.tv_usec);

	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//΢��
	printf("time_use is %f\n",time_use);

	//�����time_use is 3001410.000000
	//����Ĳ���ָ��ķ�ʽҲ���ԣ�����Ҫע��ָ���������������ڴ�Ļ���������ȷ���������н���᲻��
}
