/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: color_print.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/05/16 14:55:23
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/05/16                  build this moudle  
 ***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "color_print.h"

int
main ( int argc, char *argv[] )
{
	LOGN("%s %s %s\n", "***", "TTT", "***");
	LOGNP("%s %s %s\n", "***", "TTT", "***");
	LOGD("%s %s %s\n", "***", "TTT", "***");
	LOGDP("%s %s %s\n", "***", "TTT", "***");
	LOGW("%s %s %s\n", "***", "TTT", "***");
	LOGE("%s %s %s\n", "***", "TTT", "***");
	
		return 0;
}				
