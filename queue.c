#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_basic_Queue () {
	int n = 8;
	void ** items = (void **) malloc (sizeof (void *) * n);
	for (int i = 0; i < n; i++) {
		int val = i + 1;
		items[i] = wrap_Item (&val);
	}

	OList * list = create_OList (items, n);		
	OList * head = list;

	Queue * q = create_Queue ();
	while (list) {
		enqueue (q, list->item);
		list = list->next;
	}
	
	print_Queue (q);

	delete_Queue (q);
	delete_OList (head);

	for (int i = 0; i < n; i++)
		delete_Item (items[i]);
	free (items);	
}

void run_tests() {
	test_basic_Queue ();
}

int main() {
	run_tests();

	return 0;
}
