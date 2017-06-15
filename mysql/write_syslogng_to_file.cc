/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: write_syslogng_to_file.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月12日 03时58分13秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月12日                  build this moudle  
 *****************************************************************************/
#include "write_syslogng_to_file.h"
const char log_file[] = "/mnt/log/ftp_up.log";
FILE *fp_log;
static int flg_file_rewrite;

/* 
 * Name:  open_log_file
 * Description:  
 */ 
FILE *
open_log_file() 
{
	fp_log = fopen(log_file, "a+");
	if ( fp_log == NULL )
	{
		printf ( "open file %s failed!\n", log_file );
		return NULL;
	}

	return fp_log;
}    

/* 
 * Name:  get_log_lines
 * Description:  
 */ 
void
get_log_lines_to_write() 
{
	time_t timep;
	struct tm *p;
	int len, ret;
	char line[SZ_LINE];
	char log_bak[SZ_FNAME];
	char debug[SZ_LINE];
	
	if ( open_log_file() == NULL )
		return;

	while ( fgets(line, SZ_LINE, stdin) )
	{
		len = fwrite(line, strlen(line), 1, fp_log);
		fflush(fp_log);

		sprintf(debug, "bilibili %d\n", flg_file_rewrite);
		len = fwrite(debug, strlen(debug), 1, fp_log);
		fflush(fp_log);

		if ( flg_file_rewrite )
		{
			time(&timep); 
			p = gmtime(&timep);

			sprintf(log_bak, "/mnt/log/log_%04d%02d%02d.txt", 
					1900 + p->tm_year, (1 + p->tm_mon), p->tm_mday);
			flg_file_rewrite = 0;
			fclose(fp_log);

			remove(log_bak);
			ret = rename(log_file, log_bak);
			if ( ret == -1 )
			{
				printf ( "rename failed\n" );
			}

			open_log_file();
		}
	}
}    

int
comp_time(time_t *tm_old, time_t *tm_new) 
{
	struct tm *p_tm_old;
	struct tm *p_tm_new;
	long int day_old;
	long int day_new;
	
	p_tm_old = gmtime(tm_old);
	day_old = p_tm_old->tm_mday;

	p_tm_new = gmtime(tm_new);
	day_new = p_tm_new->tm_mday;

	if ( (day_new != day_old) )
	{
		*tm_old = *tm_new;	
		return 1;
	}
		
	return 0;
} 

int
get_timestamp(time_t *tm_old)
{
	time_t tm_new = time(&tm_new);

	if ( comp_time(tm_old, &tm_new) > 0 )
		return 1;
	
	return 0;
}

void *	
thd_timer(void *arg) 
{
	time_t tm_old = time(&tm_old);

	for ( ;; ) 
	{
		if ( get_timestamp(&tm_old) > 0 )
		{
			flg_file_rewrite = 1;	
		}

		sleep(SZ_SLEEP);
	}
}

int
create_thread(void*(*thread_func)(void*))
{
	int res;
	pthread_t pid;

	res = pthread_create(&pid,NULL, thread_func, NULL);
	if ( res != 0 ) 
	{
		printf ( "create thread failed!\n" );
		return -1;
	}

	pthread_detach(pid);

	return 0;
}

void
quit_sys()
{
	if ( fp_log )
	{
		fflush(fp_log);
		fclose(fp_log);
		fp_log = NULL;
	}
}

void
sig_quit(int signal)
{
	switch ( signal )
	{
		case SIGINT:
		case SIGSEGV:
		case SIGILL:
			quit_sys();
			break;
	}

	exit(0);
}

int
main(int argc, char *argv[])
{
	signal(SIGINT, sig_quit);
	signal(SIGSEGV, sig_quit);
	signal(SIGILL, sig_quit);

	if ( create_thread(thd_timer) < 0 )
		goto __end;

	get_log_lines_to_write();

__end:
	return 0;
}
