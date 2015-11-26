#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testGenericArray () {
	int count = 4;
	Object ** es = (Object **) calloc (sizeof (Object *), count);
	int x = 42;
	double pi = 3.14f;
	char c = 'M';
	char * str = "hitchhiker's guide to the galaxy";

	es[0] = createObject (_INT, &x);
	es[1] = createObject (_DOUBLE, &pi);
	es[2] = createObject (_CHAR, &c);
	es[3] = createObject (_STR, &str);

	printf ("["); for (int i = 0; i < count; i++) {	outObject (es[i]);	} 
	printf ("]\n");

	for (int i = 0; i < count; i++) { deleteObject (es[i]); }
	free (es);
}

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
	// testArrayPrint ();
	testGenericArray ();
}

int main() {
	runTests();

	return 0;
}
