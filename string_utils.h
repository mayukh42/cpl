#ifndef __STRING_UTILS_H
#define __STRING_UTILS_H

#include <string.h>

/** string utilities
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

#endif