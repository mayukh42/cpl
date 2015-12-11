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


BigInt * BigInt_copyPart (BigInt * b, int from) {
	if (!b || from >= b->size)
		return NULL;

	int size = b->size - from;
	BigInt * b1 = (BigInt *) calloc (sizeof (BigInt), 1);
	b1->digits = (unsigned *) calloc (sizeof (unsigned), size);
	memcpy (b1->digits, b->digits+from, sizeof (unsigned) * size);
	b1->sign = b->sign;
	b1->size = size;
	return b1;
}


BigInt * addHelper (BigInt * b1, BigInt * b2) {
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


BigInt * BigInt_trim (BigInt * b) {
	if (!b)
		return NULL;

	if (b->size == 1)
		return b;

	int msd = 0;
	for (int i = 0; i < b->size; i++) {
		if (b->digits[i])
			break;
		msd++;
	}
	if (msd) {
		BigInt * b1 = BigInt_copyPart (b, msd);
		BigInt_delete (b);
		b = b1;		
	}
	return b;
}


int BigInt_absCompare (BigInt * b1, BigInt * b2) {
	int cmp = 0;
	if (b1->size > b2->size) cmp = 1;
	else if (b1->size < b2->size) cmp = -1;
	else {
		for (int i = 0; i < b1->size; i++) {
			if (b1->digits[i] > b2->digits[i]) {
				cmp = 1;
				break;
			}
			else if (b1->digits[i] < b2->digits[i]) {
				cmp = -1;
				break;
			}
		}
	}
	return cmp;
}


int BigInt_compare (BigInt * b1, BigInt * b2) {
	int cmp = BigInt_absCompare (b1, b2);
	if (cmp == 1 && b1->sign) cmp *= -1;
	else if (cmp == -1 && b2->sign) cmp *= -1;
	return cmp;
}


BigInt * subtractHelper (BigInt * b1, BigInt * b2) {
	int size = b1->size;
	BigInt * b3 = (BigInt *) calloc (sizeof (BigInt), 1);
	b3->digits = (unsigned *) calloc (sizeof (unsigned), size);
	b3->size = size;
	int carry = 0, j, a, b;
	for (int i = 0; i < b2->size; i++) {
		int k = b2->size-1-i; j = b1->size-1-i;
		a = b1->digits[j]; b = b2->digits[k] + carry;
		if (a < b) {
			a += 10;
			carry = 1;
		}
		else
			carry = 0;
		a -= b;
		b3->digits[j] = a;
	}
	j--;
	if (carry) {
		while (j >= 0) {
			a = b1->digits[j]; b = carry;
			if (a < b) {
				a += 10;
				carry = 1;
			}
			else
				carry = 0;
			a -= b;
			b3->digits[j--] = a;
		}
	}
	return b3;
}


BigInt * BigInt_add (BigInt * b1, BigInt * b2) {	
	if (!b1 || !b2) return NULL;

	if (b1->size >= b2->size)
		return addHelper (b1, b2);
	else
		return addHelper (b2, b1);
}


BigInt * BigInt_subtract (BigInt * b1, BigInt * b2) {
	if (!b1 || !b2) return NULL;

	int cmp = BigInt_absCompare (b1, b2);
	BigInt * b3 = NULL;
	if (!cmp && b1->sign == b2->sign)
		b3 = BigInt_create (0L);
	else if (!b1->sign && b2->sign)
		b3 = BigInt_add (b1, b2);
	else if (b1->sign && !b2->sign) {
		b3 = BigInt_add (b2, b1);
		b3->sign = 1;
	}
	else if (b1->sign && b2->sign) {
		b3 = cmp == -1 ? subtractHelper (b2, b1) : subtractHelper (b1, b2);
		b3->sign = cmp == -1 ? 0 : 1;
	}
	else {
		b3 = cmp == -1 ? subtractHelper (b2, b1) : subtractHelper (b1, b2);
		b3->sign = cmp == -1 ? 1 : 0;
	}
	return BigInt_trim (b3);
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