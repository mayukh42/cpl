#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

/** author: mayukh
 * github.com/mayukh42
 */

/** Simple Linked List implementation
 */

struct List;

typedef struct List {
	int val;
	struct List * next;
} List;

List * create_Node (int v) {
	List * node = (List *) malloc (sizeof(List));
	node->val = v;
	node->next = NULL;
	return node;
}

void delete_Node (List * node) {
	if (node)
		free (node);
}

List * create_List (int * xs, unsigned n) {
	if (!xs)
		return NULL;

	List * curr = create_Node (*xs);
	n--;
	if (n > 0)
		curr->next = create_List (xs+1, n);

	return curr;
}

void delete_List (List * list) {
	if (list) {
		delete_List (list->next);
		delete_Node (list);
	}
}

void print_Nodes (List * list) {
	if (!list)
		return;
	printf ("%d, ", list->val);
	print_Nodes (list->next);
}

void print_List (List * list) {
	printf ("[");
	print_Nodes (list);
	printf ("]\n");
}

List * reverse_rec (List * list, List * acc) {
	if (!list)
		return acc;
	List * _this = list;
	List * _next = _this->next;
	_this->next = acc;
	return reverse_rec (_next, _this);
}

List * reverse (List * list) {
	return reverse_rec (list, NULL);
}

// test utility
List * create_list_from_array () {
	int xs[] = {1,2,3,4,5,6,7,8};
	int n = 8;
	List * xs_list = create_List (xs, n);
	return xs_list;
}

#endif
