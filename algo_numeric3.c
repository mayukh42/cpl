#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** lgc ()
 * ceil of log2 function
 */
long lgc (long n) {
	if (n < 1) return LONG_MIN;
	else if (n == 1) return 0;

	long x = 1, l = 0;	
	while (x < n) {
		x <<= 1;
		l++;
	}
	return l;
}

/** lgf ()
 * floor of log2 function
 */
long lgf (long n) {
	if (n < 1) return LONG_MIN;
	else if (n == 1) return 0;

	long x = 1, l = 0;	
	while (x < n) {		
		x <<= 1;
		l++;
	}
	if (x > n)
		l--;
	return l;
}

/** exponent ()
 * a pow () implementation for long
 * O(lg n)
 */
long exponent (long a, long n) {
	if (!n) return 1;
	if (n == 1) return a;

	long p = a, x = 1, m = lgf (n), y = 1<<m;
	while (x < y){
		p *= p;
		x *= 2;
	}
	for (long i = x; i < n; i++)
		p *= a;
	return p;
}


void testLg () {
	for (long i = 0; i < 10; i++) {
		printf ("ceil (lg (%ld)) = %ld\n", i, lgc (i));
		printf ("floor (lg (%ld)) = %ld\n", i, lgf (i));
	}
}

void testExponent () {
	long a = 2;
	for (long i = 0; i < 20; i++)
		printf ("%ld^%ld = %ld\n", a, i, exponent (a, i));
}

void runTests() {
	// testLg ();
	testExponent ();
}

int main() {
	runTests();

	return 0;
}
