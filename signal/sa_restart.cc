/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: sa_restart.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月09日 16时37分15秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月09日                  build this moudle  
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void 
int_handler (int signum)
{
	printf ("int handler %d\n",signum);
}	
	
int 
main(int argc, char **argv)
{
	char buf[100];
	ssize_t ret;
	struct sigaction oldact;
	struct sigaction act;
	
	act.sa_handler = int_handler;
	act.sa_flags=0;
	act.sa_flags |= SA_RESTART;
	sigemptyset(&act.sa_mask);
	if ( -1 == sigaction(SIGINT, &act, &oldact) )
	{
		printf("sigaction failed!\n");
		return -1;
	}
	
	bzero(buf,100);
	
	ret = read(STDIN_FILENO, buf, 10);
	if (ret == -1)
	{
		printf ("read error %s\n", strerror(errno));
	}

	printf ("read %d bytes, content is %s\n", ret, buf);

	sleep (10);

	return 0;
}
