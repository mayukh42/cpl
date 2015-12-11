#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
#include "limits.h"

/** author: mayukh
 * github.com/mayukh42
 */

/** Big Int tests
 */

void testBasicBigInt () {
	long n1 = 2053320533443L, n2 = 0L;
	BigInt * b1 = BigInt_create (n1);
	BigInt_print (b1); printf ("\n");

	BigInt * b2 = BigInt_create (n2);
	BigInt_print (b2); printf ("\n");

	int b2n = toInt3 (b2);
	printf ("b2 int = %d\n", b2n);

	BigInt_delete (b1); BigInt_delete (b2); 
}

void testAdd () {
	long n1 = 999L, n2 = 993L;
	BigInt * b1 = BigInt_create (n1);
	BigInt_print (b1); printf ("\n");

	BigInt * b2 = BigInt_create (n2);
	BigInt_print (b2); printf ("\n");

	BigInt * b3 = BigInt_add (b2, b1);
	BigInt_print (b3); printf ("\n");

	BigInt_delete (b1); BigInt_delete (b2);
	BigInt_delete (b3);
}

void testSubtract () {
	long n1 = 993L, n2 = 993L; 
	BigInt * b1p = BigInt_create (n1); BigInt * b1n = BigInt_create (-n1); 
	BigInt * b2p = BigInt_create (n2); BigInt * b2n = BigInt_create (-n2); 

	BigInt_print (b1p); printf (", "); BigInt_print (b2p); printf ("\n");
	BigInt * b3pp = BigInt_subtract (b1p, b2p);
	BigInt_print (b3pp); printf ("\n");

	BigInt_print (b1p); printf (", "); BigInt_print (b2n); printf ("\n");
	BigInt * b3pn = BigInt_subtract (b1p, b2n);
	BigInt_print (b3pn); printf ("\n");

	BigInt_print (b1n); printf (", "); BigInt_print (b2p); printf ("\n");
	BigInt * b3np = BigInt_subtract (b1n, b2p);
	BigInt_print (b3np); printf ("\n");

	BigInt_print (b1n); printf (", "); BigInt_print (b2n); printf ("\n");
	BigInt * b3nn = BigInt_subtract (b1n, b2n);
	BigInt_print (b3nn); printf ("\n");

	BigInt_delete (b1p); BigInt_delete (b2p);
	BigInt_delete (b1n); BigInt_delete (b2n);

	BigInt_delete (b3pp); BigInt_delete (b3pn);
	BigInt_delete (b3np); BigInt_delete (b3nn);
}

void testCompare () {
	long n1 = 19L, n2 = 17L;
	BigInt * b1p = BigInt_create (n1); BigInt * b1n = BigInt_create (-n1); 
	BigInt * b2p = BigInt_create (n2); BigInt * b2n = BigInt_create (-n2); 
	printf ("compare: %ld, %ld: %d\n", n1, n2, BigInt_compare (b1p, b2p));
	printf ("compare: %ld, %ld: %d\n", n1, -n2, BigInt_compare (b1p, b2n));
	printf ("compare: %ld, %ld: %d\n", -n1, n2, BigInt_compare (b1n, b2p));
	printf ("compare: %ld, %ld: %d\n", -n1, -n2, BigInt_compare (b1n, b2n));
	printf ("absCompare: %ld, %ld: %d\n", -n1, -n2, BigInt_absCompare (b1n, b2n));

	BigInt_delete (b1p); BigInt_delete (b2p); 
	BigInt_delete (b1n); BigInt_delete (b2n);
}

void runTests() {
	// testBasicBigInt ();
	// testAdd ();
	testSubtract ();
	// testCompare ();
}

int main() {
	runTests();

	return 0;
}
