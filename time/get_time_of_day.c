/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: get_time_of_day.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��06��11�� 05ʱ17��22��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��06��11��                  build this moudle  
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	printf("second:%ld\n",tv.tv_sec);  

	sleep(3);

	gettimeofday(&tv,NULL);
	printf("second:%ld\n",tv.tv_sec);  

	return 0;
}
