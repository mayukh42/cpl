#ifndef __TRIE_H
#define __TRIE_H
 
#include <string.h>
#define ALPHABETS 26
 

/** string utilities
 * can be refactored into separate header
 */

/** createString ()
 * utility to create C style strings
 */
char * createString (const char * src) {
    int length = strlen (src);
    char * dst = (char *) malloc (sizeof(char) * (length+1));
    strcpy (dst, src);
    return dst;
}

/** appendChar ()
 * if c is null character, return word
 * if word is null, create single character string (along with null termination)
 * otherwise, create a new string with c as last non-null character, followed by null character
 */
char * appendChar (char * word, char c) {
	char * new_word = NULL;
    if (word) {
    	int length = strlen (word);
	    new_word = (char *) malloc (sizeof(char) * (length+2));
	    if (length)
	    	strcpy (new_word, word);
	    new_word[length] = c;
	    new_word[length+1] = 0;
    }
    else {
    	new_word = (char *) malloc (sizeof(char) * (2));
    	new_word[0] = c;
    	new_word[1] = 0;
    }
    return new_word;
}

/** the Trie data structure
 * simplified: designed for only lowercase letters
 * storage is biased towards common prefix: 
 * the more common prefixes exist in the inserted words, more OPT is space
 */ 
struct Trie;
 
typedef struct Trie {
    char * word;
    int endpt;
    struct Trie * children[ALPHABETS];
} Trie;

/** createTrieNode ()
 * cons
 */
Trie * createTrieNode (char * word, char c, int endpt) {
    Trie * node = (Trie *) malloc (sizeof (Trie));
    node->word = appendChar (word, c);
    node->endpt = endpt;
    for (int i = 0; i < ALPHABETS; i++)
        node->children[i] = NULL;
    return node;
}

/** default cons
 * lame attempt at overloading
 */
Trie * createTrieRoot () {
	char nullc = 0;
    Trie * node = createTrieNode (&nullc, 0, 0);
    return node;
}

/** deleteTrie ()
 * recursive delete ()
 */
void deleteTrie (Trie * node) {
    if (node) {
        if (node->word)
            free (node->word);
        if (node->children) {
            for (int i = 0; i < ALPHABETS; i++) 
                deleteTrie (node->children[i]);
        }
        free (node);
    }
}

/** getChild ()
 * returns the child of trie corresponding to given char
 */
Trie * getChild (Trie * node, char c) {
    if (c < 'a' || c > 'z' || !node)
        return NULL;
 
    int index = c-'a';
    return node->children[index];
}

/** insertChar ()
 * insert a character if it does not exist in the trie children
 */ 
Trie * insertChar (Trie * node, char c, int endpt) {
    if (!node || !c)
        return NULL;
 
    Trie * child = getChild (node, c);
    if (!child) {
        child = createTrieNode (node->word, c, endpt);
        int index = c-'a';
        node->children[index] = child;
    }
    return child;
}

/** insertWord ()
 * insert a word in the trie
 * mark the last node as word-endpt
 */
Trie * insertWord (Trie * root, char * cs) {
	if (!root || !cs)
		return root;

	int length = strlen (cs);
	Trie * node = root;
	for (int i = 0; i < length; i++)
		node = insertChar (node, *(cs+i), i == length-1 ? 1 : 0);
	return node;
}

/** printTrieRec ()
 * recursive print function
 */
void printTrieRec (Trie * node, unsigned level) {
    if (!node)
        return;
 
 	for (unsigned i = 0; i < level; i++)
    	printf ("    ");
    printf ("%s %s\n", node->word ? node->word : "", node->endpt ? "." : "");    
    for (int i = 0; i < ALPHABETS; i++)
        printTrieRec (node->children[i], level+1);
}

/** printTrie ()
 * wrapper function for recursive print
 */
void printTrie (Trie * node) {
    printf ("[");
    unsigned trie_level = 0;
    printTrieRec (node, trie_level);
    printf ("]\n");
}
 
#endif
