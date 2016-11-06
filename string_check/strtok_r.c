/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: strtok_r.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/07/16 15:45:01
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/07/16                  build this moudle  
 ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	int
main(int argc, char *argv[])
{
	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	printf ( "argv1:%s\n", argv[1]);
	printf ( "argv2:%s\n", argv[2]);
	printf ( "argv3:%s\n", argv[3]);

//	char *buffer = "'mode=system' 'msg=testmsg'";	
//	char *a1 = "a/bbb///cc;xxx:yyy:";
//	char *a2 = ":;";
//	char *a3 = "/";

	char *saveptr;
	char *p = strtok_r(argv[1], argv[2], &saveptr);
	printf ( "%s\n", p );

	p = strtok_r(NULL, argv[2], &saveptr);
	printf ( "%s\n", p );
	p = strtok_r(NULL, argv[2], &saveptr);
	printf ( "%s\n", p );

	return 9;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s string delim subdelim\n",
				argv[0]);
		exit(EXIT_FAILURE);
	}

	for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
		token = strtok_r(str1, argv[2], &saveptr1);
		if (token == NULL)
			break;
		printf("%d: %s\n", j, token);

		for (str2 = token; ; str2 = NULL) {
			subtoken = strtok_r(str2, argv[3], &saveptr2);
			if (subtoken == NULL)
				break;
			printf(" --> %s\n", subtoken);
		}
	}

	exit(EXIT_SUCCESS);
}
