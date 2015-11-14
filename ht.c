#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * Simple HashTable in C
 * keys = integers
 * Implemented as bins + linked list
 */

#define N 8

struct Node;

typedef enum bool {
	false,
	true
} bool;

// value to be stored at HT
typedef struct Node {
	void * value;
	struct Node * prev;
	struct Node * next;
} Node;

Node * create_Node (void * value) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void destroy_Node (Node * node) {
	if (node) {
		destroy_Node (node->next);
		free (node);
	}
}

// list of values per bin
typedef struct List {
	size_t size;
	Node * head;
	Node * tail;
} List;

List * create_List () {
	List * list = (List *) malloc (sizeof (List));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void destroy_List (List * list) {
	if (list) {
		destroy_Node (list->head);
		free (list);
	}
}

// specific to type of value
void print_List (List * list) {
	if (! list)
		return;

	printf ("[ ");
	Node * it = list->head;
	while (it) {
		printf ("%ld ", * (long *) it->value);
		it = it->next;
	}
	printf ("]\n");
}

// specific to type of value
Node * List_exists (List * list, void * value) {
	if (! list)
		return NULL;

	Node * it = list->head;
	while (it && 
		* (long *) it->value != * (long *) value)
		it = it->next;

	return it;
}

List * List_insert (List * list, void * value) {
	if (! list)
		return NULL;

	Node * it = List_exists (list, value);
	if (! it) {	// append to tail
		Node * node = create_Node (value);
		node->prev = list->tail;

		if (list->size > 0)
			list->tail->next = node;

		list->tail = node;
		list->size++;

		if (list->size == 1)
			list->head = list->tail;
	}
	
	return list;
}

List * List_remove (List * list, void * value) {
	if (! list)
		return NULL;

	Node * it = List_exists (list, value);
	if (it) {
		if (list->size == 1) {
			list->head = NULL;
			list->tail = NULL;
		} else if (it == list->tail)
			list->tail = it->prev;
		
		it->prev->next = it->next;
		list->size--;
		
		free (it);
	}

	return list;
}

// keys = integers (array indices)
typedef struct Hashtable {
	size_t size;
	List * bins[N];
} Hashtable;

Hashtable * create_HT (size_t size) {
	Hashtable * ht = (Hashtable *) malloc (sizeof (Hashtable));
	ht->size = size;
	for (size_t i = 0; i < N; i++) 		
		ht->bins[i] = create_List ();

	return ht;
}

void destroy_HT (Hashtable * ht) {
	if (ht) {
		for (size_t i = 0; i < ht->size; i++)
			destroy_List (ht->bins[i]);
		free (ht);
	}
}

// specific to type of value
size_t hashfn (void * value) {
	return (* (long *) value) % N;
}

Hashtable * HT_insert (Hashtable * ht, void * value) {
	size_t bin_id = hashfn (value);
	List * list = ht->bins[bin_id];
	List_insert (list, value);
	return ht;
}

bool HT_exists (Hashtable * ht, void * value) {	
	size_t bin_id = hashfn (value);
	List * list = ht->bins[bin_id];
	Node * node = List_exists (list, value);
	return node ? true : false;
}

Hashtable * HT_remove (Hashtable * ht, void * value) {
	size_t bin_id = hashfn (value);
	List * list = ht->bins[bin_id];
	List_remove (list, value);
	return ht;
}

void HT_print (Hashtable * ht) {
	printf ("{ \n");
	for (size_t i = 0; i < ht->size; i++) {
		printf ("\t%lu: ", i);
		print_List (ht->bins[i]);
	}
	printf (" } \n");
}

void test_HT () {
	size_t size = 13;
	long vs[] = {1,1,2,3,5,8,13,21,34,55,89,144,233};
	
	Hashtable * ht = create_HT (N);
	for (size_t i = 0; i < size; i++)
		HT_insert (ht, (void *) &vs[i]);

	HT_print (ht);

	long val1 = 233;

	HT_remove (ht, (void *) &val1);
	HT_print (ht);

	HT_insert (ht, (void *) &val1);
	HT_print (ht);

	long val2 = 34;

	HT_remove (ht, (void *) &val2);
	HT_print (ht);

	long elem = 13;
	printf ("%lu exists ? %s \n", elem, HT_exists (ht, (void *) &elem) ? "true" : "false");

	destroy_HT (ht);
}

int main () {
	test_HT ();
	
	return 0;
}
