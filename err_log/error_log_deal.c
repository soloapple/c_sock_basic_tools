/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: error_log_deal.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年03月27日 05时13分56秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年03月27日                  build this moudle  
 *****************************************************************************/
#include "error_log_deal.h"

extern char *err_log_file;
extern char *sql_fac_conf;  
extern char *sql_login_conf;
extern char *sql_table_conf;

extern struct mem_pool *g_mp_err_log;

void *
err_log_get_list(void *args)
{
	char *log = NULL;

	for (;;)
	{
		log = mp_get_read(g_mp_err_log);
		write_err_log_to_file(log);
		mp_set_read_to_next(g_mp_err_log);
	}

	return NULL;
}	

void 
err_log_put_list(const char *log, int line)
{
	char *buf;

	buf = mp_get_write(g_mp_err_log);
	sprintf(buf, "[%-20s %4d] [%d]:%s\n", __FILE__, line, getpid(), log);

	if ( buf )
		mp_set_write_to_next(g_mp_err_log);	

	return;
}	

int	
write_err_log_to_file(char *log)
{	
	long int file_size;
	FILE *fp;

	fp = fopen(err_log_file, "a+");
	if( fp == NULL )
	{
		return -1;
	}

	fwrite(log, 1, strlen(log), fp);
	fflush(fp);
	fclose(fp);

	/* 
	 * back up error log info if it is oversize. 
	 * after that, rewrite it. 
	 */
	file_size = monitor_file_size(err_log_file);
	if ( file_size > ERR_LOG_FILE_MAX_SIZE )
	{
		int ret;
		char err_log_file_bak[1024];

		sprintf(err_log_file_bak, "%s.bak", err_log_file);

		ret = rename(err_log_file, err_log_file_bak);
		if (ret != 0)
			printf("Rename Error Log %s failed!\n", err_log_file);
	}

	return 1;
}		

int
monitor_file_size(const char *log_file_path)
{
	unsigned long file_size = -1;
	struct stat file_stat;	
	
	if ( stat(log_file_path, &file_stat) == 0 )
		file_size = file_stat.st_size;

	return file_size;
}		


