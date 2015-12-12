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

	int b2n = b_toInt3 (b2);
	printf ("b2 int = %d\n", b2n);

	BigInt_delete (b1); BigInt_delete (b2); 
}

void testBinaryCmpFn (bigInt_CmpFn cmp) {
	long n1 = 19L, n2 = 17L;
	BigInt * b1p = BigInt_create (n1); BigInt * b1n = BigInt_create (-n1); 
	BigInt * b2p = BigInt_create (n2); BigInt * b2n = BigInt_create (-n2); 
	printf ("%ld, %ld: %d\n", n1, n2, cmp (b1p, b2p));
	printf ("%ld, %ld: %d\n", n1, -n2, cmp (b1p, b2n));
	printf ("%ld, %ld: %d\n", -n1, n2, cmp (b1n, b2p));
	printf ("%ld, %ld: %d\n", -n1, -n2, cmp (b1n, b2n));

	BigInt_delete (b1p); BigInt_delete (b2p); 
	BigInt_delete (b1n); BigInt_delete (b2n);
}

void testBinaryFn (bigInt_BinaryFn bFn) {
	long n1 = 42L, n2 = 25L; 
	BigInt * b1p = BigInt_create (n1); BigInt * b1n = BigInt_create (-n1); 
	BigInt * b2p = BigInt_create (n2); BigInt * b2n = BigInt_create (-n2); 

	BigInt_print (b1p); printf (", "); BigInt_print (b2p); printf ("\n");
	BigInt * b3pp = bFn (b1p, b2p);
	BigInt_print (b3pp); printf ("\n");

	BigInt_print (b1p); printf (", "); BigInt_print (b2n); printf ("\n");
	BigInt * b3pn = bFn (b1p, b2n);
	BigInt_print (b3pn); printf ("\n");

	BigInt_print (b1n); printf (", "); BigInt_print (b2p); printf ("\n");
	BigInt * b3np = bFn (b1n, b2p);
	BigInt_print (b3np); printf ("\n");

	BigInt_print (b1n); printf (", "); BigInt_print (b2n); printf ("\n");
	BigInt * b3nn = bFn (b1n, b2n);
	BigInt_print (b3nn); printf ("\n");

	BigInt_delete (b1p); BigInt_delete (b2p);
	BigInt_delete (b1n); BigInt_delete (b2n);

	BigInt_delete (b3pp); BigInt_delete (b3pn);
	BigInt_delete (b3np); BigInt_delete (b3nn);
}

void testElementWiseProduct () {
	long n1 = 42L, n2 = 10L;
	BigInt * b1 = BigInt_create (n1); 
	BigInt * p1 = b_elementWiseProduct (b1, n1); 
	BigInt * p2 = b_elementWiseProduct (b1, n2);
	BigInt_print (b1); printf (" b1\n");  
	BigInt_print (p1); printf (" p1\n");
	BigInt_print (p2); printf (" p2\n"); 

	BigInt_delete (b1); BigInt_delete (p1); BigInt_delete (p2); 
}

void runTests() {
	// testBasicBigInt ();
	// testBinaryFn (BigInt_add);
	// testBinaryFn (BigInt_subtract); 
	testElementWiseProduct ();
	// testBinaryFn (BigInt_product);
	// testBinaryCmpFn (BigInt_compare);
	// testBinaryCmpFn (BigInt_absCompare);
}

int main() {
	runTests();

	return 0;
}
