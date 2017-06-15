/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: strftime.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��02��07�� 15ʱ58��27��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��02��07��                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <time.h>
#include <stddef.h>
//#include <alsa/global.h>

//void 
//getNowTime()
//{
//    struct timespec time;
//    clock_gettime(CLOCK_REALTIME, &time);  //��ȡ�����1970�����ڵ�����
//    struct tm now;
//    localtime_r(&time.tv_sec, &now);
//    char current[1024];
//    sprintf(current, "%04d%02d%02d%02d:%02d:%02d", now.tm_year + 1900, now.tm_mon+1, now.tm_mday, 
//      now.tm_hour, now.tm_min, now.tm_sec);
//	printf ( "%s\n", current );
//}

int 
sec_now()
{
	time_t timer;//time_t����long int ����
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	printf("Local time is: %s\n", asctime(tblock));
	return 0;
}

int 
main()
{
//	getNowTime();
	sec_now();
	return;

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
