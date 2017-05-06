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
#include "hex_print.h"

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
	//multi_thread_test();
	cut_false_sharing(argc, argv);

	//epoll_debug();
	//hex_print("this is dymatic hex print");

//	int status = 0;
//	status = fork();
//	if (status == 0) 
//	{
//		send_msg();	
//	} 
//	else 
//	{
//		sleep(1);
//		puts("recv run");
//		recv_msg();			
//	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
