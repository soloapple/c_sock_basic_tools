/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *   
 *    Filename: write_syslogng_to_file.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月12日 21时56分44秒
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月12日                  build this moudle
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

typedef enum {
	SZ_SLEEP = 5,
	SZ_FNAME = 256,
	SZ_LINE = 2048,
} SZ_COMM;				

#include <iostream>

using namespace std;


