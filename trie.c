#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_basic_trie () {
	// Trie * root = create_Trie_Root ();
	
	// print_Trie (root);
}

void test_append_char () {
	char * word = (char *) malloc (sizeof (char) * 5);
	strcpy (word, "fill");
	word[4] = 0;
	char * vowels = "aeiou";
	for (int i = 0; i < 5; i++) {
		word = append_char (word, vowels[i]);
		printf ("%s\n", word);
	}
	free (word);
}

void run_tests() {
	test_append_char ();
	// test_basic_trie ();
}

int main() {
	run_tests();

	return 0;
}
