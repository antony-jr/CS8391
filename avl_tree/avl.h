#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct avl_tree_t_ {
	int data;
	struct avl_tree_t_ *left;
	struct avl_tree_t_ *right;
	int height;
} avl_tree_t;

avl_tree_t *avl_tree_new(int);
void avl_tree_free(avl_tree_t*);

avl_tree_t *avl_tree_find(avl_tree_t*, int);
avl_tree_t *avl_tree_find_min(avl_tree_t*);
avl_tree_t *avl_tree_find_max(avl_tree_t*);

avl_tree_t *avl_tree_insert(avl_tree_t*, int);
avl_tree_t *avl_tree_delete(avl_tree_t*, int);
int avl_tree_height(avl_tree_t*);

#endif // AVL_H_INCLUDED
