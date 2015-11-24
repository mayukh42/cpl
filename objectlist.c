#include <stdio.h>
#include <stdlib.h>
#include "objectlist.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_basic_OList () {
	int n = 8;
	void ** items = (void **) malloc (sizeof (void *) * n);
	for (int i = 0; i < n; i++) {
		int val = i + 1;
		items[i] = wrap_Item (&val);
	}

	OList * xs_list = create_OList (items, n);	

	print_OList (xs_list, print_Item);
	delete_OList (xs_list); 

	for (int i = 0; i < n; i++)
		delete_Item (items[i]);
	free (items);
}

void run_tests() {
	test_basic_OList ();	
}

int main() {
	run_tests();

	return 0;
}
