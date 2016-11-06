/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: unlock_queue.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/14/16 23:53:57
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/14/16                  build this moudle
 ***************************************************************************************/


#ifndef _ASM_QUEUE_H_
#define _ASM_QUEUE_H_

struct list_node_st {
	struct list_node_st *next;
	void *data;
};

typedef struct {
	struct list_node_st *head, *tail;
//	pthread_mutex_t head_mut, tail_mut;
} QUEUE;

typedef void free_data(void *);

QUEUE *queue_create();

void queue_destroy(QUEUE *, free_data *);

int queue_en(QUEUE *, void *data);

void *queue_de(QUEUE *);

#endif
