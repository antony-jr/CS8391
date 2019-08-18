#include <avl.h>
#include <stdio.h>

static void avl_tree_print(avl_tree_t *tree, int indent){
	
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
	avl_tree_print(tree->left, indent+4);
	avl_tree_print(tree->right, indent+4);
}

int main(int ac, char **av){
	avl_tree_t *tree = NULL;
	int opt = 0;
	int value = 0;
	while(opt != 3){
		printf(":: OPERATIONS ::\n");
		printf("   1. Insert    \n");
		printf("   2. Delete    \n");
		printf("   3. Exit      \n");
		printf("Enter your choice: ");
		scanf("%d" , &opt);
		if(opt == 1){
			printf("\n\n");
			printf("Enter the node value to insert: ");
			scanf("%d" , &value);
			tree = avl_tree_insert(tree, value);
			avl_tree_print(tree, 0);
			printf("\n\n");
		}else if(opt == 2){
			printf("\n\n");
			printf("Enter the node value to delete: ");
			scanf("%d" , &value);
			tree = avl_tree_delete(tree, value);
			avl_tree_print(tree, 0);
			printf("\n\n");
		}else{
			opt = 3;
		}
	}
	putchar('\n');

	printf("\nAVL TREE HEIGHT:: %d\n\n" , avl_tree_height(tree));

	avl_tree_free(tree);	
	return 0;
}
