#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include "queue.h"

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

    Trie * end = findPrefixEnd (root, "hel");
    if (end)
        printTrieNode (end);

    deleteTrie (root);
}

/** suggestions ()
 * word suggestions from the trie
 * returns a list of words that are nearest to the given prefix
 * max words returned: count
 * trie traversal using BFS
 */
char ** suggestions (Trie * trie, const char * prefix, unsigned count) {
    if (!trie || !count)
        return NULL;

    char ** suggested_words = (char **) malloc (sizeof (char *) * count);
    for (unsigned i = 0; i < count; i++)
        suggested_words[i] = NULL;

    Queue * q = create_Queue ();
    Trie * end = findPrefixEnd (trie, prefix);
    if (end)
        enqueue (q, end);
    int i = 0;
    while (count && !(is_Queue_empty (q))) {
        Trie * node = (Trie *) dequeue (q);
        if (node && node->endpt) {
            suggested_words[i] = (char *) malloc (sizeof (char) * MAX_WORD_LENGTH);
            strcpy (suggested_words[i], node->word);
            i++;
            count--;
        }
        if (node) {            
            for (int j = 0; j < ALPHABETS; j++)
                enqueue (q, node->children[j]);
        }
    }
    delete_Queue (q);
    return suggested_words;
}

/** testInsertWordsFromFile ()
 * text/dictionary.txt: 109583 words, text/dictionarySmall.txt: 128 words
 * HEAP usage (valgrind): 58 MB for dictionary.txt
 */
void testInsertWordsFromFile () {
    Trie * trie = createTrieRoot ();
    char * text_file = "text/dictionarySmall.txt";
    unsigned num_words = buildTrieFromFile (text_file, trie);
    printf ("%u words inserted\n", num_words);    
    deleteTrie (trie);
}

void testSuggestions () {
    Trie * trie = createTrieRoot ();
    char * text_file = "text/dictionary.txt";
    unsigned num_words = buildTrieFromFile (text_file, trie);
    printf ("%u words inserted\n", num_words);    

    int count = 10;
    char ** suggested_words = suggestions (trie, "abbo", count);
    for (int i = 0; i < count; i++) {
        if (suggested_words[i])
            printf ("%s\n", suggested_words[i]);
    }

    for (int i = 0; i < count; i++) {
        if (suggested_words[i])
            free (suggested_words[i]);
    }
    if (suggested_words)
        free (suggested_words);

    deleteTrie (trie);
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
    // testInsertWords ();
    // testInsertWordsFromFile ();
    testSuggestions ();
}
 
int main() {
    runTests ();
 
    return 0;
}
