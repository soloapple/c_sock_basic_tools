/***************************************************************************************
 *   Copyright (C), 2006-2015, HelloWorld Technology Co., Ltd.
 *   
 *    Filename:  common.h
 * Description:  Common use
 *     Version:  1.0
 *     Created:  Liujfa   05/07/15 21:48:51
 *    Revision:  none
 *      
 *     History:  <author>   <time>    <version >         <desc>
 *               Liujfa   05/07/15                  build this moudle
 ***************************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef unsigned char        U8;
typedef unsigned short       U16;
typedef unsigned int         U32;
typedef unsigned long long   U64;

typedef char      S8;
typedef short     S16;
typedef int       S32;
typedef long long S64;

typedef enum size_str_e
{
	SIZE_NAME_SHORT  = 32,
	SIZE_NAME_NORMAL = 64,
	SIZE_NAME_LONG   = 1024,
	SIZE_LINE_SHORT  = 256,
	SIZE_LINE_NORMAL = 1024,
	SIZE_LINE_LONG   = 8192
} SIZE_STR_E;

#define COL_WHITE   "\033[40;37m"
#define COL_BULE    "\033[40;36m"
#define COL_PURPLE  "\033[40;35m"
#define COL_GREEN   "\033[40;32m"
#define COL_RED     "\033[40;31m"
#define COL_END     "\033[0m"

/* Define debug printf */
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
		printf(COL_WHITE "[NOTIC][%-20s:%-4d] " COL_END fmt,         \
				__FILE__, __LINE__, ##args);                         \
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
		printf(COL_PURPLE "[DEBUG][%-20s:%-4d] " COL_END fmt,        \
				__FILE__, __LINE__, ##args);                         \
	} while (0);

#define LOGDP(fmt, args...)                                          \
	do {                                                             \
		printf(COL_PURPLE "[DEBUG][%-20s:%-4d] [%d] " COL_END fmt,   \
				__FILE__, __LINE__, getpid(), ##args);               \
	} while (0);
#else
#define LOGD(fmt, ...)
#define LOGDP(fmt, ...)
#endif

#ifdef MLOG_WARNING
#define LOGW(fmt, args...)                                           \
	do {                                                             \
		printf(COL_GREEN"[WARNN][%-20s:%-4d] "COL_END"%s: " fmt,     \
				__FILE__, __LINE__, __FUNCTION__, ##args);           \
	} while (0);
#else
#define LOGW(fmt,...)
#endif

#ifdef MLOG_ERROR 
#define LOGE(fmt, args...)                                           \
	do {                                                             \
		printf(COL_RED "[ERROR][%-20s:%-4d][%s] "COL_END "%s: " fmt, \
				__FILE__, __LINE__, __FUNCTION__,                    \
				strerror(errno), ##args);                            \
	} while (0);
#else
#define LOGE(fmt,...)
#endif

#define ASSERT(RET, FUNC)                                            \
	if ( RET != FUNC ) {                                             \
		LOGW(""#FUNC" return not "#RET"\n");                         \
		goto _E1;                                                    \
	}

#define ASSERT_FAIL(RET, FUNC)                                       \
	if ( RET == FUNC ) {                                             \
		LOGW(""#FUNC" return is "#RET"\n");                          \
		goto _E1;                                                    \
	}

/* Define return value */
#define SUCCESS  (0)
#define FAILURE  (-1)
#define TIMEOUT  (-2)
#define RETRY    (1)

/* Socket option */
#define MAX_SNDBUF				(64*1024)	/* max buffer length send */
#define MAX_RCVBUF				(64*1024)	/* max buffer length recv */

#endif //_COMMON_H_
