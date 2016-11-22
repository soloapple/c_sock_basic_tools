/******************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: epoll.h
 * Description: most file descriptor is 1024*1024
 *				epoll will accept this num socket file client.
 *     Version: 1.0
 *     Created: soloapple   11/22/16 05:14:38
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/22/16                  build this moudle
 *****************************************************************************/

#ifndef  EPOLL_INCLUDE
#define  EPOLL_INCLUDE

#define	MAX_EVENT_NUMBER 1024
const int EP_TM_OUT = 10;

void s_process_epoll(char *ip, char *port);

#endif   
