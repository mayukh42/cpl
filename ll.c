#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * Linked List Problems, Stanford CS Education Library
 * http://cslibrary.stanford.edu/105
 */

typedef struct Node {
	int val;
	struct Node * next;
} Node;

/**
 * Utility functions
 */
typedef void (* listfn) (Node ** list);

int length (Node * list) {
	if (list == NULL)
		return 0;
	else 
		return 1 + length (list->next);
}

Node * create_node (int v) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->val = v;
	node->next = NULL;
	return node;
}

void push (Node ** node, int v) {
	Node * v_node = create_node (v);

	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = * node;
	* node = v_node;
}

void append (Node ** node, int v) {
	Node * v_node = create_node (v);

	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = (* node)->next;
	(* node)->next = v_node;
}

void append_node (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = (* node)->next;
	(* node)->next = v_node;
}

Node * create_basic_list (int * xs, int n) {
	Node * list = NULL;
	for (int i = n-1; i >= 0; i--) 
		push (&list, xs[i]);
	return list;
}

Node * find_last (Node * list) {
	if (list == NULL)
		return list;

	while (list->next != NULL)
		list = list->next;
	return list;
}

Node * create_basic_list_2 (int n) {
	Node * list = NULL;

	for (int i = 1; i <= n; i++) {
		Node * last = find_last (list);
		if (last == NULL) 
			append (&list, i);
		else 
			append (&last, i);
	}
	return list;
}

Node * create_basic_list_3 (int n) {
	Node * list = NULL;
	Node * last = NULL;

	for (int i = 1; i <= n; i++) {
		if (list == NULL) {
			push (&list, i*2);
			last = list;
		} else {
			push (&(last->next), i*2);
			last = last->next;
		}
	}
	return list;
}

void print_nodes (Node * list) {
	if (list != NULL) {
		printf ("%d, ", list->val);
		print_nodes (list->next);
	}
}

void print_list (Node * list) {
	printf ("[");
	print_nodes (list);
	printf ("]\n");
}

/** 3 - delete list 
 */
void delete_list (Node * node) {
	if (node != NULL) {
		delete_list (node->next);
		free (node);
	}
}


void test_utilities () {
	Node * list = create_basic_list_3 (5);
	print_list (list);
	delete_list (list);
}


/** 1 - count frequency of an element in list
 */
int count_value (Node * list, int value) {
	if (list != NULL) {
		if (list->val == value)
			return 1 + count_value (list->next, value);
		else 
			return count_value (list->next, value);
	} else {
		return 0;
	}
}

void test_count_value () {	
	int xs[] = {1,2,2,3,3,3,4};
	Node * list = create_basic_list (xs, 7);
	int value = 3;
	int freq = count_value (list, value);
	printf ("%d occurs %d times in the list\n", value, freq);
}

/** 2 - get nth element if at least n elements exists, else throw error
 */
int nth (Node * list, int n) {
	if (n < 0 || list == NULL)
		return -1;

	if (n == 0)
		return list->val;
	else 
		return nth (list->next, n - 1);
}

void test_nth () {
	int xs[] = {1,2,3,4,5};
	Node * list = create_basic_list (xs, 5);
	int idx0 = 3, idx1 = 6;

	printf ("%dth element (index: %d) = %d\n", idx0 + 1, idx0, nth (list, idx0));
	printf ("%dth element (index: %d) = %d\n", idx1 + 1, idx1, nth (list, idx1));
}

/** 4 - pop the head: beheads and returns value
 * mutates original list
 */
int pop (Node ** node) {
	int res = -1;
	if (* node != NULL) {
		res = (* node)->val;
		Node * head = * node;
		* node = (* node)->next;
		free (head);
	}
	return res;
}

void test_pop () {
	Node * list = create_basic_list_3 (5);
	print_list (list);
	while (list != NULL) {
		int val = pop (&list);
		printf ("popped value = %d\n", val);
	}
}

/** 5 - insert nth - inserts at nth index 
 */
