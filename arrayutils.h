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


/** 2D Matrix Utility functions
 */
int ** buildMat (const int * elems, int r, int c) {
	int ** xs = (int **) malloc (sizeof (int *) * r);
	for (int i = 0; i < r; i++) {
		int * cs = (int *) malloc (sizeof (int) * c);
		for (int j = i*c; j < (i+1)*c; j++)
			cs[j%c] = elems[j];
		xs[i] = cs;
	}
	return xs;
} 

int ** buildMat123 (int r, int c) {
	int ** xs = (int **) calloc (sizeof (int *), r);
	int val = 1;
	for (int i = 0; i < r; i++) {
		xs[i] = (int *) calloc (sizeof (int), c);
		for (int j = 0; j < c; j++)
			xs[i][j] = val++;
	}
	return xs;
}

int ** buildMatEmpty (int r, int c) {
	int ** xs = (int **) calloc (sizeof (int *), r);
	for (int i = 0; i < r; i++)
		xs[i] = (int *) calloc (sizeof (int), c);
	return xs;
}

void deleteMat (int ** xs, int r) {
	for (int i = 0; i < r; i++)
		free (xs[i]);
	free (xs);
}

void copyIntMat (int ** src, int ** dst, int size, int r, int c) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			dst[i][j] = src[r+i][c+j];
	}
}

void outArrInt2D (int ** xs, int r, int c) {
	for (int i = 0; i < r; i++)
		outArrInt (xs[i], c);
	printf ("\n");
}

/** rotateMat ()
 * 0(n^2) time, O(1) space
 */
void rotateMat (int ** xs, int size) {
	if (!xs || size <= 0)
		return;

	for (int i = 0; i < size>>1; i++) {
		for (int j = 0; j < size>>1; j++) {
			int tmp = xs[i][j];
			xs[i][j] = xs[size-j-1][i];
			xs[size-j-1][i] = xs[size-i-1][size-j-1];
			xs[size-i-1][size-j-1] = xs[j][size-i-1];
			xs[j][size-i-1] = tmp;
		}
	}
}

/** rotateMat90c ()
 * O(n^2) space, time
 */
int ** rotateMat90c (int ** src, int size) {
	int ** dst = buildMatEmpty (size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) 
			dst[j][size-i-1] = src[i][j];
	}
	return dst;
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