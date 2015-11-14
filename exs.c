#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Some random problems
 * and examples
 */

#define MAXSIZE 31

typedef enum Bool {
	false, 
	true
} Bool;

/** 2D Matrix Utility functions
 */
int ** build_mat (int ** xs, int * elems, int r, int c) {
	xs = (int **) malloc (sizeof (int *) * r);
	for (int i = 0; i < r; i++) {
		int * cs = (int *) malloc (sizeof (int) * c);
		for (int j = i*c; j < (i+1)*c; j++)
			cs[j%c] = elems[j];
		xs[i] = cs;
	}
	return xs;
} 

void delete_mat (int ** xs, int r) {
	for (int i = 0; i < r; i++)
		free (xs[i]);
	free (xs);
}

/** 1 - spiral printing of matrix
 * ex. [1 2 3
 		4 5 6
 		7 8 9]
 * should be [1 2 3 6 9 8 7 4 5]
 * Game programming: Moving the turtle
 */
void spiral_print_mat (int ** xs, int r, int c) {
	int n = r * c;	

	int nwx = 0, nwy = 0, nex = 0, ney = c - 1,
		sex = r - 1, sey = c - 1, swx = r - 1, swy = 0;

	printf ("[");
	while (1) {
		for (int j = nwy; j <= ney; j++) {
			printf ("%d ", xs[nwx][j]);
			n--;
		}
		if (n == 0)	break;
		nwx++;
		nex++;

		for (int i = nex; i <= sex; i++) {
			printf ("%d ", xs[i][ney]);
			n--;
		}
		if (n == 0)	break;
		ney--;
		sey--;

		for (int j = sey; j >= swy; j--) {
			printf ("%d ", xs[sex][j]);
			n--;
		}
		if (n == 0)	break;
		sex--;
		swx--;	

		for (int i = swx; i >= nwx; i--) {
			printf ("%d ", xs[i][swy]);
			n--;
		}
		if (n == 0)	break;
		nwy++;
		swy++;
	}
	printf ("]\n");
}

