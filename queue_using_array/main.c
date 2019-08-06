#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int size;
	int front;
	int rear;
	int *array;
} queue_t;

queue_t *queue_new(int size){
	queue_t *r = calloc(1 , sizeof *r);
	if(!r){
		return NULL;
	}
	r->size = size;
	r->array = calloc(size , sizeof(*(r->array)));
	r->front = r->rear = -1;
	return r;
}

void queue_delete(queue_t *ctx){
	free(ctx->array);
	free(ctx);
}

int queue_is_full(queue_t *ctx){
		return ctx->size - 1 <= ctx->rear;
}

int queue_is_null(queue_t *ctx){
	if(ctx->front == -1 && ctx->rear == -1){
		return 1;
	}
	return 0;
}

int queue_make_null(queue_t *ctx){
	ctx->front = ctx->rear = -1;
}

int queue_enqueue(queue_t *ctx, int el){
	if(queue_is_full(ctx)){
		printf("fatal error: queue full!\n");
		return -1;
	}
	*(ctx->array + ++(ctx->rear)) = el;
	return 0;
}

int queue_dequeue(queue_t *ctx, int *el){
	if(queue_is_null(ctx)){
		printf("fatal error: queue is empty!\n");
		return -1;
	}

	*el = *(ctx->array + 
			(ctx->front == -1 ? (ctx->front = 0) : ctx->front ));
	if(++ctx->front > ctx->rear){
		queue_make_null(ctx);
	}
	return 0;
}

static void queue_print(queue_t *ctx){
	int iter = ctx->front == -1 ? 0:ctx->front;
	printf(
	"+-------------------+\n"
	"|       QUEUE       |\n"
	"+===================+\n"
	);
	while(iter <= ctx->rear){
		printf("%d\n" , *(ctx->array + iter));
		++iter;
	}
	printf(
	"====================\n");
	return;
}

int main(){

	int buf = 0,
	    opt = 0;
	queue_t *ctx = queue_new(20);
	while(opt!=5){
		printf(
		"::QUEUE OPERATIONS::\n");
		printf(
		"1. Enqueue element to Queue.\n"
		"2. Dequeue element from Queue.\n"
		"3. Make the queue empty.\n"
		"4. Print Queue. \n"
		"5. Exit. \n"	
		);

		printf("Please enter your options: ");
		scanf("%d" , &opt);

		switch(opt){
			case 1:
				printf("\n\nEnter the element to enqueue: ");
				scanf("%d" , &buf);
				if(queue_enqueue(ctx, buf)){
					opt = 5;
					break;
				}
				printf("Successfully enqueued element to queue.\n\n");
				break;
			case 2:
				
				if(queue_dequeue(ctx, &buf)){
					opt = 5;
					break;
				}
				printf("\n\nSuccessfully dequeued element(%d) from Queue.\n\n" , buf);
				break;
			case 3:
				queue_make_null(ctx);
				break;
			case 4:
				printf("\n\n");
				queue_print(ctx);
				printf("\n\n");	
				break;
			default:
				opt = 5;
				break;
		}
	}
	queue_delete(ctx);
	return 0;
}
