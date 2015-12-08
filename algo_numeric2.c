#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

/** author: mayukh
 * github.com/mayukh42
 */

/** longestPlateau ()
 * returns the length of largest segment that has equal elements 
 * in a sorted array
 */
int longestPlateau (int * xs, int count) {
	int len = 0;
	if (!xs || !count)
		return len;

	int curr = * xs, i = 0, maxlen = 0;
	while (i < count) {
		int next = xs[i++];
		if (curr == next) 
			len++;
		else {
			curr = next;
			len = 1;
		}
		maxlen = len > maxlen ? len : maxlen;
	}
	return maxlen;
}


int missingElement (int * xs, int n) {
	int sum = (n+1) * (n+2)/2;
	for (int i = 0; i < n; i++)
		sum -= xs[i];
	return sum;
}


/** inplaceReverse ()
 * reverses an array in place
 */
void inplaceReverse (int * xs, int size) {
	if (!xs || !size)
		return;

	for (int i = 0; i < size>>1; i++)
		swapInt (xs+i, xs+size-1-i);
}


/** findSingleElement ()
 * returns the only element occuring in an array once, 
 * among all others that occur twice.
 */
int findSingleElement (int * xs, int size) {
	int single_elem = 0;
	for (int i = 0; i < size; i++)
		single_elem ^= xs[i];
	return single_elem;
}


void testPlateau () {
	int xs[] = {1,2,2,3,3,3,4,5,5,6,6,6,6,7};
	int count = 14;
	printf ("longest plateau in array is of length %d\n", longestPlateau (xs, count));
}


void testMissingElement () {
	int size1 = 10, size2 = 20;
	int * elems = (int *) calloc (sizeof (int), size1 + size2);
	int * elems1 = build123Array (size1);
	int * elems2 = build123ArrayBaseVal (size2, size1+1);
	memcpy (elems, elems1, sizeof (int) * size1);
	memcpy (elems + size1, elems2, sizeof (int) * size2);
	outArrInt (elems, size1+size2); 

	printf ("missing element in array = %d\n", missingElement (elems, size1+size2));

	free (elems); free (elems1); free (elems2);
}


void testInplaceReverse () {
	int size = 11;
	int * elems = build123Array (size);
	outArrInt (elems, size);
	inplaceReverse (elems, size);
	outArrInt (elems, size);
	free (elems);
}


void testFindSingleElement () {
	int size = 15;
	int elems[] = {1,2,1,2,3,3,4,5,5,4,6,7,6,8,7};
	printf ("single element in array = %d\n", findSingleElement (elems, size));
}


void runTests() {
	// testPlateau ();
	// testMissingElement ();
	// testInplaceReverse ();
	testFindSingleElement ();
}

int main() {
	runTests();

	return 0;
}
