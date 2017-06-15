/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: clock_gettime.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��06��15�� 03ʱ16��46��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��06��15��                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// CLOCK_REALTIME:ϵͳʵʱʱ��,��ϵͳʵʱʱ��ı���ı�,����UTC1970-1-1 0:0:0��ʼ��ʱ,
//		�м�ʱ�����ϵͳʱ�䱻�û��ĳ�����,���Ӧ��ʱ����Ӧ�ı�
// CLOCK_MONOTONIC:��ϵͳ������һ����ʼ��ʱ,����ϵͳʱ�䱻�û��ı��Ӱ��
// CLOCK_PROCESS_CPUTIME_ID:�����̵���ǰ����ϵͳCPU���ѵ�ʱ��
// CLOCK_THREAD_CPUTIME_ID:���̵߳���ǰ����ϵͳCPU���ѵ�ʱ��

struct timespec ts;

int
main(int argc, char *argv[])
{
	clock_gettime(CLOCK_REALTIME, &ts);
	printf ( "%ld %ld\n", ts.tv_sec, ts.tv_nsec );

	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf ( "%ld %ld\n", ts.tv_sec, ts.tv_nsec );

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	printf ( "%ld %ld\n", ts.tv_sec, ts.tv_nsec );

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	printf ( "%ld %ld\n", ts.tv_sec, ts.tv_nsec );
	
	return 0;
}
