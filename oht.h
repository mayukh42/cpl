#ifndef __OHT_H
#define __OHT_H

/** Open addressed Hash Table
 * General purpose, Double hash function
 */
#define MAX_ELEMENTS 31

/** client provided functions
 * TODO: refactor into the OHashTable struct
 */
typedef int (* hf_) (const void * e);
typedef int (* eq_) (const void * e1, const void * e2);
typedef void (* of_) (const void * e);

struct OHashTable;

typedef struct OHashTable {
	int size;
	double load_factor;
	void * elements[MAX_ELEMENTS];
} OHashTable;


/** Hash functions
 */

/** hf: (hf1 + i.hf2) % m
 * where i = probeInsert iteration count
 */
int hf (const void * const e, int probe, hf_ hf1, hf_ hf2) {
	return (hf1 (e) + probe * hf2 (e)) % MAX_ELEMENTS;
}


OHashTable * createOht () {
	OHashTable * oht = (OHashTable *) malloc (sizeof (OHashTable));
	oht->size = 0;
	oht->load_factor = 0.7;
	for (int i = 0; i < MAX_ELEMENTS; i++)
		oht->elements[i] = NULL;
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


int probeInsert (OHashTable * oht, const void * e, hf_ hf1, hf_ hf2, eq_ equals) {
	if (!oht || !e || (isOhtFull (oht)))
		return -1;

	int found_at = -1, it = 0;
	while (found_at < 0 && it < MAX_ELEMENTS) {
		int index = hf (e, it++, hf1, hf2);
		if (oht->elements[index] && equals (oht->elements[index], e))
			break;
		else if (!oht->elements[index])
			found_at = index;
	}
	return found_at;
}


int ohtInsert (OHashTable * oht, void * e, hf_ hf1, hf_ hf2, eq_ equals) {
	int index = probeInsert (oht, e, hf1, hf2, equals);
	if (index >= 0 && !oht->elements[index]) {
		oht->elements[index] = e;
		oht->size++;
	}
	return index;
}


int probeRemove (OHashTable * oht, const void * e, hf_ hf1, hf_ hf2, eq_ equals) {
	if (!oht || !e)
		return -1;

	int found_at = -1, it = 0;
	while (found_at < 0 && it < MAX_ELEMENTS) {
		int index = hf (e, it++, hf1, hf2);
		if (oht->elements[index] && equals (oht->elements[index], e))
			found_at = index;
		else if (!oht->elements[index])
			break;
	}
	return found_at;
}


int ohtRemove (OHashTable * oht, void * e, hf_ hf1, hf_ hf2, eq_ equals) {
	int index = probeRemove (oht, e, hf1, hf2, equals);
	if (index >= 0 && oht->elements[index]) {
		oht->elements[index] = NULL;
		oht->size--;
	}
	return index;
}


OHashTable * createOhtFromArray (void ** xs, int count, hf_ hf1, hf_ hf2, eq_ equals) {
	OHashTable * oht = createOht ();
	for (int i = 0; i < count && !isOhtFull (oht); i++)
		ohtInsert (oht, xs[i], hf1, hf2, equals);
	return oht;
}


void printOht (OHashTable * oht, of_ print_fn) {
	if (oht) {
		printf ("{size: %d\n  [", oht->size);
		for (int i = 0; i < MAX_ELEMENTS; i++) {
			if (oht->elements[i])
				print_fn (oht->elements[i]);
		}
		printf ("]\n}\n");
	}
}


#endif