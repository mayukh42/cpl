#ifndef __STACK_H
#define __STACK_H

#include "objectlist.h"

/** General purpose Stack (LIFO)
 * items: void *
 */
typedef struct Stack {
	OList * head;
	unsigned size;
} Stack;

Stack * createStack () {
	Stack * s = (Stack *) calloc (sizeof (Stack), 1);
	return s;
}

/** push ()
 * creates space for node
 */
void push (Stack * s, void * item) {
	if (!s || !item)
		return;

	OList * node = create_Node (item);
	if (!s->head) 
		s->head = node;
	else {
		node->next = s->head;
		s->head = node;
	}
	s->size++;
}

/** pop ()
 * returns removed element
 */
void * pop (Stack * s) {
	if (!s)
		return NULL;

	OList * node = s->head;
	void * item = NULL;
	if (node) {
		s->head = s->head->next;
		item = node->item;
	}
	delete_Node (node);
	s->size--;
	return item;
}

/** peek ()
 * returns last in element w/o removing it
 */
void * peek (Stack * s) {
	if (!s)
		return NULL;

	OList * node = s->head;
	void * item = node ? node->item : NULL;
	return item;
}

/** isStackEmpty ()
 * returns 1 if stack is empty, 0 otherwise
 */
int isStackEmpty (Stack * s) { return s ? !s->size : 1; }

/** deleteStack ()
 * only frees the space created during Stack ops
 */
void deleteStack (Stack * s) {
	if (s) {
		while (!isStackEmpty (s))
			pop (s);
		free (s);
	}
}


// for debugging, hence cheating the Stack interface
void printStack (Stack * s) {
	printf ("[");
	if (s) {
		printf ("(size %d) ", s->size);
		print_OList (s->head);
	}
	printf ("]\n");
}


#endif