void insert_at (Node ** list, int n, int val) {
	int len = length (* list);
	if (n < 0 || n > len)
		return;

	Node ** it = list;
	while (n > 0) {
		it =  &((* it)->next);
		n--;
	}
	push (it, val);
}

void test_insert_at () {
	Node * list = create_basic_list_3 (5);
	print_list (list);

	insert_at (&list, 3, 8);
	print_list (list);

	insert_at (&list, 0, 10);
	print_list (list);

	Node * empty = NULL;
	insert_at (&empty, 0, 11);
	print_list (empty);

	delete_list (list);
	delete_list (empty);
}

void push_node (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = * node;
	* node = v_node;
}

/** 6 - sorted insert - insert at the right position
 * in a sorted list
 */
void sorted_insert (Node ** list, Node * v_node) {
	Node ** it = list;
	while (* it != NULL && v_node->val > (* it)->val)
		it = &((* it)->next);

	push_node (it, v_node);
}

void test_sorted_insert () {
	Node * list = create_basic_list_3 (5);
	print_list (list);

	sorted_insert (&list, create_node (3));
	sorted_insert (&list, create_node (1));
	sorted_insert (&list, create_node (20));
	print_list (list);

	Node * empty = NULL;
	sorted_insert (&empty, create_node (6));
	print_list (empty);

	delete_list (list);
	delete_list (empty);
}

/** 7 - insertion sort 
 * O(n^2)
 */
void isort_list (Node ** list) {
	if (* list == NULL)
		return;

	Node * it = * list;
	* list = NULL;
	while (it != NULL) {
		Node * it2 = it->next;
		it->next = NULL;
		sorted_insert (list, it);
		it = it2;
	}
}

void test_isort () {
	int xs[] = {8,0,2,7,0,1};
	Node * list = create_basic_list (xs, 6);
	print_list (list);

	isort_list (&list);
	print_list (list);
}

void append_list (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	(* node)->next = v_node;
}

/** 8 - append (concat) lists
 */
void concat (Node ** first, Node ** second) {
	if (* first == NULL) {
		* first = * second;
		return;
	}
	
	Node ** it = first;
	while (* it != NULL) 
		it = &((* it)->next);
	append_list (it, * second);
	* second = NULL;
}

void test_concat () {
	Node * first = create_basic_list_2 (4);
	Node * second = create_basic_list_3 (5);
	concat (&first, &second);
	print_list (first);

	delete_list (first);

	Node * third = NULL;
	Node * fourth = NULL;
	Node * fifth = create_basic_list_3 (3);
	concat (&third, &fourth);
	print_list (third);

	concat (&fifth, &fourth);
	print_list (fifth);
}

/** 9 - split into 2 halves
 * longer half goes in the first
 */
void split (Node ** list, Node ** second) {
	int n = length (* list);
	if (n == 0)
		return;

	n = n - n/2;
	Node ** it = list;
	while (n > 1) {
		it = &((* it)->next);
		n--;
	}
	* second = (* it)->next;
	(* it)->next = NULL;
}

void test_split () {
	Node * list = create_basic_list_3 (3);

	Node * second = NULL;
	split (&list, &second);

	print_list (list);
	print_list (second);
}

void remove_next (Node ** node) {
	if (* node == NULL)
		return;
	else if ((* node)->next == NULL)
		return;

	Node * next = (* node)->next;
	(* node)->next = next->next;
	free (next);
}

/** 10 - remove duplicates
 * assume sorted list
 */
void distinct (Node ** list) {
	if (* list == NULL)
		return;

	Node ** it = list;
	while (* it != NULL) {
		Node * next = (* it)->next;
		if (next != NULL && next->val == (* it)->val) {
			remove_next (it);
			continue;
		} else {
			it = &((* it)->next);
		}
	}
}

void test_distinct () {
	int xs[] = {1,1,2,3,3,3,4,5,5};
	Node * list = create_basic_list (xs, 9);
	print_list (list);
	// remove_next (&list);
	distinct (&list);
	print_list (list);
}

