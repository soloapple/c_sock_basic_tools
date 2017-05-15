/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: main.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月15日 12时34分31秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月15日                  build this moudle  
 *****************************************************************************/
#include "mempool.h"
#include "error_log_deal.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define	MP_ERR_LOG_COUNT 8192

struct mem_pool *g_mp_err_log;

char *err_log_file = PATH_ERRLOG;

int init_err_log_thread();
int create_thread(void*(*thread_func)(void*));

void
quit_sys()
{
	if ( g_mp_err_log )
		mp_free(&g_mp_err_log);
}

int
init_err_log_thread()
{
	g_mp_err_log = mp_init(MP_DEFAULT_BLOCK_SIZE, MP_ERR_LOG_COUNT);
	if ( !g_mp_err_log )
		return -1;    

	if ( create_thread(err_log_get_list) < 0 ) 
		return -1; 

	return 0;
}

int
create_thread(void*(*thread_func)(void*))
{
    int res;
    pthread_t pid;

    res = pthread_create(&pid,NULL, thread_func, NULL);
    if ( res != 0 ) 
    {   
        err_log_put_list(err_log_create_thread, __LINE__);

        return -1; 
    }   

    pthread_detach(pid);

    return 0;
}

int
main(int argc, char *argv[])
{
	init_err_log_thread();

	err_log_put_list(__FILE__, __LINE__);	
	err_log_put_list("hello, error", __LINE__);	

	sleep(1);

	return 0;
}
