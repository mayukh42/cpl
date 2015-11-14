#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist.h"

/** author: mayukh
 * github.com/mayukh42
 */

/** m_from_last ()
 * returns mth element counting from last. O(n) w/ single pass
 * m = 0 returns the last element
 * returns INT_MIN if m >= length of list
 */
int m_from_last (List * list, int m) {
	if (list == NULL || m < 0)
		return INT_MIN;

	int n = 0;
	List * mth = list, * it = list;
	while (n < m && it != NULL) {
		it = it->next;
		n++;
	}	
	if (it == NULL)
		return INT_MIN;
	while (it->next != NULL) {
		it = it->next;
		mth = mth->next;
	}
	return mth->val;
}

/** detect_cycle ()
 * returns true if list contains a cycle. O(n)
 */
int detect_cycle (List * list) {
	if (list == NULL)
		return 0;

	List * first = list, * second = list->next;
	while (first != second && second != NULL && second->next != NULL) {
		first = first->next;
		second = second->next->next;
	}
	return first == second;
}

// all tests
void test_detect_cycle () {
	List * xs_list = create_list_from_array ();
	List * jn = xs_list->next->next;
	List * head = xs_list;
	while (head != NULL && head->next != NULL)
		head = head->next;
	head->next = jn;

	int is_cycle = detect_cycle (xs_list);
	printf ("List %s a cycle.\n", is_cycle ? "has" : "does not have");

	head->next = NULL;
	delete_List (xs_list);
}

void test_m_from_last () {
	List * xs_list = create_list_from_array ();
	int m = 0;
	int elem = m_from_last (xs_list, m);
	printf ("%dth from last = %d\n", m, elem);

	delete_List (xs_list);
}

void test_create () {
	List * xs_list = create_list_from_array ();
	print_List (xs_list);

	delete_List (xs_list);
}

void test_reverse () {
	List * xs = create_list_from_array ();
	print_List (xs);

	xs = reverse (xs);
	print_List (xs);

	delete_List (xs);
}

void run_tests () {
	// test_create ();
	// test_m_from_last ();
	// test_detect_cycle ();
	test_reverse ();
}

int main () {
	run_tests ();

	return 0;
}
