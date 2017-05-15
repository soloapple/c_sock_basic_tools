/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: multi_thread_test.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/02/16 00:28:35
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/02/16                  build this moudle  
 ***************************************************************************************/
#include "multi_thread_test.h"

#define	N 8			/*  */
static volatile unsigned long op[100];
static volatile int g_rand = 0;
static volatile unsigned long pre_op[100];
/*用于测试的不同锁*/
pthread_mutex_t g_mutex[100];
pthread_rwlock_t g_mutex_rw[100];
pthread_spinlock_t g_spinlock[100];
/*500W的Hash表*/
//#define HASH_SIZE  (5*1024*1024)
#define HASH_SIZE  (5*1024)
static unsigned int *g_hash[32];

static void *thread_select(void *arg)
{
		int i = * (int *)arg;
		printf("thread:%d\n",i);
	 	cpu_set_t mask;
	    cpu_set_t get;
	    char buf[256];
	    int num = sysconf(_SC_NPROCESSORS_CONF);
	    printf("system has %d processor(s)\n", num);
	    CPU_ZERO(&mask);
	    CPU_SET(i, &mask);
	    /*设置线程的CPU亲缘性。
	     */
	      if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
              fprintf(stderr, "set thread affinity failed\n");
        }

//	    unsigned int obj = rand();
		while(1)
		{
/***1.是否加锁****/
//			pthread_mutex_lock(&g_mutex[i]);
//			pthread_spin_lock(&g_spinlock[i]);
//			pthread_rwlock_rdlock(&g_mutex_rw[i] );
			//		time(NULL);
//					rand();
			//	操作计数
			op[i] ++;
			unsigned int obj  = g_rand;
			memcmp(&obj,   g_hash[i] + (g_rand % HASH_SIZE ) , sizeof(unsigned int )   );
//			pthread_rwlock_unlock(&g_mutex_rw[i] );
//			pthread_spin_unlock(&g_spinlock[i]);
//			pthread_mutex_unlock(&g_mutex[i]);
		}
}

/*打印线程*/
void *thread_print(void *arg)
{
    int n;
	printf ( "create print thread\n" );
    while(1)
    {
    	/*打印前四个线程当前总的操作计数*/
 //   	printf("op[3]:%lu\n",op[3]);
        printf("thread0_op_times: %lu pps	thread1_op_times: %lu pps	thread2_op_times: %lu pps	 thread3_op_times: %lu pps\n",  op[0], op[1] ,op[2], op[3]  );
        unsigned long all_op = 0;
        int j = 0;
        for(j = 0 ;j < 32; j ++)
        {
//        	pthread_mutex_lock(&g_mutex[j]);
        	all_op += (op[j] - pre_op[j]);
        	pre_op[j] = op[j];
 //       	pthread_mutex_unlock(&g_mutex[j]);
        }
        /*打印休眠周期内的总操作次数*/
        printf("all_op:%lu\n",  all_op );
        all_op = 0;
        /*休眠*/
        sleep(10);
//        usleep(1000 * 990);
    }
    return NULL;
}
void *thread_rand(void *arg)
{
	while(1)
	{
		g_rand = rand();
		sleep(1);
	}
}

int multi_thread_test(void)
{
		pthread_t t[40];
        int i = 0;
        int thread_id[32];
        int total_num = 0;

		printf ( "srand before\n" );
        srand(time(NULL));
		printf ( "srand after\n" );

		pthread_create(&t[34], NULL, thread_rand, NULL);
		printf ( "create thread rand done!\n" );

        for( i = 0 ; i < 32; i ++)
        {
			printf ("init %d thread\n", i);
        	op[i] = 0;
        	pre_op[i] = 0;
        	pthread_mutex_init(&g_mutex[i],NULL);
        	pthread_rwlock_init(&g_mutex_rw[i], NULL);
        	pthread_spin_init(&g_spinlock[i],0);
        	g_hash[i] = (unsigned int *)malloc( sizeof(unsigned int ) * HASH_SIZE );
        	memset(g_hash[i], 0, sizeof(unsigned int ) * HASH_SIZE );
        }

		printf("start create thread_select\n");
		/*线程优先级*/
		struct sched_param param;
		param.__sched_priority = 20;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
		pthread_attr_setschedpolicy(&attr,SCHED_FIFO);
		pthread_attr_setschedparam(&attr,&param);

		/*启动打印线程*/
		pthread_create(&t[35], NULL, thread_print, NULL);
		/*线程编号*/
        for( i=0;i<32;i++){
           thread_id[i]=i;
        }
        /***在这里修改线程数****/
		for(i=0;i < 3;i++){
			/*是否设置线程的优先级*/
			pthread_create(&t[i], NULL, thread_select, (void *)&thread_id[i]);
////			pthread_create(&t[i], &attr, thread_select, (void *)&thread_id[i]);
		}

	while(1) {
		sleep(1);
	}
	return 0;
}
