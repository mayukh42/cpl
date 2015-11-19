#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
 
/** author: mayukh
 * github.com/mayukh42
 */
 
void test_basic_trie () {
    Trie * root = create_Trie_Root ();
    char * tokens = "aeiou";
    for (unsigned i = 0; i < strlen (tokens); i++)
        insert_char (root, tokens[i], i == 0 || i == 2 ? 1 : 0);
    print_Trie (root); 
    delete_Trie (root);
}
 
void test_append_char () {    
    char * vowels = "aeiou", * word_heap = NULL, * new_word = NULL;
    for (int i = 0; i < 5; i++) {
        new_word = append_char (word_heap, vowels[i]);
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
 
void run_tests() {
    // test_append_char ();
    test_basic_trie (); 
}
 
int main() {
    run_tests();
 
    return 0;
}