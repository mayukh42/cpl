# cpl
Problems coded in C

1. ht.c: A simple Hashtable in C

2. Cmain.sublime-snippet: A small template for quick-starting a C source code in Sublime Text

3. ll.c: 18 LinkedList problems (http://cslibrary.stanford.edu/105)

4. bt.c: 14 BinaryTree problems (http://cslibrary.stanford.edu/110)

5. ds.c: Some problems in data structures, maily linked list

&nbsp;&nbsp;&nbsp;&nbsp;print_alt, array2list, find_y_point, find_jn_cycle, reverse_arrows, reverse (recursive), reverse_iter, delete_alt, a linked list container with tail reference (enables functional pattern of doing a reverse)

6. text/: Text files for use in exercises

7. tl.c: The Great Tree-List Recursion Problem (http://cslibrary.stanford.edu/109)

8. exs.c: Matrix and numerical problems

&nbsp;&nbsp;&nbsp;&nbsp;spiral_print_mat, add_ut, hash_str (a hash function like Java), str_array_diff, gcd, double2rational, reverse_num, find_circles_within, factors, inverse_round (rounds off 1/n to k decimal places), period (of 1/n)

9. ga.c: Graph algorithms

&nbsp;&nbsp;&nbsp;&nbsp;dfs, bfs (TODO: refactor to use Queue in queue.h)

10. str.c: String utility functions

&nbsp;&nbsp;&nbsp;&nbsp;remove_at, is_equal, is_equal_upto, permute, subsets, sequences, naive_matcher, rabin_karp (matcher), boyer_moore (matcher)

11. linkedlist.c, linkedlist.h: Some more linked list problems

&nbsp;&nbsp;&nbsp;&nbsp;m_from_last, detect_cycle, reverse (recursive)

12. objectlist.c, objectlist.h: General purpose linked list

13. queue.c, queue.h: General purpose queue, utilizing the general purpose linked list

14. triplelist.c, triplelist.h: Flatten/ unflatten a 2D linked list (doubly linked horizontally, with optional child element vertically)

15. algo_numeric.c, algo_numeric2.c: Numerical algorithms

&nbsp;&nbsp;&nbsp;&nbsp;sqrt_nr, minmax, binary_search, matrix_search, asSumOfSquares, findCelebrity

16. arrayutils.c, arrayutils.h: Some array and matrix utility functions, matrix rotation, quicksort

16. trie.c, trie.h: The Trie data structure, including a suggestions algorithm, that returns top n suggestions for a given prefix.

17. oht.h, oht.c: Open-addressed Hashtable (general purpose, using objectlist). This is done in a more OOP way (i.e. with function ptrs in struct)

18. stack.h, stack.c: A general purpose Stack, using objectlist

19. sealer.c: A simple file encrypter using user-defined key

20. utils.c, utils.h: A minimal, general purpose Object struct; helper print functions for all primitive types and string

21. bigint.c, bigint.h: A BigInteger implementation (WIP - supports add, subtract, product, divide)

All programs are valgrind-tested for memory leaks.


Usage: 

$ git clone https://github.com/mayukh42/cpl.git

$ cd cpl

$ make

$ valgrind ./[executable]