void test_spiral_print_mat () {
	int r = 3, c = 4;
	int elems[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int ** xs = NULL;
	xs = build_mat (xs, elems, r, c);

	spiral_print_mat (xs, r, c);
	delete_mat (xs, r);	
}

/** add_ut ()
 * add elements in the upper triangular part
 * of a square matrix
 */
int add_ut (int ** xs, int r) {
	int sum = 0, dl = 0, dh = 0;
	int n = r * (r + 1) / 2;

	while (n > 0) {
		printf ("[");
		for (int i = dl; i >= 0; i--) {
			printf ("%d ", xs[i][dh - i]);
			sum += xs[i][dh - i];
			n--;
		}
		printf ("]\n");
		dl++;
		dh++;
	}
	return sum;
}

void test_add_ut () {
	int r = 3;
	int elems[] = {1,2,3,4,5,6,7,8,9};
	int ** xs = NULL; 
	xs = build_mat (xs, elems, r, r);

	printf ("sum of upper triangle is %d\n", add_ut (xs, r));
	delete_mat (xs, r);
}

void print_arr (int * xs, int size) {
	printf ("[");
	for (int i = 0; i < size; i++)
		printf ("%d, ", xs[i]);
	printf ("]\n"); 
} 

unsigned long hash_str (char * cs) {
	unsigned long h = 0;
	for (unsigned i = 0; i < strlen (cs); i++)
		h += 31 * h + cs[i];
	return h;
}

void print_str_array (char ** cs, int size) {
	printf ("[");
	for (int i = 0; i < size; i++)
		printf ("%s, ", cs[i]);
	printf ("]\n");
}

/** str_array_diff ()
 * difference between 2 arrays, the 2nd of which contain 
 * one element that is not in 1st
 */
void str_array_diff (char ** first, char ** second, int size) {
	int * xs = (int *) malloc (sizeof (int) * MAXSIZE);
	for (int i = 0; i < size; i++) {
		unsigned long h = hash_str (first[i]);
		xs[h % MAXSIZE]++;
	}
	// print_arr (xs, MAXSIZE);
	printf ("[");
	for (int i = 0; i < size + 1; i++) {
		unsigned long h = hash_str (second[i]);
		if (! xs[h % MAXSIZE])
			printf ("%s, ", second[i]);
	}
	printf ("]\n");
	free (xs);
}

void test_str_array_diff () {
	char * first[] = {"dog", "cat", "monkey"};
	char * second[] = {"dog", "cat", "rat", "monkey"};
	int size = 3;
	// print_str_array (first, size);
	// print_str_array (second, size + 1);

	str_array_diff (first, second, size);
}

/** gcd ()
 * find the gcd of 2 numbers
 */
unsigned gcd (unsigned m, unsigned n) {
	if (m > n)
		return gcd (m-n, n);
	else if (m < n)
		return gcd (m, n-m);
	else
		return m;
}

/** double2rational ()
 * convert a double number to rational fraction
 */
void double2rational (double n) {
	double whole = floor (n);
	double decimal = n - whole;
	if (decimal == 0.0)
		decimal = 1.0;
	double base = 10.0, multiplier = 1.0, tolerance = 0.0001;

	while (decimal - floor (decimal) >= tolerance) {
		decimal *= base;
		multiplier *= base;
	}	

	unsigned factor = gcd ((unsigned) decimal, (unsigned) multiplier);
	decimal /= (double) factor;
	multiplier /= (double) factor;

	printf ("rational fraction of %.8f = %ld %ld/%ld\n", 
		n, (long) whole, (long) decimal, (long) multiplier);
}

void test_gcd_double2rational () {
	int m = 6, n = 9;
	printf ("gcd of %d and %d = %d\n", m, n, gcd (m, n));

	double2rational (1234.5678);
	double2rational (0.5223);
	double2rational (1.125);
	double2rational (6.116);	// not quite the ouput we want
	double2rational (42.0);
}

/** reverse_num ()
 * reverse a positive number in a given base
 */
unsigned reverse_num (unsigned n, unsigned radix) {
	unsigned i = 0;
	while (n > 0) {
		i = i * radix + (n % radix);
		n = n / radix;
	}
	return i;
}

/** find_circles_within ()
 * finds all x, y $ x^2 + y^2 < n
 */
void find_circles_within (unsigned n) {
	unsigned x = 0, y = 0;
	printf ("  x\t  y\n");
	while (x * x + y * y < n) {
		printf ("%3u\t%3u\n", x, y);
		y++;
		while (x * x + y * y < n) {
			printf ("%3u\t%3u\n", x, y);
			y++;
		}
		y = 0;
		x++;
	}
}

/** factors ()
 * prints all factors of n
 */
void factors (unsigned n) {
	if (n == 0)
		return;

	printf ("factors of %u:\n", n);
	unsigned a = 1, b = n;
	while (a <= b) {
		if (a * b == n)
			printf ("%u, %u\n", a, b);
		a++; 
		b = n / a;
	}
}

/** inverse_round ()
 * rounds off 1/n to k decimal places
 * integer part of 10^k / n
 */
void inverse_round (unsigned n, unsigned k) {
	unsigned b = 1;
	printf (".");
	while (k > 0) {
		unsigned a = 10 * b / n;
		printf ("%u", a);
		b = (10 * b) % n;
		k--;
	}
	printf ("\n");
}

/** period ()
 * find period of the fraction part of 1/n
 */
void period (unsigned n) {
	if (n < 2)
		return;

	unsigned m = 0, b = 1;
	char * buf = (char *) malloc (sizeof (char) * (n + 1) * 2);
	unsigned * qs = (unsigned *) malloc (sizeof (unsigned) * n);
	qs[b] = 1, qs[0] = 1;
	
	while (m < n + 1) {
		unsigned q = 10 * b / n;
		unsigned r = (10 * b) % n;
		buf[m++] = q + '0';	
		if (qs[r])
			break;
		else {			
			qs[r] = true;
			b = r;
		}
	}

	buf[m] = '\0';
	printf ("1/%u = .%s'\n period of 1/%u = %u\n", n, buf, n, m);
	free (buf);
}

void test_numbers () {
	// unsigned d = 173;
	// printf ("reverse of %u = %u\n", d, reverse_num (d, 10));
	// find_circles_within (5);
	// factors (768);
	// inverse_round (7, 10);
	
	for (unsigned i = 11; i <= 37; i++)
		period (i);
}

void run_tests () {
	// test_spiral_print_mat ();
	// test_add_ut ();
	// test_str_array_diff ();
	// test_gcd_double2rational ();
	test_numbers ();
}

int main () {
	run_tests ();

	return 0;
}
