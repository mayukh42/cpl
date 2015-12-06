#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testSwap () {
	int a = 3, b = 5;
	printf ("before swap: a = %d, b = %d\n", a, b);
	swapInt (&a, &b);
	printf ("after swap: a = %d, b = %d\n", a, b);
	SWAP(int, a, b);	// macro, not a function
	printf ("after SWAP: a = %d, b = %d\n", a, b);
}

void runTests() {
	testSwap ();
}

int main() {
	runTests();

	return 0;
}
