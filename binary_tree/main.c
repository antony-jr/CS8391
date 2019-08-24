#include <stdio.h>
#include <stdlib.h>
typedef struct _btree_t {
	int data;
	struct _btree_t *left,*right;
} btree_t;
btree_t *insert(btree_t *root, int v){
	char c[2];
	if(!root){
		root = calloc(1, sizeof *root);
		root->data = v;
	}else{
		printf("Where to insert left(l)/right(r) of (%d): ", root->data);
		scanf("%s",c);
		if(c[0] == 'r' || c[0] == 'R')
			root->right = insert(root->right, v);
		else
			root->left = insert(root->left, v);
	}
	return root;
}
static void inorder(btree_t *root){
	if(!root)
		return;
	inorder(root->left);
	printf("[%p]: %d\n",root,root->data);
	inorder(root->right);
}
static void preorder(btree_t *root){
	if(!root)
		return;
	printf("[%p]: %d\n",root,root->data);
	preorder(root->left);
	preorder(root->right);
}
static void postorder(btree_t *root){
	if(!root)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("[%p]: %d\n",root,root->data);	
}
int main(){
	int buf = 0, opt = 0;
	btree_t *root = NULL;
	while(opt!=5){
		printf("\n\n::BINARY TREE OPERATIONS::\n");
		printf("1. Insert.\n2. Inorder.\n3. Preorder.\n4. Postorder.\n5.Exit\n");
		printf("Enter the your choice: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				printf("Enter the value to insert: ");
				scanf("%d", &buf);
				root = insert(root, buf);
				break;
			case 2:
				inorder(root);
				break;
			case 3:
				preorder(root);
				break;
			case 4:
				postorder(root);
				break;
			default:
				opt = 5;
				break;
		}
	}
	return 0;
}
