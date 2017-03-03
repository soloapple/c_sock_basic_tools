/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: strftime.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月07日 15时58分27秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月07日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <time.h>

int 
main()
{
	char *format[] = {"%I: %M: %S %p %m/%d %a", "%x %X %Y", NULL};
	char buf[30];
	int i;
	time_t clock;
	struct tm *tm;

	time(&clock);
	tm = localtime(&clock);

	for(i = 0; format[i] != NULL; i++)
	{
		strftime(buf, sizeof(buf), format[i], tm);
		printf("%s => %s\n", format[i], buf);
	}

	return 0;
}
