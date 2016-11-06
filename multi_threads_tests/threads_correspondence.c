/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: threads_correspondence.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/14/16 20:31:48
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/14/16                  build this moudle  
 ***************************************************************************************/

#include<stdio.h>  
#include<memory.h>  
#include<pthread.h>  

int buf[1000000];  
int w=0,r=0;
int size=10;
pthread_mutex_t lock;
pthread_cond_t is_empty;
pthread_cond_t is_full;

void *sender(void *a) 
{  
	int i,j,k;  

	for(i=1;i<=100;i++)
	{  
		pthread_mutex_lock(&lock);
		
		if(w-r>size)
			pthread_cond_wait(&is_full,&lock);
		
		buf[w++]=i;
		printf("sender--->%d\n",i);
		
		pthread_cond_signal(&is_empty);
		pthread_mutex_unlock(&lock);
	}  
	return ;  
}  

void *receiver(void *a)
{  
	int x;  
	while(1)  
	{  
		pthread_mutex_lock(&lock);

		if(r==w)
			pthread_cond_wait(&is_empty,&lock);

		x=buf[r++];
		if(x!=0)  
			printf("receiver--->%d\n",x);
		else  
			break;

		pthread_cond_signal(&is_full);
		pthread_mutex_unlock(&lock); 
	}  
	return ;  
}  

int main()  
{  
	memset(buf,0,sizeof(buf));  
	pthread_t a,b;

	pthread_mutex_init(&lock,NULL);  
	pthread_cond_init(&is_full,NULL);  
	pthread_cond_init(&is_empty,NULL);  

	pthread_create(&a,NULL,sender,0);  
	pthread_create(&b,NULL,receiver,0);  

	void *recycle;

	pthread_join(a,&recycle);
	pthread_join(b,&recycle);

	return 0;  
}  
