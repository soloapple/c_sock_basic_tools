/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: kuohao.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月17日 03时05分53秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月17日                  build this moudle  
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>


/* 
 * Name:  foo2
 * Description:  
 */ 
int
foo2( ) 
{
	{
#ifdef  DEBUG 
		printf ( "not define3\n" );	
#endif
	}

	return 0;
}    

/* 
 * Name:  foo1
 * Description:  
 */ 
int
foo1( ) 
{
	{
#ifdef  DEBUG 
		printf ( "not define1\n" );	
#endif
	}

	{
#ifndef  DEBUG
#define	 DEBUG
		printf ( "debug\n" );	
#endif
	}
	
	{
#ifdef  DEBUG 
		printf ( "not define2\n" );	
#endif
	}



	return 0;
}    

int
main(int argc, char *argv[])
{
	foo1();	
	foo2();
	return 0;
}
