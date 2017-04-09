/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: signal.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月09日 16时55分20秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月09日                  build this moudle  
 *****************************************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void
sig_in_sig(int sig)
{
	printf ( "sig in sig\n", sig );
}

void 
ouch(int sig)
{
    printf("I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
	(void) signal(SIGINT, sig_in_sig);
}

int main()
{
    (void) signal(SIGINT, ouch);

    while(1)
    {
        printf("hello world...\n");
        sleep(1);
    }
}

