#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testArrayPrint () {
	unsigned n = 5;
	int * xs = malloc (sizeof (int) * n);
	for (unsigned i = 0; i < n; i++)
		xs[i] = i+1;	
	outArrInt (xs, n);

	char * css[] = {"he", "hell", "hello", "helium", "helios"};
	outArrStr (css, n);

	free (xs);
}

void runTests() {
	testArrayPrint ();
}

int main() {
	runTests();

	return 0;
}
