/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: fdarray.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/22/16 11:01:00
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/22/16                  build this moudle
 *****************************************************************************/

#ifndef  FDARRAY_INCLUDE
#define  FDARRAY_INCLUDE

#define	CLI_SOCK_FD_NUM 20000

void quit_sock_array();
void c_process_fdarray(char *ip, char *port, char *file, int link_num, int link_mode, int interval, int times);

#endif   
