#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int tos;
	int size;
	int *array;
} stack_t;

stack_t *stack_new(int size){
	stack_t *r = calloc(1 , sizeof *r);
	if(!r){
		return NULL;
	}
	r->size = size;
	r->array = calloc(size , sizeof(*(r->array)));
	r->tos = -1;
	return r;
}

void stack_delete(stack_t *ctx){
	free(ctx->array);
	free(ctx);	
}

int stack_make_empty(stack_t *ctx){
	ctx->tos = -1;
	return 0;
}

int stack_top_element(stack_t *ctx, int *el){
	if(0 > ctx->tos){
		printf("fatal error: stack is empty!");
		return -2;
	}
	*el = *(ctx->array + ctx->tos);
	return 0;
}

int stack_push(stack_t *ctx, int el){
	ctx->tos += 1;
	if(ctx->tos >= ctx->size){	
		printf("fatal error: stack overflow!\n");
		ctx->tos -= 1;
		return -2; /* stack overflow. */
	}	
	*(ctx->array + ctx->tos) = el;
	return 0;
}

int stack_pop(stack_t *ctx , int *el){
	if(0 > ctx->tos){
		printf("fatal error: empty stack!\n");
		return -3; /* empty stack */
	}
	*el = *(ctx->array + ctx->tos);
	ctx->tos -= 1;
	return 0;
}

static void stack_print(stack_t *ctx){
	int iter = 0;
	if(!ctx){
		printf("fatal error: no stack context.\n");
		return;
	}

	printf(
	"+-----------------+\n"
	"+      STACK      +\n"
	"+-----------------+\n");
	
	iter = ctx->tos;
	while(iter!=-1){
	printf(
	"%d\n",
	*(ctx->array + iter) 
	);
	--iter;
	}
	printf(
	"==================\n");
	return;
}

int main(){
	int opt = 0,
	    buf = 0;
	stack_t *ctx = stack_new(20);	
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
