#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
#include "limits.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testBasicBigInt () {
	long n1 = 2053320533443L, n2 = -15L;
	BigInt * b1 = BigInt_create (n1);
	BigInt_print (b1); printf ("\n");

	BigInt * b2 = BigInt_create (n2);
	BigInt_print (b2); printf ("\n");

	int b2n = toInt3 (b2);
	printf ("b2 int = %d\n", b2n);

	BigInt_delete (b1);
	BigInt_delete (b2); 
}

void testAdd () {
	long n1 = 999L, n2 = 993L;
	BigInt * b1 = BigInt_create (n1);
	BigInt_print (b1); printf ("\n");

	BigInt * b2 = BigInt_create (n2);
	BigInt_print (b2); printf ("\n");

	BigInt * b3 = BigInt_add (b2, b1);
	BigInt_print (b3); printf ("\n");

	BigInt_delete (b1);
	BigInt_delete (b2);
	BigInt_delete (b3);
}

void runTests() {
	testBasicBigInt ();
	// testAdd ();
}

int main() {
	runTests();

	return 0;
}
