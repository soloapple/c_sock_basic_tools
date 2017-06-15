/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: fgets.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月13日 21时53分25秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月13日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char line[10] = {0};
	line[10] = '\n';

	while ( fgets(line, 9, stdin) )
	{
		printf("%s\n", line);
	}
	
	return 0;
}
