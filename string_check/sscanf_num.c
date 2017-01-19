/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: sscanf_num.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年01月14日 04时00分39秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年01月14日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main()
{
	char log_time[32];
	char log_fac[32];
	char log_sev[32];
	char log_mod[32];

	char *line = "2017-01-14 03:56:31,local3,warning:mode=1,msg=\"suli\";";
	int ret = sscanf(line, "%[^,],%[^,],%[^:]:%[^,]", 
			log_time, log_fac, log_sev, log_mod);
	printf ( "%d\n", ret );
	printf ( "%s,%s,%s,%s\n", log_time, log_fac, log_sev, log_mod );

	return 0;
}
