#ifndef __ARRAYUTILS_H
#define __ARRAYUTILS_H

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

void outFn (void * element, Type t) {
	switch (t) {
		case _CHAR:
			outChar ((char *) element);
			break;
		case _INT:
			outInt ((int *) element);
			break;
		case _LONG:
			outLong ((long *) element);
			break;
		case _FLOAT:
			outFloat ((float *) element);
			break;
		case _DOUBLE:
			outDouble ((double *) element);
			break;
		case _STR:
			outStr ((char **) element);
			break;
	}
}

void outArrInt (void * arr, int count) {
	int * xs = (int *) arr;
	printf ("[");
	for (int i = 0; i < count; i++) 
		outFn (xs+i, _INT);
	printf ("]\n");
}

void outArrStr (void * arr, int count) {
	char ** strs = (char **) arr;
	printf ("[");
	for (int i = 0; i < count; i++) 
		outFn (strs+i, _STR);
	printf ("]\n");
}

/** General purpose element
 * The field 'size' is not actually used atm; kept for future
 */
typedef struct Element {
	Type type;
	void * content;
	size_t size;
} Element;

Element * createElement (Type t, void * item) {
	Element * e = (Element *) calloc (sizeof (Element), 1);
	e->type = t;
	e->content = item;
	e->size = sizeof (Element);
	return e;
}

void deleteElement (Element * e) {
	free (e);
}

void outElement (Element * e) {
	if (e) {
		outFn (e->content, e->type);
		printf (" ");
	}
}


#endif