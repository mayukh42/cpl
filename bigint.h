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

/** Binary functions 
 */
typedef BigInt * (* bigInt_BinaryFn) (const BigInt * larger, const BigInt * smaller);
typedef int (* bigInt_CmpFn) (const BigInt * larger, const BigInt * smaller);

BigInt * BigInt_create (long n) {
	BigInt * bi = (BigInt *) calloc (sizeof (BigInt), 1);
	if (n < 0) {
		bi->sign = 1;
		n = -n;
	}
	bi->digits = numToDigits (n);
	bi->size = !n ? 1 : (int) (1.0 + log10 (n * 1.0));
	return bi;
}


BigInt * b_empty (int n) {
	BigInt * b = (BigInt *) calloc (sizeof (BigInt), 1);
	b->digits = (unsigned *) calloc (sizeof (unsigned), n);
	b->size = n;
	return b;
}


void BigInt_delete (BigInt * b) {
	if (b) {
		free (b->digits);
		free (b);
	}
}


void BigInt_print (const BigInt * b) {
	if (b) {
		printf ("%s", b->sign ? "-" : " ");
		for (int i = 0; i < b->size; i++)
			printf ("%u", b->digits[i]);
	}
}

// for debugging
void print_empty (const BigInt * b) {
	if (!b)
		return;
	printf ("size: %d, %s", b->size, b->sign ? "-" : " ");
	outArrInt (b->digits, b->size);
}


/** b_copyFrom ()
 * copies digits from a given index onto a new BigInt
 */
BigInt * b_copyFrom (const BigInt * b, int from) {
	if (!b || from >= b->size)
		return NULL;

	int size = b->size - from;
	BigInt * bi = b_empty (size);
	memcpy (bi->digits, b->digits+from, sizeof (unsigned) * size);
	bi->sign = b->sign;
	bi->size = size;
	return bi;
}

/** b_copyRange ()
 * copies the digits of given BigInt between from (inclusive) and to (exclusive)
 */
BigInt * b_copyRange (const BigInt * b, int from, int to) {
	if (!b || from >= to || from >= b->size || to > b->size || from < 0 || to < 0)
		return NULL;
	int size = to-from;
	BigInt * e = b_empty (size);
	e->size = size;
	memcpy (e->digits, b->digits+from, sizeof (unsigned) * size);
	e->sign = b->sign;
	return e;
}


/** BigInt_copy ()
 * copies the given BigInt into a new BigInt
 */
BigInt * BigInt_copy (const BigInt * b) {
	if (!b)
		return NULL;
	return b_copyFrom (b, 0);
}


BigInt * b_trim (BigInt * b) {
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
	if (msd && msd != b->size) {
		BigInt * bi = b_copyFrom (b, msd);
		BigInt_delete (b);
		b = bi;		
	}
	else if (msd == b->size) {
		BigInt_delete (b);
		b = BigInt_create (0L);
	}
	return b;
}


BigInt * b_createFromDigits (unsigned * digits, int n) {
	BigInt * b = (BigInt *) calloc (sizeof (BigInt), 1);
	b->digits = (unsigned *) calloc (sizeof (unsigned), n);
	memcpy (b->digits, digits, n * sizeof (unsigned));
	b->size = n;
	return b_trim (b);
}


int BigInt_absCompare (const BigInt * larger, const BigInt * smaller) {
	int cmp = 0;
	if (larger->size > smaller->size) cmp = 1;
	else if (larger->size < smaller->size) cmp = -1;
	else {
		for (int i = 0; i < larger->size; i++) {
			if (larger->digits[i] > smaller->digits[i]) {
				cmp = 1;
				break;
			}
			else if (larger->digits[i] < smaller->digits[i]) {
				cmp = -1;
				break;
			}
		}
	}
	return cmp;
}


int b_compareDigits (const unsigned * lrg, const unsigned * sml, int lo_lrg, int lo_sml, int size) {
	int cmp = 0;
	for (int i = 0; i < size; i++) {
		if (lrg[lo_lrg+i] > sml[lo_sml+i]) {
			cmp = 1;
			break;
		}
		else if (lrg[lo_lrg+i] < sml[lo_sml+i]) {
			cmp = -1;
			break;
		}
	}
	return cmp;
}


int b_findMsb (const unsigned * xs, int size) {
	int i = 0, idx = -1; 
	while (i < size) {
		if (xs[i]) {
			idx = i;
			break;
		}
		i++;
	}
	return idx;
} 

