/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: thread_counts.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/23/16 14:37:43
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/23/16                  build this moudle  
 ***************************************************************************************/

#include "unlock_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static QUEUE *q_local;
static QUEUE *q_remote;

void
deal_with_msg_line ( int *nonius)
{
	printf ( "nonius is:%d\n", *nonius );

	if (*nonius == 10)
	{
		printf ( "take 10 to 0\n" );
		*nonius == 0;
	}

	/* ----- bracket is very important ----- */
	(*nonius)++;

	return ;
}



void *
push_data_local_mysql ( void *arg )
{
	void *data = NULL;
	char *line;
	static int nonius = 0;
	
	for(;;)
	{
		data = queue_de(q_local);
		if(data != NULL)
		{
			printf ( "O get\n" );
			deal_with_msg_line (&nonius);
		}

		usleep(10);
	}

	return NULL;
}



void *
push_data_remote_mysql ( void *arg )
{
	char *line;
	void *data = NULL;
	static int nonius = 0;

	for (;;)
	{
		data = queue_de(q_remote);
		if(data != NULL)
		{
			printf ( "A get\n" );
			deal_with_msg_line (&nonius);
		}

		usleep(10);
	}

	return NULL;
}


int 
main(int argc, char* argv)
{
	int result;	

	q_local = queue_create();
	if (q_local == NULL)
		return 0;

	q_remote = queue_create();
	if (q_remote == NULL)
		return 0;

	pthread_t pid_local;
	pthread_t pid_remote;	

	result = pthread_create(&pid_local,NULL, push_data_local_mysql,NULL);
	if (result != 0) 
		return -1;

	result = pthread_create(&pid_remote,NULL,push_data_remote_mysql,NULL);
	if (result != 0) 
		return -1;

	char cmd[512] = {0};

	char buf[BUFSIZ];
	char log_facility[128];

	char *line;
	static int i;

	while(fgets(buf, sizeof(buf), stdin))
	{
		if (i%2==0)
		{
			printf ( "add O\n" );
			queue_en(q_local, buf);
		}
		else
		{
			printf ( "add A\n" );
			queue_en(q_remote, buf);		
		}
		
		i++;
	}

	pthread_join(pid_local, NULL);
	pthread_join(pid_remote, NULL);

	exit(0);
}
