#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/** author: mayukh
 * github.com/mayukh42
 */

/* Dynamic Programming Problems
 */

/* Helper functions
 * TODO: Move to array utils
 */
int min (int i, int j) {
	return i <= j ? i : j;
}

int max (int i, int j) {
	return i > j ? i : j;
}

int array_min (int * xs, int length) {
	int a = xs[0];
	for (int i = 0; i < length; i++) {
		if (xs[i] < a)
			a = xs[i];
	}
	return a;
}


/* minCoins()
 * returns the minimum number of coins of given dimensions to reach the sum
 */
int minCoins(int n, int * coins, int numCoins) {
	int * ms = calloc(sizeof(int), n+1);
	int * mins = calloc(sizeof(int), numCoins);
	for (int i = 0; i <= n; i++) 
		ms[i] = i ? -1 : 0;

	for (int i = 1; i <= n; i++) {		
		for (int j = 0; j < numCoins; j++)
			mins[j] = INT_MAX;

		for (int j = 0; j < numCoins; j++) {
			int target = i - coins[j];
			if (target < 0)
				break;
			mins[j] = ms[target] + 1;
		}
		ms[i] = array_min(mins, numCoins);
	}

	int m = ms[n];
	free(mins);
	free(ms);
	return m;
}


/* longestNonDecSeq()
 * returns the length of the longest sequence of non-decreasing numbers
 * also includes alternate solution w/o using extra array (less intuitive)
 */
int longestNonDecSeq(int * xs, int size) {
	if (!xs || size <= 0)
		return -1;

	int * sol = calloc(sizeof(int), size);
	for (int i = 0; i < size; i++)
		sol[i] = 1;

	int longest = sol[0];
	for (int i = 1; i < size; i++) {
		if (xs[i] >= xs[i-1])
			sol[i] = max(sol[i-1] + 1, sol[i]);
		longest = max(longest, sol[i]);
	}

	// int prev = 1, longest = prev;
	// for (int i = 1; i < size; i++) {
	// 	int curr = 1;
	// 	if (xs[i] >= xs[i-1])
	// 		curr = prev + 1;
	// 	longest = max(longest, curr);
	// 	prev = curr;
	// }

	free(sol);
	return longest;
}

// all tests
void testLongestNonDecSeq() {
	int xs[] = {5,3,4,8,6,7,8,8,9,4,3,1,2,3,4};
	int size = 15;
	printf("Length of longest non-decreasing sequence = %d\n", longestNonDecSeq(xs, size));
}

void testMinCoins() {
	int sum = 100;
	int numCoins = 3;
	int coins[] = {1,3,5};
	for (int i = 0; i <= sum; i++) {
		int coinsRequired = minCoins(i, coins, numCoins);
		printf("Minimum number of coins to reach %d = %d\n", i, coinsRequired);
	}
}

void runTests() {
	// testMinCoins();
	testLongestNonDecSeq();
}

int main() {
	runTests();

	return 0;
}
