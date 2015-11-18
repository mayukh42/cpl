#ifndef __OBJECTLIST_H
#define __OBJECTLIST_H

/** author: mayukh
 * github.com/mayukh42
 */

/** Simple Linked List implementation
 * General purpose, i.e. void *
 * tested using int
 */

// typedef void * (* wrapper_fn) (void * element);

// item (type: int)
int * wrap_Item (int * v) {
	int * item = (int *) malloc (sizeof (int));
	* item = * v;
	return item;
}

void delete_Item (int * item) {
	if (item)
		free (item);
}

// override for different item type
void print_Item (int * item) {
	if (item)
		printf ("%d ", * item);
}


struct OList;

typedef struct OList {
	void * item;
	struct OList * next;
} OList;

OList * create_Node (void * item) {
	OList * node = (OList *) malloc (sizeof (OList));
	node->item = item;
	node->next = NULL;
	return node;
}

void delete_Node (OList * node) {
	if (node) 
		free (node);
}

OList * create_OList (void ** items, unsigned n) {
	if (!items)
		return NULL;

	OList * curr = create_Node (* items);
	n--;
	if (n > 0)
		curr->next = create_OList (items + 1, n);

	return curr;
}

void delete_OList (OList * list) {
	if (list) {
		delete_OList (list->next);
		delete_Node (list);
	}
}

void print_Nodes (OList * list) {
	if (!list)
		return;
	print_Item (list->item);
	print_Nodes (list->next);
}

void print_OList (OList * list) {
	printf ("[");
	print_Nodes (list);
	printf ("]\n");
}

#endif
