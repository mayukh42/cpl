#ifndef __DIGITS_H
#define __DIGITS_H

/** Digits implementation
 * A wrapper over an array that also includes its size 
 * and index of its most significant bit
 */

typedef struct Digits {
	unsigned * array;
	int size;
	int msb;
} Digits;


#endif