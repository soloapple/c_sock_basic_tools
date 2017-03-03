/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: trans_time_to_seconds.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月07日 16时06分26秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月07日                  build this moudle  
 *****************************************************************************/
#include <time.h>
#include <stdarg.h>
#include <iostream>

using namespace std;

time_t
get_time_t(char *time_fixed_format)
{
    int tff_year;
    int tff_mon;
    int tff_mday;
    int tff_hour;
    int tff_min;
    int tff_sec;
    
    sscanf(time_fixed_format, "%d-%d-%d %d:%d:%d", 
            &tff_year, &tff_mon, &tff_mday,
            &tff_hour, &tff_min, &tff_sec
            );  

    struct tm t;
    time_t tm_of_day;

    t.tm_year = tff_year - 1900;
    t.tm_mon = tff_mon - 1;
    t.tm_mday = tff_mday;
    t.tm_hour = tff_hour;
    t.tm_min = tff_min;
    t.tm_sec = tff_sec;
    t.tm_isdst = 0;
    tm_of_day = mktime(&t);

    return tm_of_day;
}

int
main()
{
	time_t t;
	t = get_time_t("2010-01-28 16:41:31");
	cout << "time: " << t << endl;

	t = get_time_t("1970-01-01 01:00:00");
	cout << "time: " << t << endl;

	return 0;
}
