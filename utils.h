#ifndef __UTILS_H
#define __UTILS_H

#include <string.h>
#include <math.h>
#include "globals.h"

#define SWAP(T, a, b) {T tmp = a; a = b; b = tmp; }

typedef enum Type {
	_CHAR,
	_INT,
	_FLOAT,
	_DOUBLE,
	_LONG,
	_STR
} Type;

typedef void (* outArr) (void * arr, int count);

void outInt (int * x) { if (x) printf ("%d ", * x); }
void outChar (char * x) { if (x) printf ("%c ", * x); }
void outFloat (float * x) { if (x) printf ("%.2f ", * x); }
void outUnsigned (unsigned * x) { if (x) printf ("%u ", * x); }
void outDouble (double * x) { if (x) printf ("%.2f ", * x); }
void outLong (long * x) { if (x) printf ("%ld ", * x); }
void outStr (char ** x) { if (x && (* x)) printf ("%s ", * x); }

void outFn (void * Object, Type t) {
	switch (t) {
		case _CHAR:
			outChar ((char *) Object);
			break;
		case _INT:
			outInt ((int *) Object);
			break;
		case _LONG:
			outLong ((long *) Object);
			break;
		case _FLOAT:
			outFloat ((float *) Object);
			break;
		case _DOUBLE:
			outDouble ((double *) Object);
			break;
		case _STR:
			outStr ((char **) Object);
			break;
	}
}

/** swap is defined only in context of type
 * it does not make sense to swap 2 ptrs of different types
 * hence swap should be a client function, like comparator
 * for a macro version, see SWAP
 * for generic version, see swap ()
 */
void swapInt (int * p1, int * p2) {
	if (* p1 != * p2) {
		int tmp = * p1;		// the delcaration is why we need type
		* p1 = * p2;
		* p2 = tmp;
		num_swaps++;
	}
}


/** swap ()
 * generic swap hack
 */
void swap (void * p1, void * p2, int size) {
	void * tmp = calloc (sizeof (char), size);
	memcpy (tmp, p1, size);
	memcpy (p1, p2, size);
	memcpy (p2, tmp, size);
	free (tmp);
}


/** numToDigits () 
 * convert a number to digit array
 * digits must be unsigned, else makes no sense
 */
unsigned * numToDigits (long n) {
	int size = !n ? 1 : (int) (1.0 + log10 (n * 1.0));
	unsigned * xs = (unsigned *) calloc (sizeof (unsigned), size);
	int i = 0;
	while (n > 0 && i < size) {
		int r = n % 10;
		// printf ("size = %d, r = %d\n", size, r);
		xs[size-1-i] = r;
		n = (n - r) / 10;
		i++;
	}
	return xs;
}


/** General purpose Object
 * The field 'size' is not actually used atm; kept for future
 */
typedef struct Object {
	Type type;
	void * content;
	size_t size;
} Object;

Object * createObject (Type t, void * item) {
	Object * e = (Object *) calloc (sizeof (Object), 1);
	e->type = t;
	e->content = item;
	e->size = sizeof (Object);
	return e;
}

void deleteObject (Object * e) {
	free (e);
}

void outObject (Object * e) {
	if (e) {
		outFn (e->content, e->type);
		printf (" ");
	}
}


#endif