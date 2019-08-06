#include <stdlib.h>
#include <stdio.h>

typedef struct _stack_record_t {
	int data;
	struct _stack_record_t *prev;
	struct _stack_record_t *next;
} stack_record_t;

typedef struct {
	stack_record_t *head,
		       *tail;
} stack_t;

stack_t *stack_new(){
	stack_t *r = calloc(1 , sizeof *r);
	if(!r){
		return NULL;
	}
	return r;
}

void stack_delete(stack_t *ctx){
	if(!ctx){
		return;
	}
	
	stack_record_t *p = ctx->head;
	stack_record_t *to_free = NULL;
	while(p){
		to_free = p;
		p = p->next;
		free(to_free);
	}
	free(ctx);
}


int stack_is_empty(stack_t *ctx){
	return !ctx->head;
}

int stack_top_element(stack_t *ctx, int *el){
	if(stack_is_empty(ctx)){
		printf("fatal error: stack is empty!\n");
		return -1;
	}
	return (*el = ctx->head->data) * 0;
}

int stack_make_empty(stack_t *ctx){
	stack_record_t *to_free = NULL;
	stack_record_t *p = ctx->head;
	while(p){
		to_free = p;
		p = p->next;
		free(to_free);
	}
	ctx->head = NULL;
	ctx->tail = NULL;
	return 0;
}

int stack_push(stack_t *ctx, int el){
	stack_record_t *p = NULL;
	if(!ctx->tail){
		ctx->head = calloc(1 , sizeof *(ctx->head));
		p = ctx->head;
		ctx->tail = p;
	}else{
		ctx->tail->next = calloc(1 , sizeof *(ctx->tail));
		p = ctx->tail->next;
		p->prev = ctx->tail;
		ctx->tail = p;
	}
	if(!p){
		printf("fatal error: stack overflow!\n");
		return -1; /* no memory */
	}
	p->data = el;
	return 0;
}

static void stack_print(stack_t *ctx){
	stack_record_t **p = &ctx->tail;
	printf(
	"----------------------\n"
	"|       STACK        |\n"
	"----------------------\n");
	while(*p){
		printf("[%p]: %d\n" , *p , (*p)->data);
		p = &((*p)->prev);
	}
	printf("--------------------\n");
	return;
}


int stack_pop(stack_t *ctx, int *el){
	stack_record_t *p = NULL;
	if(stack_is_empty(ctx)){
		printf("fatal error: stack empty!\n");
		return -1;
	}

	p = ctx->tail;
	if(ctx->head == ctx->tail){
		ctx->head = ctx->tail = NULL;
	}else{
		ctx->tail = ctx->tail->prev;
		ctx->tail->next = NULL;
	}
	*el = p->data;
	free(p);
	return 0;
}


int main(){
	int opt = 0,
	    buf = 0;
	stack_t *ctx = stack_new();	
	while(opt!=6){
		printf(
		"::STACK OPERATIONS::\n");
		printf(
		"1. Push element to stack.\n"
		"2. Pop element from stack.\n"
		"3. Show top element in stack.\n"
		"4. Print stack. \n"
		"5. Make the stack empty.\n"
		"6. Exit. \n"	
		);

		printf("Please enter your options: ");
		scanf("%d" , &opt);

		switch(opt){
			case 1:
				printf("\n\nEnter the element to push: ");
				scanf("%d" , &buf);
				if(stack_push(ctx, buf)){
					opt = 6;
					break;
				}
				printf("Successfully pushed element to stack.\n\n");
				break;
			case 2:
				
				if(stack_pop(ctx, &buf)){
					opt = 6;
					break;
				}
				printf("\n\nSuccessfully poped element(%d) from stack.\n\n" , buf);
				break;
			case 3:
				
				if(stack_top_element(ctx, &buf)){
					opt = 6;
					break;
				}
				printf("\n\nTop element in stack: %d.\n\n" , buf);
				break;
			case 4:
				printf("\n\n");
				stack_print(ctx);
				printf("\n\n");	
				break;
			case 5:
				if(stack_make_empty(ctx)){
					printf("Failed to make the stack empty.\n\n");
				}
				break;
			default:
				opt = 6;
				break;
		}
	}
	stack_delete(ctx);
	return 0;
}
