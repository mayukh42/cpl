#ifndef __TRIE_H
#define __TRIE_H

#include <string.h>
#define ALPHABETS 26


char * append_char (char * word, char c) {
	if (!word)
		return NULL;

	int length = strlen (word);
	char * new_word = (char *) malloc (sizeof (char) * (length+2));
	strcpy (new_word, word);
	new_word[length] = c;
	new_word[length+1] = 0;
	free (word);
	return new_word;
}

struct Trie;

typedef struct Trie {
	char * word;
	int length;
	int endpt;
	struct Trie ** children;
} Trie;

Trie * create_Trie_Node (char * word, int length, char c, int endpt) {
	Trie * node = (Trie *) malloc (sizeof (Trie));
	node->word = c ? append_char (word, c) : word;
	node->endpt = endpt;
	node->length = length+1;

	Trie ** children = (Trie **) malloc (sizeof (Trie *) * ALPHABETS);
	for (int i = 0; i < ALPHABETS; i++) 
		children[i] = NULL;
	node->children = children;

	return node;
}

Trie * create_Trie_Root () {
	char * word = (char *) malloc (sizeof (char));
	* word = 0;
	Trie * node = create_Trie_Node (word, 0, 0, 0);
	return node;
}

void delete_Trie (Trie * node) {
	if (node) {
		if (node->word)
			free (node->word);
		if (node->children) {
			Trie ** child = node->children;
			for (int i = 0; i < ALPHABETS; i++)
				delete_Trie (child[i]);
			free (child);
		}
		free (node);
	}
}

Trie * get_child (Trie * node, char c) {
	if (!node || c < 'a' || c > 'z')
		return NULL;

	int index = (int)(c-'a');
	return (node->children)[index];
}

Trie * insert_char (Trie * node, char c, int endpt) {
	if (!node)
		return NULL;

	Trie * child = get_child (node, c);
	if (!child) {
		child = create_Trie_Node (node->word, node->length, c, endpt);
	}
	return child;
}

void print_Trie_rec (Trie * node) {
	if (!node)
		return;

	printf ("word: %s ", node->word ? node->word : "");
	printf ("endpt: %d ", node->endpt);
	Trie ** children = node->children;
	for (int i = 0; i < ALPHABETS; i++)
		print_Trie_rec (children[i]);
}

void print_Trie (Trie * node) {
	printf ("[");
	print_Trie_rec (node);
	printf ("]\n");
}

#endif