/** 11 - move_node ()
 * move 1st node of 2nd list to head of 1st list
 */
void move_node (Node ** first, Node ** second) {
	if (* second == NULL)
		return;

	Node * s0 = * second;
	* second = (* second)->next;
	s0->next = NULL;
	push_node (first, s0);
}

void test_move_node () {
	Node * list = create_basic_list_3 (5);
	Node * list2 = create_basic_list_2 (5);

	move_node (&list, &list2);
	print_list (list);
	print_list (list2);
}

/** 12 - alter_split ()
 * split every alternate element into the same list
 * return 2 lists
 */
void alter_split (Node ** list, Node ** first, Node ** second) {
	while (* list != NULL) {
		move_node (first, list);
		move_node (second, list);
	}
}

void test_alter_split () {
	Node * list = create_basic_list_2 (9);
	print_list (list);

	Node * first = NULL;
	Node * second = NULL;

	alter_split (&list, &first, &second);
	print_list (first);
	print_list (second);
}

/** 13 - shuffle_merge ()
 * merges alternate nodes of 2 lists one after the other
 * inverse of alter_split: shuffle_merge (alter_split (xs)) == xs
 */
void shuffle_merge (Node ** first, Node ** second, Node ** list) {
	while (* first != NULL && * second != NULL) {
		move_node (list, first);
		move_node (list, second);
	} 
	while (* first != NULL)
		move_node (list, first);
	while (* second != NULL)
		move_node (list, second);
}

void test_shuffle_merge () {
	Node * list = create_basic_list_2 (9);
	print_list (list);	
	Node * first = NULL;
	Node * second = NULL;

	alter_split (&list, &first, &second);
	print_list (first);
	print_list (second);

	shuffle_merge (&first, &second, &list);
	print_list (list);	// should be same as original list
}

/** move_node_last ()
 * move 1st node of 2nd list to end of 1st list
 */
void move_node_last (Node ** list, Node ** second) {
	if (* second == NULL)
		return;

	Node * node = * second;
	* second = (* second)->next;
	node->next = NULL;

	Node * last = find_last (* list);
	if (last == NULL)	// change find_last to return addr, to avoid this hack
		append_list (list, node);
	else
		append_list (&last, node);
}

void test_move_node_last () {
	Node * list = create_basic_list_2 (4);
	Node * second = create_basic_list_3 (3);
	move_node_last (&list, &second);

	print_list (list);
	print_list (second);
}

/** 14 - sorted_merge ()
 * merge 2 sorted lists
 */
void sorted_merge (Node ** first, Node ** second, Node ** list) {
	while (* first != NULL && * second != NULL) {
		if ((* first)->val < (* second)->val)
			move_node_last (list, first);
		else
			move_node_last (list, second);
	}
	while (* first != NULL)
		move_node_last (list, first);
	while (* second != NULL)
		move_node_last (list, second);
}

void test_sorted_merge () {
	Node * first = create_basic_list_3 (3);
	Node * second = create_basic_list_2 (5);
	Node * list = NULL;

	print_list (first);
	print_list (second);

	sorted_merge (&first, &second, &list);
	print_list (list);
}

/** 15 - mergesort ()
 * classical merge sort algorithm
 */
void mergesort (Node ** list) {
	if (length (* list) <= 1)
		return;
	else {
		Node * second = NULL;
		Node * first = * list;
		split (&first, &second);

		mergesort (&first);
		mergesort (&second);

		* list = NULL;
		sorted_merge (&first, &second, list);
	}
}

void test_mergesort () {
	int xs[] = {8,0,2,7,0,1};
	Node * list = create_basic_list (xs, 6);

	mergesort (&list);
	print_list (list);
}

/** 16 - sorted_intersect () 
 * returns set intersection of 2 sorted lists
 */
