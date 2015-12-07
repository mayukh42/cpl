#ifndef __ARRAYUTILS_H
#define __ARRAYUTILS_H

#include "utils.h"

typedef int (* cmpFn) (int x, int y);

int cmpIntAsc (int x, int y) {
	return x <= y;
}

int cmpIntDsc (int x, int y) {
	return x >= y;
}

/** buildRandomIntArray ()
 * create an int array with randomized elements
 * for general testing
 */
int * buildRandomIntArray (int size, int max_val) {
	int * elems = (int *) calloc (sizeof (int), size);
	for (int i = 0; i < size; i++)
		elems[i] = rand () % max_val;
	return elems;
}

int * buildFillIntArray (int size, int val) {
	int * elems = (int *) calloc (sizeof (int), size);
	if (val) { 
		for (int i = 0; i < size; i++)
			elems[i] = val;
	}
	return elems;
}

int * build123Array (int size) {
	int * elems = (int *) calloc (sizeof (int), size);
	for (int i = 0; i < size; i++)
		elems[i] = i+1;
	return elems;
}

/** outArrInt ()
 * output an int array
 */
void outArrInt (void * arr, int count) {
	int * xs = (int *) arr;
	printf ("[");
	for (int i = 0; i < count; i++) 
		outFn (xs+i, _INT);
	printf ("]\n");
}

/** outArrStr ()
 * output a string array
 */
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


/** partitionQS ()
 * CAR Hoare's partition scheme for Quicksort 
 */
int partitionQS (int * xs, int lo, int hi) {
	if (lo >= hi)
		return lo;

	int p_idx = rand () % (hi+1-lo);
	if (xs[p_idx] != xs[lo])
		swapInt (xs+lo+p_idx, xs+lo);

	int p = xs[lo], i = lo+1, j = hi;
	while (i <= j) {
		while (i <= hi && xs[i] <= p)	// first check to bypass bad ptr errors
			i++;
		while (j >= lo && xs[j] > p) 
			j--;
		if (i < j)
			swapInt (xs+i, xs+j);
	}
	if (xs[lo] != xs[j])
		swapInt (xs+lo, xs+j);	// put partition in its place
	return j;
}


/** quicksort_rec ()
 * classic quicksort algorithm, O(n.lgn) expected case
 * qsort is already taken
 */
void quicksort_rec (int * xs, int lo, int hi) {
	if (lo >= hi)
		return;

	int p = partitionQS (xs, lo, hi);
	quicksort_rec (xs, lo, p-1);
	quicksort_rec (xs, p+1, hi);
}


/** isSorted ()
 * an OPT for quicksort
 */
int isSorted (int * xs, int size, cmpFn cf) {
	int sorted = 1;
	for (int i = 0; i < size-1; i++) {
		if (!cf (xs[i], xs[i+1])) {
			sorted = 0;
			break;
		}
	}
	return sorted;
} 


/** quicksort ()
 * quicksort API
 */
void quicksort (int * xs, int size) {
	int sorted = isSorted (xs, size, cmpIntAsc);
	num_swaps = 0;
	if (!sorted) 
		quicksort_rec (xs, 0, size-1);
}


#endif