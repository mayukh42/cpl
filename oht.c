#include <stdio.h>
#include <stdlib.h>
#include "oht.h"

/** author: mayukh
 * github.com/mayukh42
 */

/** hf1 (): k % m
 */
int hf1Int (const void * const e) {
	int * e_int = (int *) e;
	return (* e_int) % MAX_ELEMENTS;
}


/** hf2: 1 + k % m' 
 * where m' = m-2
 */
int hf2Int (const void * const e) {
	int * e_int = (int *) e;
	return 1 + ((* e_int) % (MAX_ELEMENTS-2));
}


/** equals ()
 * client fn returns !0 if two elements are equal
 * or 0 if not equal
 */
int equalsInt (const void * e1, const void * e2) {
	int e1_int = * (int *)e1;
	int e2_int = * (int *)e2;
	return e1_int == e2_int;
}


void printInt (const void * e) {
	int * e_int = (int *) e;
	printf ("%d, ", * e_int);
}


void testHf1 () {
	int xs[] = {4,14,28,42,128,28};
	printf ("hash fn 1:\n");
	for (int i = 0; i < 6; i++) {
		int h = hf1Int (xs+i); 
		printf ("%d: %d\n", xs[i], h);	
	}
}


void testHf2 () {
	int xs[] = {4,14,28,42,128,28};
	printf ("hash fn 2:\n");
	for (int i = 0; i < 6; i++) {
		int h = hf2Int (xs+i); 
		printf ("%d: %d\n", xs[i], h);	
	}
}


void testHf () {
	int xs[] = {4,14,28,42,128,28};
	printf ("double hash fn:\n");
	for (int i = 0; i < 6; i++) {
		int h = hf (xs+i, 1, hf1Int, hf2Int);
		printf ("%d: %d\n", xs[i], h);	
	}
}


void testOht () {
	int count = 24;
	int ** xs = (int **) malloc (sizeof (int *) * count);
	for (int i = 0; i < count; i++) {
		xs[i] = (int *) malloc (sizeof (int));
		int val = rand () % (MAX_ELEMENTS<<2);
		* xs[i] = val;
	}
	OHashTable * oht = createOhtFromArray ((void **) xs, count, hf1Int, hf2Int, equalsInt);
	printOht (oht, printInt);

	// insert same elements again
	for (int i = 0; i < (count>>2); i++) {
		int * x = xs[rand () % count];
		int res = ohtInsert (oht, x, hf1Int, hf2Int, equalsInt);
		printf ("  %d %s\n", * x, res != -1 ? "inserted" : "not inserted");
	}
	printOht (oht, printInt);

	// remove some elements
	for (int i = 0; i < (count>>2); i++) {
		int * x = xs[rand () % count];
		int res = ohtRemove (oht, x, hf1Int, hf2Int, equalsInt);
		printf ("  %d %s\n", * x, res != -1 ? "removed" : "not removed");
	}
	printOht (oht, printInt);

	deleteOht (oht);
	for (int i = 0; i < count; i++)
		free (xs[i]);
	free (xs);
}


void testHfs () {
	testHf1 ();
	testHf2 ();
	testHf ();
}


void runTests() {
	// testHfs ();
	testOht ();
}


int main() {
	runTests();

	return 0;
}
