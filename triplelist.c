#include <stdio.h>
#include <stdlib.h>

#include "triplelist.h"
#include "queue.h"

/** author: mayukh
 * github.com/mayukh42
 */

/** build_List ()
 * Build this list:
 	5 <--> 33 <--> 17 <--> 2 <--> 1
 	|					   |
 	6 <--> 25 <--> 6 	   2 <--> 7
 		   |	   | 	   | 
 		   8 	   9 	   12 <--> 5
 		   		   | 	   | 
 		   		   7 	   21 <--> 3
 * flatten () should produce
	5 <--> 33 <--> 17 <--> 2 <--> 1 <--> 6 <--> 25 <--> 6 <--> 2 <--> 7 <--> 8 <--> 9 <--> 12 <--> 5 <--> 7 <--> 21 <--> 3
	while preserving the child relationships
 */
TList * build_TList () {
	int x0s[] = {5,33,17,2,1};
	TList * list0 = create_List_from_Array (NULL, x0s, 5);

	int x1s[] = {6,25,6};
	TList * list1 = create_List_from_Array (NULL, x1s, 3);

	int x2s[] = {2,7};
	TList * list2 = create_List_from_Array (NULL, x2s, 2);

	list0->child = list1;
	list0->next->next->next->child = list2;

	int x3s[] = {8};
	TList * list3 = create_List_from_Array (NULL, x3s, 1);

	int x4s[] = {9};
	TList * list4 = create_List_from_Array (NULL, x4s, 1);

	int x5s[] = {12,5};
	TList * list5 = create_List_from_Array (NULL, x5s, 2);

	list1->next->child = list3;
	list1->next->next->child = list4;
	list2->child = list5;

	int x6s[] = {7};
	TList * list6 = create_List_from_Array (NULL, x6s, 1);

	int x7s[] = {21,3};
	TList * list7 = create_List_from_Array (NULL, x7s, 2);

	list4->child = list6;
	list5->child = list7;

	return list0;
}

/** flatten ()
 * Flatten a 2D list to a single horizontal level
 * preserve child relationships
 */
TList * flatten (TList * list) {
	Queue * q = create_Queue ();
	TList * it = list;
	while (it) {
		if (it->child)
			enqueue (q, it->child);
		if (!it->next) {
			TList * next = (TList *) dequeue (q);
			it->next = next;
			if (next) 
				next->prev = it;
		}
		it = it->next;
	}
	delete_Queue (q);
	return list;
}

/** unflatten ()
 * Unflatten the list back to its original shape
 * i.e. inverse of the fn flatten ()
 * unflatten () on original list returns the same list
 */
TList * unflatten (TList * list) {
	Queue * q = create_Queue ();
	TList * it = list;
	while (it) {
		if (it->child) {
			TList * last = it->child->prev;
			if (last) 
				last->next = NULL;
			it->child->prev = NULL;
			enqueue (q, it->child);
		}
		if (!it->next) {
			TList * next = (TList *) dequeue (q);
			it = next;
		}
		else
			it = it->next;
	}
	delete_Queue (q);
	return list;
}

/** tests
 */
void test_flatten_unflatten () {
	TList * list = build_TList ();
	printf ("Original: \n");
	print_TList (list, print_TNode_rec);
	
	list = flatten (list);
	printf ("Flattened: \n");
	print_TList (list, print_TNode_flattened);

	list = unflatten (list);
	printf ("Unflattened (i.e. Original): \n");
	print_TList (list, print_TNode_rec);

	delete_TList (list);
}

void test_create_TList () {
	TList * list = build_TList ();
	print_TList (list, print_TNode_rec);
}

void run_tests() {
	// test_create_TList ();
	test_flatten_unflatten ();
}

int main() {
	run_tests();

	return 0;
}
