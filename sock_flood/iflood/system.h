/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: system.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/20/16 01:26:16
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/20/16                  build this moudle
 ***************************************************************************************/

#ifndef  system_INCLUDE
#define  system_INCLUDE

#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <dlfcn.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include <sys/wait.h>
#include <assert.h>

#define	true 1				/*  */
#define	false -1			/*  */

#endif   /* ----- #ifndef system_INC  ----- */
