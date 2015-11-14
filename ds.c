#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * DataStructures - Some problems
 */

#define SIZE 5

/** Classical LinkedList
 */
typedef struct LinkedList {
	int val;
	struct LinkedList * next;
} LinkedList;

LinkedList * create_node (int v) {
	LinkedList * node = (LinkedList *) malloc (sizeof (LinkedList));
	node->val = v;
	node->next = NULL;
	return node;
}

void delete_nodes (LinkedList * list) {
	if (list != NULL) {
		delete_nodes (list->next);
	}
	free (list);
}

void print_nodes (LinkedList * list) {
	if (list != NULL) {
		printf ("%d, ", list->val);
		print_nodes (list->next);
	}
}

void print_list (LinkedList * list) {
	printf ("[");
	print_nodes (list);
	printf ("]\n");
}

void print_alt (LinkedList * list, int first) {
	if (list != NULL) {
		if (first)
			printf ("%d, ", list->val);
		print_alt (list->next, (first + 1) % 2);
	} 
}

/** append_node ()
 * find last, then append to it
 * return list head
 */
LinkedList * append_node (LinkedList * list, LinkedList * node) {
	if (list == NULL)
		return node;
	if (node == NULL)
		return list;

	LinkedList * it = list;
	while (it->next != NULL) {
		it = it->next;
	}
	it->next = node;
	return list;
}

/** array2list ()
 * create LinkedList from array
 */
LinkedList * array2list (int * xs, int size) {	
	LinkedList * list = NULL;
	for (int i = 0; i < size; i++) {
		LinkedList * node = create_node (xs[i]);
		if (list == NULL)
			list = node;
		else 
			list = append_node (list, node);
	}
	return list;
}

void test_print_alt () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = array2list (xs, SIZE);
	print_list (list);

	print_alt (list, 1); printf ("\n");
	print_alt (list, 0); printf ("\n");

	delete_nodes (list);
}

/** find_y_point ()
 * find jn at which 2 finite lists meet
 */
void find_y_point (LinkedList * list1, LinkedList * list2) {
	int len1 = 0, len2 = 0;
	LinkedList * first = list1;
	LinkedList * second = list2;
	while (first != NULL) {
		len1++;
		first = first->next;
	}
	while (second != NULL) {
		len2++;
		second = second->next;
	}

	first = list1;
	second = list2;

	if (len1 > len2) {
		int n = len1 - len2;
		while (n > 0) {
			first = first->next;
			n--;
		}		
	} else if (len2 > len1) {
		int n = len2 - len1;
		while (n > 0) {
			second = second->next;
			n--;
		}
	}

	while (first != NULL && second != NULL) {
		if (first->val == second->val) {
			printf ("The lists meet at value = %d\n", first->val);
			return;
		}
		first = first->next;
		second = second->next;
	}
	printf ("Lists are separate\n");
}

void test_y_point () {
	int xs[] = {1,2,3,4,5,6};
	LinkedList * list = NULL;
	LinkedList * last = NULL;
	LinkedList * jn = NULL;
	int jn_val = 4;
	for (int i = 0; i < 6; i++) {
		LinkedList * node = create_node (xs[i]);
		if (xs[i] == jn_val)
			jn = node;

		if (list == NULL) {
			list = node;
			last = list;
		} else {
			last->next = node;
			last = node;
		}
	}

	LinkedList * list2 = create_node (7);
	LinkedList * node1 = create_node (8);
	LinkedList * node2 = create_node (9);
	node2->next = jn;
	node1->next = node2;
	list2->next = node1;

	print_list (list);
	print_list (list2);

	find_y_point (list, list2);
}

/** find_jn_cycle ()
 * find the jn point in a list shaped like a '6'
 * assume input list has cycle; else may get SIGSEGV
 */
void find_jn_cycle (LinkedList * list) {
	if (list == NULL) 
		return;

	LinkedList * first = list;
	LinkedList * second = list->next;
	while (first->val != second->val) {
		first = first->next;
		second = second->next->next;
	}

	second = second->next;
	first->next = NULL;
	first = list;

	find_y_point (first, second);
}

void test_jn_cycle () {
	int xs[] = {1,2,3,4,5,6,7,8,9};
	int jn_val = 4;
	LinkedList * list = NULL;
	LinkedList * last = NULL;
	LinkedList * jn = NULL;
	for (int i = 0; i < 9; i++) {
		LinkedList * node = create_node (xs[i]);
		if (xs[i] == jn_val)
			jn = node;

		if (list == NULL) {
			list = node;
			last = list;
		} else {
			last->next = node;
			last = node;
		}
	}

	last->next = jn;						// cycle introduced
	// print_nodes (list); printf ("\n");	// don't print! testing only
	find_jn_cycle (list);
}

