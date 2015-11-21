#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
 
/** author: mayukh
 * github.com/mayukh42
 */

void testBasicTrie () {
    Trie * root = createTrieRoot ();
    char * tokens = "aeiou";
    for (unsigned i = 0; i < strlen (tokens); i++)
        insertChar (root, tokens[i], i == 0 || i == 2 ? 1 : 0);

    printTrie (root);
    deleteTrie (root);
}

void testInsertWords () {
    Trie * root = createTrieRoot ();
    char * words[] = {"he", "helios", "helium", "hell", "help", "hello"};
    for (int i = 0; i < 6; i++)
        insertWord (root, *(words+i));
    
    printTrie (root);
    deleteTrie (root);
}
 
void testAppendChar () {    
    char * vowels = "aeiou", * word_heap = NULL, * new_word = NULL;
    for (int i = 0; i < 5; i++) {
        new_word = appendChar (word_heap, vowels[i]);
        printf ("%s, %s\n", word_heap, new_word);
        free (word_heap);
        word_heap = new_word;
        new_word = NULL;
    }
    if (word_heap)
    	free (word_heap);
    if (new_word) 
    	free (new_word);
}
 
void runTests () {
    // testAppendChar ();
    // testBasicTrie ();
    testInsertWords ();
}
 
int main() {
    runTests ();
 
    return 0;
}
