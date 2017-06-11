/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: thread.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月11日 02时06分07秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月11日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *	
thd_demo(void *arg) 
{
	for ( ;; ) 
	{
		printf ( "thread demo\n" );
		sleep(1);
	}
}

int
create_thread(void*(*thread_func)(void*))
{
	int res;
	pthread_t pid;

	res = pthread_create(&pid,NULL, thread_func, NULL);
	if ( res != 0 ) 
	{
		printf ( "create thread failed!\n" );
		return -1;
	}

	pthread_detach(pid);

	return 0;
}

int
main(int argc, char *argv[])
{
	if ( create_thread(thd_demo) < 0 )
		goto __end;

	do 
	{
		printf ( "main\n" );
		sleep(1);
	} while (0);				

	pthread_exit(0);

__end:
	printf ( "end\n" );
//	return 0;
}
