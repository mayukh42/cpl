#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define MAXSIZE 32
#define MAXSYM 256

typedef enum Bool {
	false,
	true
} Bool;

char * remove_at (char * cs, unsigned idx) {
	unsigned len = strlen (cs);
	if (idx >= len)
		return cs;

	char * ds = (char *) malloc (sizeof (char) * len);
	for (unsigned i = 0; i < len - 1; i++) {
		if (i >= idx) 
			ds[i] = cs[i+1];
		else
			ds[i] = cs[i];
	}
	ds[len - 1] = '\0';
	return ds;
}

void test_remove_at () {
	char cs[] = "germany";
	unsigned i = 6;
	char * ds = remove_at (cs, i);
	printf ("%s, after removal at %u = %s\n", cs, i, ds);
	free (ds);
}

/** is_equal ()
 * returns true iff 2 strings are equal
 */
Bool is_equal (char * first, char * second) {
	if (first[0] == '\0' && second[0] == '\0')
		return true;
	else 
		return (first[0] == second[0]) &&
			is_equal (first + 1, second + 1);
}

/** is_equal_upto ()
 * returns true if same chars up to the given index
 */
Bool is_equal_upto (char * first, char * second, int n) {
	if (n == 0)
		return first[0] == second[0];
	else 
		return (first[0] == second[0]) &&
			is_equal_upto (first + 1, second + 1, n - 1);
}

void print_upto (char * str, int idx) {
	for (int i = 0; i <= idx; i++)
		printf ("%c", str[i]);
	printf ("\n");
}

void test_basic_utilities () {
	char cs[] = "hellgate";
	char ds[] = "hello";
	Bool eq = is_equal (cs, ds);
	int idx = 3;
	Bool eq_upto = is_equal_upto (cs, ds, idx);

	printf ("the strings are %sequal\n", eq ? "" : "not ");
	printf ("the strings are %sequal upto index %d\n", eq_upto ? "" : "not ", idx);
	print_upto (cs, 3);
}

/** permute ()
 * print all permutations of a given string
 */
void permute (char * cs, char * buf, int last) {
	if (strlen (cs) == 0) {
		buf[last] = '\0';
		printf ("%s\n", buf);
	} else {
		for (unsigned i = 0; i < strlen (cs); i++) {
			buf[last] = cs[i];
			char * rest = remove_at (cs, i);
			permute (rest, buf, last + 1);
			free (rest);
		}
	}
}

/** subsets ()
 * print all subsets of the given string, including the empty string
 */
void subsets (char * cs, char * buf, int last) {
	if (strlen (cs) == 0) {
		buf[last] = '\0';
		printf ("%s\n", buf);
	} else {
		char c = cs[0];
		char * rest = remove_at (cs, 0);
		subsets (rest, buf, last);
		buf[last] = c;
		subsets (rest, buf, last + 1);
		free (rest);
	}
}

/** sequences ()
 * print all sequences of length k composed of given alphabet
 * includes repetitions
 * assumes alphabet is a collection of unique chars
 */
void sequences (char * cs, char * buf, unsigned k, unsigned j) {
	if (j == k) {
		buf[k] = '\0';
		printf ("%s\n", buf);
	} else {
		for (unsigned i = 0; i < strlen (cs); i++) {
			buf[j] = cs[i];
			sequences (cs, buf, k, j + 1);
		}
	}
}

void test_combinatorics () {
	char * buf = (char *) malloc (sizeof (char) * MAXSIZE);
	char cs[] = "abc";

	printf ("\npermutations of %s:\n", cs);
	permute (cs, buf, 0);
	
	printf ("\nsubsets of %s:\n", cs);
	subsets (cs, buf, 0);

	unsigned len = 2;
	printf ("\nsequences of alphabet %s, length = %d:\n", cs, len);
	sequences (cs, buf, len, 0);

	free (buf);
}


/** String matching algorithms
 */

