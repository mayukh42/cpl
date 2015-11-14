#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Binary Trees
 * Stanford CS Education Library
 * http://cslibrary.stanford.edu/110
 */
typedef struct Node {
	int val;
	struct Node * left;
	struct Node * right;
} Node;

typedef enum Bool {
	false,
	true
} Bool;

int max (int a, int b) {
	return a > b ? a : b;
}

Bool lookup (Node * root, int value) {
	if (root == NULL) 
		return false;
	
	if (root->val == value)
		return true;
	else if (root->val < value)
		return lookup (root->left, value);
	else 
		return lookup (root->right, value);
}

Node * create_node (int value) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->val = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void insert (Node ** root, int value) {
	if (* root == NULL) {
		Node * node = create_node (value);
		* root = node;
		return;
	} 
	else if (value < (* root)->val) 
		insert (&(* root)->left, value);
	else if (value > (* root)->val)
		insert (&(* root)->right, value);
	else
		return;
}

/** Rotation functions - rightrot () & leftrot ()
 * to keep tree balanced during inserts
 */
void rightrot (Node ** root) {
	if (* root == NULL || (* root)->left == NULL)
		return;

	Node * nroot = (* root)->left;
	(* root)->left = nroot->right;
	nroot->right = * root;
	* root = nroot;
}

void leftrot (Node ** root) {
	if (* root == NULL || (* root)->right == NULL)
		return;

	Node * nroot = (* root)->right;
	(* root)->right = nroot->left;
	nroot->left = * root;
	* root = nroot;
}

/** 1 - create_basic_tree ()
 * creates a balanced BST w/ values in the given range 
 * including lower, excluding upper
 */
Node * create_basic_tree (Node * root, int m, int n) {
	if (m >= n)
		return root;

	int middle = ((n - m) / 2) + m;
	root = create_node (middle);
	root->left = create_basic_tree (root->left, m, middle);
	root->right = create_basic_tree (root->right, middle + 1, n);
	return root;
} 

/** create_tree ()
 * creates a tree from list of values
 * list of values are same as in-order traversal of the created tree
 * if values are not sorted, the tree is not a BST
 * lo = 0, hi = len (xs)
 */
Node * create_tree (Node * root, int * xs, int lo, int hi) {
	if (lo >= hi)
		return root;

	int midx = ((hi - lo) / 2) + lo;
	root = create_node (xs[midx]);
	root->left = create_tree (root->left, xs, lo, midx);
	root->right = create_tree (root->right, xs, midx + 1, hi);
	return root;
}

Node * create_tree_with_insert (Node * root, int * xs, int n) {
	for (int i = 0; i < n; i++) 
		insert (&root, xs[i]);
	return root;
}

/** prototype for traversal functions
 */
typedef void (* pf) (Node * root);

/** 5 - inorder ()
 * in-order traversal of the tree
 */
void inorder (Node * root) {
	if (root != NULL) {
		inorder (root->left);
		printf ("%d, ", root->val);
		inorder (root->right);
	}
}

/** 6 - postorder ()
 * post-order traversal of the tree
 */
void postorder (Node * root) {
	if (root != NULL) {
		postorder (root->left);
		postorder (root->right);
		printf ("%d, ", root->val);
	}
}

void print_tabs (int cpos) {
	printf ("\n");
	for (int i = 0; i < cpos; i++) 
		printf ("    ");
}

void pretty_rec (Node * root, int cpos) {
	if (root != NULL) {
		print_tabs (cpos - 1);
		if (cpos > 0)
			printf (" -- ");
		printf ("%d", root->val);
		pretty_rec (root->left, cpos + 1);
		pretty_rec (root->right, cpos + 1);
	}
}

/** pretty ()
 * pretty printing of the tree
 * pre-order traversal
 */
void pretty (Node * root) {
	int n = 0;
	pretty_rec (root, n);
}

void print_tree (Node * root, pf print) {
	printf ("[");
	print (root);
	printf ("]\n");
}

void delete_tree (Node * root) {
	if (root != NULL) {
		delete_tree (root->left);
		delete_tree (root->right);
		free (root);
	}
}

/** 2 - size ()
 */
int size (Node * root) {
	if (root != NULL) 
		return 1 + size (root->left) + size (root->right);
	else
		return 0;
}

void test_size () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 0, 5);
	print_tree (tree, inorder);
	printf ("Size of the tree = %d\n", size (tree));
}

/** 3 - max_depth ()
 * balanced BST must have max_depth == lg (n) + 1
 * where n = upper - lower in the range from which tree was created
 */
int max_depth (Node * root) {
	if (root == NULL)
		return 0;
	else 
		return max (max_depth (root->left) + 1, max_depth (root->right) + 1);
}

Bool is_balanced (Node * tree) {
	if (tree != NULL) {
		int leftdepth = max_depth (tree->left);
		int rightdepth = max_depth (tree->right);
		return abs (leftdepth - rightdepth) <= 1 ? true : false;
	}
	else
		return false;
}

