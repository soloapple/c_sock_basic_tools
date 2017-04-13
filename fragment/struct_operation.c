/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: struct_operation.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年03月31日 22时34分02秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年03月31日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stddef.h>

struct stuff{
	char name[16];
};

struct stuff array[]={
	{"The"},
	{"quick"},
	{"brown"},
	{"fox"},
	{"jumped"},
	{"over"},
	{"the"},
	{"lazy"},
	{"dog."},
	{""}
};

int 
main()
{
	struct stuff   *p0= & array[0];
	struct stuff   *p8= & array[8]; 

	ptrdiff_t      diff = p8 - p0; 
	ptrdiff_t      addr_diff = (char*)p8 - (char*)p0;

	printf("&array[0]=p0=%p\n", (void*)p0);
	printf("&array[8]=p8=%p\n", (void*)p8);

	printf("The difference of pointers is %ld\n", (long)diff); 
	printf("The difference of addresses is %ld\n", (long)addr_diff);

	printf("p8-8=%p\n", (void*)(p8-8));
	printf("p0+8=%p(same as p8)\n", (void*)(p0+8));

	return 0;
}           
