/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: cpu_sets.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   10/23/16 22:22:01
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/23/16                  build this moudle  
 ***************************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>


#include<sched.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>
#define THREAD_MAX_NUM 100  


int num=0; 

void* threadFun(void* arg) 
{
	cpu_set_t mask; 
	cpu_set_t get; 
	int *a = (int *)arg; 
	printf("the a is:%d\n",*a);

	CPU_ZERO(&mask); 
	CPU_SET(*a, &mask);

	if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
	{
		printf("warning: could not set CPU affinity, continuing...\n");
	}

	CPU_ZERO(&get);
	if (sched_getaffinity(0, sizeof(get), &get) == -1)
	{
		printf("warning: cound not get thread affinity, continuing...\n");
	}

	while (1)
	{
		int i;
		for (i = 0; i < num; i++)
		{
			if (CPU_ISSET(i, &get))
			{
				printf("this thread %d is running processor : %d\n", pthread_self(),i);
				sleep(1);
			}
		}
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	num = sysconf(_SC_NPROCESSORS_CONF);
	pthread_t thread[THREAD_MAX_NUM];
	printf("system has %i processor(s). \n", num);

	int tid[THREAD_MAX_NUM];
	int i;
	for(i=0;i<num;i++)
	{
		tid[i] = i;
		pthread_create(&thread[i],NULL,threadFun,(void*)&tid[i]);
	}

	for(i=0; i< num; i++)
	{
		pthread_join(thread[i],NULL);
	}
	return 0;
}
