CFLAGS = -Wall -Wextra -g -std=c11 -pedantic-errors -MD
LDLIBS = -lm

all: ht ds ll bt tl exs str ga linkedlist triplelist objectlist queue algo_numeric arrayutils trie

clean:
	rm -rf *.d *.o *.out ht ds ll bt tl exs str ga linkedlist triplelist objectlist queue algo_numeric arrayutils trie
