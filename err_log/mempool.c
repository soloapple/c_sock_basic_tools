#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mempool.h"
#include "common.h"

#define FREE_POINTER(p)                         \
    do {                                        \
        if ( p ) {                              \
            free(p);                            \
            p = NULL;                           \
        }                                       \
    } while (0)

struct mem_pool *mp_init(_uint32 block_size, _uint32 block_count)
{
	struct mem_pool *mp_head;

	if (!block_size || !block_count)
		return NULL;
	
	/* set memory page is integer times */
	if (block_size % 1024)
		block_size = MP_DEFAULT_BLOCK_SIZE;

	/* set it is 2 ^ x */
	if (block_count & (block_count - 1))
		block_count = MP_DEFAULT_BLOCK_COUNT;

	mp_head = (struct mem_pool *)malloc(sizeof(struct mem_pool));
	if (!mp_head) {
		printf("error: malloc() memory pool head failed.\n");
		return mp_head;
	}

	mp_head->buffer = (char *)malloc(block_size * block_count);
	if (!mp_head->buffer) {
		printf("error: malloc() memory pool space failed.\n");
		FREE_POINTER(mp_head);
		return NULL;
	}

	mp_head->block_size  = block_size;
	mp_head->block_count = block_count;
	mp_head->pos_read    = mp_head->pos_write = 0;

	return mp_head;
}

void mp_free(struct mem_pool **mph)
{
	struct mem_pool *mpn = *mph;

	if (mpn) {
		if (mpn->buffer)
			FREE_POINTER(mpn->buffer);

		FREE_POINTER(mpn);
	}
}

char *mp_get_write(struct mem_pool *mph)
{
	int newpos = (mph->pos_write + 1) & 
		(mph->block_count - 1);

	/* memory pool be fill full */
	while (newpos == (int)mph->pos_read) {
		usleep(WAIT_TIMES);
	}

	return (mph->buffer + mph->pos_write * mph->block_size);
}

void mp_set_write_to_next(struct mem_pool *mph)
{
	/* point to next can be write memory position */
	mph->pos_write = (mph->pos_write + 1) &
		(mph->block_count - 1);
}

char *mp_get_read(struct mem_pool *mph)
{
	/* begin or no content can be read */
	while (mph->pos_read == mph->pos_write) {
		usleep(WAIT_TIMES);
	}

	return (mph->buffer + mph->pos_read * mph->block_size);
}

void mp_set_read_to_next(struct mem_pool *mph)
{
	/* point to next can be read memory position */
	mph->pos_read = (mph->pos_read + 1) & 
		(mph->block_count - 1);
}
