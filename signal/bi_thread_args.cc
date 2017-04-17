/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: bi_thread_args.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月17日 05时28分24秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月17日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#include <iostream>

using namespace std;
int sign_work = 0;

int
create_thread(void*(*thread_func)(void*))
{
	int res;
	pthread_t pid;

	res = pthread_create(&pid,NULL, thread_func, NULL);
	if ( res != 0 ) 
	{
		printf ( "[%s:%d] create thread func failed\n" ); __FILE__, __LINE__;

		return -1;
	}

	pthread_detach(pid);
	return 0;
}

/* 
 * Name:  main_loop
 * Description:  
 */ 
int
main_loop() 
{
	int cnt = 0;

	for ( ;; ) 
	{
		printf ( "count is:%d\n", cnt );
		sleep(1);
		cnt++;
		if ( sign_work == 1 )
			printf ( "sign works\n" );
	}

	return 0;
}    


/* 
 * Name:  change_sign_work
 * Description:  
 */ 
void
change_sign_work(int signal) 
{
	switch ( signal )
	{
		case SIGUSR1:
			printf ( "receive signal SIGUSR1\n" );
			sign_work = 1;
			break;

		default:	
			break;
	}
}    

/* 
 * Name:  branch_sig
 * Description:  
 */ 
void *
branch_sig(void *arg ) 
{
	int sig = getpid();

	if ( 1 ) 
	{
		sleep(5);
		cout << "kill signal SIGUSR1" << endl;
		kill(sig, SIGUSR1);
	}

	return NULL;
}    

int
main(int argc, char *argv[])
{
	signal(SIGUSR1, change_sign_work);
	create_thread(branch_sig);
	main_loop();
	
	return 0;
}
