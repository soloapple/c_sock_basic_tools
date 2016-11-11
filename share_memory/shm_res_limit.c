/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: shm_res_limit.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/06/16 00:51:55
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/06/16                  build this moudle  
 ***************************************************************************************/

#include 	<stdio.h>
#include 	<errno.h>	
#include 	<sys/types.h>
#include 	<sys/ipc.h>
#include 	<sys/shm.h>
#define 	MAX_ATTACH_NUM  150

int 
main(int argc, char* argv[])
{
    key_t       mem_key;
    long        mem_id;
    void*       mem_addr[MAX_ATTACH_NUM];
    int          i;
    if ( ( mem_key = ftok("/tmp/mykeyfile", 1) ) == (key_t)(-1) )  {
            printf("Failed to generate shared memory access key, ERRNO=%d\n",
			errno);
            goto MOD_EXIT;
    }
    if ( ( mem_id = shmget(mem_key, 256, IPC_CREAT) ) == (-1) )  {
            printf("Failed to obtain shared memory ID, ERRNO=%d\n", errno);
            goto MOD_EXIT;
    }
    for ( i=1; i<=MAX_ATTACH_NUM; i++ )  {
		if ( ( mem_addr[i] = (void *)shmat(mem_id, 0, 0) ) == (void *)(-1) )
      printf("Failed to attach shared memory, times [%02d], errno:%d\n", i,
			errno);
		else
			printf("Successfully attached shared memory, times [%02d]\n", i);
    }
MOD_EXIT:
    shmctl(mem_id, IPC_RMID, NULL);

	return 0;
}				
