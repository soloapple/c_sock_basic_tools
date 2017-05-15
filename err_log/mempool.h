#ifndef __MEM_POOL_H
#define __MEM_POOL_H

typedef unsigned int _uint32;

#define MP_DEFAULT_BLOCK_SIZE  2048
#define MP_DEFAULT_BLOCK_COUNT 65536

#define WAIT_TIMES 1000

/* 
 * the block size must be 2 square 
 * for example 2^8.
 */
struct mem_pool {
	_uint32 block_count;	/* total memory block */
	_uint32 block_size;		/* every memory block length */
	
	_uint32 pos_read;		/* can be read memory block */
	_uint32 pos_write;		/* can be write memory block */

	char *buffer;		    /* memory space queue */
};

/* free memory pool */
void mp_free(struct mem_pool **mph);
/* init memory pool */
struct mem_pool *mp_init(_uint32 block_size, _uint32 block_count);
/* get one memory block that can be write */
char *mp_get_write(struct mem_pool *mph);
/* get one memory block that can be read */
char *mp_get_read(struct mem_pool *mph);
/* set to next memory that can be write */
void mp_set_write_to_next(struct mem_pool *mph);
/* set to next memory that can be read */
void mp_set_read_to_next(struct mem_pool *mph);

#endif // ~__MEM_POOL_H
