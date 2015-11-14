#ifndef __TRIPLELIST_H
#define __TRIPLELIST_H

struct TList;

/** TList: value, prev, next, child
 */
typedef struct TList {
	int val;
	struct TList * next;
	struct TList * prev;
	struct TList * child;
} TList;

TList * create_TNode (int value) {
	TList * node = (TList *) malloc (sizeof (TList));
	node->val = value;
	node->next = NULL;
	node->prev = NULL;
	node->child = NULL;
	return node;
}

void delete_TNode (TList * node) {
	if (node) 
		free (node);
}

void add_Child (TList * list, TList * child) {
	if (!list)
		return;

	list->child = child;
}

// pattern to implement recursive create
TList * append_TNode (TList * list, TList * node) {
	if (!node || !list)
		return list;

	node->prev = list;
	list->next = node;
	return list;
}

TList * prepend_TNode (TList * list, TList * node) {
	if (!node || !list)
		return list;

	node->next = list;
	list->prev = node;
	return node;
}

TList * create_List_from_Array (TList * prev, int * xs, int n) {
	if (n <= 0 || !xs)
		return NULL;

	TList * list = create_TNode (* xs);
	list->prev = prev;
	n--;
	if (n > 0)
		list->next = create_List_from_Array (list, xs+1, n);

	return list;
}

/* print_Node
 * prints a triple Node in the following format:
 * [v: p, n, c]
 * where v = val, p = prev val, n = next val, c = child val
 * NULL neighbors are represented by -1
 */
void print_TNode (TList * node) {
	if (node) {
		int n = node->next != NULL ? node->next->val : -1;
		int p = node->prev != NULL ? node->prev->val : -1;
		int c = node->child != NULL ? node->child->val : -1;
		printf ("[%d: %d,%d,%d], ", node->val, p, n, c);
	}
}

void print_TNode_rec (TList * list) {
	if (list) {
		print_TNode (list);
		print_TNode_rec (list->child);
		print_TNode_rec (list->next);
	}
}

void print_TNode_flattened (TList * list) {
	if (list) {
		print_TNode (list);
		print_TNode_flattened (list->next);
	}
}

typedef void (* print_fn) (TList * list);

void print_TList (TList * list, print_fn pf) {
	printf ("[");
	pf (list);
	printf ("]\n");
}

void delete_TList (TList * list) {
	if (list) {
		delete_TList (list->child);
		delete_TList (list->next);
		delete_TNode (list);
	}
}

#endif