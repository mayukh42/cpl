#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

typedef enum Bool {
	false,
	true
} Bool;

/** sqrt_nr ()
 * Square Root of a number using Newton-Raphson method
 * x1 = x0 - f(x0)/f'(x0)
 * f(x): x*x - n = 0
 */
void sqrt_nr (double n, double tolerance) {
	double x0 = n/2.0, x1;
	int iter = 0;
	while (true) {
		x1 = (x0*x0 + n)/(2.0*x0);
		iter++;
		if (abs (x0-x1) < tolerance)
			break;
		x0 = x1;
	}
	printf ("Square root of %.1f = %.2f (%d iterations).\n", n, x1, iter);
} 

/** minmax ()
 * find min, max of array in one pass: O(n)
 */
void minmax (int * xs, int n) {
	if (!xs)
		return;

	int mn = * xs, mx = * xs, i = 0;
	for (i = 0; i < n && i+1 < n; i = i+2) {
		int lower = xs[i] < xs[i+1] ? xs[i] : xs[i+1];
		int upper = xs[i] > xs[i+1] ? xs[i] : xs[i+1];
		mn = lower < mn ? lower : mn;
		mx = upper > mx ? upper : mx;
	}
	if (i < n) {
		mn = xs[i] < mn ? xs[i] : mn;
		mx = xs[i] > mx ? xs[i] : mx;
	}
	printf ("min = %d, max = %d.\n", mn, mx);
}

/** binary_search ()
 * Classical Binary Search Algorithm: O(lg n)
 */
int binary_search (int * xs, int lower, int upper, int element) {
	if (lower >= upper || !xs) 
		return -1;

	int mid = lower + (upper - lower)/2;
	if (element == xs[mid])
		return mid;
	else if (element < xs[mid])
		return binary_search (xs, lower, mid, element);
	else
		return binary_search (xs, mid + 1, upper, element);
}

/** Container for matrix_search results
 */
typedef struct Pair {
	int x;
	int y;
} Pair;

/** binary_search_2d ()
 * binary search helper function for matrix_search
 * assume ret != NULL (we can always check it)
 */
void binary_search_2d (int ** xss, int lower, int upper, int element, Pair * ret) {
	ret->x = lower;
	ret->y = upper;
	if (lower >= upper || !xss) {
		ret->x = upper - 1;
		return;
	}

	int mid = lower + (upper - lower)/2;
	if (element == xss[mid][mid]) {
		ret->x = mid;
		ret->y = mid;
	}
	else if (element < xss[mid][mid])
		binary_search_2d (xss, lower, mid, element, ret);
	else
		binary_search_2d (xss, mid + 1, upper, element, ret);
}

/** matrix_search ()
 * Sorted matrix search algorithm. O(lg n) + O(lg n)
 * Given a[i][j] < a[i][j+1] && a[i][j] < a[i+1][j]
 * For simplicity, only square matrices are considered
 * assume container for result has -1
 */
void matrix_search (int ** xss, int size, int element, Pair * result) {
	if (!xss || size <= 0)
		return;

	if (element < xss[0][0] || element > xss[size-1][size-1])
		return;

	binary_search_2d (xss, 0, size, element, result);

	if (result->x == result->y)
		return;

	int row = result->x;
	int col = binary_search (xss[row], 0, size, element);
	if (col != -1) {
		result->x = row, result->y = col;
		return;
	}
	row = result->y;
	col = binary_search (xss[row], 0, size, element);
	if (col != -1) {
		result->x = row, result->y = col;
		return;
	}
	result->x = -1;
	result->y = -1;
}

/** saddleback_search ()
 * Saddleback Search algorithm for sorted matrix: O(n)
 */
void saddleback_search (int ** xss, int size, int element, Pair * result) {
	int i = 0, j = size-1;
	while (element != xss[i][j] && j >= 0 && i < size) {
		if (element < xss[i][j])
			j -= 1;
		else
			i += 1;
	}
	result->x = i;
	result->y = j;
}

/** hamming ()
 * Hamming problem: find first n integers whose only factors are primes 2, 3, 5, other than 1
 * Axiom 1: 1 is in the sequence
 * Axiom 2: if x is in sequence, so is 2x, 3x, 5x
 */ 
unsigned * hamming (unsigned n) {
	if (n <= 0)
		return NULL;
	unsigned * seq = (unsigned *) malloc (sizeof (unsigned) * n);
	unsigned i = 0, x2 = 2, x3 = 3, x5 = 5, y2 = 0, y3 = 0, y5 = 0;
	seq[i++] = 1;
	while (i < n) {
		unsigned x = seq[i-1] + 1;
		while (true) {
			if (!(x % x2)) {
				y2 = x;
				break;
			}
			x++;
		}
		x = seq[i-1] + 1;
		while (true) {
			if (!(x % x3)) {
				y3 = x;
				break;
			}
			x++;
		}
		x = seq[i-1] + 1;
		while (true) {
			if (!(x % x5)) {
				y5 = x;
				break;
			}
			x++;
		}
		seq[i++] = y2 < y3 ? (y2 < y5 ? y2 : y5) : (y3 < y5 ? y3 : y5); 
	}
	return seq;
}

void test_hamming () {
	unsigned n = 42;
	unsigned * seq = hamming (n);
	for (unsigned i = 0; i < n; i++)
		printf ("%d ", seq[i]);
	printf ("\n");
	free (seq);
}

void test_matrix_search_algorithms () {
	int mn = 1, mx = 45, size = 5;
	int ** xss = (int **) malloc (sizeof (int *) * size);
	int elements[] = {1,3,5,7,9,10,12,14,16,18,19,21,23,25,27,28,30,32,34,36,37,39,41,43,45};
	for (int i = 0; i < size; i++) {
		xss[i] = (int *) malloc (sizeof (int) * size);
		for (int j = 0; j < size; j++)
			xss[i][j] = elements[i*size + j];
	}
	Pair * ret = (Pair *) malloc (sizeof (Pair));
	ret->x = -1, ret->y = -1;
	for (int i = mn; i <= mx; i++) {
		matrix_search (xss, size, i, ret);
		if (ret->x != -1 && ret->y != -1)
			printf ("matrix] %d: [%d,%d]\n", i, ret->x, ret->y);

		ret->x = -1, ret->y = -1;
		saddleback_search (xss, size, i, ret);
		if (ret->x != size && ret->y != -1)
			printf ("saddleback] %d: [%d,%d]\n", i, ret->x, ret->y);
	}

	for (int i = 0; i < size; i++)
		free (xss[i]);
	free (xss);
	free (ret);
}

void test_123 () {	
	// sqrt_nr (42.0, TOLERANCE);

	// int xs[] = {2,1,4,5,3};
	// minmax (xs, 5);

	int ys[] = {1,7,13,19,25};	//{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
	int elements[] = {-1,3,6,7,11,22};	//{-1,2,14,19,23,28,29,42,47,61};
	int upper = 5, found;
	for (int i = 0; i < 6; i++) {
		found = binary_search (ys, 0, upper, elements[i]);
		printf ("%d %s in the array.\n", elements[i], found > -1 ? "is" : "is not");
	}	
}

void run_tests() {
	// test_123 ();
	// test_matrix_search_algorithms ();
	test_hamming ();
}

int main() {
	run_tests();

	return 0;
}
