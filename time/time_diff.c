/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: time_diff.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月09日 02时09分17秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月09日                  build this moudle  
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

	//struct timezone tz; //后面有说明

	gettimeofday(&start,NULL);//gettimeofday(&start,&tz);结果一样
	printf("start.tv_sec:%d\n",start.tv_sec);
	printf("start.tv_usec:%d\n",start.tv_usec);

	sleep(3);

	gettimeofday(&end,NULL);
	printf("end.tv_sec:%d\n",end.tv_sec);
	printf("end.tv_usec:%d\n",end.tv_usec);

	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %f\n",time_use);

	//输出：time_use is 3001410.000000
	//下面的采用指针的方式也可以，但是要注意指针类型若不分配内存的话，编译正确，但是运行结果会不对
}
