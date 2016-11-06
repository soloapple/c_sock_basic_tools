/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: iproxy.c
 * Description: for all data transfer.
 *     Version: 1.0
 *     Created: soloapple   07/21/16 21:54:44
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   07/21/16                  build this moudle  
 ***************************************************************************************/



#include <stdlib.h>
#include <stdio.h>
#include "../dynamic_lib/hex_print.h"
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	printf ( "iproxy start!\n" );

	epoll_debug();
	hex_print("this is dymatic hex print");

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
