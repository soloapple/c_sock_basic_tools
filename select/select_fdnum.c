/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: select_fdnum.c
 * Description: 
 *     Version: 1.0
 *     Created: Liujfa   06/17/15 16:19:33
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   06/17/15                  build this moudle  
 ***************************************************************************************/



#include <sys/select.h>  
#include <sys/socket.h>  
#include <stdio.h>  
#define NUM 3000
int fds[NUM];  
int main()  
{  
	//char buf[2222];
	int i = 100;
    fd_set rset;  
    for( i; i < NUM; ++i )  
    {     
        printf("[%d]\t", i);   
		
		
        if( ( fds[i] = socket( AF_INET, SOCK_STREAM, 0 ) ) >= 0 )   
        {     
            printf( "%d\n",fds[i] );  
			//printf("1 i: %d\n", i);
            FD_ZERO(&rset);  
			//printf("2 i: %d\n", i);
            FD_SET( fds[i], &rset);  
			//printf("3 i: %d\n", i);
        }     
        else  
        {     
            printf( "fail\n" );  
        }     
		
    }     
    printf( "succ i: %d\n", i );  
	sleep(1000000);		
    return 0;  
}  