/** naive_matcher ()
 * O(n-m+1 . m)
 */
void naive_matcher (char * text, char * pat) {
	unsigned t = strlen (text), p = strlen (pat);
	if (p > t)
		return;

	for (unsigned i = 0; i < t-p+1; i++) {
		if (is_equal_upto (pat, text + i, p - 1))
			printf ("strings match at shift %d\n", i);
	}
}

void test_naive () {
	char cs[] = "2359023141526739921";
	char ds[] = "59023141526";	
	naive_matcher (cs, ds);
}

/** rabin_karp ()
 * Rabin-Karp algorithm for string matching
 * O(n-m+1 . m) w/ better avg performance

 * Power of 2 used = 65536 (2^16)
 * Prime = 2147483647 (2^31 - 1); @TODO: does not work always
 * Alphabet = 8 bit ASCII; base = 256
 */
void rabin_karp (char * text, char * pat, int radix, int q) {
	int tlen = strlen (text), plen = strlen (pat);
	long h = ((long) pow (radix * 1.0, (plen - 1) * 1.0)) % q;
	long m = 0, ts = 0;

	// preprocessing
	for (int i = 0; i < plen; i++) {
		m = (radix * m + pat[i]) % q;
		ts = (radix * ts + text[i]) % q;
	}

	// matching
	printf ("looking for a match of \"%s\":\n", pat);
	for (int s = 0; s < tlen - plen + 1; s++) {
		if (m == ts) {
			if (is_equal_upto (pat, text + s, plen - 1))
				printf ("strings match at shift %d\n", s);
		}
		if (s < tlen - plen)
			ts = (radix * (ts - text[s] * h) + text[s + plen]) % q;
	}
}

void test_rabin_karp () {
	int base = 256, q = 65536;

	char cs[] = "naive string matcher algorithm for strings";
	char ds[] = "string";
	rabin_karp (cs, ds, base, q);

	char es[] = "2359023141526739921";
	char fs[] = "90231415267";	
	rabin_karp (es, fs, base, q);
}

void print_int_array (int * xs, unsigned n) {
	printf ("[");
	for (unsigned i = 0; i < n; i++)
		printf ("%d ", xs[i]);
	printf ("]\n");
}

/** boyer_moore ()
 * Boyer-Moore string matcher algorithm
 * matches all occurrences
 * O (m/n) avg
 */
void boyer_moore (char * text, char * pat) {
	unsigned n = strlen (text), m = strlen (pat);
	if (n < m || n == 0 || m == 0)
		return;

	int * last_idx = (int *) malloc (sizeof (int) * MAXSYM);
	for (unsigned i = 0; i < MAXSYM; i++)
		last_idx[i] = -1;
	
	for (unsigned i = 0; i < m; i++)
		last_idx[(int) pat[i]] = i;		// cast to avoid -Wchar-subscripts

	unsigned i = 0;
	while (i < n - m + 1) {
		int j = m - 1;
		while (j >= 0 && pat[j] == text[i + j])
			j--;

		if (j == -1) {
			printf ("shift occurs at %u for '%s'\n", i, pat);
			i++;
		} else {
			if (last_idx[(int) text[i+j]] != -1)
				i += j - last_idx[(int) text[i+j]];
			else
				i += m;
		}		
	}

	free (last_idx);
}

void test_boyer_moore () {
	char cs[] = "findinahaystackneedleinahaystackneedlefindallneedles";
	char ds[] = "needle";
	boyer_moore (cs, ds);

	char es[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";		// worst case for Boyer Moore
	char fs[] = "aaaaaaaaa";
	boyer_moore (es, fs);
}

void test_matchers () {
	// test_naive ();
	// test_rabin_karp ();
	test_boyer_moore ();
}

void run_tests () {
	// test_remove_at ();
	// test_basic_utilities ();
	test_combinatorics ();
	// test_matchers ();
}

int main () {
	run_tests ();

	return 0;
}
