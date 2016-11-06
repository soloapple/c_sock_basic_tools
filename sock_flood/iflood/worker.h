/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: worker.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/26/16 12:46:37
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/26/16                  build this moudle
 ***************************************************************************************/

#include "system.h"

#include <pthread.h>

void *foo(void*);
void max_thread();
void c_process(char *ip, char *port, char *file, int link_num, int link_mode, int interval, int times);
void s_process(char *ip, char *port);
int w_mission_start(char *ip, char *port, char *file);
int w_short_mission_start(char *ip, char *port, char *t_buf, int n_read);