// zs = xs + ys 
// assume |zs| is at least |xs| + 1
void b_addDigits (const unsigned * xs, const unsigned * ys, unsigned * zs, int x_size, int y_size, int size) {
	int i = 0, carry = 0;
	for (; i < y_size; i++) {
		unsigned z = xs[x_size-i-1] + ys[y_size-i-1] + carry;
		if (z > 9) {
			carry = 1;
			z -= 10;
		}
		else
			carry = 0;
		zs[size-i-1] = z;
	}
	for (; i < x_size; i++) {
		unsigned z = xs[x_size-i-1] + carry;
		if (z > 9) {
			carry = 1;
			z -= 10;
		}
		else
			carry = 0;
		zs[size-i-1] = z;
	}
	if (carry)
		zs[size-i-1] = carry;
}


unsigned b_multiplierRange (const unsigned * lrg, const unsigned * sml, int lrg_size, int sml_size) {
	int cmp = b_compareDigits (lrg, sml, 0, 0, sml_size);
	if (!cmp)
		return 1u;

	unsigned p = 0;
	int buf_size = lrg_size+1;
	unsigned * buf = (unsigned *) calloc (sizeof (unsigned), buf_size);	
	unsigned * acc = (unsigned *) calloc (sizeof (unsigned), buf_size);
	while (p < 10) {
		printf ("p = %u\n", p);
		outArrInt (acc, buf_size); outArrInt (buf, buf_size);
		b_addDigits (buf, sml, acc, buf_size, sml_size, buf_size);
		// outArrInt (acc, buf_size); outArrInt (buf, buf_size);
		p++;
		cmp = b_compareDigits (lrg, acc, 0, 0, lrg_size);
		if (cmp < 0)
			break;
		memcpy (buf, acc, sizeof (unsigned) * (buf_size));
		// outArrInt (acc, buf_size); outArrInt (buf, buf_size);
	}

	return p;
}


int BigInt_compare (const BigInt * larger, const BigInt * smaller) {
	int cmp = BigInt_absCompare (larger, smaller);
	if (cmp == 1 && larger->sign) cmp *= -1;
	else if (cmp == -1 && smaller->sign) cmp *= -1;
	return cmp;
}


