#ifndef __ARRAYUTILS_H
#define __ARRAYUTILS_H

typedef enum Type {
	_CHAR,
	_INT,
	_FLOAT,
	_DOUBLE,
	_LONG,
	_STRING
} Type;

typedef void (* out) (void *);

void out_int (int * x) { if (x) printf ("%d ", * x); }
void out_char (char * x) { if (x) printf ("%c ", * x); }
void out_float (float * x) { if (x) printf ("%.2f ", * x); }
void out_unsigned (unsigned * x) { if (x) printf ("%u ", * x); }
void out_double (double * x) { if (x) printf ("%.2f ", * x); }
void out_long (long * x) { if (x) printf ("%ld ", * x); }
void out_str (char ** x) { if (x && (* x)) printf ("%s ", * x); }


void print_arr (void * element, Type t) {
	switch (t) {
		case _CHAR:
			out_char ((char *) element);
			break;
		case _INT:
			out_int ((int *) element);
			break;
		case _LONG:
			out_long ((long *) element);
			break;
		case _FLOAT:
			out_float ((float *) element);
			break;
		case _DOUBLE:
			out_double ((double *) element);
			break;
		case _STRING:
			out_str ((char **) element);
			break;
	}
}




#endif