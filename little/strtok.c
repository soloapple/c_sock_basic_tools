/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: strtok.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月27日 15时41分56秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月27日                  build this moudle  
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	char *tok;
	char *options = (char*)("123	nnn	ss	tt	");
	options = strdup(options);

	for (tok = strtok(options, " \t,"); tok; tok = strtok(NULL," \t,")) {	
		printf ( "tok:%s\n", tok );
	}

	free(options);
	return 0;
}
