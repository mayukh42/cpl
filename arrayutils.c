#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testGenericArray () {
	int count = 4;
	Element ** es = (Element **) calloc (sizeof (Element *), count);
	int x = 42;
	double pi = 3.14f;
	char c = 'M';
	char * str = "hitchhiker's guide to the galaxy";

	es[0] = createElement (_INT, &x);
	es[1] = createElement (_DOUBLE, &pi);
	es[2] = createElement (_CHAR, &c);
	es[3] = createElement (_STR, &str);

	printf ("["); for (int i = 0; i < count; i++) {	outElement (es[i]);	} 
	printf ("]\n");

	for (int i = 0; i < count; i++) { free (es[i]); }
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
