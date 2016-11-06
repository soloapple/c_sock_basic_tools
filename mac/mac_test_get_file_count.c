/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: a.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/19/16 08:08:12
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/19/16                  build this moudle  
 ***************************************************************************************/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GET_FIELD_COUNT(msg, n_field) \
{\
	int len = strlen(msg);\
	for (len; len>0; len--)\
	{\
		if(msg[len] == ' ')\
			n_field++;\
	}\
}


int
main ( int argc, char *argv[] )
{
	char line[] = "sss 1 1 1 1";
	int count;
	GET_FIELD_COUNT(line, count);
	printf ( "%d\n", count );

	return EXIT_SUCCESS;
}			
