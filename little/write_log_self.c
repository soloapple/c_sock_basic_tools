/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: write_log_self.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月11日 01时29分00秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月11日                  build this moudle  
 *****************************************************************************/
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

#include <string.h>
#include <assert.h>

int main( int argc, char* argv[] )
{
	int logfd = open( "/root/log.self", O_RDWR | O_CREAT | O_APPEND, 0644 );
	assert( -1 != logfd );

	close( STDERR_FILENO );
	dup2( logfd, STDERR_FILENO );
	close( logfd );

	openlog( NULL, LOG_PERROR, LOG_DAEMON );
	syslog( LOG_DEBUG, "%i\n", time( NULL ) );

	return 0;
}
