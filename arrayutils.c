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

void testMat () {
	int size = 4;
	int elems[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int ** xs = buildMat (elems, size, size);
	outMat (xs, size, size);

	int ** ys = buildTriangularMat (size, elems);
	outTriangularMat (ys, size);

	deleteMat (xs, size);
	deleteMat (ys, size);
}

void testArrayPrint () {
	unsigned n = 5;
	int * xs = calloc (sizeof (int), n);
	for (unsigned i = 0; i < n; i++)
		xs[i] = i+1;	
	outArrInt (xs, n);

	char * css[] = {"he", "hell", "hello", "helium", "helios"};
	outArrStr (css, n);

	free (xs);
}

void testRotateMat () {
	int size = 4;
	int ** xs = buildMat123 (size, size);
	outMat (xs, size, size);

	rotateMat (xs, size);
	outMat (xs, size, size);

	deleteMat (xs, size);
}

void testRotateMat90c () {
	int size = 4;
	int ** xs = buildMat123 (size, size);
	outMat (xs, size, size);

	int ** ys = rotateMat90c (xs, size);
	outMat (ys, size, size);

	deleteMat (xs, size);
	deleteMat (ys, size);
}

void testQuickSort () {
	int size = 32;
	int * elems = buildRandomIntArray (size, 100);
	outArrInt (elems, size);

	quicksort (elems, size);
	outArrInt (elems, size);
	printf ("number of swaps: %d\n", num_swaps);

	quicksort (elems, size);
	outArrInt (elems, size); 
	printf ("number of swaps: %d\n", num_swaps);

	free (elems);
}

void runTests() {
	// testArrayPrint ();
	// testGenericArray ();
	// testMat ();		
	// testRotateMat ();
	// testRotateMat90c ();
	testQuickSort (); 
}

int main() {
	runTests();

	return 0;
}
