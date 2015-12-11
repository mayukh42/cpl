#ifndef __BIGINT_H
#define __BIGINT_H

#include "arrayutils.h"

/** Big Integer implementation
 */

typedef struct BigInt {
	unsigned * digits;
	int size;
	int sign;
} BigInt;


BigInt * BigInt_create (long n) {
	BigInt * bi = (BigInt *) calloc (sizeof (BigInt), 1);
	if (n < 0) {
		bi->sign = 1;
		n *= -1;
	}
	bi->digits = numToDigits (n);
	bi->size = !n ? 1 : (int) (1.0 + log10 (n * 1.0));
	return bi;
}

void BigInt_delete (BigInt * bi) {
	if (bi) {
		free (bi->digits);
		free (bi);
	}
}

void BigInt_print (BigInt * b) {
	if (b) {
		printf ("%s", b->sign ? "-" : " ");
		for (int i = 0; i < b->size; i++)
			printf ("%u", b->digits[i]);
	}
}

BigInt * BigInt_addHelper (BigInt * b1, BigInt * b2) {
	int size = b1->size;
	BigInt * b3 = (BigInt *) calloc (sizeof (BigInt), 1);
	b3->digits = (unsigned *) calloc (sizeof (unsigned), size);
	b3->size = size;
	int carry = 0, j, sum = 0;
	for (int i = 0; i < b2->size; i++) {
		int k = b2->size-1-i; j = b1->size-1-i;
		sum = carry + b1->digits[j] + b2->digits[k];
		if (sum > 9) {
			sum -= 10;
			carry = 1;
		} 
		else
			carry = 0;
		b3->digits[j] = sum;
	}
	j--;
	for (; j >= 0; j--) {
		sum = carry + b1->digits[j];
		if (sum > 9) {
			sum -= 10;
			carry = 1;
		}
		else
			carry = 0;
		b3->digits[j] = sum;
	}
	if (carry) {
		unsigned * digits = (unsigned *) calloc (sizeof (unsigned), size+1);
		memcpy (digits + 1, b3->digits, sizeof (unsigned) * size);
		digits[0] = 1u;
		free (b3->digits);
		b3->digits = digits;
		b3->size++;
	}
	return b3;
}

BigInt * BigInt_add (BigInt * b1, BigInt * b2) {	
	if (!b1 && !b2) return NULL;
	else if (!b1) return b2;
	else if (!b2) return b1;

	if (b1->size >= b2->size)
		return BigInt_addHelper (b1, b2);
	else
		return BigInt_addHelper (b2, b1);
}

int toInt3 (BigInt * b) {
	if (!b || b->size > 4)
		return -1;
	int n = 0;
	for (int i = 0; i < b->size; i++)
		n = n * 10 + b->digits[i];

	if (b->sign)
		n *= -1;
	return n;
}



#endif