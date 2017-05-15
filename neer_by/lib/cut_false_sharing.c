/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: cut_false_sharing.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/02/16 02:53:32
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/02/16                  build this moudle  
 ***************************************************************************************/
#include "cut_false_sharing.h"

struct thread_info
{
	pthread_t tid;
	int id;
	unsigned seed;
	unsigned* hash;
	int64_t count;
};

const int HASH_SIZE = 5 * 1024 ;
const int64_t TOTAL_OPS = 1000 * 1000 * 1000;

double now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void* thread_func(void* arg)
{
	struct thread_info ti = *(struct thread_info*)arg;
	printf("%f thread: %d started\n", now(), ti.id);

	int64_t i = 0;
	for (; i < ti.count; ++i)
	{
		unsigned int obj = rand_r(&ti.seed);
		ti.hash[obj % HASH_SIZE] = obj; // rand_r(&ti.seed);
	}

	printf("%f thread: %d finished\n", now(), ti.id);
	return NULL;
}

int cut_false_sharing(int argc, char *argv[])
{
	struct thread_info thread_infos[32];
	bzero(thread_infos, sizeof thread_infos);

	int num = sysconf(_SC_NPROCESSORS_CONF);
	printf("system has %d processor(s)\n", num);

	srand(time(NULL));

	int nThreads = argc > 1 ? atoi(argv[1]) : 1;
	double start = now();
	printf("%f creating %d threads\n", start, nThreads);
	int i = 0;
	for (; i < nThreads; i++)
	{
		thread_infos[i].id = i;
		thread_infos[i].seed = rand();
		thread_infos[i].hash = calloc(HASH_SIZE, sizeof(unsigned int));
		thread_infos[i].count = TOTAL_OPS;
		pthread_create(&thread_infos[i].tid, NULL, thread_func, &thread_infos[i]);
	}

	for (i = 0; i < nThreads; i++)
	{
		pthread_join(thread_infos[i].tid, NULL);
	}
	double end = now();
	double seconds = end - start;
	printf("%f all threads stopped, elapsed %f seconds\n", end, seconds);
	printf("total_ops/s = %.3f M\nops/s for each thread = %.3f M\n",
			TOTAL_OPS / seconds / 1000000 * nThreads,
			TOTAL_OPS / seconds / 1000000);
	return 0;
}
