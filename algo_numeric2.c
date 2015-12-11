#include <stdio.h>
#include <stdlib.h>
#include "arrayutils.h"

#define MAX_ELEMENTS 128

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


/** trailingZerosInFact ()
 * returns the number of trailing zeros in factorial of given number
 * http://www.spoj.com/problems/FCTRL/
 */
int trailingZerosInFact (int n) {
	int max_exp_5 = (int) (log (n * 1.0)/ log (5.0));
	int max_power = (int) (pow (5.0, max_exp_5));
	int num5 = 0;
	while (max_power > 1) {
		num5 += n/max_power;
		max_power /= 5;
	}
	return num5;
}


/** primeGeneratr ()
 * generate primes up to given number
 * Sieve of Eratosthenes + Memoization
 * # primes approximated using Prime Number Theorem (PNT)
 */
int primeGeneratr (int n) {
	if (n < 2)
		return 0;

	int pnt_n = (int) (n * 1.3 / log (n));
	printf ("n = %d. PNT n = %d\n", n, pnt_n);
	int * primes = (int *) calloc (sizeof (int), pnt_n);

	int last_idx = 0; primes[last_idx++] = 2;
	for (int i = 3; i <= n; i++) {
		int is_prime = 1;
		for (int j = 0; j < last_idx; j++) {
			if (!(i % primes[j])) {
				is_prime = 0;
				break;
			}
		}
		if (last_idx == pnt_n)
			break;
		if (is_prime)
			primes[last_idx++] = i;
	}
	outArrInt (primes, last_idx);
	free (primes);
	return last_idx;
}


/** palin ()
 * returns the next palindrome higher than given number
 * takes the number as an array of digits
 * extremely subtle cases: 6999 and the like
 */
void palin (unsigned * xs, int lo, int hi, int carry) {
	if (lo > hi)
		return;

	xs[lo] = (xs[lo] + carry) % 10;
	if (xs[hi] > xs[lo]) {
		xs[hi-1] = (xs[hi-1] + 1) % 10;
		if (!xs[hi-1]) {
			carry = 1;
			xs[lo] = (xs[lo] + carry) % 10;
		}
	}
	xs[hi] = xs[lo];
	palin (xs, lo+1, hi-1, carry);
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


void testTrailingZerosInFact () {
	int ns[] = {3,60,100,1024,23456,8735373};
	int size = 6, tz = 0;
	for (int i = 0; i < size; i++) {
		tz = trailingZerosInFact (ns[i]);
		printf ("number of trailing zeros in %d! = %d\n", ns[i], tz);
	}
}


void testPrimality () {
	int ns[] = {10,100,500,1000,2000,10000,100000};
	int size = 7;
	for (int i = 0; i < size; i++) {		
		int last_idx = primeGeneratr (ns[i]);
		printf ("# primes = %d\n\n", last_idx);
	}
}


void testPalin () {
	int test_cases = 8;
	int sizes[] = {1, 2, 3, 4, 5, 8, 13, 18};
	long ns[] = {8, 12, 113, 4999, 69999, 22833822, 2053320533443, 100000000000000002L};
	for (int i = 0; i < test_cases; i++) {		
		unsigned * xs = numToDigits (ns[i]);
		printf ("%ld: \n", ns[i]);
		outArrInt (xs, sizes[i]); 

		palin (xs, 0, sizes[i]-1, 0);
		outArrInt (xs, sizes[i]);
		printf ("\n");
		free (xs);
	}
}


void runTests() {
	// testPlateau ();
	// testMissingElement ();
	// testInplaceReverse ();
	// testFindSingleElement ();
	// testTrailingZerosInFact ();
	// testPrimality ();
	testPalin ();
}

int main() {
	runTests();

	return 0;
}
