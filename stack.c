#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/** author: mayukh
 * github.com/mayukh42
 */

void testBasicStack () {
	int xs[] = {1,2,3,4,5,6,7,8};
	int count = 8;
	Stack * s = createStack ();
	for (int i = 0; i < count; i++)
		push (s, &xs[i]);

	printStack (s, print_Item);

	for (int i = 0; i < count; i++) {
		int * x = pop (s);
		printf ("%d %s", * x, i == count-1 ? "\n" : "");
	}

	deleteStack (s);
}

void testStringStack () {
	char * strs[] = {"he", "hell", "help", "helios", "helium"};
	int count = 5;
	Stack * s = createStack ();
	for (int i = 0; i < count; i++)
		push (s, strs[i]);

	printStack (s, print_Item_Str);

	for (int i = 0; i < count; i++) {
		char * str = pop (s);		
		printf ("%s %s", str, i == count-1 ? "\n" : "");
	}

	deleteStack (s);
}

void runTests() {
	// testBasicStack ();
	testStringStack ();
}

int main() {
	runTests();

	return 0;
}
