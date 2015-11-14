#ifndef __DOUBLELIST_H
#define __DOUBLELIST_H

/* Doubly-Linked List
 */

struct DList;

typedef struct DList {
	int val;
	struct DList * next;
	struct DList * prev;
} DList;

DList * create_Node (int value) {
	DList * node = (DList *) malloc (sizeof (DList));
	node->val = value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}



#endif