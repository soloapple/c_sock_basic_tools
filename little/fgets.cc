/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: fgets.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��06��13�� 21ʱ53��25��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��06��13��                  build this moudle  
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
