/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: signal_block.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年04月09日 17时12分54秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年04月09日                  build this moudle  
 *****************************************************************************/
#include <signal.h>  
#include <stdio.h>  
#include <unistd.h>  
 
static void 
sig_quit(int);  
  
int 
main() 
{  
    sigset_t new, old, pend;  
      
    signal(SIGQUIT, sig_quit);  
  
    sigemptyset(&new);  
    sigaddset(&new, SIGQUIT);  
    sigprocmask(SIG_BLOCK, &new, &old);  
  
    sleep(5);  
  
    printf("SIGQUIT unblocked\n");  
    sigprocmask(SIG_SETMASK, &old, NULL);  
  
    sleep(50);  
    return 1;  
}  
  
static void sig_quit(int signo) {  
    printf("catch SIGQUIT\n");  
    signal(SIGQUIT, SIG_DFL);  
}  
