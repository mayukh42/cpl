#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testSwap () {
	int a = 3, b = 5;
	printf ("original: a = %d, b = %d\n", a, b);
	swapInt (&a, &b);
	printf ("after swapInt: a = %d, b = %d\n", a, b);
	SWAP(int, a, b);	// macro, not a function
	printf ("after SWAP: a = %d, b = %d\n", a, b);
	swap (&a, &b, sizeof (int));
	printf ("after swap: a = %d, b = %d\n", a, b);

	Object * o1 = createObject (_INT, &a);	// not a good idea
	Object * o2 = createObject (_INT, &b);	// in general, dont use stack addresses
	outObject (o1); outObject (o2);
	printf ("\n");

	swap (o1, o2, sizeof (Object));
	outObject (o1); outObject (o2);
	printf ("\n");

	deleteObject (o1); deleteObject (o2);
}

void runTests() {
	testSwap ();
}

int main() {
	runTests();

	return 0;
}