void test_max_depth () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);

	double gold = log2 (size (tree));
	int depth = max_depth (tree);
	printf ("Max depth of the tree = %d\n", depth);
	printf ("Depth check: %s\n", abs (ceil (gold) - (double) depth) <= 1.0 ? "ok" : "not ok");
	printf ("Balanced check: %s\n", is_balanced (tree) == true ? "ok" : "not ok");
}

/** is_leaf ()
 * check if node is leaf
 */
Bool is_leaf (Node * root) {
	if (root != NULL && root->left == NULL && root->right == NULL)
		return true;
	else 
		return false;
}

/** balance ()
 * recursively balance the BST
 */
void balance (Node ** root) {
	if ((* root) != NULL && ! is_leaf (* root)) {
		int leftdepth = max_depth ((* root)->left);
		int rightdepth = max_depth ((* root)->right);

		if (leftdepth - rightdepth > 1)
			rightrot (root);
		else if (rightdepth - leftdepth > 1)
			leftrot (root);

		balance (&((* root)->left));
		balance (&((* root)->right));
	}
}

/** create_tree_proper ()
 * creates a balanced BST from given array of values
 * BST depth: O(lg n)
 */
Node * create_tree_proper (int * xs, int n) {
	Node * root = NULL;
	for (int i = 0; i < n; i++) {
		insert (&root, xs[i]);
		balance (&root);
	}
	return root;
}

void test_create () {
	Node * tree = NULL;

	// naive creation - BST
	tree = create_basic_tree (tree, 1, 16);
	print_tree (tree, inorder);
	print_tree (tree, pretty);
	delete_tree (tree);

	// naive creation w/ given values - not a BST if values not sorted
	int xs[] = {8,0,2,7,0,1};
	tree = create_tree (tree, xs, 0, 6);
	print_tree (tree, inorder);
	print_tree (tree, pretty);
	delete_tree (tree);

	// unbalanced BST 
	int ys[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	tree = create_tree_with_insert (tree, ys, 15);
	print_tree (tree, inorder);
	print_tree (tree, pretty);
	delete_tree (tree);

	// balanced BST w/ given values
	tree = create_tree_proper (ys, 15);
	print_tree (tree, inorder);
	print_tree (tree, pretty);
	delete_tree (tree);
}

/** 4 - min_val (), max_val ()
 * returns the min, max value in BST
 */
int min_val (Node * root) {
	if (is_leaf (root)) 
		return root->val;
	else if (root != NULL)
		return min_val (root->left);
	else
		return -1;	
}

int max_val (Node * root) {
	if (is_leaf (root)) 
		return root->val;
	else if (root != NULL)
		return max_val (root->right);
	else
		return -1;	
}

void test_min_max () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 17);
	print_tree (tree, inorder);
	int min_v = min_val (tree);
	int max_v = max_val (tree);
	printf ("Minimum = %d, Maximum = %d\n", min_v, max_v);
}

/** 7 - has_path ()
 * returns true if a root-leaf path exists that sum to the given value
 */
Bool has_path (Node * root, int total) {
	if (is_leaf (root) && total == root->val)
		return true;
	else if (root != NULL) 
		return (has_path (root->left, total - root->val) || 
			has_path (root->right, total - root->val));
	else
		return false;
}

void test_has_path () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	// possible totals: 7, 9, 15, 17
	int total = 9;
	Bool res = has_path (tree, total);
	if (res)
		printf ("The tree has a path that sums to %d\n", total);
	else
		printf ("The tree does not have a path that sums to %d\n", total);

	delete_tree (tree);
}

void print_array (int * xs, int n) {
	printf ("[");
	for (int i = 0; i < n; i++)
		printf ("%d, ", xs[i]);
	printf ("]\n");
}

/** 8 - print_paths ()
 * print path-from-root for all leaves
 * one per line
 */
void print_paths (Node * root, int * xs, int n) {
	if (is_leaf (root)) {
		xs[n++] = root->val;
		print_array (xs, n);
	}
	else if (root != NULL) {
		xs[n++] = root->val;
		print_paths (root->left, xs, n);
		print_paths (root->right, xs, n);
	}
}

void test_print_paths () {
	int lo = 1, hi = 8;
	Node * tree = NULL;
	tree = create_basic_tree (tree, lo, hi);
	size_t height = ((unsigned) log2 (hi - lo)) + 1;
	int * xs = (int *) malloc (sizeof (int) * height);

	print_paths (tree, xs, 0);

	delete_tree (tree);
	free (xs);
}

/** 9 - mirror ()
 * mirrors the tree - swaps the left and right nodes
 * changes the tree
 */
void mirror (Node ** root) {
	if (* root != NULL) {
		Node * tmp = (* root)->left;
		(* root)->left = (* root)->right;
		(* root)->right = tmp;
		mirror (&((* root)->left));
		mirror (&((* root)->right));
	}
}

