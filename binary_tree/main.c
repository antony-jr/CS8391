#include <stdlib.h>
#include <stdio.h>

#define max(a,b) ((a>b)?a:b)

#ifndef BIN_TREE_DEF
#define BIN_TREE_DEF
typedef struct bin_tree_t_ {
	int data;
	struct bin_tree_t_ *left;
	struct bin_tree_t_ *right;
} bin_tree_t;

bin_tree_t *bin_tree_new(int);
void bin_tree_free(bin_tree_t*);

bin_tree_t *bin_tree_find(bin_tree_t*, int);
bin_tree_t *bin_tree_find_min(bin_tree_t*);
bin_tree_t *bin_tree_find_max(bin_tree_t*);

bin_tree_t *bin_tree_insert(bin_tree_t*, int);
bin_tree_t *bin_tree_delete(bin_tree_t*, int);
int bin_tree_height(bin_tree_t*);
#endif /* BIN_TREE_DEF */

static void bin_tree_print(bin_tree_t *tree, int indent){
	int iter = 0;
	if(indent){
		while(iter++ < indent){
			putchar(' ');
		}
	}
	if(!tree){
		printf("( NULL )\n");
		return;
	}
	printf("( %d )\n" , tree->data);
	bin_tree_print(tree->left, indent+4);
	bin_tree_print(tree->right, indent+4);
}

int main(int ac, char **av){
	bin_tree_t *tree = NULL,
		   *p = NULL;
	int opt = 0;
	int value = 0;
	while(opt != 7){
		printf(
		":: OPERATIONS ::\n"
		"   1. Insert\n"
		"   2. Delete\n"
		"   3. Find\n"
		"   4. Find minimum\n"
		"   5. Find maximum\n"
		"   6. Display\n"
		"   7. Exit\n");
		printf("Enter your choice: ");
		scanf("%d" , &opt);
		if(opt == 1){
			printf("Enter the node value to insert: ");
			scanf("%d" , &value);
			tree = bin_tree_insert(tree, value);
			printf("\n\n");
		}else if(opt == 2){
			printf("Enter the node value to delete: ");
			scanf("%d" , &value);
			tree = bin_tree_delete(tree, value);
			printf("\n\n");
		}
		else if(opt == 3){
			printf("Enter the node value to find: ");
			scanf("%d" , &value);
			p = bin_tree_find(tree, value);
			if(p){
				printf("[%p](%d) Found!\n\n", p, p->data);
			}else{
				printf("Node not found!\n\n");
			}
		}else if(opt == 4){
			p = bin_tree_find_min(tree);
			if(p){
				printf("Minimum: [%p][%d]\n\n",p ,p->data);
			}else{
				printf("Tree is empty!\n\n");
			}
		}else if(opt == 5){
			p = bin_tree_find_max(tree);
			if(p){
				printf("Maximum: [%p][%d]\n\n",p ,p->data);
			}else{
				printf("Tree is empty!\n\n");
			}
		}	
		else if(opt == 6){
			printf("\n\n\n");
			bin_tree_print(tree, 0);
			printf("\n\n\n");	
		}else{
			opt = 7;
		}
	}
	printf("\n\nBINARY TREE HEIGHT:: %d\n" , bin_tree_height(tree));
	bin_tree_free(tree);	
	return 0;
}

bin_tree_t *bin_tree_new(int data){
	bin_tree_t *r = calloc(1 , sizeof *r);
	if(!r)
		return NULL;
	r->data = data;
	return r;
}

void bin_tree_free(bin_tree_t *tree){
	if(!tree)
		return;
	/* We will be using postorder transversal for 
	 * deleting the entire tree. */
	bin_tree_free(tree->left);
	bin_tree_free(tree->right);
	free(tree);
	return;
}

bin_tree_t *bin_tree_find(bin_tree_t *tree, int value){
	return !tree ? NULL :
		tree->data == value ? tree : 
		tree->data > value ? bin_tree_find(tree->left, value) :
		bin_tree_find(tree->right, value);
}

bin_tree_t *bin_tree_find_min(bin_tree_t *tree){
	return tree ? 
		(tree->left) ? bin_tree_find_min(tree->left) : tree
		: NULL;
}

bin_tree_t *bin_tree_find_max(bin_tree_t *tree){
	return tree ?
		(tree->right) ? bin_tree_find_max(tree->right) : tree
		: NULL;
}

bin_tree_t *bin_tree_insert(bin_tree_t *tree, int value){
	if(!tree){
		tree = bin_tree_new(value);
	}
	else if(tree->data > value){
		tree->left = bin_tree_insert(tree->left, value);
	}else if(tree->data < value){
		tree->right = bin_tree_insert(tree->right, value);	
	}
	return tree;
}

bin_tree_t *bin_tree_delete(bin_tree_t *tree, int value){
	bin_tree_t *p = NULL;
	if(!tree){
		return NULL;
	}else if(tree->data > value){
		tree->left =  bin_tree_delete(tree->left, value);
	}else if(tree->data < value){
		tree->right = bin_tree_delete(tree->right, value);
	}
	else if(tree->left && tree->right){
		p = bin_tree_find_min(tree->right);
		tree->data = p->data;
		tree->right = bin_tree_delete(tree->right, tree->data);
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
		return tree;
	}
	return tree;
}

int bin_tree_height(bin_tree_t *tree){
	return tree ? 
	       max(bin_tree_height(tree->left), bin_tree_height(tree->right))+1:-1;
}
