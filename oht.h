#ifndef __OHT_H
#define __OHT_H

/** Open addressed Hash Table
 * General purpose, Double hash function
 */
#define MAX_ELEMENTS 31

/** client provided functions
 * typedef'ed to make more readable
 * else would have to use entire signature instead of T_hf
 */
typedef int (* T_hf) (const void * e);
typedef int (* T_eq) (const void * e1, const void * e2);
typedef void (* T_of) (const void * e);

struct OHashTable;

typedef struct OHashTable {
	int size;
	double load_factor;
	void * elements[MAX_ELEMENTS];

	// client function holders
	T_hf hashFn1;
	T_hf hashFn2;
	T_eq equalsFn;
	T_of outputFn;

} OHashTable;


/** Hash functions
 */

/** hf: (hf1 + i.hf2) % m
 * where i = probeInsert iteration count
 */
int hf (OHashTable * oht, const void * e, int probe) {
	if (!oht || !e)
		return -1;
	return (oht->hashFn1 (e) + probe * oht->hashFn2 (e)) % MAX_ELEMENTS;
}


OHashTable * createOht (T_hf _hf1, T_hf _hf2, T_eq _eq, T_of _of) {
	OHashTable * oht = (OHashTable *) malloc (sizeof (OHashTable));
	oht->size = 0;
	oht->load_factor = 0.7;
	for (int i = 0; i < MAX_ELEMENTS; i++)
		oht->elements[i] = NULL;

	oht->hashFn1 = _hf1;
	oht->hashFn2 = _hf2;
	oht->equalsFn = _eq;
	oht->outputFn = _of;
	return oht;
}


void deleteOht (OHashTable * oht) {
	if (oht) {
		for (int i = 0; i < MAX_ELEMENTS; i++) {
			if (oht->elements[i])
				oht->elements[i] = NULL;
		}
		free (oht);
	}
}


int isOhtEmpty (OHashTable * oht) {
	if (oht)
		return !oht->size;
	return 0;
}


int isOhtFull (OHashTable * oht) {
	if (oht)
		return oht->size >= (MAX_ELEMENTS * oht->load_factor);
	return 0;
}


int probeInsert (OHashTable * oht, const void * e) {
	if (!oht || !e || (isOhtFull (oht)))
		return -1;

	int found_at = -1, it = 0;
	while (found_at < 0 && it < MAX_ELEMENTS) {
		int index = hf (oht, e, it++);
		if (oht->elements[index] && oht->equalsFn (oht->elements[index], e))
			break;
		else if (!oht->elements[index])
			found_at = index;
	}
	return found_at;
}


int ohtInsert (OHashTable * oht, void * e) {
	int index = probeInsert (oht, e);
	if (index >= 0 && !oht->elements[index]) {
		oht->elements[index] = e;
		oht->size++;
	}
	return index;
}


int probeRemove (OHashTable * oht, const void * e) {
	if (!oht || !e)
		return -1;

	int found_at = -1, it = 0;
	while (found_at < 0 && it < MAX_ELEMENTS) {
		int index = hf (oht, e, it++);
		if (oht->elements[index] && oht->equalsFn (oht->elements[index], e))
			found_at = index;
		else if (!oht->elements[index])
			break;
	}
	return found_at;
}


int ohtRemove (OHashTable * oht, void * e) {
	int index = probeRemove (oht, e);
	if (index >= 0 && oht->elements[index]) {
		oht->elements[index] = NULL;
		oht->size--;
	}
	return index;
}


OHashTable * createOhtFromArray (void ** xs, int count, 
		T_hf _hf1, T_hf _hf2, T_eq _eq, T_of _of) {
	OHashTable * oht = createOht (_hf1, _hf2, _eq, _of);
	for (int i = 0; i < count && !isOhtFull (oht); i++)
		ohtInsert (oht, xs[i]);
	return oht;
}


void printOht (OHashTable * oht) {
	if (oht) {
		printf ("{size: %d\n  [", oht->size);
		for (int i = 0; i < MAX_ELEMENTS; i++) {
			if (oht->elements[i])
				oht->outputFn (oht->elements[i]);
		}
		printf ("]\n}\n");
	}
}


#endif