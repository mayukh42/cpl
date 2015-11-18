#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_array_print () {
	unsigned n = 5;
	int * xs = malloc (sizeof (int) * n);
	for (unsigned i = 0; i < n; i++)
		xs[i] = i+1;
	print_arr (&xs, _INT);
}

void run_tests() {
	test_array_print ();
}

int main() {
	run_tests();

	return 0;
}
