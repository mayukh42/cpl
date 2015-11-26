#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** longestPlateau ()
 * returns the length of largest segment that has equal elements 
 * in a sorted array
 */
int longestPlateau (int * xs, int count) {
	int len = 0;
	if (!xs || !count)
		return len;

	int curr = * xs, i = 0, maxlen = 0;
	while (i < count) {
		int next = xs[i++];
		if (curr == next) 
			len++;
		else {
			curr = next;
			len = 1;
		}
		maxlen = len > maxlen ? len : maxlen;
	}
	return maxlen;
}

void testPlateau () {
	int xs[] = {1,2,2,3,3,3,4,5,5,6,6,6,6,7};
	int count = 14;
	printf ("longest plateau in array is of length %d\n", longestPlateau (xs, count));
}


void runTests() {
	testPlateau ();	
}

int main() {
	runTests();

	return 0;
}
