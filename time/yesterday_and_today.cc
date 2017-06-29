/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: yesterday_and_today.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月28日 06时33分01秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月28日                  build this moudle  
 *****************************************************************************/
#include <time.h>
#include <stdio.h>

int 
main(int argc, char **argv)
{
    time_t tmpcal_ptr = {0};
    struct tm *tmp_ptr = NULL;

    tmpcal_ptr = time(NULL);
    printf("tmpcal_ptr=%d\n", tmpcal_ptr);   

    tmp_ptr = gmtime(&tmpcal_ptr);
    printf("after gmtime, the time is:\n%d %d:%d:%d\n", tmp_ptr->tm_mday, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);

    tmp_ptr = localtime(&tmpcal_ptr);
    printf("after localtime, the time is:\n%d %d:%d:%d\n", tmp_ptr->tm_mday, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);

    return 0;
}
