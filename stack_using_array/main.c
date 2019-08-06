#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int tos;
	int size;
	int *array;
} stack_t;

stack_t *stack_new(){
	stack_t *r = calloc(1 , sizeof *r);
	if(!r){
		return NULL;
	}
	r->tos = -1;
	r->size = 0;
	return r;
}

void stack_delete(stack_t *ctx){
	if(!ctx){
		return;
	}

	if(ctx->array){
		free(ctx->array);
	}
	free(ctx);	
}

int stack_make_empty(stack_t *ctx){
	if(!ctx){
		return -1;
	}
	ctx->tos = -1;
	return 0;
}

int stack_top_element(stack_t *ctx, int *el){
	if(!ctx){
		return -1;
	}else if(0 > ctx->tos){
		return -2;
	}

	*el = *(ctx->array + ctx->tos);
	return 0;
}

int stack_push(stack_t *ctx, int el){
	int *guard = NULL;
	if(!ctx){
		return -1;
	}	

	ctx->tos += 1;
	if(ctx->tos >= ctx->size){	
		/* reallocate */
		ctx->size += 1;
		guard = realloc(ctx->array , sizeof(*(ctx->array)) * ctx->size);
		if(!guard){ /* realloc failed */
			ctx->size -= 1;
			ctx->tos -= 1;
			return -2; /* stack overflow. */
		}
		ctx->array = guard;
	}	
	*(ctx->array + ctx->tos) = el;
	return 0;
}

int stack_pop(stack_t *ctx , int *el){
	if(!ctx){
		return -1;
	}else if(0 > ctx->tos){
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
	
	printf(
	"+ INDEX  |  VALUE +\n"
	"+-----------------+\n");
	iter = ctx->tos;
	while(iter!=-1){
	printf(
	"   %d    |   %d   \n",
	iter, *(ctx->array + iter) 
	);
	--iter;
	}
	printf(
	"+-----------------+\n");

	return;
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
					printf("Cannot push element, failed!\n");
					opt = 6;
					break;
				}
				printf("Successfully pushed element to stack.\n\n");
				break;
			case 2:
				
				if(stack_pop(ctx, &buf)){
					printf("Cannot pop element, failed!\n\n");
					opt = 6;
					break;
				}
				printf("\n\nSuccessfully poped element(%d) from stack.\n\n" , buf);
				break;
			case 3:
				
				if(stack_top_element(ctx, &buf)){
					printf("Cannot take top element, failed!\n\n");
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
