#ifndef __ARRAYUTILS_H
#define __ARRAYUTILS_H

#include "utils.h"

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

int ** buildTriangularMat (int size, int * elems) {
	int k = 0;
	int ** mat = (int **) calloc (sizeof (int *), size);
	for (int i = 0; i < size; i++) {
		mat[i] = (int *) calloc (sizeof (int), i+1);
		for (int j = 0; j < i+1; j++)
			mat[i][j] = elems[k++];
	}
	return mat;
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

void outMat (int ** xs, int r, int c) {
	for (int i = 0; i < r; i++)
		outArrInt (xs[i], c);
	printf ("\n");
}

void outTriangularMat (int ** xs, int size) {
	for (int i = 0; i < size; i++)
		outArrInt (xs[i], i+1);
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

#endif