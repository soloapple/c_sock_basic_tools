/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: clock_gettime.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月15日 03时16分46秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月15日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,
//		中间时刻如果系统时间被用户改成其他,则对应的时间相应改变
// CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
// CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
// CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间

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