void sorted_intersect (Node ** first, Node ** second, Node ** list) {
	int last_val = -1;
	while (* first != NULL && * second != NULL) {

		if ((* first)->val == (* second)->val 
			&& (* first)->val != last_val) {

			last_val = (* first)->val;
			push (list, last_val);
			* first = (* first)->next;
			* second = (* second)->next;
		} 
		else if ((* first)->val < (* second)->val)
			* first = (* first)->next;
		else
			* second = (* second)->next;
	}
} 

void test_sorted_intersect () {	
	int xs[] = {1,2,2,3};
	int ys[] = {2,2,3,4,5};
	Node * first = create_basic_list (xs, 4);
	Node * second = create_basic_list (ys, 5);
	Node * list = NULL;

	print_list (first);
	print_list (second);

	sorted_intersect (&first, &second, &list);
	print_list (list);
}

/** testfactory_list ()
 * a factory of test functions for reverse 
 */
void testfactory_list (listfn fn) {
	int xs[] = {1,2,3,4,5};
	Node * list = create_basic_list (xs, 5);
	print_list (list);

	fn (&list);
	print_list (list);

	delete_list (list);
}

/** 17 - reverse_iter ()
 * iterative solution of the linked list reverse
 */
void reverse_iter (Node ** list) {
	Node * res = NULL;
	while (* list != NULL) 
		move_node (&res, list);
	* list = res;
}

/** reverse_rec ()
 * recursive solution of the linked list reverse
 * functional programming approach
 * O(n^2) for naive linked list
 */
void reverse_rec (Node ** list) {
	if (* list == NULL)
		return;
	if ((* list)->next == NULL)
		return;
	else {
		Node * node = * list;
		* list = (* list)->next;
		reverse_rec (list);
		move_node_last (list, &node);
	}
}

/** rev_rec ()
 * helper function for reverse (), a recursive version of reverse_iter ()
 */
void rev_rec (Node ** list, Node ** acc) {
	if (* list != NULL) {
		move_node (acc, list);
		rev_rec (list, acc);
	}
}

void test_rev_rec () {
	Node * list = create_basic_list_2 (5);
	Node * acc = NULL;
	print_list (list); 
	print_list (acc);

	rev_rec (&list, &acc);
	print_list (list);
	print_list (acc);
}

/** 18 - reverse ()
 * recursive version of reverse_iter ()
 * O(n)
 */
void reverse (Node ** list) {
	Node * acc = NULL;
	rev_rec (list, &acc);
	* list = acc;
}

/** is_equal ()
 * returns 1 if 2 lists have same values, else returns 0
 */
int is_equal (Node ** first, Node ** second) {
	int res = 1;
	Node * l1 = * first;
	Node * l2 = * second;
	while (l1 != NULL && l2 != NULL) {
		if (l1->val != l2->val) {
			res = 0;
			return res;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	if (l1 != NULL || l2 != NULL)
		res = 0;
	return res;  
}

void test_reverse () {
	testfactory_list (reverse_iter);
	testfactory_list (reverse_rec);
	testfactory_list (reverse);

	int n = 5;
	Node * list = create_basic_list_2 (n);
	Node * gold = create_basic_list_2 (n);

	reverse (&list);
	reverse (&list);

	int same = is_equal (&gold, &list);
	if (same)
		printf ("reverse . reverse test passed\n");
	else 
		printf ("reverse . reverse test failed\n");

	delete_list (list);
	delete_list (gold);
}

// all tests
void run_tests () {
	// test_utilities ();

	// test_count_value ();
	// test_nth ();
	// test_pop ();
	// test_insert_at ();
	// test_sorted_insert ();
	// test_isort ();
	// test_concat ();
	// test_split ();
	// test_distinct ();
	// test_move_node ();
	// test_alter_split ();
	// test_shuffle_merge ();
	// test_move_node_last ();
	// test_sorted_merge ();
	// test_mergesort ();
	// test_sorted_intersect ();
	// test_rev_rec ();
	test_reverse ();
}

int main () {
	run_tests ();

	return 0;
}
