#ifndef __TRIE_H
#define __TRIE_H
 
#include <string.h>
#define ALPHABETS 26
 
 
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
 
struct Trie;
 
typedef struct Trie {
    char * word;
    int endpt;
    struct Trie * children[ALPHABETS];
} Trie;
 
Trie * create_Trie_Node (char * word, char c, int endpt) {
    Trie * node = (Trie *) malloc (sizeof (Trie));
    node->word = append_char (word, c);
    node->endpt = endpt;
    for (int i = 0; i < ALPHABETS; i++)
        node->children[i] = NULL;
    return node;
}
 
Trie * create_Trie_Root () {
	char nullc = 0;
    Trie * node = create_Trie_Node (&nullc, 0, 0);
    return node;
}
 
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
 
Trie * get_child (Trie * node, char c) {
    if (c < 'a' || c > 'z' || !node)
        return NULL;
 
    int index = c-'a';
    return node->children[index];
}
 
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
 
void print_Trie_rec (Trie * node) {
    if (!node)
        return;
 
    printf ("'%s' %s", node->word ? node->word : "", node->endpt ? "w" : "nw");
    printf ("\n   ");
    for (int i = 0; i < ALPHABETS; i++)
        print_Trie_rec (node->children[i]);
}
 
void print_Trie (Trie * node) {
    printf ("[");
    print_Trie_rec (node);
    printf ("]\n");
}
 
#endif