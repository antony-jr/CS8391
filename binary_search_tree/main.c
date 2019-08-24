#include <stdlib.h>
#include <stdio.h>
typedef struct _bstree_t {
	int data;
	struct _bstree_t *left,*right;
} bstree_t;
bstree_t *insert(bstree_t *root, int v){
	if(!root){
		root = calloc(1, sizeof *root);
		root->data = v;
	}else if(root->data > v){
		root->left = insert(root->left, v);
	}else if(root->data < v){
		root->right = insert(root->right, v);
	}
	return root;
}
bstree_t *search(bstree_t *root, int v){
	return !root ? NULL : 
		(root->data == v) ? root :
		(root->data > v) ? search(root->left, v) :
		search(root->right, v);
}
int main(){
	int opt = 0, buf = 0;
	bstree_t *root = NULL,*p=NULL;
	while(opt!=3){
		printf("\n\n::BINARY SEARCH TREE OPERATIONS::\n");
		printf("1. Insert.\n2. Search.\n3. Exit.\n");
		printf("Enter your choice: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				printf("Enter the value: ");
				scanf("%d", &buf);
				root=insert(root, buf);
				break;
			case 2:
				printf("Enter the value to search: ");
				scanf("%d", &buf);
				p = search(root, buf);
				if(p)
					printf("Value found at address [%p].\n", p);
				else 
					printf("Value not found!\n");
				break;
			default:
				opt = 3;
				break;
		}
	}	
}