BigInt * b_adder (const BigInt * larger, const BigInt * smaller) {
	int size = larger->size;
	BigInt * b3 = b_empty (size);
	int carry = 0, j, sum = 0;
	for (int i = 0; i < smaller->size; i++) {
		int k = smaller->size-1-i; j = larger->size-1-i;
		sum = carry + larger->digits[j] + smaller->digits[k];
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
		sum = carry + larger->digits[j];
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


BigInt * b_subtracter (const BigInt * larger, const BigInt * smaller) {
	int size = larger->size;
	BigInt * b3 = b_empty (size);
	int carry = 0, j, a, b;
	for (int i = 0; i < smaller->size; i++) {
		int k = smaller->size-1-i; j = larger->size-1-i;
		a = larger->digits[j]; b = smaller->digits[k] + carry;
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
	while (j >= 0) {
		a = larger->digits[j]; b = carry;
		if (a < b) {
			a += 10;
			carry = 1;
		}
		else
			carry = 0;
		a -= b;
		b3->digits[j--] = a;
	}
	return b3;
}


void b_subtractDigits (unsigned * lrg, unsigned * sml, unsigned * buf, int lrg_size, int sml_size) {
	int carry = 0, j, a, b;
	for (int i = 0; i < sml_size; i++) {
		int k = sml_size-1-i; j = lrg_size-1-i;
		a = lrg[j]; b = sml[k] + carry;
		if (a < b) {
			a += 10;
			carry = 1;
		}
		else
			carry = 0;
		a -= b;
		buf[j] = a;
	}
	j--;
	while (j >= 0) {
		a = lrg[j]; b = carry;
		if (a < b) {
			a += 10;
			carry = 1;
		}
		else
			carry = 0;
		a -= b;
		buf[j--] = a;
	}
}


BigInt * BigInt_add (const BigInt * larger, const BigInt * smaller) {	
	if (!larger || !smaller) return NULL;

	int cmp = BigInt_absCompare (larger, smaller);
	BigInt * b3 = NULL;
	if (!cmp && larger->sign != smaller->sign)
		b3 = BigInt_create (0L);
	else if (!larger->sign && smaller->sign) 
		b3 = cmp > -1 ? b_subtracter (larger, smaller) : b_subtracter (smaller, larger);
	else if (larger->sign && !smaller->sign) {
		b3 = cmp > -1 ? b_subtracter (larger, smaller) : b_subtracter (smaller, larger);
		b3->sign = 1;
	}
	else if (larger->sign && smaller->sign) {
		b3 = cmp > -1 ? b_adder (larger, smaller) : b_adder (smaller, larger);
		b3->sign = 1;
	}
	else 
		b3 = cmp > -1 ? b_adder (larger, smaller) : b_adder (smaller, larger);
	return b_trim (b3);
}


BigInt * BigInt_subtract (const BigInt * larger, const BigInt * smaller) {
	if (!larger || !smaller) return NULL;

	int cmp = BigInt_absCompare (larger, smaller);
	BigInt * b3 = NULL;
	if (!cmp && larger->sign == smaller->sign)
		b3 = BigInt_create (0L);
	else if (!larger->sign && smaller->sign) 
		b3 = cmp > -1 ? b_adder (larger, smaller) : b_adder (smaller, larger);
	else if (larger->sign && !smaller->sign) {
		b3 = cmp > -1 ? b_adder (larger, smaller) : b_adder (smaller, larger);
		b3->sign = 1;
	}
	else if (larger->sign && smaller->sign) {
		b3 = cmp > -1 ? b_subtracter (larger, smaller) : b_subtracter (smaller, larger);
		b3->sign = 1;
	}
	else 
		b3 = cmp > -1 ? b_subtracter (larger, smaller) : b_subtracter (smaller, larger);
	return b_trim (b3);
}


BigInt * b_multiplyByDigit (const BigInt * b, int n) {
	n = n % 10;
	if (!b) return NULL;
	if (!n) return BigInt_create (0L);
	if (n == 1) return BigInt_copy (b);

	int i = 0, carry = 0, size = b->size+1;
	BigInt * bi = b_empty (size);
	if (n < 0) {
		bi->sign = 1;	
		n *= -1;
	}
	for (i = 0; i < size-1; i++) {
		int p = b->digits[size-2-i] * n + carry;
		if (p > 9) {
			carry = p / 10;
			p %= 10;
		}
		else
			carry = 0;
		bi->digits[size-1-i] = p;
	}
	if (carry) {
		if (i < 0)
			bi->digits[0] = carry;
		else
			bi->digits[size-1-i] = carry;
	}
	bi = b_trim (bi);
	return bi;
}


BigInt * b_leftShift (const BigInt * b, int n) {
	if (!b)
		return NULL;
	int size = b->size+n;
	BigInt * p = b_empty (size);
	memcpy (p->digits, b->digits, sizeof (unsigned) * b->size);
	return p;
}


BigInt * b_multiplyByNumber (const BigInt * b, long n) {
	BigInt * sum = BigInt_create (0L);
	int sign = n < 0;
	int pow10 = 0;
	while (n > 0) {
		int r = n % 10;
		BigInt * prod = b_multiplyByDigit (b, r);
		BigInt * prod10 = b_leftShift (prod, pow10);
		BigInt_delete (prod);
		BigInt * row = BigInt_add (sum, prod10); 
		BigInt_delete (sum); BigInt_delete (prod10);
		sum = row;		
		n /= 10;
		pow10++;
	}
	sum->sign = sign;
	return sum;
}


BigInt * b_productHelperNaive (const BigInt * larger, const BigInt * smaller) {
	BigInt * sum = BigInt_create (0L);
	int pow10 = 0;
	int size = smaller->size;
	for (int i = 0; i < size; i++) {
		int r = smaller->digits[size-1-i];
		BigInt * prod = b_multiplyByDigit (larger, r);
		BigInt * prod10 = b_leftShift (prod, pow10);
		BigInt_delete (prod);
		BigInt * row = BigInt_add (sum, prod10); 
		BigInt_delete (sum); BigInt_delete (prod10);
		sum = row;	
		pow10++;	
	}
	return sum;
}


BigInt * BigInt_product (const BigInt * larger, const BigInt * smaller) {
	int cmp = BigInt_absCompare (larger, smaller);
	int sign = larger->sign != smaller->sign;
	BigInt * p = NULL;
	if (cmp == -1)
		p = b_productHelperNaive (smaller, larger);
	else
		p = b_productHelperNaive (larger, smaller);
	p->sign = sign;
	return p;
}


void b_leftShiftDigits (unsigned * digits, int size, int n) {
	if (n >= size)
		return;

	int i = n;
	for (; i < size; i++)
		digits[i-n] = digits[i];
	for (i = size-n; i < size; i++)
		digits[i] = 0;
}


int b_toInt3 (BigInt * b) {
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