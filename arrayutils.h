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