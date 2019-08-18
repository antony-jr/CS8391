#include <stdlib.h>
#include <avl.h>

#define max(a,b) ((a > b) ? a : b)

static int abs_node_height(avl_tree_t *node){
	return max(avl_tree_height(node->left) ,  avl_tree_height(node->right)) + 1;
}

static int balance_factor(avl_tree_t *node){
	return avl_tree_height(node->left) - avl_tree_height(node->right);
}

static avl_tree_t *single_rotate_left(avl_tree_t *tree){
	avl_tree_t *p = NULL;
	if(!tree)
		return NULL;

	p = tree->left;
	tree->left = p->right;
	p->right = tree;
	
	/* Update heights. */
	tree->height = abs_node_height(tree);
	p->height = abs_node_height(p);
	return p;
}

static avl_tree_t *single_rotate_right(avl_tree_t *tree){
	avl_tree_t *p = NULL;
	if(!tree)
		return NULL;

	p = tree->right;
	tree->right = p->left;
	p->left = tree;

	/* Update heights. */
	tree->height = abs_node_height(tree);
	p->height = abs_node_height(p);
	return p;
}

static avl_tree_t *double_rotate_left(avl_tree_t *tree){
	if(!tree)
		return NULL;

	tree->left = single_rotate_right(tree->left);
	return single_rotate_left(tree);
}

static avl_tree_t *double_rotate_right(avl_tree_t *tree){
	if(!tree)
		return NULL;
	tree->right = single_rotate_left(tree->right);
	return single_rotate_right(tree);
}

avl_tree_t *avl_tree_new(int data){
	avl_tree_t *r = calloc(1 , sizeof *r);
	if(!r)
		return NULL;
	r->data = data;
	return r;
}

void avl_tree_free(avl_tree_t *tree){
	if(!tree)
		return;
	/* We will be using postorder transversal for 
	 * deleting the entire tree. */

	avl_tree_free(tree->left);
	avl_tree_free(tree->right);
	free(tree);
	return;
}

avl_tree_t *avl_tree_find(avl_tree_t *tree, int value){
	if(!tree)
		return NULL;

	if(tree->data == value){
		return tree;
	}
	else if(tree->data > value)
		return avl_tree_find(tree->left , value);
	return avl_tree_find(tree->right , value);
}

avl_tree_t *avl_tree_find_min(avl_tree_t *tree){
	return tree ? 
		(tree->left) ? avl_tree_find_min(tree->left) : tree
		: NULL;
}

avl_tree_t *avl_tree_find_max(avl_tree_t *tree){
	return tree ?
		(tree->right) ? avl_tree_find_max(tree->right) : tree
		: NULL;
}

avl_tree_t *avl_tree_insert(avl_tree_t *tree, int value){
	if(!tree){
		tree = avl_tree_new(value);
	}
	else if(tree->data > value){
		/* insert into left. */
		tree->left = avl_tree_insert(tree->left, value);
		/* Check if AVL properties are not voilated. */
		if(avl_tree_height(tree->left) - avl_tree_height(tree->right) == 2){
			/* Do the required rotations to fix the voilation.*/
			if(tree->left->data > value){
				/* It must be inserted in the left subtree of the left child of
				 * the given tree.
				 *
				 * This is case 1, So we must do a single rotation with left.
				 */
				 tree = single_rotate_left(tree);
			}else{
				/*
				 * It must be inserted in the right subtree of the left child of 
				 * the given tree.
				 *
				 * This is case 2, So we must do a double rotation with left.
				 */
			 	 tree = double_rotate_left(tree);
			}
		}
	}else if(tree->data < value){
		/* insert into right. */
		tree->right = avl_tree_insert(tree->right, value);	
		if(avl_tree_height(tree->right) - avl_tree_height(tree->left) == 2){
			if(tree->right->data > value){
				 tree = double_rotate_right(tree); /* Case 3 */
			}else{
			 	 tree = single_rotate_right(tree); /* Case 4 */
			}
		}
	}
	/* Note: 
	 * Case 1,4 are so called "outside" which is always solved by a simple 
	 * single rotation.
	 *
	 * Case 2,3 are so called "insdie" which is always solved by a little complicated
	 * double rotation.
	*/

	/* Update tree height */	
	tree->height = abs_node_height(tree);
	return tree;
}

avl_tree_t *avl_tree_delete(avl_tree_t *tree, int value){
	avl_tree_t *p = NULL;
	if(!tree){
		return NULL;
	}else if(tree->data > value){
		tree->left =  avl_tree_delete(tree->left, value);
	}else if(tree->data < value){
		tree->right = avl_tree_delete(tree->right, value);
	}
	else if(tree->left && tree->right){
		p = avl_tree_find_min(tree->right);
		tree->data = p->data;
		tree->right = avl_tree_delete(tree->right, tree->data);
	}
	else{
		p = tree;
		if(tree->left){
			tree = tree->left;
		}else if(tree->right){
			tree = tree->right;
		}else{
			tree = NULL;
		}
		free(p);

		if(tree){
			tree->height = abs_node_height(tree);
		}
		return tree;
	}
	/* Update height. */
	tree->height = abs_node_height(tree);
	if(avl_tree_height(tree->left) - avl_tree_height(tree->right) == 2 ||
	   avl_tree_height(tree->right) - avl_tree_height(tree->left) == 2){
		/* balance is broken. */
	
		/* left child is imbalanced */	
		if(avl_tree_height(tree->left) > avl_tree_height(tree->right)){
			/* left child's left tree  is imbalanced, so case 1*/
			if(avl_tree_height(tree->left->left) > avl_tree_height(tree->left->right)){
				tree = single_rotate_left(tree);		
			}else{ /* left child's right subtree is imbalanced */
				tree = double_rotate_left(tree); /* case 2 */ 
			}
		}
		else{ /* right child is imbalanced. */	
			/* right child's right tree  is imbalanced, so case 4*/
			if(avl_tree_height(tree->right->right) > avl_tree_height(tree->right->left)){
				tree = single_rotate_right(tree);		
			}else{ /* right child's left tree is imbalanced. */
				tree = double_rotate_right(tree); /* case 3 */
			}
		}
	}
	/* Update height again. */
	tree->height = abs_node_height(tree);
	return tree;
}

int avl_tree_height(avl_tree_t *tree){
	return tree ? tree->height : -1;
}
