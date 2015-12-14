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
	long n1 = 2053320533443L, n2 = 205332L; 
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

void testHelpers () {
	// trim
	int size = 10;
	for (int i = 0; i < 10; i++) {
		unsigned n = rand () % 8;
		BigInt * b = b_empty (size);
		b->digits[2+n] = i ? n : 0;
		b = b_trim (b);
		BigInt_print (b); printf (" (index=%d) (fromlast=%d) (digit=%u)\n", 2+n, 8-n, n);
		BigInt_delete (b);
	}

	long n = 42L;
	BigInt * b = BigInt_create (n); 
	BigInt_print (b); printf (" b\n");   
	// multiplyByDigit
	for (int i = 0; i < 10; i++) {
		int k = rand () % 10;
		printf ("%d\n", k);
		int digit = k;
		BigInt * p = b_multiplyByDigit (b, digit);
		BigInt_print (p); printf (" p, x%u\n", digit); 
		BigInt_delete (p); 
	}

	// leftShift 
	for (int i = 0; i < 10; i++) {
		BigInt * p = b_leftShift (b, i);
		BigInt_print (p); printf (" p, multiply by 10^%d\n", i); 
		BigInt_delete (p);   
	}

	// multiplyByNumber
	long ls[] = {2,25,300,420,1024};
	for (int i = 0; i < 5; i++) { 
		BigInt * p = b_multiplyByNumber (b, ls[i]);  
		BigInt_print (p); printf (" p, x%ld\n", ls[i]); 
		BigInt_delete (p); 
	}

	BigInt_delete (b); 

	// copyRange
	BigInt * b1 = BigInt_create (2053320533443L);
	BigInt * b2 = b_copyRange (b1, 2, 8);
	BigInt_print (b1); printf (" b1\n");
	BigInt_print (b2); printf (" b2\n");
	BigInt_delete (b1); BigInt_delete (b2);

	// absCompareRange
	BigInt * b3 = BigInt_create (2053320533443L); 
	BigInt * b4 = BigInt_create (4096);
	BigInt_print (b3); printf (" b3\n");
	BigInt_print (b4); printf (" b4\n");
	for (int i = 0; i < 10; i++)
		printf ("%d\n", b_compareDigitsRange (b3->digits, b4->digits, i, 0, 4));
	BigInt_delete (b3); BigInt_delete (b4);

	// addRange
	int x = 4, y = 4, z = x+1;
	unsigned xs[] = {5,6,7,8}; 
	unsigned ys[] = {5,3,1,0}; 
	unsigned * zs = (unsigned *) calloc (sizeof (unsigned), z); 
	b_addRange (xs, ys, zs, x, y); 
	outArrInt (xs, x); outArrInt (ys, y); outArrInt (zs, z);
	free (zs);

	// multiplierRange	
	size = 4; 
	unsigned es[] = {5,6,7,8};
	unsigned fs[] = {1,2,3,4}; 
	printf ("multipler = %u\n", b_multiplierRange (es, fs, size));
}

void runTests() { 
	// testBasicBigInt ();
	// testBinaryFn (BigInt_add);
	// testBinaryFn (BigInt_subtract); 
	// testBinaryFn (BigInt_product);
	// testBinaryCmpFn (BigInt_compare);
	// testBinaryCmpFn (BigInt_absCompare);
	testHelpers ();
}

int main() {
	runTests();

	return 0;
}
