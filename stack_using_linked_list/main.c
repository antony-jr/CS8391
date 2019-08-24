#include <stdlib.h>
#include <stdio.h>
typedef struct _stack_t {
	int data; 
	struct _stack_t *next;
} stack_t;
static void push(stack_t **s, int el){
	stack_t *p = calloc(1,sizeof *p);
	p->data = el;
	p->next = *s?*s:NULL;
	*s = p;
}
static int pop(stack_t **s, int *el){
	stack_t *p = *s;
	if(!*s){
		printf("Stack is empty!\n");
		return -1;
	}
	*el = p->data;
	*s = p->next;
	free(p);
	return 0;
}
static void display(stack_t *s){
	while(s){
		printf("%d\n",s->data);
		s = s->next;
	}
	return;
}
int main(){
	int opt = 0,
	    buf = 0;
	stack_t *s = NULL;
	while(opt!=4){
		printf("\n\n::STACK OPERATIONS::\n");
		printf("1. Push.\n2. Pop.\n3. Display.\n4. Exit. \n");
		printf("Please enter your options: ");
		scanf("%d" , &opt);
		switch(opt){
			case 1:
				printf("Enter the element to push: ");
				scanf("%d" , &buf);
				push(&s, buf);
				break;
			case 2:
				if(!pop(&s, &buf))
					printf("Poped element %d.\n" , buf);
				break;
			case 3:
				display(s);
				break;
			default:
				opt = 4;
				break;
		}
	}
	return 0;
}
