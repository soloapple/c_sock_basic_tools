/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: hash_time.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月07日 13时14分42秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月07日                  build this moudle  
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

const int TIMES = 10000000;
int len = 512;

unsigned int BKDR_hash(char *str)  
{  
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..  
	unsigned int hash = 0;  

	while (*str)  
	{  
		hash = hash * seed + (*str++);  
	}  

	return (hash & 0x7FFFFFFF);  
}  

	int
main(int argc, char *argv[])
{
	unsigned int c;
	float time_use=0;
	struct timeval start;
	struct timeval end;

	unsigned long i = 0;
	string part("一");
	string message;

	cout << "Now here DEBUG" << endl;

	do 
	{
		message = message + part;
	} while ( (i++) < len );				

	cout << "message is:" << message.c_str() << endl;

	gettimeofday(&start,NULL);//gettimeofday(&start,&tz);结果一样
	printf("start.tv_sec:%d\n",start.tv_sec);
	printf("start.tv_usec:%d\n",start.tv_usec);

	char *p = (char *)malloc(1024);
	strcpy(p, message.c_str());

	for ( i = 0 ; i < TIMES ; i++ ) 
	{
		c = BKDR_hash(p);	
	}

	gettimeofday(&end,NULL);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒

	printf("end.tv_sec:%d\n",end.tv_sec);
	printf("end.tv_usec:%d\n",end.tv_usec);
	printf("time_use is %f\n",time_use);
	printf ( "speed is %f tiao/s, single tiao length is %d\n", TIMES/time_use*1000000, len );

	printf ( "%d\n", TIMES );

	if ( p )
	{
		free(p);
		p = NULL;
	}

	return 0;
}
