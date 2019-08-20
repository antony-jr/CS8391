#include <stdlib.h>
#include <stdio.h>

#define max(a,b) ((a>b)?a:b)

typedef struct bin_tree_t_ {
	int data;
	struct bin_tree_t_ *left;
	struct bin_tree_t_ *right;
} bin_tree_t;

bin_tree_t *bin_tree_new(int);
void bin_tree_free(avl_tree_t*);

bin_tree_t *bin_tree_find(avl_tree_t*, int);
bin_tree_t *bin_tree_find_min(avl_tree_t*);
bin_tree_t *bin_tree_find_max(avl_tree_t*);

bin_tree_t *bin_tree_insert(avl_tree_t*, int);
bin_tree_t *bin_tree_delete(avl_tree_t*, int);
int bin_tree_height(avl_tree_t*);

int main(int ac, char **av){
	bin_tree_t *tree = NULL;
	int opt = 0;
	int value = 0;
	while(opt != 4){
		printf(":: OPERATIONS ::\n");
		printf("   1. Insert    \n");
		printf("   2. Delete    \n");
		printf("   3. Display   \n");
		printf("   4. Exit      \n");
		printf("Enter your choice: ");
		scanf("%d" , &opt);
		if(opt == 1){
			printf("Enter the node value to insert: ");
			scanf("%d" , &value);
			tree = avl_tree_insert(tree, value);
			printf("\n\n");
		}else if(opt == 2){
			printf("Enter the node value to delete: ");
			scanf("%d" , &value);
			tree = avl_tree_delete(tree, value);
			printf("\n\n");
		}else if(opt == 3){
			printf("\n\n\n");
			avl_tree_print(tree, 0);
			printf("\n\n\n");	
		}else{
			opt = 4;
		}
	}
	putchar('\n');

	printf("\nAVL TREE HEIGHT:: %d\n\n" , avl_tree_height(tree));

	avl_tree_free(tree);	
	return 0;
}
