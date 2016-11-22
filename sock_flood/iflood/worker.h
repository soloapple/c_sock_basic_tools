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
#ifndef  WORKER_INCLUDE
#define  WORKER_INCLUDE

typedef enum 
{
	SHORT_MODE = 0,
	LONG_MODE = 1
}e_link_mode;

void c_process(char *ip, char *port, char *file, int link_num, int link_mode, int interval, int times);
void s_process(char *ip, char *port);
void w_mission_start(char *ip, char *port, char *file);
void w_short_mission_start(char *ip, char *port, char *t_buf, int n_read);
int w_read_file_to_buf(char *file, char *t_buf);

#endif   