/**
 * reverse_arrows ()
 * reversal of a linked list (change links)
 * O(n) * O(n) = O(n^2)
 * For a linear solution, see reverse (), reverse_arrows_cont ()
 */
LinkedList * reverse_arrows (LinkedList * list) {
	if (list == NULL)
		return list;

	if (list->next == NULL)
		return list;
	else {
		LinkedList * tail = list->next;
		list->next = NULL;
		return append_node (reverse_arrows (tail), list);
	}
}

void test_reverse_arrows () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = array2list (xs, SIZE);
	print_list (list);

	list = reverse_arrows (list);
	print_list (list);

	delete_nodes (list);
}

/** reverse ()
 * reverse a LinkedList, O(n)
 * uses helper recursive function rev_rec ()
 */
void rev_rec (LinkedList ** list, LinkedList ** head, LinkedList ** tail) {
	if (* list != NULL) {
		rev_rec (&((* list)->next), head, tail);
		if (* head == NULL) {
			* head = * list;
			* tail = * head;
			return;
		}
		(* tail)->next = * list;
		* tail = * list;
	}
}

void reverse (LinkedList ** list) {
	LinkedList * head = NULL, * tail = NULL;
	rev_rec (list, &head, &tail);
	* list = head;
	tail->next = NULL;
}

/** reverse_iter ()
 * iterative reversal of LinkedList
 * 3-node solution - O(n)
 */
void reverse_iter (LinkedList ** list) {
	LinkedList * head = NULL, * tail = NULL;

	while (* list != NULL) {
		if (tail == NULL) {
			tail = * list;
			head = * list;
			continue;
		}
		LinkedList * cur = head;	// 3rd node
		head = * list;
		* list = (* list)->next;		
		head->next = cur;
	}
	* list = head;
	tail->next = NULL;
}

void test_reverse () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = array2list (xs, SIZE);
	print_list (list);

	// reverse (&list);
	reverse_iter (&list);
	print_list (list);

	delete_nodes (list);
}

/** delete_alt ()
 * delete every alternate element, starting w/ 2nd
 */
void delete_alt (LinkedList * list) {
	if (list != NULL) {
		while (list->next != NULL) {
			LinkedList * node = list->next;
			list->next = list->next->next;
			free (node);
			list = list->next;
		}
	}
}

void test_delete_alt () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = array2list (xs, SIZE);
	print_list (list);

	delete_alt (list);
	print_list (list);

	delete_nodes (list);
}


/** LinkedList container, w/ a reference to the last element 
 * for O(1) append () ops
 * Allows O(n) reversal
 */
typedef struct LLContainer {
	LinkedList * head;
	LinkedList * last;
} LLContainer;

LLContainer * append_cont (LLContainer * cont, LinkedList * node) {
	if (cont == NULL)
		return cont;

	if (node != NULL) {
		if (cont->head == NULL) {
			cont->head = node;
			cont->last = cont->head;
		} else {
			cont->last->next = node;
			cont->last = node;
		}
	}
	return cont;
}

void print_LLContainer (LLContainer * cont) {
	printf ("[ ");
	print_nodes (cont->head);
	printf (" ]\n");
}

LLContainer * reverse_arrows_cont (LLContainer * cont) {
	if (cont == NULL)
		return cont;

	if (cont->head == NULL)
		return cont;

	if (cont->head->next == NULL)
		return cont;
	else {
		LinkedList * head = cont->head;
		cont->head = cont->head->next;
		head->next = NULL;
		return append_cont (reverse_arrows_cont (cont), head);
	}
}

void delete_cont (LLContainer * cont) {
	if (cont != NULL) {
		delete_nodes (cont->head);
		free (cont);
	}
}

void test_reverse_arrows_cont () {
	LLContainer * cont = (LLContainer *) malloc (sizeof (LLContainer));
	cont->head = NULL;
	cont->last = NULL;
	int xs[] = {1,2,3,4,5};
	for (int i = 0; i < SIZE; i++) {
		LinkedList * node = create_node (xs[i]);
		cont = append_cont (cont, node);
	}

	print_LLContainer (cont);

	cont = reverse_arrows_cont (cont);
	print_LLContainer (cont);

	delete_cont (cont);
}

/** All tests
 */
void run_tests () {
	// test_y_point ();
	// test_reverse_arrows ();
	test_reverse ();
	// test_print_alt ();
	// test_reverse_arrows_cont ();
	// test_delete_alt ();
	// test_jn_cycle ();
}

int main () {
	run_tests ();

	return 0;
}