void test_mirror () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);

	mirror (&tree);
	print_tree (tree, inorder);

	delete_tree (tree);
}

/** 10 - double_nodes ()
 * creates a duplicate of each node and inserts in the tree
 */
void double_nodes (Node ** root) {
	if (* root != NULL) {
		double_nodes (&((* root)->left));
		double_nodes (&((* root)->right));
		Node * node = create_node ((* root)->val);
		node->left = (* root)->left;
		(* root)->left = node;
	}
}

void test_double_nodes () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);

	double_nodes (&tree);
	print_tree (tree, inorder);

	delete_tree (tree);
}

/** 11 - is_same ()
 * returns true iff 2 trees are exactly same
 * structurally, value-wise for each node
 */
Bool is_same (Node * one, Node * two) {
	if (one != NULL && two != NULL) {
		Bool current = one->val == two->val;
		return (current && is_same (one->left, two->left) && 
			is_same (one->right, two->right));
	} else if (one == NULL && two == NULL)		// controversial ?
		return true;
	else
		return false;
}

void test_same () {
	Node * first = NULL;
	Node * second = NULL;
	first = create_basic_tree (first, 1, 8);
	second = create_basic_tree (second, 1, 8);

	Bool res = is_same (first, second);

	if (res)
		printf ("The trees are same.\n");
	else
		printf ("The trees are different.\n");

	delete_tree (first);
	delete_tree (second);
}

/** search_bt ()
 * returns true if the given value exists, false otherwise
 * Note: tree is NOT a BST
 */
Bool search_bt (Node * root, int value) {
	if (root != NULL) {
		if (root->val == value)
			return true;

		Bool has_left = search_bt (root->left, value);
		if (has_left)
			return true;

		Bool has_right = search_bt (root->right, value);
		if (has_right)
			return true;		

		return false;
	} else
		return false;
}

void test_search_bt () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 100);
	int value = 79;
	Bool res = search_bt (tree, value);

	if (res)
		printf ("%d found\n", value);
	else
		printf ("%d not found\n", value);

	delete_tree (tree);
}

/** 12 - catalan ()
 * returns the number of possible BST with n nodes that store [1..n]
 * also called the Catalan Number
 * each element can be a root; when root = leftmost or rightmost, the left subtree
 * or right subtree is empty, and this contributes as 1 to the combination of trees
 */
int catalan (int n) {
	if (n <= 1)
		return 1;
	
	int total = 0;
	for (int i = 1; i <= n; i++) {
		int nl = i - 1;
		int nr = n - i;
		total += catalan (nl) * catalan (nr);
	}
	return total;
}

void test_catalan () {
	int n = 3;
	printf ("%d BSTs are possible w/ %d nodes containing [%d..%d]\n", 
		catalan (n), n, 1, n);
}

/** 13 - is_bst1 () 
 * uses min_val & max_val to determine if the tree is a bst
 */
Bool is_bst1 (Node * tree) {
	if (is_leaf (tree)) 
		return true;
	else if (tree != NULL) {
		Bool left = true, right = true;
		if (tree->left != NULL)
			left = is_bst1 (tree->left) && max_val (tree->left) < tree->val;

		if (! left)
			return false;

		if (tree->right != NULL)
			right = is_bst1 (tree->right) && min_val (tree->right) > tree->val;

		return left && right;
	} else 
		return false;
}

void test_is_bst1 () {
	int xs[] = {8,0,2,7,0,1};
	Node * tree = NULL;
	tree = create_tree (tree, xs, 0, 6);
	print_tree (tree, inorder);

	Bool ans = is_bst1 (tree);
	if (ans)
		printf ("The above tree is a BST\n");
	else
		printf ("The above tree is not a BST\n");

	delete_tree (tree);
}

/** 14 - is_bst2 ()
 * w/o using min_val, max_val
 */
Bool is_bst2 (Node * tree, int mn, int mx) {
	if (tree != NULL) {
		Bool current = tree->val >= mn && tree->val <= mx;
		return (current && 
			is_bst2 (tree->left, mn, tree->val - 1) &&
			is_bst2 (tree->right, tree->val + 1, mx));
	} else 
		return true;
}

void test_is_bst2 () {
	int xs[] = {1,2,3,4,5,6};
	Node * tree = NULL;
	tree = create_tree (tree, xs, 0, 6);
	print_tree (tree, inorder);

	Bool ans = is_bst2 (tree, INT_MIN, INT_MAX);
	if (ans)
		printf ("The above tree is a BST\n");
	else
		printf ("The above tree is not a BST\n");

	delete_tree (tree);
}

void run_tests () {
	test_create ();
	// test_size ();
	// test_max_depth ();
	// test_min_max ();
	// test_has_path ();
	// test_print_paths ();
	// test_mirror ();
	// test_double_nodes ();
	// test_same ();
	// test_search_bt ();
	// test_catalan ();
	// test_is_bst1 ();
	// test_is_bst2 ();
}

int main () {
	run_tests ();

	return 0;
}
