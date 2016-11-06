/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: union_in_mempool.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/01/16 04:37:49
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/01/16                  build this moudle  
 ***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */


union obj {
	union obj *free_list_link;
	char client_data[2];
};				/* ----------  end of union obj  ---------- */

typedef union obj Obj;

	int
main ( int argc, char *argv[] )
{
	Obj *free_list[128];

	Obj x;
	Obj m;
	Obj n;

	printf ( "size of Obj:%d\n", sizeof(Obj) );
	printf ( "size of free link list:%d\n", sizeof(x.free_list_link) );
	printf ( "size of client data:%d\n", sizeof(x.client_data) );

	x.free_list_link = &m;
	printf ( "x addr: %p\n", &x );
	printf ( "x clidata: %p\n", x.client_data );
	printf ( "x clidata: %08p\n", &(x.client_data[0]) );

	printf ( "m addr: %p\n", &m );
	printf ( "m clidata: %p\n", m.client_data );
	printf ( "m clidata: %08p\n", &(m.client_data[0]) );

	m.free_list_link = &n;
	printf ( "n addr: %p\n", &n );
	printf ( "n clidata: %p\n", n.client_data );
	printf ( "n clidata: %08p\n", &(n.client_data[0]) );

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
