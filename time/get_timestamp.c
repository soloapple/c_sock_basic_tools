/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: get_timestamp.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月04日 20时26分18秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月04日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int 
main()
{
	for (;;)
	{
//		char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		time_t timep;
		struct tm *p;
		time(&timep); /*获得time_t结构的时间，UTC时间*/
		p = gmtime(&timep); /*转换为struct tm结构的UTC时间*/

		printf("%d/%d/%d \n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
//		printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour,
//				p->tm_min, p->tm_sec);

//		if ( (p->tm_hour == 20) && (p->tm_min == 36) && (p->tm_sec == 0) )
//			printf ( "middile night\n" );

		sleep(1);
	}

	return 0;
}
