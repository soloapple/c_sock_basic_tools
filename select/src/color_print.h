/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: color_print.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/05/16 14:54:42
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/05/16                  build this moudle
 ***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define COL_WHITE   "\033[40;37m"
#define COL_BULE    "\033[40;36m"
#define COL_PURPLE  "\033[40;35m"
#define COL_BLUE	"\033[40;34m"
#define COL_YELLOW  "\033[40;33m"
#define COL_GREEN   "\033[40;32m"
#define COL_RED     "\033[40;31m"
#define COL_END     "\033[0m"

#define	 MLEVEL 10

#if ( MLEVEL >= 4 )
	#define MLOG_NOTICE
	#define MLOG_DEBUG
	#define MLOG_WARNING
	#define MLOG_ERROR
#elif ( MLEVEL >= 3 )
	#define MLOG_DEBUG
	#define MLOG_WARNING
	#define MLOG_ERROR
#elif ( MLEVEL >= 2 )
	#define MLOG_WARNING
	#define MLOG_ERROR
#elif ( MLEVEL >= 1 )
	#define MLOG_ERROR
#endif

#ifdef MLOG_NOTICE
#define LOGN(fmt, args...)                                           \
	do {                                                             \
		printf(COL_WHITE "[NOTIC][%-20s:%-4d] " COL_END"%s: " fmt,   \
				__FILE__, __LINE__, __FUNCTION__, ##args);           \
	} while (0);

#define LOGNP(fmt, args...)                                          \
	do {                                                             \
		printf(COL_WHITE "[NOTIC][%-20s:%-4d] [%d] " COL_END fmt,    \
				__FILE__, __LINE__, getpid(), ##args);               \
	} while (0);

#else
#define LOGN(fmt, ...)
#define LOGNP(fmt, ...)
#endif

#ifdef MLOG_DEBUG
#define LOGD(fmt, args...)                                           \
	do {                                                             \
		printf(COL_GREEN "[DEBUG][%-20s:%-4d] " COL_END"%s: " fmt,    \
				__FILE__, __LINE__, __FUNCTION__, ##args);           \
	} while (0);													

#define LOGDP(fmt, args...)                                          \
	do {                                                             \
		printf(COL_GREEN "[DEBUG][%-20s:%-4d] [%d] " COL_END fmt,   \
				__FILE__, __LINE__, getpid(), ##args);               \
	} while (0);
#else
#define LOGD(fmt, ...)
#define LOGDP(fmt, ...)
#endif

#ifdef MLOG_WARNING
#define LOGW(fmt, args...)                                           \
	do {                                                             \
		printf(COL_YELLOW "[WARNING][%-20s:%-4d] " COL_END"%s: " fmt,\
				__FILE__, __LINE__, __FUNCTION__, ##args);           \
	} while (0);													

#define LOGWP(fmt, args...)                                          \
	do {                                                             \
		printf(COL_YELLOW "[WARNING][%-20s:%-4d] [%d] " COL_END fmt, \
				__FILE__, __LINE__, getpid(), ##args);               \
	} while (0);
#else
#define LOGW(fmt, ...)
#define LOGWP(fmt, ...)
#endif

#ifdef MLOG_ERROR 
#define LOGE(fmt, args...)                                           \
	do {                                                             \
		printf(COL_RED "[ERROR][%-20s:%-4d][%s] "COL_END "%s: " fmt, \
				__FILE__, __LINE__, __FUNCTION__,                    \
				strerror(errno), ##args);                            \
	} while (0);

	#define LOGEP(fmt, args...)                                      \
	do {                                                             \
		printf(COL_RED "[WARNING][%-20s:%-4d] [%d] " COL_END fmt,    \
				__FILE__, __LINE__, getpid(), ##args);               \
	} while (0);
#else
#define LOGE(fmt,...)
#define LOGEP(fmt,...)
#endif

