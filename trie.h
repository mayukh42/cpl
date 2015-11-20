#ifndef __TRIE_H
#define __TRIE_H
 
#include <string.h>
#define ALPHABETS 26
 

/** string utilities
 * can be refactored into separate header
 */

/** create_String ()
 * utility to create C style strings
 */
char * create_String (const char * src) {
    int length = strlen (src);
    char * dst = (char *) malloc (sizeof(char) * (length+1));
    strcpy (dst, src);
    return dst;
}

/** append_char ()
 * if c is null character, return word
 * if word is null, create single character string (along with null termination)
 * otherwise, create a new string with c as last non-null character, followed by null character
 */
char * append_char (char * word, char c) {
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

/** create_Trie_Node ()
 * cons
 */
Trie * create_Trie_Node (char * word, char c, int endpt) {
    Trie * node = (Trie *) malloc (sizeof (Trie));
    node->word = append_char (word, c);
    node->endpt = endpt;
    for (int i = 0; i < ALPHABETS; i++)
        node->children[i] = NULL;
    return node;
}

/** default cons
 * lame attempt at overloading
 */
Trie * create_Trie_Root () {
	char nullc = 0;
    Trie * node = create_Trie_Node (&nullc, 0, 0);
    return node;
}

/** delete_Trie ()
 * recursive delete ()
 */
void delete_Trie (Trie * node) {
    if (node) {
        if (node->word)
            free (node->word);
        if (node->children) {
            for (int i = 0; i < ALPHABETS; i++) 
                delete_Trie (node->children[i]);
        }
        free (node);
    }
}

/** get_child ()
 * returns the child of trie corresponding to given char
 */
Trie * get_child (Trie * node, char c) {
    if (c < 'a' || c > 'z' || !node)
        return NULL;
 
    int index = c-'a';
    return node->children[index];
}

/** insert_char ()
 * insert a character if it does not exist in the trie children
 */ 
Trie * insert_char (Trie * node, char c, int endpt) {
    if (!node || !c)
        return NULL;
 
    Trie * child = get_child (node, c);
    if (!child) {
        child = create_Trie_Node (node->word, c, endpt);
        int index = c-'a';
        node->children[index] = child;
    }
    return child;
}

/** insert_word ()
 * insert a word in the trie
 * mark the last node as word-endpt
 */
Trie * insert_word (Trie * root, char * cs) {
	if (!root || !cs)
		return root;

	int length = strlen (cs);
	Trie * node = root;
	for (int i = 0; i < length; i++)
		node = insert_char (node, *(cs+i), i == length-1 ? 1 : 0);
	return node;
}

/** print_Trie_rec ()
 * recursive print function
 */
void print_Trie_rec (Trie * node, unsigned level) {
    if (!node)
        return;
 
 	for (unsigned i = 0; i < level; i++)
    	printf ("    ");
    printf ("'%s' %s\n", node->word ? node->word : "", node->endpt ? "w" : "n");    
    for (int i = 0; i < ALPHABETS; i++)
        print_Trie_rec (node->children[i], level+1);
}

/** print_Trie ()
 * wrapper function for recursive print
 */
void print_Trie (Trie * node) {
    printf ("[");
    unsigned trie_level = 0;
    print_Trie_rec (node, trie_level);
    printf ("]\n");
}
 
#endif
