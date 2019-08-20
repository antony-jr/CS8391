#include <stdlib.h>
#include <stdio.h>

typedef struct _queue_record_t {
	int data;
	struct _queue_record_t *prev;
	struct _queue_record_t *next;
} queue_record_t;

typedef struct {
	queue_record_t *head,
		       *tail;
} queue_t;

queue_t *queue_new(){
	queue_t *r = calloc(1 , sizeof *r);
	if(!r){
		return NULL;
	}
	return r;
}

void queue_delete(queue_t *ctx){
	if(!ctx){
		return;
	}
	
	queue_record_t *p = ctx->head;
	queue_record_t *to_free = NULL;
	while(p){
		to_free = p;
		p = p->next;
		free(to_free);
	}
	free(ctx);
}


int queue_is_empty(queue_t *ctx){
	return !ctx->head;
}

int queue_make_empty(queue_t *ctx){
	queue_record_t *to_free = NULL;
	queue_record_t *p = ctx->head;
	while(p){
		to_free = p;
		p = p->next;
		free(to_free);
	}
	ctx->head = NULL;
	ctx->tail = NULL;
	return 0;
}

int queue_enqueue(queue_t *ctx, int el){
	queue_record_t *p = NULL;
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
		printf("fatal error: queue full!\n");
		return -1; /* no memory */
	}
	p->data = el;
	return 0;
}

int queue_dequeue(queue_t *ctx, int *el){
	queue_record_t *p = NULL;
	if(queue_is_empty(ctx)){
		printf("fatal error: queue empty!\n");
		return -1;
	}

	p = ctx->head;
	if(ctx->head == ctx->tail){
		ctx->head = ctx->tail = NULL;
	}else{
		ctx->head = ctx->head->next;
		ctx->head->prev = NULL;
	}
	*el = p->data;
	free(p);
	return 0;
}

static void queue_print(queue_t *ctx){
	queue_record_t **p = NULL;
	if(!ctx){
		return;
	}
	p = &ctx->head;
	printf(
	"+-------------------+\n"
	"|       QUEUE       |\n"
	"+===================+\n"
	);
	while(*p){
		printf("%d\n" , (*p)->data);
		p = &((*p)->next);
	}
	printf(
	"====================\n");
	return;
}

int main(){
	int opt = 0,
	    buf = 0;
	queue_t *ctx = queue_new();	
	while(opt!=5){
		printf(
		"::QUEUE OPERATIONS::\n");
		printf(
		"1. Enqueue element to queue.\n"
		"2. Dequeue element from queue.\n"
		"3. Print queue. \n"
		"4. Make the queue empty.\n"
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
				printf("\n\nSuccessfully dequeued element(%d) from queue.\n\n" , buf);
				break;
			case 3:
				printf("\n\n");
				queue_print(ctx);
				printf("\n\n");	
				break;
			case 4:
				if(queue_make_empty(ctx)){
					printf("Failed to make the queue empty.\n\n");
				}
				break;
			default:
				opt = 5;
				break;
		}
	}
	queue_delete(ctx);
	return 0;
}
