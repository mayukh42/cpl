#ifndef __QUEUE_H
#define __QUEUE_H

#include "objectlist.h"

/** General purpose Queue
 * items: void *
 */
typedef struct Queue {
	OList * head;
	OList * last;
	unsigned size;
} Queue;

Queue * create_Queue () {
	Queue * q = (Queue *) malloc (sizeof (Queue));
	q->head = NULL;
	q->last = NULL;
	q->size = 0;
	return q;
}

/** enqueue ()
 * creates space for element
 */
void enqueue (Queue * q, void * item) {
	if (!q || !item)
		return;

	OList * node = create_Node (item);
	if (!q->head)
		q->head = node;
	else 
		q->last->next = node;
	q->last = node;
	q->size++;
}

/** dequeue ()
 * returns element
 * caller must free the space
 */
void * dequeue (Queue * q) {
	if (!q || !q->size)
		return NULL;

	OList * node = q->head;
	void * item = node->item;
	if (q->size == 1) {
		q->head = NULL;
		q->last = NULL;
	}
	else
		q->head = q->head->next;

	delete_Node (node);
	q->size--;
	return item;
}

int is_Queue_empty (Queue * q) {
	if (q)
		return !q->size;
	return 0;
}

/** delete_Queue ()
 */
void delete_Queue (Queue * q) {
	if (q) {
		while (!is_Queue_empty (q))
			dequeue (q);
		free (q);
	}
}

void print_Queue (Queue * q) {
	if (q)
		print_OList (q->head);
}

#endif
