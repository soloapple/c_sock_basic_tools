/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: unlock_queue.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   09/14/16 23:53:18
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   09/14/16                  build this moudle  
 ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "unlock_queue.h"

QUEUE *queue_create()
{
	QUEUE *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}
	
	new->head = new->tail = malloc(sizeof(struct list_node_st));
	if (new->head == NULL) {
		return NULL;
	}

	new->head->next = NULL;
	new->head->data = NULL;

	return new;
}

void queue_destroy(QUEUE *ptr, free_data *user_free)
{
	struct list_node_st *cur, *save;

	for (cur = ptr->head; cur != NULL; cur = save) {
		save = cur->next;
		if (user_free) {
			user_free(cur->data);
		}

		free(cur);
	}

	free(ptr);
}

int queue_en(QUEUE *ptr, void *data)
{
	if (ptr == NULL)
	{
		printf ( "ptr is NULL, cant de\n" );	
		return 0;
	}

	struct list_node_st *new;

	new = malloc(sizeof(struct list_node_st));
	if (new == NULL) {
		return -1;
	}

	new->data = data;
	new->next = NULL;
	ptr->tail->next = new;
	ptr->tail = new;

	return 0;
}

void *queue_de(QUEUE *ptr)
{
	if(ptr == NULL)
	{
		printf ( "ptr is NULL, cant de\n" );
		return 0;
	}

	struct list_node_st *save;

	if (ptr->head->next == NULL) {
		return NULL;
	}

	save = ptr->head;
	ptr->head = ptr->head->next;
	free(save);

	return ptr->head->data;
}
