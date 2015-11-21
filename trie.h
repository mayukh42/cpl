#ifndef __TRIE_H
#define __TRIE_H

#include "string_utils.h"
#define ALPHABETS 26
#define MAX_WORD_LENGTH 32
 
/** the Trie data structure
 * simplified: designed for only lowercase letters
 * storage is biased towards common prefix: 
 * the more common prefixes exist in the inserted words, more OPT is space
 * ref. suggestions () in trie.c for practical usage example
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
Trie * insertWord (Trie * root, const char * cs) {
	if (!root || !cs)
		return root;

	int length = strlen (cs);
	Trie * node = root;
	for (int i = 0; i < length; i++)
		node = insertChar (node, *(cs+i), i == length-1 ? 1 : 0);
	return node;
}

/** findPrefixEnd ()
 * find the trie node holding last char of the prefix
 */
Trie * findPrefixEnd (Trie * root, const char * cs) {
	if (!cs || !root)
		return root;

	int length = strlen (cs);
	Trie * node = root;
	for (int i = 0; i < length; i++) {
		Trie * child = getChild (node, *(cs+i));
		if (child)
			node = child;
		else
			break;
	}
	return node;
}

/** printTrieNode ()
 * print the word and endpt flag contained in the node
 */
void printTrieNode (Trie * node) {
	if (node)
		printf ("%s %s\n", node->word ? node->word : "", node->endpt ? "." : "");  
}

/** printTrieRec ()
 * recursive print function
 */
void printTrieRec (Trie * node, unsigned level) {
    if (!node)
        return;
 
 	for (unsigned i = 0; i < level; i++)
    	printf ("    ");
    printTrieNode (node);
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

/** buildTrieFromFile ()
 * build a trie from dictionary of words in a text file
 * only lowercase characters are considered
 */ 
unsigned buildTrieFromFile (const char * text_file, Trie * trie) {
	FILE * text_f = fopen (text_file, "r");
    char * line = (char *) malloc (sizeof (char) * MAX_WORD_LENGTH);
    unsigned num_words = 0;
    while (fgets (line, MAX_WORD_LENGTH, text_f)) {
        for (unsigned i = 0; i < strlen (line); i++)
            if (line[i] == '\n')
                line[i] = 0;
        insertWord (trie, line);
        num_words++;
    }
    fclose (text_f);
    free (line);
    return num_words;
}
 
#endif
