/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *   
 *    Filename: error_log_deal.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年03月27日 05时12分52秒
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年03月27日                  build this moudle
 *****************************************************************************/
#ifndef  ERROR_LOG_DEAL_INCLUDE
#define  ERROR_LOG_DEAL_INCLUDE

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common.h"
#include "mempool.h"

#define	ERR_LOG_FILE_CHECK_TIME 3
#define	ERR_LOG_FILE_CHECK_ROWS 10 
#define	ERR_LOG_FILE_MAX_SIZE 	2048 * 1024
#define	ERR_LOG_WAIT_TIME		10000

const char err_log_create_thread[] = "create thread error!";

void err_log_put_list(const char *log, int line);
void *err_log_get_list(void *args);
int  write_err_log_to_file(char *log);
int  monitor_file_size(const char *log_file_path);

#endif   
