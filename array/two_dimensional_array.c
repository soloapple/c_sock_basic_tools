/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: two_dimensional_array.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月03日 07时18分57秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月03日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef enum {
	SZ_LITTLE = 4,
	SZ_SHORT = 8,
	SZ_INT = 16,
	SZ_LONG = 32,
	SZ_LABEL = 64,
	SZ_LINE = 1024,
	SZ_BUFF = 4096,
	SZ_FILE = 8192,
	SZ_SUPER = 40960,	
} SZ_COMM;				

char ss[][SZ_LITTLE] = 
{
	"XSS",
	"Y",
	"Z",
	"!"
};

int
main(int argc, char *argv[])
{
	printf ( "%d\n", sizeof(char) );
	printf ( "row:%d\n", sizeof(ss)/sizeof(ss[0]) );
	printf ( "col:%d\n", sizeof(ss)[0]/sizeof(char));
	
	return 0;
}				
